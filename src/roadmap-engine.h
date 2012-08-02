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

#ifndef _ROADMAP_ENGINE_H_
#define _ROADMAP_ENGINE_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define ROADMAP_TYPE_ENGINE             (roadmap_engine_get_type ())
#define ROADMAP_ENGINE(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), ROADMAP_TYPE_ENGINE, RoadmapEngine))
#define ROADMAP_ENGINE_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), ROADMAP_TYPE_ENGINE, RoadmapEngineClass))
#define ROADMAP_IS_ENGINE(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ROADMAP_TYPE_ENGINE))
#define ROADMAP_IS_ENGINE_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), ROADMAP_TYPE_ENGINE))
#define ROADMAP_ENGINE_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), ROADMAP_TYPE_ENGINE, RoadmapEngineClass))

typedef struct _RoadmapEngineClass RoadmapEngineClass;
typedef struct _RoadmapEngine RoadmapEngine;
typedef struct _RoadmapEnginePrivate RoadmapEnginePrivate;

struct _RoadmapEngineClass
{
	GObjectClass parent_class;
};

struct _RoadmapEngine
{
	GObject parent_instance;
	RoadmapEnginePrivate *priv;
};

GType roadmap_engine_get_type (void) G_GNUC_CONST;
GList *roadmap_engine_get_tickets (RoadmapEngine *self, gchar *username);
RoadmapEngine *roadmap_engine_new ();

G_END_DECLS

#endif /* _ROADMAP_ENGINE_H_ */
