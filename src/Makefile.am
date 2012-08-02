## Process this file with automake to produce Makefile.in

## Created by Anjuta


uidir = $(pkgdatadir)/ui
ui_DATA = roadmap.ui


AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(ROADMAP_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = roadmap

roadmap_SOURCES = \
	main.c \
	roadmap.h \
	roadmap.c \
	roadmap-tickets-store.c \
	roadmap-tickets-store.h \
	roadmap-engine.c \
	roadmap-engine.h \
	roadmap-ticket.c \
	roadmap-ticket.h	

roadmap_LDFLAGS = \
	-Wl,--export-dynamic

roadmap_LDADD = $(ROADMAP_LIBS)


EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(pkgdatadir)

