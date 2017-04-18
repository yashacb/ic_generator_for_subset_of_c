#include "list.c"

extern char* to_str_data_type(int type) ;
extern char* to_str_eletype(int type) ;

typedef struct struct_def struct_def ;
typedef struct struct_def_row struct_def_row ;

enum data_type
{
	SIMPLE , ARRAY , STRUCT_T 
} ;

struct symbol_table ;

typedef struct symbol_table_row
{
	char* name ;
	int type ;
	int eletype ;
	struct symbol_table_row* next ;
	list* dimlist ;
	int scope ;

}symbol_table_row ;

typedef struct symbol_table
{
	int size ;
	symbol_table_row* list ;
}symbol_table ;

symbol_table_row* st_get_symbol(symbol_table* st , int ind)
{
	int i = 0 ;
	symbol_table_row* cur = st -> list ;
	while(i < ind && cur != NULL)
	{
		printf("%s\n", cur -> name) ;
		cur = cur -> next ;
		i++ ;		
	}
	return cur ;
}

void st_print(symbol_table* st)
{
	if(st == NULL)
		return ;
	symbol_table_row* cur = st -> list ;
	printf("[") ;
	while(cur != NULL)
	{
		printf("{ ") ;
		printf("name : %s , " , cur -> name) ;
		printf("type : %s , " , to_str_data_type(cur -> type)) ;
		printf("scope : %d , " , cur -> scope) ;
		printf("eletype : %s" , to_str_eletype(cur -> eletype)) ;
		if(cur -> dimlist != NULL)
		{
			printf(" , dimlist : ") ;
			list_print(cur -> dimlist) ;
		}
		printf(" }") ;
		cur = cur -> next ;	
		if(cur != NULL)
			printf(" ,\n");
	}
	printf("]\n");
}

symbol_table_row* st_find(symbol_table* st , char* name , int scope)
{
	if(st == NULL)
		return NULL ;
	symbol_table_row* a = st -> list ;
	symbol_table_row* res = NULL ;
	while(a != NULL)
	{
		if(strcmp(name , a -> name) == 0)
		{
			return a ;
		}
		a = a -> next ;
	}
	return res ;
}

symbol_table_row* st_find_strict(symbol_table* st , char* name , int scope)
{
	if(st == NULL)
		return NULL ;
	symbol_table_row* a = st -> list ;
	symbol_table_row* res = NULL ;
	while(a != NULL)
	{
		if(strcmp(name , a -> name) == 0 && a -> scope == scope)
		{
			return a ;
		}
		a = a -> next ;
	}
	return res ;
}

symbol_table_row* st_add(symbol_table* st , char* name , int type , int eletype , list* dimlist , int scope)
{
	if(st == NULL)
		return NULL ;
	symbol_table_row* new_row = (symbol_table_row*) malloc(sizeof(symbol_table_row)) ;
	new_row -> name = name ;
	new_row -> type = type ;
	new_row -> eletype = eletype ;
	new_row -> dimlist = dimlist ;
	new_row -> scope = scope ;
	new_row -> next = st -> list ;
	st -> list = new_row ;	
	return new_row ;
}

symbol_table* st_new()
{
	symbol_table* new_st = (symbol_table*) malloc(sizeof(symbol_table)) ;
	new_st -> size = 0 ;
	new_st -> list = NULL ;
}

int st_size(symbol_table* st)
{
	int len = 0 ;
	symbol_table_row* cur = st -> list ;
	while(cur != NULL)
	{
		len++ ;
		cur = cur -> next ;
	}
	return len ;
}

int st_compare(symbol_table_row* a , symbol_table_row* b)
{
	if( a == NULL || b == NULL)
		return 1 ;
	if(a -> type == b -> type && a -> eletype == b -> eletype && 
		list_length(a -> dimlist) == list_length(b -> dimlist))
		return 1 ;
	return 0 ;
}

int temp_num = 0 ;

symbol_table_row* st_new_temp(symbol_table* st , int eletype , int scope) // this is eletype !!
{
	char* name = dupstr("$temp") ;
	char num[10] ;
	sprintf(num , "%d" , temp_num++) ;
	name = strcat2(name , num) ;
	return st_add(st , name , SIMPLE , eletype , NULL , scope) ;
}