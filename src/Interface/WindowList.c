#include "WindowList.h"
#include <stdlib.h>

extern void on_tab_closed(GtkWidget* widget, gpointer data);

struct OBJ_WINDOWLIST
{
	GtkWidget* _notebook;
	Window** _windows;
	int _size;	//Allocated size
	int _count;	//Actual window count
	Window* _selected_window;
};

WindowList* WindowList_new(GtkWidget* notebook)
{
	WindowList* wlist = (WindowList*)malloc(sizeof(WindowList));
	wlist->_notebook = notebook;
	wlist->_count = 0;
	
	return wlist;
}

void WindowList_add_window(WindowList* windowlist)
{
	Window* w = Window_new(10);
		
	GtkWidget *icon, *button, *hbox = gtk_hbox_new(FALSE, 2);
	icon = GTK_WIDGET( gtk_image_new_from_stock (GTK_STOCK_CLOSE, GTK_ICON_SIZE_MENU) );
	button = gtk_button_new();
	
	gtk_widget_set_name(button, "my-close-button");
	
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(on_tab_closed), w);
	
	gtk_button_set_relief(GTK_BUTTON( button ), GTK_RELIEF_NONE);
	gtk_button_set_focus_on_click(GTK_BUTTON( button ), FALSE);
	
	gtk_container_add(GTK_CONTAINER(button), icon);
	
	gtk_box_pack_start(GTK_BOX( hbox ), gtk_label_new("tmp"), TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX( hbox ), button, FALSE, FALSE, 0);
	
	gtk_widget_show_all(hbox);
	
	gtk_notebook_append_page(GTK_NOTEBOOK( windowlist->_notebook ), Window_get_scrolledwindow(w), hbox);
}
