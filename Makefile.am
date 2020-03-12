include $(top_srcdir)/build/modmake.rulesam
MODNAME=mod_parser

mod_LTLIBRARIES = mod_parser.la
mod_parser_la_SOURCES  = mod_parser.c utils.c
mod_parser_la_CFLAGS   = $(AM_CFLAGS)
mod_parser_la_LIBADD   = $(switch_builddir)/libfreeswitch.la
mod_parser_la_LDFLAGS  = -avoid-version -module -no-undefined -shared
