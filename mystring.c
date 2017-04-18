char* dupstr(char* ip)
{
	char* res = (char*)malloc(strlen(ip) + 1) ;
	strcpy(res , ip) ;
	return res ;
}

char* strcat2(char* a , char* b)
{
	char* res = (char*)realloc(a , strlen(a) + strlen(b) + 1) ;
	strcat(a , b) ;
	return res ;
}

char* get_first(char* s)
{
	char* dup = dupstr(s) ;
	return strtok(s , "[.") ;
}