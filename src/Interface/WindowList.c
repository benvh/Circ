#include "WindowList.h"
#include <stdlib.h>

extern void on_tab_closed(GtkWidget* widget, gpointer data);
extern void on_switch_page(GtkWidget* notebook, GtkWidget* page, guint page_num, gpointer data);

struct OBJ_WINDOWLIST
{
	GtkWidget* _notebook;
	GArray* _windows;
	Window* _selected_window;
};

WindowList* WindowList_new(GtkWidget* notebook)
{
	WindowList* wlist = (WindowList*)malloc(sizeof(WindowList));
	g_signal_connect(G_OBJECT(notebook), "switch-page", G_CALLBACK(on_switch_page), wlist);
	wlist->_notebook = notebook;
	wlist->_windows = g_array_new(FALSE, FALSE, sizeof(Window*));
	
	return wlist;
}

void WindowList_add_window(WindowList* windowlist, const gchar* name)
{
	Window* w = Window_new(windowlist->_windows->len, name);
		
	GtkWidget *icon, *button, *hbox = gtk_hbox_new(FALSE, 2);
	icon = GTK_WIDGET( gtk_image_new_from_stock (GTK_STOCK_CLOSE, GTK_ICON_SIZE_MENU) );
	button = gtk_button_new();
	
	gtk_widget_set_name(button, "my-close-button");
	
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_tab_closed), w);
	
	gtk_button_set_relief(GTK_BUTTON( button ), GTK_RELIEF_NONE);
	gtk_button_set_focus_on_click(GTK_BUTTON( button ), FALSE);
	
	gtk_container_add(GTK_CONTAINER(button), icon);
	
	gtk_box_pack_start(GTK_BOX( hbox ), gtk_label_new(name), TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX( hbox ), button, FALSE, FALSE, 0);
	
	gtk_widget_show_all(hbox);
	
	g_array_append_val(windowlist->_windows, w);
	
	gtk_notebook_append_page(GTK_NOTEBOOK( windowlist->_notebook ), Window_get_scrolledwindow(w), hbox);
}

void WindowList_remove_window(WindowList* windowlist, int id)
{
	Window* w = g_array_index(windowlist->_windows, Window*, id);
	
	g_array_remove_index(windowlist->_windows, id);
	gtk_notebook_remove_page(GTK_NOTEBOOK(windowlist->_notebook), id);
		
	Window_destroy(w);
}

void WindowList_set_selected_window(WindowList *windowlist, Window* window)
{
	windowlist->_selected_window = window;
}

Window* WindowList_get_window(WindowList* windowlist, int id)
{
	if(windowlist->_windows->len == 0) return NULL;
	return g_array_index(windowlist->_windows, Window*, id);
}

Window* WindowList_get_selected_window(WindowList* windowlist)
{
	return windowlist->_selected_window;
}
