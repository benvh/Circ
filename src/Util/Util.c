#include "Util.h"

const char* strreplace(const char* string, const char* match, const char* replace)
{
	char* tmp;
	if(!(tmp = strstr(string, match))) return string;
	
	int len = (strlen(string) - strlen(match)) + strlen(replace) + 1;
	char *buff = (char*)malloc(len*sizeof(char));
		
	strncpy(buff, string, tmp-string);
	buff[tmp-string] = 0;
	
	sprintf(buff+(tmp-string), "%s%s", replace, tmp+strlen(match));
	
	return buff;
}

const char* get_time_12(void)
{
	char* buff = (char*)malloc(10 * sizeof(char));
	time_t t = time(NULL);
	strftime(buff, 10, "%I:%M%p", localtime(&t));
	
	return (const char*)buff;
}

const char* get_time_24(void)
{
	char* buff = (char*)malloc(8 * sizeof(char));
	time_t t = time(NULL);
	strftime(buff, 8, "%H:%M", localtime(&t));
	
	return (const char*)buff;
}
