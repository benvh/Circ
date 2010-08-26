#ifndef __MESSAGE_H__
#define __MESSAGE_H__

typedef struct OBJ_MESSAGE Message;

#include "../Style/Style.h"

Message* Message_new(const char* from, const char* msg, int id);

const char*		Message_get_from(Message* msg);
const char* 	Message_get_text(Message* msg);
const char* 	Message_get_parsed_text(Message* msg);
int				Message_get_id(Message* msg);

Message* 		Message_get_child(Message *msg);
void 			Message_set_child(Message *msg, Message *child);

void 			Message_set_parsed_text(Message* msg, char* text);

void			Message_parse(Message* msg, Style* style);

#endif /* __MESSAGE_H__ */

