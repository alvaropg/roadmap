/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Roadmap
 * Copyright (C) Álvaro Peña 2012 <alvaropg@gmail.com>
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

#include "roadmap-ticket.h"

enum
{
	PROP_0,

	PROP_ID,
	PROP_ATTRIBUTES
};

struct _RoadmapTicketPrivate {
	guint id;
	GHashTable *attributes;
};

G_DEFINE_TYPE (RoadmapTicket, roadmap_ticket, G_TYPE_OBJECT);
#define ROADMAP_TICKET_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE ((obj), ROADMAP_TYPE_TICKET, RoadmapTicketPrivate))

static void
roadmap_ticket_init (RoadmapTicket *roadmap_ticket)
{
}

static void
roadmap_ticket_finalize (GObject *object)
{
	G_OBJECT_CLASS (roadmap_ticket_parent_class)->finalize (object);
}

static void
roadmap_ticket_set_property (GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
	RoadmapTicketPrivate *priv;
	g_return_if_fail (ROADMAP_IS_TICKET (object));

	priv = ROADMAP_TICKET_GET_PRIVATE (ROADMAP_TICKET (object));

	switch (prop_id) {
	case PROP_ID:
		priv->id = g_value_get_uint (value);
		break;
	case PROP_ATTRIBUTES:
		priv->attributes = (GHashTable *) g_value_get_boxed (value);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
roadmap_ticket_get_property (GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
	RoadmapTicketPrivate *priv;
	g_return_if_fail (ROADMAP_IS_TICKET (object));

	priv = ROADMAP_TICKET_GET_PRIVATE (ROADMAP_TICKET (object));

	switch (prop_id) {
	case PROP_ID:
		g_value_set_uint (value, priv->id);
		break;
	case PROP_ATTRIBUTES:
		g_value_set_boxed (value, priv->attributes);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
roadmap_ticket_class_init (RoadmapTicketClass *klass)
{
	GObjectClass* object_class = G_OBJECT_CLASS (klass);
	GObjectClass* parent_class = G_OBJECT_CLASS (klass);

	g_type_class_add_private (klass, sizeof (RoadmapTicketPrivate));

	object_class->finalize = roadmap_ticket_finalize;
	object_class->set_property = roadmap_ticket_set_property;
	object_class->get_property = roadmap_ticket_get_property;

	g_object_class_install_property (object_class,
	                                 PROP_ID,
	                                 g_param_spec_uint ("id",
														"Identifier", "Ticket identifier",
														0, 10000, 0,
														G_PARAM_READABLE | G_PARAM_WRITABLE));

	g_object_class_install_property (object_class,
	                                 PROP_ATTRIBUTES,
	                                 g_param_spec_boxed ("attributes",
														 "Attributes", "Ticket attributes",
														 G_TYPE_HASH_TABLE,
														 G_PARAM_READABLE | G_PARAM_WRITABLE));
}

guint
roadmap_ticket_get_id (RoadmapTicket *self)
{
	g_return_val_if_fail (ROADMAP_IS_TICKET (self), 0);

	return self->priv->id;
}

gchar*
roadmap_ticket_get_string_attribute (RoadmapTicket *self, const gchar* attr_name)
{
	RoadmapTicketPrivate *priv;
	GValue *data;
	gchar *string;

	g_return_val_if_fail (ROADMAP_IS_TICKET (self), NULL);

	string = NULL;
	priv = ROADMAP_TICKET_GET_PRIVATE (self);

	if (g_hash_table_contains (priv->attributes, attr_name)) {
		data = g_hash_table_lookup (priv->attributes, attr_name);
		if (G_VALUE_HOLDS_STRING (data)) {
			string = g_value_get_string (data);
		} else {
			g_warning ("The attribute: %s isn't a string", attr_name);
		}
	} else {
		g_warning ("Can't find attribute: %s", attr_name);
	}

	return string;
}
