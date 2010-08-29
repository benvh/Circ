#include <stdio.h>
#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include <string.h>

#include "Util/Signals.h"


GtkWidget *window, *scrolledwindow, *entry, *webview;
MessageBuffer* buffer;
Style* style;

int 
main (int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	
	GtkBuilder* builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "data/Interface.ui", NULL);

	window = GTK_WIDGET( gtk_builder_get_object(builder, "mainWindow") );
	scrolledwindow = GTK_WIDGET( gtk_builder_get_object(builder, "scrolledwindow1") );
	entry = GTK_WIDGET( gtk_builder_get_object(builder, "entry1"));
	webview = GTK_WIDGET( webkit_web_view_new() );

	gtk_container_add(GTK_CONTAINER( scrolledwindow ), GTK_WIDGET( webview ));
	buffer = MessageBuffer_new(10);
	style = Style_new("Lol");

	connect_signals();

	webkit_web_view_load_uri(WEBKIT_WEB_VIEW(webview), "file://data/styles/default.html");

	gtk_widget_show_all(window);

	gtk_main();

	
	return 0;
}
