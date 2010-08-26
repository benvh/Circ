#ifndef __MESSAGEBUFFER_H__
#define __MESSAGEBUFFER_H__

#include "Message.h"

#define MESSAGEBUFFER_NO -1

typedef struct OBJ_MESSAGE_BUFFER MessageBuffer;



MessageBuffer*		MessageBuffer_new(int max_count);
void				MessageBuffer_destroy(MessageBuffer* buffer);

void				MessageBuffer_add_message(MessageBuffer* buffer, Message* msg);
void				MessageBuffer_del_message(MessageBuffer* buffer, int id);

void				MessageBuffer_clear(MessageBuffer* buffer);

Message*			MessageBuffer_get_message(MessageBuffer* buffer, int id);
int					MessageBuffer_get_message_count(MessageBuffer* buffer);
int					MessageBuffer_get_max_message_count(MessageBuffer* buffer);
int					MessageBuffer_get_next_id(MessageBuffer* buffer);

int					MessageBuffer_message_deleted(MessageBuffer* buffer);

void				MessageBuffer_set_max_message_count(MessageBuffer* buffer, int max_count);

#endif /* __MESSAGEBUFFER_H__ */

