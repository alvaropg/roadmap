/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * roadmap.h
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

#ifndef _ROADMAP_
#define _ROADMAP_

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define ROADMAP_TYPE_APPLICATION             (roadmap_get_type ())
#define ROADMAP_APPLICATION(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), ROADMAP_TYPE_APPLICATION, Roadmap))
#define ROADMAP_APPLICATION_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), ROADMAP_TYPE_APPLICATION, RoadmapClass))
#define ROADMAP_IS_APPLICATION(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ROADMAP_TYPE_APPLICATION))
#define ROADMAP_IS_APPLICATION_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), ROADMAP_TYPE_APPLICATION))
#define ROADMAP_APPLICATION_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), ROADMAP_TYPE_APPLICATION, RoadmapClass))

typedef struct _RoadmapClass RoadmapClass;
typedef struct _Roadmap Roadmap;
typedef struct _RoadmapPrivate RoadmapPrivate;

struct _RoadmapClass
{
	GtkApplicationClass parent_class;
};

struct _Roadmap
{
	GtkApplication parent_instance;

	RoadmapPrivate *priv;

};

GType roadmap_get_type (void) G_GNUC_CONST;
Roadmap *roadmap_new (void);

/* Callbacks */

G_END_DECLS

#endif /* _APPLICATION_H_ */
