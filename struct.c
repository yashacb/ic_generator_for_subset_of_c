#include "symbol.c"

struct struct_def_row ;

typedef struct 
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

void sdf_add(struct_def* sdf , char* name , int scope , symbol_table* st)
{
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
		printf("Name : %s\n", cur -> name) ;
		printf("Definition : \n") ;
		st_print(cur -> st) ;
		printf("\n") ;
		cur = cur -> next ;
	}
}