/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
 * Copyright (C) Álvaro Peña 2012 <alvaropg@gmail.com>
 * 
 */

#include <config.h>
#include <gtk/gtk.h>
#include "roadmap.h"


#include <glib/gi18n.h>


int
main (int argc, char *argv[])
{
	Roadmap *app;
	int status;


#ifdef ENABLE_NLS
	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif

	
  app = roadmap_new ();
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
