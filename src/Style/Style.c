#include "Style.h"
#include <stdio.h>
#include <stdlib.h>

struct OBJ_STYLE
{
	const char* _msg_template;
};



Style* Style_new(const char* name)
{
	FILE *f = fopen(name, "r");
	if(!f) return NULL;
	
	char c;
	int count;
	while((c = fgetc(f)) != EOF)
		if(c != '\n')count++;
		
	char* contents = (char*)malloc(count * sizeof(char));
	int i = 0;
	rewind(f);
	
	while((c = fgetc(f)) != EOF)
	{
		if(c != '\n')
		{
			contents[i] = c;
			i++;
		}
	}
	
	fclose(f);
	
	Style *s = (Style*)malloc(sizeof(Style));
	s->_msg_template = (const char*)contents;
	
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
