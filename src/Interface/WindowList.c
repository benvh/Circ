#include "WindowList.h"
#include <stdlib.h>

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
	Window* w = Window_new();
	
	GtkWidget *button, *hbox = gtk_hbox_new(FALSE, 3);
	button = gtk_button_new();
	gtk_container_add(GTK_CONTAINER(button), gtk_image_new_from_stock (GTK_STOCK_CLOSE, GTK_ICON_SIZE_SMALL_TOOLBAR));
	
	gtk_box_pack_start(GTK_BOX( hbox ), gtk_label_new("tmp"), TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX( hbox ), button, TRUE, TRUE, 0);
	
	gtk_widget_show_all(hbox);
	
	gtk_notebook_append_page(GTK_NOTEBOOK( windowlist->_notebook ), Window_get_scrolledwindow(w), hbox);
}
