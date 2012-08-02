/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * roadmap.c
 * Copyright (C) 2012 Álvaro Peña <alvaropg@gmail.com>
 * 
 * Roadmap is free software: you can redistribute it and/or modify it
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
#include <glib/gi18n.h>

#include "roadmap.h"
#include "roadmap-engine.h"
#include "roadmap-ticket.h"

/* For testing propose use the local (not installed) ui file */
/* #define UI_FILE PACKAGE_DATA_DIR"/ui/roadmap.ui" */
#define UI_FILE "src/roadmap.ui"
#define TOP_WINDOW "main_window"


G_DEFINE_TYPE (Roadmap, roadmap, GTK_TYPE_APPLICATION);


/* Define the private structure in the .c file */
#define ROADMAP_GET_PRIVATE(obj) (G_TYPE_INSTANCE_GET_PRIVATE((obj), ROADMAP_TYPE_APPLICATION, RoadmapPrivate))

struct _RoadmapPrivate
{
	GtkWidget *main_window;
	RoadmapEngine *engine;
};


/* GApplication implementation */
static void
roadmap_activate (GApplication *self)
{
	GtkBuilder *builder;
	GError* error = NULL;
	RoadmapPrivate *priv = ROADMAP_GET_PRIVATE(self);
	GList *tickets;
	RoadmapTicket *ticket;

	/* Load UI from file */
	builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, UI_FILE, &error)) {
		g_critical ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}

	/* Auto-connect signal handlers */
	gtk_builder_connect_signals (builder, self);

	/* Get the window object from the ui file */
	priv->main_window = GTK_WIDGET (gtk_builder_get_object (builder, TOP_WINDOW));
    if (!priv->main_window) {
		g_critical ("Widget \"%s\" is missing in file %s.",
		            TOP_WINDOW,
		            UI_FILE);
	}

	g_object_unref (builder);
	
	gtk_window_set_application (GTK_WINDOW (priv->main_window), GTK_APPLICATION (self));

	gtk_widget_show_all (GTK_WIDGET (priv->main_window));

	tickets = roadmap_engine_get_tickets (priv->engine, "alvaro.pena");
	while (tickets) {
		ticket = ROADMAP_TICKET (tickets->data);
		if (ROADMAP_IS_TICKET (ticket)) {
			gchar *summary;

			summary = roadmap_ticket_get_string_attribute (ticket, "summary");
			g_print ("%s\n", summary);
		}

		tickets = g_list_next (tickets);
	}
}

static void
roadmap_init (Roadmap *self)
{
	RoadmapPrivate *priv;

	priv = ROADMAP_GET_PRIVATE(self);

	priv->engine = roadmap_engine_new ();
}

static void
roadmap_finalize (GObject *object)
{

	G_OBJECT_CLASS (roadmap_parent_class)->finalize (object);
}

static void
roadmap_class_init (RoadmapClass *klass)
{
	G_APPLICATION_CLASS (klass)->activate = roadmap_activate;

	g_type_class_add_private (klass, sizeof (RoadmapPrivate));

	G_OBJECT_CLASS (klass)->finalize = roadmap_finalize;
}

Roadmap *
roadmap_new (void)
{
	g_type_init ();

	return g_object_new (roadmap_get_type (),
	                     "application-id", "org.gnome.roadmap",
	                     "flags", G_APPLICATION_HANDLES_OPEN,
	                     NULL);
}
