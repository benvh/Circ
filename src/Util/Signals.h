#ifndef __SIGNALS_H__
#define __SIGNALS_H__

#include <gtk/gtk.h>
#include <webkit/webkit.h>

#include "../Util/Util.h"
#include "../Interface/WindowList.h"
#include "../Message/MessageBuffer.h"
#include "../Style/Style.h"

void connect_signals(void);

void on_window_delete_event(GtkWidget* widget, gpointer data);
void on_entry_activate(GtkWidget* widget, gpointer data);
void on_webview_load_finished(GtkWidget* widget, gpointer data);

void on_tab_closed(GtkWidget* widget, gpointer data);
void on_switch_page(GtkWidget* notebook, GtkWidget* page, guint page_num, gpointer data);

#endif /* __SIGNALS_H__ */

