bin_PROGRAMS = circ

SUBDIRS = \
	Message \
	Style \
	Util


circ_CFLAGS = `pkg-config --cflags glib-2.0 gtk+-2.0 webkit-1.0`
circ_LDFLAGS = `pkg-config --libs glib-2.0 gtk+-2.0 webkit-1.0`

circ_LDADD = Message/libcircmessage.a Style/libcircstyle.a Util/libcircutil.a

circ_SOURCES = \
	main.c
	

