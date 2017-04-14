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

func_table* ft_new(func_table_row* list)
{
	func_table* new = (func_table*) malloc(sizeof(func_table)) ;
	new -> count = 0 ;
	new -> list = list ;
}

func_table_row* ft_add(func_table* ft , char* name 
	, symbol_table* param_list , symbol_table* local_list , int res_type , int np)
{
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
			printf("eletype : %s" , to_str_eletype(cur_param -> eletype)) ;
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
		printf("\n");
		printf("Printing local list : \n") ;
		st_print(cur -> local_list) ;
		cur = cur -> next ;
	}
}