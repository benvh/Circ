#ifndef __STYLE_H__
#define __STYLE_H__

typedef struct OBJ_STYLE Style;

#include "../Message/Message.h"

Style*			Style_new(const char* name);
void			Style_destroy(Style* style);

const char*		Style_get_message_template(Style* style);

#endif /* __STYLE_H__ */

