#include <string.h>
#include "Signals.h"

extern GtkWidget *window;
extern GtkWidget *entry;
extern MessageBuffer* buffer;
extern WindowList* windowlist;
extern Style* style;

void connect_signals(void)
{
	g_signal_connect(G_OBJECT( window ), "delete-event", G_CALLBACK(on_window_delete_event), NULL);
	g_signal_connect(G_OBJECT( entry ), "activate", G_CALLBACK(on_entry_activate), NULL);
}

void on_window_delete_event(GtkWidget* widget, gpointer data)
{
	gtk_main_quit();
}

void on_entry_activate(GtkWidget* widget, gpointer data)
{
	if(strcmp(gtk_entry_get_text(GTK_ENTRY(widget)), "") != 0)
	{
		Window* w = WindowList_get_selected_window(windowlist);		
		Window_add_message(w, gtk_entry_get_text(GTK_ENTRY(widget)));
		gtk_entry_set_text(GTK_ENTRY(entry), "");
	}
}

void on_webview_load_finished(GtkWidget* widget, gpointer data)
{

	/* (re)load style stylesheet */
	gchar* path = g_strdup_printf("%s.style/style.css", Style_get_name(style));
	gchar* script = g_strdup_printf("set_stylesheet('%s')", path);
	webkit_web_view_execute_script(WEBKIT_WEB_VIEW( widget ), script);
	
	g_free(path);
	g_free(script);
	/* ------------------------ */
}

void on_tab_closed(GtkWidget* widget, gpointer data)
{
	Window* w = (Window*)data;
	WindowList_remove_window(windowlist, Window_get_id(w));
}

void on_switch_page(GtkWidget* notebook, GtkWidget* page, guint page_num, gpointer data)
{
	WindowList* wlist = (WindowList*)data;
	WindowList_set_selected_window(wlist, WindowList_get_window(wlist, page_num));
}
