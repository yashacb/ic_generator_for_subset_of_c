#include "symbol.c"

void sdf_print(struct_def* sdf) ;

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
	return ind != -1 ? len - 1 - ind : -1 ; // index from last !
}

symbol_table* sdf_find_row(struct_def* sdf , int ind) // ind is from last of the list
{
	int len = 0 ;
	struct_def_row* cur = sdf -> list ;
	while(cur != NULL)
	{
		len++ ;
		cur = cur -> next ;
	}
	int find = len - 1 - ind ;
	cur = sdf -> list ;
	int i = 0 ;
	while(i < find)
	{
		cur = cur -> next ;
		i++ ;
	}
	return cur -> st ;
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