#include "Style.h"
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

struct OBJ_STYLE
{
	const char* _msg_template;
};



Style* Style_new(const char* name)
{
	char* msg_style_path = g_strdup_printf("data/styles/%s.style/msg_style.html", name);	
	GIOChannel *msg_style_file = g_io_channel_new_file(msg_style_path, "r", NULL);
	char *msg_style_contents;
	
	g_io_channel_read_to_end(msg_style_file, &msg_style_contents, NULL, NULL);
	g_io_channel_close(msg_style_file);
	
	Style *s = (Style*)malloc(sizeof(Style));
	s->_msg_template = (const char*)msg_style_contents;
	
	free(msg_style_path);
	return s;
}

void Style_destroy(Style* style)
{
	free(style);
}

const char*	Style_get_message_template(Style* style)
{
	return style->_msg_template;
}
