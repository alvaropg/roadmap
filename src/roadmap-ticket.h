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

#ifndef _ROADMAP_TICKET_H_
#define _ROADMAP_TICKET_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define ROADMAP_TYPE_TICKET             (roadmap_ticket_get_type ())
#define ROADMAP_TICKET(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), ROADMAP_TYPE_TICKET, RoadmapTicket))
#define ROADMAP_TICKET_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), ROADMAP_TYPE_TICKET, RoadmapTicketClass))
#define ROADMAP_IS_TICKET(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), ROADMAP_TYPE_TICKET))
#define ROADMAP_IS_TICKET_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), ROADMAP_TYPE_TICKET))
#define ROADMAP_TICKET_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), ROADMAP_TYPE_TICKET, RoadmapTicketClass))

typedef struct _RoadmapTicketClass RoadmapTicketClass;
typedef struct _RoadmapTicket RoadmapTicket;
typedef struct _RoadmapTicketPrivate RoadmapTicketPrivate;


struct _RoadmapTicketClass
{
	GObjectClass parent_class;
};

struct _RoadmapTicket
{
	GObject parent_instance;
	RoadmapTicketPrivate *priv;
};

GType roadmap_ticket_get_type (void) G_GNUC_CONST;
guint roadmap_ticket_get_id (RoadmapTicket *self);
gchar* roadmap_ticket_get_string_attribute (RoadmapTicket *self, const gchar* attr_name);

G_END_DECLS

#endif /* _ROADMAP_TICKET_H_ */
