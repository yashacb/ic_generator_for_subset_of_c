#include "scope.c"

typedef struct func_table_row
{
	char* name ;
	struct func_table_row* next ;
	symbol_table* param_list ;
	symbol_table* local_list ;
	int num_param ;
	int res_type ;		
}func_table_row ;

typedef struct func_table{
	int count ;
	func_table_row* list ;
}func_table ;

func_table_row* ft_pop(func_table* ft)
{
	if(ft -> list != NULL && ft -> list -> name[0] == '$')
	{
		func_table_row* ret = ft -> list ;
		ft -> list = ft -> list -> next ;
		return ret ;
	}
	return NULL ;
}

symbol_table_row* ft_get_param(func_table_row* ft , int ind)
{
	if(ind < 0 || ind >= ft -> num_param || ft -> param_list -> list == NULL)
		return NULL ;
	symbol_table_row* cur = ft -> param_list -> list ;
	int i = 0 ;
	while(cur != NULL && i < ft -> num_param && i < ind)
	{
		cur = cur -> next ;
		i++ ;
	}
	return cur ;
}

func_table_row* ft_find(func_table* ft , char* name)
{
	if(ft == NULL)
		return NULL ;
	func_table_row* cur = ft -> list ;
	while(cur != NULL)
	{
		if(strcmp(cur -> name , name) == 0)
			return cur ;
		cur = cur -> next ;
	}
	return NULL ;
}

func_table* ft_new(func_table_row* list)
{
	func_table* new = (func_table*) malloc(sizeof(func_table)) ;
	new -> count = 0 ;
	new -> list = list ;
}

func_table_row* ft_add(func_table* ft , char* name , symbol_table* param_list , symbol_table* local_list , int res_type , int np)
{
	if(ft == NULL)
		return NULL ;
	func_table_row* new = (func_table_row*) malloc(sizeof(func_table_row)) ;
	new -> param_list = param_list ;
	new -> local_list = local_list ;
	new -> res_type = res_type ;	
	new -> next = ft -> list ;
	new -> name = name ;
	new -> num_param = np ;
	ft -> list = new ;
	return new ;
}

void ft_print(func_table* ft)
{
	func_table_row* cur = ft -> list ;
	while(cur != NULL)
	{
		printf("Function : %s\n", cur -> name) ;
		printf("\n");
		printf("Printing param list : \n") ;
		symbol_table_row* cur_param = cur -> param_list -> list ;
		int i = 0 ;
		while(cur_param != NULL && i < cur -> num_param)
		{
			printf("{ ") ;
			printf("name : %s , " , cur_param -> name) ;
			printf("type : %s , " , to_str_data_type(cur_param -> type)) ;
			printf("scope : %d , " , cur_param -> scope) ;
			printf("eletype : %d" , (cur_param -> eletype)) ;
			if(cur_param -> dimlist != NULL)
			{
				printf(" , dimlist : ") ;
				list_print(cur_param -> dimlist) ;
			}
			printf(" }") ;
			cur_param = cur_param -> next ;	
			if(cur_param != NULL)
				printf(" ,\n");
			i++ ;
		}
		printf("\n\n");
		printf("Printing local list : \n") ;
		st_print(cur -> local_list) ;
		cur = cur -> next ;
	}
	printf("\n");
}