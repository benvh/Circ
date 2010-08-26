#include "Message.h"
#include <stdlib.h>
#include <string.h>
#include "../Util/Util.h"

struct OBJ_MESSAGE{
	Message* _child;
	int _parsed;
	int _id;

	const char* _from;
	const char* _text;

	const char* _parsed_text;
};




Message* Message_new(const char* from, const char* text, int id)
{
	Message* msg = (Message*)malloc(sizeof(Message));
	
	msg->_from = from;
	msg->_text = text;

	msg->_parsed = 0;
	msg->_id = id;

	return msg;
}

void Message_destroy(Message* msg)
{
	free(msg);
}


const char* Message_get_from(Message* msg)
{
	return msg->_from;
}

const char* Message_get_text(Message* msg)
{
	return msg->_text;
}

const char* Message_get_parsed_text(Message* msg)
{
	return (const char*)msg->_parsed_text;
}

int Message_get_id(Message* msg)
{
	return msg->_id;
}

void Message_set_parsed_text(Message* msg, char* text)
{
	msg->_parsed_text = text;	
}

void Message_set_child(Message* msg, Message* child)
{
	msg->_child = child;
}

Message* Message_get_child(Message* msg)
{
	return msg->_child;
}

void Message_parse(Message* msg, Style* style)
{
	const char* msg_template = Style_get_message_template(style);
	char id[7];
	sprintf(id, "msg%d", msg->_id);
	
	const char* p1 = strreplace(msg_template, "%_id_%", id);
	const char* p2 = strreplace(p1, "%_message_%", msg->_text);
	const char* p3 = strreplace(p2, "%_user_%", msg->_from);
	const char* p4 = strreplace(p3, "%_time_%", get_time_12());
	
	if(p1 != p2)free((char*)p1);
	if(p2 != p3)free((char*)p2);
	if(p3 != p4)free((char*)p3);
	
	msg->_parsed = 1;
	msg->_parsed_text = p4;
}
