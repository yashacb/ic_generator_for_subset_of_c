#include "symbol.c"

struct struct_def_row ;

typedef struct struct_def
{
	int size ;
	struct struct_def_row* list ;
}struct_def ;

typedef struct struct_def_row
{
	char* name ;
	int scope ;
	symbol_table* st ;
	struct struct_def_row* next ;	
}struct_def_row ;

struct_def* sdf_new()
{
	struct_def* new_def = (struct_def*) malloc(sizeof(struct_def)) ;
	new_def -> size = 0 ;
	new_def -> list = NULL ;
	return new_def ;
}

int sdf_find(struct_def* sdf , char* name)
{
	int ind = -1 , len = 0 ;
	struct_def_row* cur = sdf -> list ;
	while(cur != NULL)
	{
		if(strcmp(name , cur -> name) == 0)
			ind = len ;
		len++ ;
		cur = cur -> next ;
	}
	return ind != -1 ? len - 1 - ind : -1 ;
}

struct_def_row* sdf_find_row(struct_def* sdf , char* name)
{
	int ind = sdf_find(sdf , name) ;
	if(ind == -1)
		return NULL ;
	int i = 0 ;
	struct_def_row* res = sdf -> list ;
	while(i < ind)
		res = res -> next ;
	return res ;
}

void sdf_add(struct_def* sdf , char* name , int scope , symbol_table* st)
{
	// printf("SDF : %d \n", scope) ;
	struct_def_row* new_row = (struct_def_row*) malloc(sizeof(struct_def_row)) ;
	new_row -> name = name ;
	new_row -> st = st ;
	new_row -> next = sdf -> list ;
	new_row -> scope = scope ;
	new_row -> next = sdf -> list ;
	sdf -> list = new_row ;
}

void sdf_print(struct_def* sdf)
{
	struct_def_row* cur = sdf -> list ;
	printf("Printing struct definitions table : \n") ;
	while(cur != NULL)
	{
		printf("Name : %s . Scope : %d\n", cur -> name , cur -> scope) ;
		printf("Definition : \n") ;
		st_print(cur -> st) ;
		printf("\n") ;
		cur = cur -> next ;
	}
}