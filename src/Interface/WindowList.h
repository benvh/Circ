#ifndef __WINDOWLIST_H__
#define __WINDOWLIST_H__

#include "Window.h"
#include <gtk/gtk.h>

typedef struct OBJ_WINDOWLIST WindowList;


WindowList*			WindowList_new(GtkWidget* notebook);

#endif /* __WINDOWLIST_H__ */

