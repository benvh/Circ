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
	GString *str = g_string_new(Style_get_message_template(style));

	const gchar* id = g_strdup_printf("msg%d", msg->_id);
	strreplace2(str, "%_id_%", id);
	g_free(id); //we need to free this!
	
	strreplace2(str, "%_message_%", g_markup_escape_text(msg->_text, strlen(msg->_text)));
	strreplace2(str, "%_user_%", msg->_from);
	strreplace2(str, "%_time_%", get_time_12());
	
	msg->_parsed_text = g_strescape(str->str, NULL);
	g_string_free(str, TRUE);
}
