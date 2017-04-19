#include "struct.c"

typedef struct scope_map
{
	int scope ;
	symbol_table* st ;
	struct scope_map* next ;
}scope_map ;

void sm_print(scope_map* sm)
{
	if(sm == NULL)
		return ;
	printf("Scope : %d\n", sm -> scope) ;
	printf("Symbol table : \n") ;
	st_print(sm -> st) ;
	printf("\n");
	sm_print(sm -> next) ;
}

int max_scope = 0 ;

void sm_print_table(scope_map* sm)
{
	if(sm == NULL)
		return ;
	printf("\nPrinting whole table :\n");
	scope_map* cur = sm ;
	while(cur != NULL)
	{
		symbol_table_row* list = cur -> st -> list ;
		while(list != NULL && list -> scope == cur -> scope)
		{
			printf("{ ") ;
			printf("name : %s , ", list -> name) ;
			printf("type : %s , " , to_str_data_type(list -> type)) ;
			printf("scope : %d , " , list -> scope) ;
			printf("eletype : %s" , to_str_eletype(list -> eletype)) ;
			if(list -> dimlist != NULL)
			{
				printf(" , dimlist : ") ;
				list_print(list -> dimlist) ;
			}
			printf(" }") ;
			list = list -> next ;
			if(list != NULL)
				printf(" ,\n");
			else
				printf("\n");
		}
		cur = cur -> next ;
	}
}

int sm_get_scope()
{
	return ++max_scope ;
}

scope_map* sm_new(int scope , symbol_table* st)
{
	scope_map* new_map = (scope_map*) malloc(sizeof(scope_map)) ;
	new_map -> next = NULL ;
	new_map -> scope = scope ;
	new_map -> st = st_new() ;
	new_map -> st -> list = st -> list ;
	new_map -> st -> size = st -> size ;
	return new_map ;
}

scope_map* sm_add(scope_map* sm , int scope , symbol_table* st)
{
	scope_map* new_map = sm_new(scope , st) ;
	new_map -> next = sm ;
	return new_map ;
}

symbol_table* sm_find(scope_map* sm , int scope)
{
	if(sm == NULL)
		return NULL ;
	if(sm -> scope == scope)
		return sm -> st ;
	return sm_find(sm -> next , scope) ;
}

typedef struct scope_stack
{
	list* stack ;
}scope_stack ;

scope_stack* sstk_new()
{
	scope_stack* new_sstk = (scope_stack*) malloc(sizeof(scope_stack)) ;
	new_sstk -> stack = NULL ;
	return new_sstk ;
}

void sstk_push(scope_stack* sstk , int scope)
{
	sstk -> stack = list_add(sstk -> stack , scope) ;
}

int sstk_pop(scope_stack* sstk)
{
	int val = sstk -> stack -> val ;
	sstk -> stack = sstk -> stack -> next ;
	return val ;
}