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

#include "roadmap-tickets-store.h"
#include "roadmap-engine.h"

enum
{
	PROP_0,

	PROP_ENGINE
};



G_DEFINE_TYPE (RoadmapTicketsStore, roadmap_tickets_store, GTK_TYPE_LIST_STORE);

static void
roadmap_tickets_store_init (RoadmapTicketsStore *roadmap_tickets_store)
{


	/* TODO: Add initialization code here */
}

static void
roadmap_tickets_store_finalize (GObject *object)
{
	/* TODO: Add deinitalization code here */

	G_OBJECT_CLASS (roadmap_tickets_store_parent_class)->finalize (object);
}

static void
roadmap_tickets_store_set_property (GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
	g_return_if_fail (ROADMAP_IS_TICKETS_STORE (object));

	switch (prop_id)
	{
	case PROP_ENGINE:
		/* TODO: Add setter for "engine" property here */
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
roadmap_tickets_store_get_property (GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
	g_return_if_fail (ROADMAP_IS_TICKETS_STORE (object));

	switch (prop_id)
	{
	case PROP_ENGINE:
		/* TODO: Add getter for "engine" property here */
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
roadmap_tickets_store_class_init (RoadmapTicketsStoreClass *klass)
{
	GObjectClass* object_class = G_OBJECT_CLASS (klass);
	GtkListStoreClass* parent_class = GTK_LIST_STORE_CLASS (klass);

	object_class->finalize = roadmap_tickets_store_finalize;
	object_class->set_property = roadmap_tickets_store_set_property;
	object_class->get_property = roadmap_tickets_store_get_property;

	g_object_class_install_property (object_class,
	                                 PROP_ENGINE,
	                                 g_param_spec_object ("engine",
	                                                      "engine",
	                                                      "The backend engine",
	                                                      ROADMAP_TYPE_ENGINE,
	                                                      G_PARAM_READABLE | G_PARAM_WRITABLE));
}

