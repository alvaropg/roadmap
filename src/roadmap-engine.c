/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Roadmap
 * Copyright (C) Álvaro Peña 2012 <alvaropg@oriwork>
 * 
Roadmap is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Roadmap is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libsoup/soup.h>
#include <gtk/gtk.h>
#include <string.h>

#include "roadmap-engine.h"
#include "roadmap-ticket.h"

enum
{
	PROP_0,

	PROP_APP
};

G_DEFINE_TYPE (RoadmapEngine, roadmap_engine, G_TYPE_OBJECT);
#define ROADMAP_ENGINE_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), ROADMAP_TYPE_ENGINE, RoadmapEnginePrivate))

struct _RoadmapEnginePrivate {
	SoupSession *session;
};

void engine_authenticate_cb (SoupSession *session, SoupMessage *msg, SoupAuth *auth, gboolean retrying, gpointer user_data);

static void
roadmap_engine_init (RoadmapEngine *self)
{
	RoadmapEnginePrivate *priv;

	priv = ROADMAP_ENGINE_GET_PRIVATE(self);

	/* TODO: Move the NTLM use to a configurable option in the preferences dialog */
	priv->session = soup_session_async_new_with_options (SOUP_SESSION_USE_NTLM, TRUE, NULL);
	g_signal_connect (priv->session, "authenticate", G_CALLBACK (engine_authenticate_cb), self);
}

static void
roadmap_engine_finalize (GObject *object)
{
	/* TODO: Add deinitalization code here */

	G_OBJECT_CLASS (roadmap_engine_parent_class)->finalize (object);
}

