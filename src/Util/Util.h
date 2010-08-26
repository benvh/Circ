#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <time.h>

const char* strreplace(const char* string, const char* match, const char* replace);
GString* strreplace2(GString* string, const char* match, const char* replace);
const char* get_time_12(void);
const char* get_time_24(void);

#endif /* __UTIL_H__ */

