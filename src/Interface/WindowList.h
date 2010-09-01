#ifndef __WINDOWLIST_H__
#define __WINDOWLIST_H__

#include "Window.h"
#include <gtk/gtk.h>

typedef struct OBJ_WINDOWLIST WindowList;


WindowList*			WindowList_new(GtkWidget* notebook);
void				WindowList_destroy(WindowList* windowlist);
void				WindowList_remove_window(WindowList* windowlist, int id);

void 				WindowList_add_window(WindowList* windowlist, const gchar* name);
Window*				WindowList_get_window(WindowList* windowlist, int id);
Window*				WindowList_get_selected_window(WindowList*);
void				WindowList_set_selected_window(WindowList* windowlist, Window* window);


#endif /* __WINDOWLIST_H__ */

