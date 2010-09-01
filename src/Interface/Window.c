#include "Window.h"
#include <stdlib.h>

extern Style* style;
extern void on_webview_load_finished(GtkWidget* widget, gpointer data);

struct OBJ_WINDOW
{
	GtkWidget* _scrolledwindow;
	GtkWidget* _webview;
	
	int _id;
	const gchar* _name;
	MessageBuffer* _buffer;
};



Window* Window_new(int id, const gchar* name)
{
	Window* w = (Window*)malloc(sizeof(Window));
	
	w->_id = id;
	w->_name = name;
	w->_webview = GTK_WIDGET( webkit_web_view_new() );
	w->_buffer = MessageBuffer_new(10);

	GtkAdjustment *vadjustment, *hadjustment;
	vadjustment = GTK_ADJUSTMENT( gtk_adjustment_new(0, 0, 0, 0, 0, 0) );
	hadjustment = GTK_ADJUSTMENT( gtk_adjustment_new(0, 0, 0, 0, 0, 0) );	
	w->_scrolledwindow = GTK_WIDGET( gtk_scrolled_window_new(vadjustment, hadjustment) );
	
	gtk_container_add(GTK_CONTAINER(w->_scrolledwindow), w->_webview);
	
	g_signal_connect(G_OBJECT(w->_webview), "load-finished", G_CALLBACK(on_webview_load_finished), NULL);
	webkit_web_view_load_uri(WEBKIT_WEB_VIEW(w->_webview), "file://data/styles/default.html");
	
	gtk_widget_show_all(w->_scrolledwindow);
	
	return w;
}

void Window_destroy(Window* window)
{
	/* 
	 * The webview and scrolledwindow have already been destroy due to the tab closing. 
	 * So we don't have to destroy them anymore!
	 */
	 
	printf("%s\n", window->_name);
	MessageBuffer_destroy(window->_buffer);
	free(window);
}

GtkWidget* Window_get_webview(Window* window)
{
	return window->_webview;
}

GtkWidget* Window_get_scrolledwindow(Window* window)
{
	return window->_scrolledwindow;
}

int Window_get_id(Window* window)
{
	return window->_id;
}

const gchar* Window_get_name(Window* window)
{
	return window->_name;
}

void Window_add_message(Window* window, const gchar* text)
{
	printf("%s\n", Style_get_name(style));
	Message* msg = Message_new("Ben", text, MessageBuffer_get_next_id(window->_buffer));
	Message_parse(msg, style);
	MessageBuffer_add_message(window->_buffer, msg);
	
	gchar *script_add = g_strdup_printf("append_message(\"%s\")", Message_get_parsed_text(msg));
	webkit_web_view_execute_script(WEBKIT_WEB_VIEW(window->_webview), script_add);
	g_free(script_add);
	
	int id;
	if((id = MessageBuffer_message_deleted(window->_buffer)) != MESSAGEBUFFER_NO)
	{
		gchar *script_del = g_strdup_printf("delete_message(\"msg%d\")", id);
		webkit_web_view_execute_script(WEBKIT_WEB_VIEW(window->_webview), script_del);
		g_free(script_del);
	}
}
