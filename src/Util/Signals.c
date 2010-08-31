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
//	g_signal_connect(G_OBJECT( webview ), "load-finished", G_CALLBACK(on_webview_load_finished), NULL);
}

void on_window_delete_event(GtkWidget* widget, gpointer data)
{
	gtk_main_quit();
}

void on_entry_activate(GtkWidget* widget, gpointer data)
{
/*	if(strcmp(gtk_entry_get_text(GTK_ENTRY(widget)), "") != 0)*/
/*	{*/
/*		Message* msg = Message_new("Ben", gtk_entry_get_text(GTK_ENTRY(widget)), MessageBuffer_get_next_id(buffer));*/
/*		MessageBuffer_add_message(buffer, msg);*/
/*		*/
/*		Message_parse(msg, style);*/
/*		*/
/*		gchar *script_add = g_strdup_printf("append_message(\"%s\")", Message_get_parsed_text(msg));*/
/*		*/
/*		webkit_web_view_execute_script(WEBKIT_WEB_VIEW(webview), script_add);*/
/*		*/
/*		int id;*/
/*		if((id = MessageBuffer_message_deleted(buffer)) != MESSAGEBUFFER_NO)*/
/*		{*/
/*			gchar *script_del = g_strdup_printf("delete_message(\"msg%d\")", id);*/
/*			webkit_web_view_execute_script(WEBKIT_WEB_VIEW(webview), script_del);*/
/*			g_free(script_del);*/
/*		}*/
/*		*/
/*		gtk_entry_set_text(GTK_ENTRY(entry), "");*/
/*		*/
/*		g_free(script_add);*/
/*	}*/
}

void on_webview_load_finished(GtkWidget* widget, gpointer data)
{

	/* (re)load style stylesheet */
/*	gchar* path = g_strdup_printf("%s.style/style.css", Style_get_name(style));*/
/*	gchar* script = g_strdup_printf("set_stylesheet('%s')", path);*/
/*	webkit_web_view_execute_script(WEBKIT_WEB_VIEW( webview ), script);*/
/*	*/
/*	g_free(path);*/
/*	g_free(script);*/
	/* ------------------------ */
}

void on_tab_closed(GtkWidget* widget, gpointer data)
{
	Window* w = (Window*)data;
	
	printf("%d\n", Window_get_id(w));
}