static void
roadmap_engine_set_property (GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
	g_return_if_fail (ROADMAP_IS_ENGINE (object));

	switch (prop_id)
	{
	case PROP_APP:
		/* TODO: Add setter for "app" property here */
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
roadmap_engine_get_property (GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
	g_return_if_fail (ROADMAP_IS_ENGINE (object));

	switch (prop_id)
	{
	case PROP_APP:
		/* TODO: Add getter for "app" property here */
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
roadmap_engine_class_init (RoadmapEngineClass *klass)
{
	GObjectClass* object_class = G_OBJECT_CLASS (klass);
	GObjectClass* parent_class = G_OBJECT_CLASS (klass);

	g_type_class_add_private (klass, sizeof (RoadmapEnginePrivate));

	object_class->finalize = roadmap_engine_finalize;
	object_class->set_property = roadmap_engine_set_property;
	object_class->get_property = roadmap_engine_get_property;

	g_object_class_install_property (object_class,
	                                 PROP_APP,
	                                 g_param_spec_object ("app",
	                                                      "app",
	                                                      "Roadmap application",
	                                                      GTK_TYPE_APPLICATION,
	                                                      G_PARAM_READABLE | G_PARAM_WRITABLE));
}

void
engine_authenticate_cb (SoupSession *session, SoupMessage *msg, SoupAuth *auth, gboolean retrying, gpointer user_data)
{
	if (retrying) {
		g_print ("Fallo el login");
		return;
	}

	soup_auth_authenticate (auth, "alvaro.pena", "1ae89zs2");
}

static gboolean
check_xmlrpc (GValue *value, GType type, ...)
{
	va_list args;

	if (!G_VALUE_HOLDS (value, type)) {
		g_print ("ERROR: could not parse response\n");
		g_value_unset (value);
		return FALSE;
	}

	va_start (args, type);
	SOUP_VALUE_GETV (value, type, args);
	va_end (args);
	return TRUE;
}

static gboolean
do_xmlrpc (SoupSession *session, const char *method, GValue *retval, ...)
{
	SoupMessage *msg;
	va_list args;
	GValueArray *params;
	GError *err = NULL;
	char *body;
	int i;

	va_start (args, retval);
	params = soup_value_array_from_args (args);
	va_end (args);

	/*
	for (i = 0; i < params->n_values; i++) {
		g_print ("param: %s\n", g_value_get_string (g_value_array_get_nth (params, i)));
	}
	*/
	
	body = soup_xmlrpc_build_method_call (method, params->values,
										  params->n_values);
	g_value_array_free (params);
	if (!body)
		return FALSE;

	msg = soup_message_new ("POST", "http://dev.map.es/trac/acceda/login/xmlrpc");
	soup_message_set_request (msg, "text/xml", SOUP_MEMORY_TAKE, body, strlen (body));
	soup_session_send_message (session, msg);

	if (!SOUP_STATUS_IS_SUCCESSFUL (msg->status_code)) {
		g_print ("ERROR: %d %s\n", msg->status_code,
			      msg->reason_phrase);
		g_object_unref (msg);
		return FALSE;
	}

	if (!soup_xmlrpc_parse_method_response (msg->response_body->data,
						msg->response_body->length,
						retval, &err)) {
		if (err) {
			g_print ("%s", body);
			g_print ("FAULT: %d %s\n", err->code, err->message);
			g_error_free (err);
		} else
			g_print ("ERROR: could not parse response\n");
		g_object_unref (msg);
		return FALSE;
	}
	g_object_unref (msg);

	return TRUE;
}

GList*
roadmap_engine_get_tickets (RoadmapEngine *self, gchar *username)
{
	GValue retval;
	GValueArray *tickets;
	int i, j;
	gboolean ok;
	GList *r_tickets;
	RoadmapEnginePrivate *priv;

	priv = ROADMAP_ENGINE_GET_PRIVATE(self);
	r_tickets = NULL;

	ok = (do_xmlrpc (priv->session,
					 "ticket.query", &retval,
					 G_TYPE_STRING, g_strdup_printf ("owner=%s", username),
					 G_TYPE_INVALID) &&
		  check_xmlrpc (&retval, G_TYPE_VALUE_ARRAY, &tickets));

	if (!ok) {
		g_print ("No se han podido obtener los tickets");
		return NULL;
	}
	
	for (i = 0; i < tickets->n_values; i++) {
		GValueArray *ticket_info;
		gint t_id;
		GHashTable *attributes;
		GList *keys;
		RoadmapTicket *rd_ticket;
		gchar *test;

		t_id = g_value_get_int (g_value_array_get_nth (tickets, i));
		ok = (do_xmlrpc (priv->session,
						 "ticket.get", &retval,
						 G_TYPE_STRING, g_strdup_printf ("%d", t_id),
						 G_TYPE_INVALID) &&
			  check_xmlrpc (&retval, G_TYPE_VALUE_ARRAY, &ticket_info));

		if (!ok) {
			g_print ("No se ha encontrado información del ticket: %d", t_id);
			return NULL;
		}

		// String?, SoupDate*, SoupDate*, GHashTable*
		// g_print ("ID: %d (%d)\n", t_id, ticket_info->n_values);

		// The 3 element it's the hash table with the ticket description
		attributes = (GHashTable *) g_value_get_boxed (g_value_array_get_nth (ticket_info, 3));
		/*
		keys = g_hash_table_get_keys (attributes);
		while (keys) {
			g_print (" Attr: %s\n", ((gchar*) keys->data));

			keys = g_list_next (keys);
		}

		g_list_free (keys);
		*/

		/*
		for (j = 0; j < ticket_info->n_values; j++) {
			GValue *ti;

			ti = g_value_array_get_nth (ticket_info, j);
			g_print ("%s\n", g_strdup_value_contents (ti));
		}
		*/
		rd_ticket = g_object_new (ROADMAP_TYPE_TICKET,
								  "id", t_id,
								  "attributes", attributes,
								  NULL);
		r_tickets = g_list_append (r_tickets, rd_ticket);
	}

	return r_tickets;
}

RoadmapEngine*
roadmap_engine_new ()
{
	return g_object_new (roadmap_engine_get_type (),
						 NULL);
}
