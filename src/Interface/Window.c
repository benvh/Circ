#include "Window.h"
#include <stdlib.h>

struct OBJ_WINDOW
{
	GtkWidget* _scrolledwindow;
	GtkWidget* _webview;
	int _id;
};



Window* Window_new(int id)
{
	Window* w = (Window*)malloc(sizeof(Window));
	
	w->_id = id;
	w->_webview = GTK_WIDGET( webkit_web_view_new() );

	GtkAdjustment *vadjustment, *hadjustment;
	vadjustment = GTK_ADJUSTMENT( gtk_adjustment_new(0, 0, 0, 0, 0, 0) );
	hadjustment = GTK_ADJUSTMENT( gtk_adjustment_new(0, 0, 0, 0, 0, 0) );
	
	
	w->_scrolledwindow = GTK_WIDGET( gtk_scrolled_window_new(vadjustment, hadjustment) );
	
	gtk_container_add(GTK_CONTAINER(w->_scrolledwindow), w->_webview);
	
	return w;
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
