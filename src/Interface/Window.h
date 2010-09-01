#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include "../Message/MessageBuffer.h"
#include "../Style/Style.h"

typedef struct OBJ_WINDOW Window;

Window*			Window_new(int id, const gchar* name);
void			Window_destroy(Window* window);
void			Window_add_message(Window* window, const gchar* text);

GtkWidget*		Window_get_webview(Window* window);
GtkWidget*		Window_get_scrolledwindow(Window* window);
int				Window_get_id(Window* window);
const gchar*	Window_get_name(Window* window);

#endif /* __WINDOW_H__ */

