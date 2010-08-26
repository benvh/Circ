#include "MessageBuffer.h"
#include <stdlib.h>
#include <stdio.h>

struct OBJ_MESSAGE_BUFFER{
	int _count; 	/* Actual message count */
	int _max_count;	/* Maximum amount of messages the buffer is allowd to hold */
	int _next_id;	/* ID for the next messages that's added (this increments) */
	
	int _deleted;

	/* 
	 * The Messages function like a linked list.
	 * _msgs points to the FIRST message in the 'list'
	 * _msgs_end points to the LAST message in the 'list'
	 *
	 * Each Message has a pointer to a next message (except for the last one of course)
	 */
	Message *_msgs, *_msgs_end;	
	
};





MessageBuffer* MessageBuffer_new(int max_count)
{
	MessageBuffer* msgbf = (MessageBuffer*)malloc(sizeof(MessageBuffer));

	msgbf->_max_count = max_count;

	/* There aren't any messages yet */
	msgbf->_count = 0; 
	msgbf->_msgs = NULL;
	msgbf->_msgs_end = NULL;
	msgbf->_next_id = 1;
	
	msgbf->_deleted = MESSAGEBUFFER_NO;

	return msgbf;
}

void MessageBuffer_destroy(MessageBuffer* buffer)
{
	MessageBuffer_clear(buffer);
	free(buffer);
}

void MessageBuffer_add_message(MessageBuffer* buffer, Message* msg)
{
	if(buffer->_count == buffer->_max_count)
	{
		/* 
		 * If we have reached our maximum message count we need to remove a message.
		 * This is quite simple (because our Messages work like a linked list)
		 *
		 * We make our second Message the first one and destroy the old first message.
		 */
		Message *tmp = buffer->_msgs;
		//buffer->_msgs = tmp->_child;
		buffer->_msgs = Message_get_child(tmp);
		
		buffer->_deleted = Message_get_id(tmp);
		Message_destroy(tmp);
	}
	else
		buffer->_count++;

	if(buffer->_msgs_end)
		Message_set_child(buffer->_msgs_end, msg);
	else
		buffer->_msgs = msg;
		
	buffer->_msgs_end = msg;
}

void MessageBuffer_del_message(MessageBuffer* buffer, int id)
{
	int n = 0;
	Message* cur = buffer->_msgs;
	Message* parent = NULL;
	while(n < id)
	{
		parent = cur;
		//cur = parent->_child;
		cur = Message_get_child(parent);
		n++;
	}

	//parent->_child = cur->_child;
	if(parent)Message_set_child(parent, Message_get_child(cur));
	buffer->_deleted = Message_get_id(cur);
	
	Message_destroy(cur);

	buffer->_count--;
}

void MessageBuffer_clear(MessageBuffer* buffer)
{
	Message* msg, *next;
	msg = buffer->_msgs;

	//while((next = msg->_child) != NULL)
	while((next = Message_get_child(msg) ) != NULL)
	{
		Message_destroy(msg);
		msg = next;
	}
}

Message* MessageBuffer_get_message(MessageBuffer* buffer, int id)
{
	int n = 0;
	Message* cur = buffer->_msgs;
	while(n < id)
	{
		//cur = cur->_child;
		cur = Message_get_child(cur);
		n++;
	}

	return cur;
}

int MessageBuffer_get_message_count(MessageBuffer* buffer)
{
	return buffer->_count;
}

int MessageBuffer_get_max_message_count(MessageBuffer* buffer)
{
	return buffer->_max_count;
}

int MessageBuffer_get_next_id(MessageBuffer* buffer)
{
	return buffer->_next_id++;
}

void MessageBuffer_set_max_message_count(MessageBuffer* buffer, int max_count)
{
	buffer->_max_count = max_count;
}


int MessageBuffer_message_deleted(MessageBuffer* buffer)
{
	int id = buffer->_deleted;
	buffer->_deleted = MESSAGEBUFFER_NO;
	return id;	
}
