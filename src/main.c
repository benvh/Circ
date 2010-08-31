#include <stdio.h>
#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include <string.h>

#include "Util/Signals.h"
#include "Interface/WindowList.h"


GtkWidget *window, *entry, *tabview;
MessageBuffer* buffer;
WindowList* windowlist;
Style* style;

int 
main (int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	
	GtkBuilder* builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "data/Interface.ui", NULL);
	
	/* Style stuff to 'fix' tab close button size */
	gtk_rc_parse_string(
		"style \"my-button-style\"\n"
		"{\n"
		"	GtkWidget::focus-padding = 0\n"
		"	GtkWidget::focus-line-width = 0\n"
		"	xthickness = 0\n"
		"	ythickness = 0\n"
		"}\n"
		"widget \"*.my-close-button\" style \"my-button-style\""
	);

	window = GTK_WIDGET( gtk_builder_get_object(builder, "mainWindow") );
	entry = GTK_WIDGET( gtk_builder_get_object(builder, "entry1") );
	tabview = GTK_WIDGET( gtk_builder_get_object(builder, "tabs") );
	
	buffer = MessageBuffer_new(10);
	windowlist = WindowList_new(tabview);
	WindowList_add_window(windowlist);
	WindowList_add_window(windowlist);
	style = Style_new("Lol");
	
	gtk_widget_grab_focus(entry);

	connect_signals();
	gtk_widget_show_all(window);
	gtk_main();

	
	return 0;
}
