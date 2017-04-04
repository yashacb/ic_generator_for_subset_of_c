typedef struct map
{
	char* key ;
	char* value ;
	symbol_table* other ;
	struct map* next ;
}map ;

map* map_add(map* m , char* key , char* value , symbol_table* other)
{
	map* new = (map*) malloc(sizeof(map)) ;
	new -> key = key ;
	new -> value = value ;
	new -> other = other ;
	new -> next = m ;
	return new ;
}

map* map_find(map* m , char* key)
{
	if(m == NULL)
		return NULL ;
	else
	{
		if(strcmp(m -> key , key) == 0)
			return m ;
		return map_find(m -> next , key) ;
	}
}

void map_print(map* m)
{
	if(m != NULL)
	{
		printf("  { key : %s , value : %s }\n" , m -> key , m -> value) ;
		map_print(m -> next) ;
	}
}