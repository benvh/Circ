#include <string.h>
#include "Signals.h"

extern GtkWidget *window;
extern GtkWidget *entry;
extern GtkWidget *webview;
extern GtkWidget *scrolledwindow;
extern MessageBuffer* buffer;
extern Style* style;

void connect_signals(void)
{
	g_signal_connect(G_OBJECT( window ), "delete-event", G_CALLBACK(on_window_delete_event), NULL);
	g_signal_connect(G_OBJECT( entry ), "activate", G_CALLBACK(on_entry_activate), NULL);
	g_signal_connect(G_OBJECT( webview ), "load-finished", G_CALLBACK(on_webview_load_finished), NULL);
}

void on_window_delete_event(GtkWidget* widget, gpointer data)
{
	gtk_main_quit();
}

void on_entry_activate(GtkWidget* widget, gpointer data)
{
	if(strcmp(gtk_entry_get_text(GTK_ENTRY(widget)), "") != 0)
	{
		Message* msg = Message_new("Ben", gtk_entry_get_text(GTK_ENTRY(widget)), MessageBuffer_get_next_id(buffer));
		MessageBuffer_add_message(buffer, msg);
		
		Message_parse(msg, style);
		
		char *test = (char*)malloc( (strlen(Message_get_parsed_text(msg))+20)*sizeof(char));
		sprintf(test, "append_message('%s')", Message_get_parsed_text(msg));
		printf("%s\n", test);
		
		webkit_web_view_execute_script(WEBKIT_WEB_VIEW(webview), test);
		
		int id;
		if((id = MessageBuffer_message_deleted(buffer)) != MESSAGEBUFFER_NO)
		{
			char buff[30];
			sprintf(buff, "delete_message('msg%d')", id);
			webkit_web_view_execute_script(WEBKIT_WEB_VIEW(webview), buff);
		}
	
/*		char test[500];*/
/*		//sprintf(test, "append_message('<div id=\"msg%d\">&lt;%s&gt; %s</div>')", Message_get_id(msg), Message_get_from(msg), Message_get_text(msg));*/
/*		sprintf(test, "append_message('%s')" , strreplace("<div>%_message_%</div>", "%_message_%", Message_get_text(msg)));*/
/*	*/
/*		webkit_web_view_execute_script(WEBKIT_WEB_VIEW(webview), test);*/
/*	*/
/*		int id;*/
/*		if((id = MessageBuffer_message_deleted(buffer)) != MESSAGEBUFFER_NO)*/
/*		{*/
/*			char buff[100];*/
/*			sprintf(buff, "delete_message('msg%d')", id);*/
/*			webkit_web_view_execute_script(WEBKIT_WEB_VIEW(webview), buff);*/
/*		}*/
		
		gtk_entry_set_text(GTK_ENTRY(entry), "");
	}
}

void on_webview_load_finished(GtkWidget* widget, gpointer data)
{
	printf("lol\n");
}
