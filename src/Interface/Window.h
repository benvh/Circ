#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <gtk/gtk.h>
#include <webkit/webkit.h>

typedef struct OBJ_WINDOW Window;

Window*			Window_new(void);
GtkWidget*		Window_get_webview(Window* window);
GtkWidget*		Window_get_scrolledwindow(Window* window);

#endif /* __WINDOW_H__ */

