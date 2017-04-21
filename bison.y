%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mystring.c"
#include "func.c"
#include "ic.c"

#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

symbol_table_row* resolve(symbol_table_row* str , list* dimlist) ;
char* datatype_to_string(symbol_table_row* str) ;
int expr_type(int t1 , int t2) ;
int is_int(int t) ;
int is_float(int t) ;
int is_array(int t) ;
int is_struct(int t) ;
int is_char(int t) ;
int parse_error = 0 ;

func_table* ft = NULL ;
symbol_table* st = NULL ;
struct_def* sdf = NULL ;
scope_stack* sstk = NULL ;
scope_map* sm = NULL ;
inter_code* ic = NULL ;
list* hlt_list = NULL ;

int ind_dim = 0 ;
int line_no = 1 ;
int cur_scope = 0 ;
int cur_dt = 0 ;
int cur_arr_index = -1 ;
int sdt ;
func_table_row* cur_func_ptr = NULL ; // the functions which is being defiend 
func_table_row* call_func_ptr = NULL ; // the functions which is being called
char* to_str_eletype(int type) ;
symbol_table_row* add_offsets(symbol_table_row* o1 , symbol_table_row* o2) ;
void yyerror (char const *s)
{
	printf("Parse error on line no. %d : %s\n" , line_no , s) ;
	exit(0) ;
}
// Union types
typedef struct decl{
	int type ;
	symbol_table_row* ptr ;
}decl ;

typedef struct expr{
	int type ;
	symbol_table_row* temp ;
	int constant ; // is this a constant ?
	char* val ; // if yes , then this is the value .
	list* nextlist ;
	list* truelist ; // used by boolean expr
	list* falselist ; // used by boolean expr
}expr ;

typedef struct arr_list{
	expr e ;
	struct arr_list* next ;
}arr_list ;

typedef struct id{
	int type ; // this contains the element type and not if it is SMIPLE , ARRAY or STRUCT ! This you need to get from ptr !
	char* val ;
	symbol_table_row* ptr ;
	symbol_table* st ;
	arr_list* arrlist ;
	list* dimlist ; // this is used in lvalue .
	symbol_table_row* offset ;
}id ;

typedef struct constant{
	int type ;
	int i_val ;
	float f_val ;
	char c_val ;
} constant;
//
list* arr_to_list(arr_list* al) ;
symbol_table_row* calculate_offset(arr_list* al , list* dimlist , int size) ;
int sdf_struct_size(struct_def* sdf , int ind) ;
int get_size(int eletype) ;
symbol_table_row* sdf_offset(struct_def* sdf , int eletype , char* name) ;
symbol_table_row* coerce(symbol_table_row* cur , int to_type) ;
int equal_types(int t1 , int t2) ;
char* relop_to_str(int type) ;

%}
%union{
	char op ;
	decl d ;
	expr e ;
	constant c ;
	id i ;
	list* l ;
	arr_list* al ;
	func_table_row* f ;
	symbol_table_row* a ; // argument list for function calls
	int np ; // no. of parameters . Used by PARAM_LIST . This is also used fot ARG_LIST , but in this 
	// case it respresents the 'np' the argument in the function call .
}
%define parse.error verbose
%token <d> T_INT
%token <d> T_FLOAT
%token <d> T_CHAR
%token <d> T_STRUCT
%token <d> T_ERROR
%token <i> ID
%token <c> V_INT
%token <c> V_FLOAT
%token <c> V_CHAR
%token <np> WHILE // this doexnt need any type .
%token <np> IF // this doexnt need any type .
%token <np> ELSE // this doexnt need any type .
%token <np> LT 
%token <np> GT 
%token <np> LTE
%token <np> GTE
%token <np> EQ 
%token <np> RETURN

%type <d> TYPE
%type <d> DECL_LIST
%type <d> DECL
%type <d> SVAR_LIST
%type <d> VAR_LIST
%type <d> VAR
%type <d> VAR_CHECK
%type <d> SVAR_CHECK
%type <l> DIM_LIST
%type <al> ARR_LIST
%type <e> ASG
%type <i> LVALUE
%type <i> LVALUE_CHECK
%type <e> BLOCK
%type <e> EXPR
%type <e> TERM
%type <e> FACTOR
%type <e> WHILE_STMT
%type <e> IF_STMT
%type <e> IFELSE_STMT
%type <e> BOOL_EXPR
%type <e> AND_EXPR
%type <np> M
%type <e> BASE
%type <np> RELOP
%type <f> FUNC_DEF
%type <f> FUNC_CALL
%type <np> PARAM_LIST
%type <np> ARG_LIST
%type <np> ARGS_LIST
%type <op> ASOP
%type <op> MDOP

%start S
%%
S : FUNC_DEF S
	| DECL S
	|
	;
FUNC_DEF : TYPE ID {
		if(ft_find(ft , $2.val) != NULL)
		{
			printf("Function '%s' already defined .\n", $2.val) ; // Think of improving this .
			exit(0) ;
		}
		cur_func_ptr = ft_add(ft , $2.val , NULL , NULL , $1.type , 0) ;

		char code[100] ;
		sprintf(code , "function begin %s" , $2.val) ;
		ic = ic_add(ic , NOT_GOTO , code , -1) ;

		sstk_push(sstk , cur_scope) ;
		cur_scope = sm_get_scope() ;
		sm = sm_add(sm , cur_scope , st) ;
		st = sm_find(sm , cur_scope) ;
	} '(' PARAM_LIST ')' {
		cur_func_ptr -> param_list = st_new() ;
		cur_func_ptr -> param_list -> list = st -> list ;		
		cur_func_ptr -> num_param = $5 ;
	} '{' STMTS RETURN_STMT '}' { 
		char code[100] ;
		sprintf(code , "func end") ;
		ic = ic_add(ic , NOT_GOTO , code , -1) ;

		cur_func_ptr -> local_list = st ;
		cur_scope = sstk_pop(sstk) ;
		st = sm_find(sm , cur_scope) ;
		cur_func_ptr = NULL ;
		$$ = NULL ; }
	;
RETURN_STMT: RETURN ';' {
		char code[100] ;
		sprintf(code , "return") ;
		ic = ic_add(ic , NOT_GOTO , code , -1) ;
	}
	| RETURN EXPR ';' {
		char code[100] ;
		if($2.temp != NULL)
		{
			sprintf(code , "return %s" , $2.temp -> name) ;
			ic = ic_add(ic , NOT_GOTO , code , -1) ;				
		}
		else if($2.constant != 0)
		{
			sprintf(code , "return %s" , $2.val) ;
			ic = ic_add(ic , NOT_GOTO , code , -1) ;			
		}
		else
		{
			printf("Unknown return value for function %s on line no : %d\n", cur_func_ptr -> name , line_no) ;
			parse_error = 1 ;
		}
	}
	| 
PARAM_LIST : TYPE VAR {
		if($2.ptr != NULL)
			$2.ptr -> eletype = $1.type ;
	} ',' PARAM_LIST { $$ = 1 +  $5 ; }
	| TYPE VAR {
		if($2.ptr != NULL)
			$2.ptr -> eletype = $1.type ;
		$$ = 1 ;
	}
	| T_STRUCT ID ID SVAR_CHECK ARR_LIST { 
		$$ = 1 ; 
		st_add(st , $3.val , STRUCT_T , $4.type , arr_to_list($5) , cur_scope) ;
	}
	| T_STRUCT ID ID SVAR_CHECK ARR_LIST  ',' PARAM_LIST { 
		$$ = 1 + $7 ; 
		st_add(st , $3.val , STRUCT_T , $4.type , arr_to_list($5) , cur_scope) ;
	}
	| { $$ = 0 ; }
	;
FUNC_CALL : ID { 
		call_func_ptr = ft_find(ft , $1.val) ;		
		if(call_func_ptr == NULL)
		{
			printf("Unknown function '%s' on line_no : %d .\n\n", $1.val , line_no) ;
			parse_error = 1 ;
		}
	}'(' ARGS_LIST ')' ';' { 
		int called_params = $4 ;
		if(call_func_ptr != NULL)
		{
			if(call_func_ptr -> num_param != called_params + 1 )
			{
				printf("Error incorrect number of arguments for function '%s' on line no : %d .\n" , call_func_ptr -> name , line_no) ;
				printf("Expected : %d , but found : %d . \n\n", call_func_ptr -> num_param , called_params + 1) ;
				parse_error = 1 ;
			}
			else
			{
				char code[100] ;
				symbol_table_row* ret_temp = st_new_temp(st , call_func_ptr -> res_type , cur_scope) ;
				sprintf(code , "refparam %s" , ret_temp -> name) ;
				ic = ic_add(ic , NOT_GOTO , code , -1) ;
				sprintf(code , "call %s %d" , call_func_ptr -> name , call_func_ptr -> num_param) ;
				ic = ic_add(ic , NOT_GOTO , code , -1) ;
			}
		}
		$$ = NULL ;
	}
	;
ARGS_LIST : ARG_LIST {$$ = $1 ;}
	| {$$ = -1 ; // don't change this :p
	 }
	;
ARG_LIST : ARG_LIST ',' EXPR { 
		$$ = $1 + 1 ; 
		if(call_func_ptr != NULL)
		{
			int num_param = call_func_ptr -> num_param ;
			symbol_table_row* expected = ft_get_param(call_func_ptr , num_param - 1 - $$) ;			
			if(expected != NULL)
			{
				if($3.temp != NULL)
				{
					symbol_table_row* found = $3.temp ;
					if(expected -> dimlist == NULL && found -> dimlist == NULL && is_float(expected -> eletype) && is_int($3.temp -> eletype))	
					{
						symbol_table_row* temp = st_new_temp(st , T_FLOAT , cur_scope) ;
						char code[100] ;
						sprintf(code , "%s = (float)%s" , temp -> name , $3.temp -> name) ;
						ic = ic_add(ic , NOT_GOTO , code , -1) ;
						sprintf(code , "param %s" , temp -> name) ;
						ic = ic_add(ic , NOT_GOTO , code , -1) ;
					}
					else if(st_compare(expected , found) != 1)
					{
						printf("Incorrect argument %d for function '%s' on line no : %d .\n", $$ + 1 , call_func_ptr -> name , line_no) ;
						printf("Expected %s , but found %s\n\n" , datatype_to_string(expected) , datatype_to_string(found)) ;
						parse_error = 1 ;
					}
					else
					{
						char code[100] ;
						sprintf(code , "param %s" , $3.temp -> name) ;
						ic = ic_add(ic , NOT_GOTO , code , -1) ;
					}
				}
				else
				{
					if(expected -> dimlist == NULL && is_float(expected -> eletype) && $3.constant == V_INT)
					{
						symbol_table_row* temp = st_new_temp(st , T_FLOAT , cur_scope) ;
						char code[100] ;
						sprintf(code , "%s = (float)%s" , temp -> name , $3.val) ;
						ic = ic_add(ic , NOT_GOTO , code , -1) ;
						sprintf(code , "param %s" , $3.val) ;
						ic = ic_add(ic , NOT_GOTO , code , -1) ;
					}
					else if(expected -> dimlist != NULL || !equal_types(expected -> eletype , $3.constant))
					{
						printf("Incorrect argument %d for function '%s' on line no : %d .\n", $$ + 1 , call_func_ptr -> name , line_no) ;
						printf("Expected %s , but found %s\n\n" , datatype_to_string(expected) , to_str_eletype($3.constant == 0 ? -1 : $3.constant)) ;
						parse_error = 1 ;
					}
					else
					{
						char code[100] ;
						sprintf(code , "param %s" , $3.val) ;
						ic = ic_add(ic , NOT_GOTO , code , -1) ;
					}
				}
			}
		}
	}
	| EXPR  { 
		$$ = 0 ; 
		if(call_func_ptr != NULL)
		{
			int num_param = call_func_ptr -> num_param ;
			symbol_table_row* expected = ft_get_param(call_func_ptr , num_param - 1 - $$) ;
			if(expected != NULL)
			{
				if($1.temp != NULL)
				{
					symbol_table_row* found = $1.temp ;	
					if(expected -> dimlist == NULL && found -> dimlist == NULL && is_float(expected -> eletype) && is_int($1.temp -> eletype))	
					{
						symbol_table_row* temp = st_new_temp(st , T_FLOAT , cur_scope) ;
						char code[100] ;
						sprintf(code , "%s = (float)%s" , temp -> name , $1.temp -> name) ;
						ic = ic_add(ic , NOT_GOTO , code , -1) ;
						sprintf(code , "param %s" , temp -> name) ;
						ic = ic_add(ic , NOT_GOTO , code , -1) ;
					}	
					else if(st_compare(expected , found) != 1)
					{
						printf("Incorrect argument %d for function '%s' on line no : %d .\n", $$ + 1 , call_func_ptr -> name , line_no) ;
						printf("Expected %s , but found %s\n\n" , datatype_to_string(expected) , datatype_to_string(found)) ;
						parse_error = 1 ;
					}
					else
					{
						char code[100] ;
						sprintf(code , "param %s" , $1.temp -> name) ;
						ic = ic_add(ic , NOT_GOTO , code , -1) ;
					}
				}
				else
				{
					if(expected -> dimlist == NULL && is_float(expected -> eletype) && $1.constant == V_INT)
					{
						symbol_table_row* temp = st_new_temp(st , T_FLOAT , cur_scope) ;
						char code[100] ;
						sprintf(code , "%s = (float)%s" , temp -> name , $1.val) ;
						ic = ic_add(ic , NOT_GOTO , code , -1) ;
						sprintf(code , "param %s" , $1.val) ;
						ic = ic_add(ic , NOT_GOTO , code , -1) ;
					}
					else if(expected -> dimlist != NULL || !equal_types(expected -> eletype , $1.constant))
					{
						printf("Incorrect argument %d for function '%s' on line no : %d .\n", $$ + 1 , call_func_ptr -> name , line_no) ;
						printf("Expected %s , but found %s\n\n" , datatype_to_string(expected) , to_str_eletype($1.constant == 0 ? -1 : $1.constant)) ;
						parse_error = 1 ;
					}
					else
					{
						char code[100] ;
						sprintf(code , "param %s" , $1.val) ;
						ic = ic_add(ic , NOT_GOTO , code , -1) ;
					}
				}
			}
		}
	}
	;
STMTS : DECL STMTS
	| BLOCK STMTS
	| ASG STMTS
	| FUNC_CALL STMTS
	| EXPR ';' STMTS
	| WHILE_STMT { 
		ic = ic_backpatch(ic , $1.falselist , nextquad) ;
	 } STMTS
	| IF_STMT {
		ic = ic_backpatch(ic , $1.falselist , nextquad) ;
	} STMTS
	| IFELSE_STMT {
		ic = ic_backpatch(ic , $1.truelist , nextquad) ;
	} STMTS
	|
	;
BLOCK : '{' { sstk_push(sstk , cur_scope) ;
		cur_scope = sm_get_scope() ;
		sm = sm_add(sm , cur_scope , st) ;
		st = sm_find(sm , cur_scope) ;
	} STMTS '}' { cur_scope = sstk_pop(sstk) ; 
		st = sm_find(sm , cur_scope) ;
	}
	;

DECL_LIST :  DECL_LIST DECL
		| DECL
		;
DECL :   TYPE VAR_LIST ';'
	| T_STRUCT {cur_dt = T_STRUCT ;} ID TEMP ';'
	;
TEMP : '{' { 
		sstk_push(sstk , cur_scope) ;
		cur_scope = sm_get_scope() ;
		st = st_new() ;
		} DECL_LIST '}' {
		cur_scope = sstk_pop(sstk) ;
		sdf_add(sdf , $<i>0.val , cur_scope , st) ;
		st = sm_find(sm , cur_scope) ; 
	}
	| SVAR_LIST	
	;
SVAR_LIST : ID SVAR_CHECK ARR_LIST { 
		$$.type = $2.type ; 
		if($$.type != -1)
			st_add(st , $1.val , STRUCT_T , $2.type , arr_to_list($3) , cur_scope) ;
	}
	| SVAR_LIST ',' ID VAR_CHECK  { 
		$$.type = $1.type ; 
		if($$.type != -1)
			st_add(st , $3.val , STRUCT_T , $1.type , NULL , cur_scope) ;
	}
	;
SVAR_CHECK : {
		if(st_find_strict(st , $<i>0.val , cur_scope) != NULL)
		{
			printf("Redeclaration of variable '%s' in current scope on line no : %d\n\n" , $<i>0.val , line_no) ;
			parse_error = 1 ;
			$$.type = -1 ;
		}
		else
		{
			int ind = sdf_find(sdf , $<i>-1.val) ; // This index is from the last !!
			if(ind != -1)
				; // :p
			else
			{
				printf("Unknown type '%s' for variable '%s' on line no : %d\n\n" , $<i>-1.val , $<i>0.val , line_no) ;
				parse_error = 1 ;
			}
			$$.type = ind ; // this is eletype !
		}
	}
	;
VAR_LIST : VAR_LIST ',' VAR {
		$$.type = $3.type ;
	}
	| VAR {
		$$.type = $1.type ;
	}
	;
VAR : ID VAR_CHECK { 
		$$.type = $1.type ; 
		if($2.type != -1)
			$$.ptr = st_add(st , $1.val , SIMPLE , $1.type , NULL , cur_scope) ;
		else
			$$.ptr = NULL ;
	}
	| ID VAR_CHECK DIM_LIST { 
		$$.type = $1.type ; 
		if($2.type != -1)
			$$.ptr = st_add(st , $1.val , ARRAY , $1.type , list_reverse($3) , cur_scope) ;
		else
			$$.ptr = NULL ;
	}
	;
VAR_CHECK : 
	{
		if(st_find_strict(st , $<i>0.val , cur_scope) != NULL)
		{
			printf("Redeclaration of variable '%s' in current scope on line no : %d .\n\n" , $<i>0.val , line_no) ;
			parse_error = 1 ;
			$$.type = -1 ;
		}
		else
			$$.type = $<i>0.type ;
	}
	;
DIM_LIST : '[' V_INT ']' {
		$$ = list_add(NULL , $2.i_val) ;
	}
	| DIM_LIST '[' V_INT ']' {
		$$ = list_add($1 , $3.i_val) ;
	}
	; 
ASG : LVALUE '=' EXPR ';' {	
		symbol_table_row* resolved = resolve($1.ptr , $1.dimlist) ;	
		if(resolved != NULL && resolved -> type == ARRAY)
		{
			printf("Cannot assign to array '%s' on line no : %d\n\n", $1.val , line_no) ;
			parse_error = 1 ;
		}
		if($3.temp != NULL && $3.temp -> type == ARRAY)
		{
			printf("Cannot assign an array to lvalue on line no : %d\n\n", line_no) ;
			parse_error = 1 ;	
		}
		char* lname = get_first($1.val) ;
		int expr_t = expr_type($1.type , $3.type) ; // cmopares eletypes !
		if(expr_t == -1)
		{
			if($1.type == -1)
			{
				printf("Unknown type for lvalue '%s' on line no : %d .\n\n", $1.val , line_no) ;
			}
			else
			{
				printf("Assignment of incompatible types on line no : %d .\n", line_no) ;
				if($3.temp == NULL)
					printf("Assigning '%s' to '%s' \n\n", to_str_eletype($3.type) , datatype_to_string(resolve($1.ptr , $1.dimlist))) ;
				else
					printf("Assigning '%s' to '%s' \n\n", datatype_to_string($3.temp) , datatype_to_string(resolve($1.ptr , $1.dimlist))) ;
				parse_error = 1 ;
			}
		}
		else if($1.type == T_INT && (is_float($3.type) || is_float($3.constant)))
		{
			printf("Assignment of incompatible type on line no : %d\n", line_no) ;
			printf("Assigning 'float' to an 'int' . \n\n\n") ;
			parse_error = 1 ;
		}
		else
		{			
			int flag = 0 ;
			if(is_int($3.type) && is_float($1.type))
				flag = 1 ;			
			if($1.ptr != NULL && parse_error == 0)
			{
				char code[100] ;
				if($1.offset != NULL)
				{
					if($3.constant == 0)
					{
						if(flag)
							sprintf(code , "%s[%s] = (float)%s" , lname , $1.offset -> name , $3.temp -> name) ;
						else
							sprintf(code , "%s[%s] = %s" , lname , $1.offset -> name , $3.temp -> name) ;
					}
					else
					{
						if(flag)
							sprintf(code , "%s[%s] = (float)%s" , lname , $1.offset -> name , $3.val) ;
						else
							sprintf(code , "%s[%s] = %s" , lname , $1.offset -> name , $3.val) ;
					}
				}
				else
				{
					if($3.constant == 0)
					{
						if(flag)
							sprintf(code , "%s = (float)%s" , lname , $3.temp -> name) ;
						else
							sprintf(code , "%s = %s" , lname , $3.temp -> name) ;
					}
					else
					{
						if(flag)
							sprintf(code , "%s = (float)%s" , lname , $3.val) ;
						else
							sprintf(code , "%s = %s" , lname , $3.val) ;
					}
				}
				ic = ic_add(ic , NOT_GOTO , code , -1) ;
			}
		}
		$$.type = $1.type ;
		$$.temp = $1.ptr ;
		$$.constant = 0 ;
		$$.val = "" ;
	}
	;
LVALUE : ID  ARR_LIST { $<i>$.st = st ; $<i>$.val = "<block>" ; } LVALUE_CHECK {		
		$$.type = $4.type ;
		$$.ptr = $4.ptr ;
		$$.st = $4.st ;
		$$.val = $4.val ;
		$$.dimlist = arr_to_list($2) ;
		$$.arrlist = $2 ;
		$$.offset = NULL ;

		if($$.ptr != NULL)
		{
			symbol_table_row* offset = calculate_offset($$.arrlist , $$.ptr -> dimlist , get_size($$.ptr -> eletype)) ;			
		
			$$.offset = offset ;
			$$.val = (char*) malloc(30*sizeof(30)) ;
			$$.val = strcat2($$.val , $1.val) ;
			list* cur = arr_to_list($2) ;
			while(cur != NULL)
			{
				cur = cur -> next ;
				$$.val = strcat2($$.val , "[]") ;
			}
		}
	}
	| LVALUE '.' ID ARR_LIST { $<i>$.st = $1.st ;  $<i>$.val = $1.val ; } LVALUE_CHECK {
		$$.type = $6.type ;
		$$.ptr = $6.ptr ;
		$$.st = $6.st ;
		$$.val = dupstr($1.val) ;
		$$.val = strcat2($$.val , ".") ;
		$$.val = strcat2($$.val , $3.val) ;
		list* cur = arr_to_list($4) ;
		while(cur != NULL)
		{
			cur = cur -> next ;
			$$.val = strcat2($$.val , "[]") ;
		}
		$$.dimlist = arr_to_list($4) ;
		$$.arrlist = $4 ;
		if($$.ptr != NULL)
		{
			symbol_table_row* right = calculate_offset($$.arrlist , $$.ptr -> dimlist , get_size($$.ptr -> eletype)) ;
			symbol_table_row* struct_offset = sdf_offset(sdf , $1.ptr -> eletype , $3.val) ;

			symbol_table_row* offset = $1.offset ;
			offset = add_offsets(offset , right) ;
			offset = add_offsets(offset , struct_offset) ;
			$$.offset = offset ;			
		}

		if($1.ptr == NULL || list_length($1.dimlist) < list_length($1.ptr -> dimlist) || $1.ptr -> type != STRUCT_T)
		{
			printf("Cannot de-reference a non-struct type '%s' on line no : %d\n\n", $1.val , line_no) ;
			parse_error = 1 ;
			$$.type = -1 ;
		}
	}
	;
LVALUE_CHECK : {	
		char* val = $<i>-2.val ;
		list* cur = arr_to_list($<al>-1) ;
		arr_list* cur_al = $<al>-1 ;
		symbol_table* cur_st = $<i>0.st ;
		symbol_table_row* res = st_find(cur_st , val , cur_scope) ;
		if(res == NULL)
		{
			$$.type = -1 ;

			printf("'%s' is not declared in '%s s' scope on line no : %d. \n\n" , val , $<i>-0.val , line_no) ;
			parse_error = 1 ;
		}
		else
		{
			list* dimlist = res -> dimlist ;
			int lc = list_length(cur) , ld = list_length(dimlist) ;
			int ind = 0 ;
			while(cur != NULL && dimlist != NULL)
			{
				if(cur -> val != -1)
				{
					if(cur -> val >= dimlist -> val)
					{
						printf("Array index %d out of bounds for '%s' on line no : %d . \n", ind , val , line_no) ;
						printf("Actual size : %d . Found index : %d\n\n", dimlist -> val , cur -> val) ;
						parse_error = 1 ;
					}
				}
				else
				{
					char code[100] ;
					hlt_list = list_add(hlt_list , nextquad) ;
					sprintf(code , "if %s >= %d goto " , cur_al -> e.temp -> name , dimlist -> val) ;
					ic = ic_add(ic , GOTO , code , -1) ;
				}
				ind ++ ;
				cur_al = cur_al -> next ;
				cur = cur -> next ;
				dimlist = dimlist -> next ;
			}
			if(lc > ld)
			{
				printf("Number of dimensions exceeded for '%s' on line no : %d .\n", val , line_no) ;
				printf("Declared dimensions : %d . Found dimensions : %d\n\n", ld , lc) ;
				parse_error = 1 ;
				res = NULL ;				
			}
		}
		$$.ptr = res ;
		$$.val = val ;
		$$.type = res != NULL ? res -> eletype : -1 ;
		if(res != NULL && res -> type == STRUCT_T)
		{
			$$.st = sdf_find_row(sdf , res -> eletype) == NULL ? NULL : sdf_find_row(sdf , res -> eletype) -> st ;
		}
		else
			$$.st = NULL ;
	}
	;
ARR_LIST : { $$ = NULL ; cur_arr_index = 0 ;}
	| '[' EXPR  ']' ARR_LIST {
		if($2.constant != 0 && $2.constant != V_INT)
		{
			printf("Array index no. %d (from last) is not an integer on line no : %d\n\n", cur_arr_index , line_no) ;
			parse_error = 1 ;
		}
		else if($2.temp != NULL && $2.temp -> eletype != T_INT)
		{
			printf("Array index %d (from last) is not an integer on line no : %d\n\n", cur_arr_index , line_no) ;	
			parse_error = 1 ;
		}
		$$ = (arr_list*) malloc(sizeof(arr_list)) ;
		$$ -> next = $4 ;
		$$ -> e.type = $2.type ;
		$$ -> e.temp = $2.temp ;
		$$ -> e.constant = $2.constant ;
		$$ -> e.val = $2.val ;
		$$ -> next = $4 ;
		cur_arr_index ++ ;
	}
	;

ASOP : '+' { $$ = '+' ; }
	| '-' { $$ = '-' ; }
	;
EXPR : EXPR ASOP TERM {
		$$.temp = NULL ;
		$$.constant = 0 ;
		$$.type = -1 ;
		$$.val = "" ;
		int expr_t = expr_type($1.type , $3.type) ;	
		if(expr_t == -1 || is_struct($1.type) || is_char($1.type) || is_char($3.type))
		{
			printf("Invalid operands '%s' and '%s' for \'+\' on line_no : %d\n\n", to_str_eletype($1.type) , to_str_eletype($3.type) , line_no) ;
			parse_error = 1 ;
		}
		else if(($1.temp != NULL && $1.temp -> type == ARRAY) || ($3.temp != NULL && $3.temp -> type == ARRAY))
		{
			printf("Arrays cannot be used as operands for '%c' on line no : %d .\n\n", $2 , line_no) ;
			parse_error = 1 ;
		}
		else
		{
			$$.temp =  st_new_temp(st , expr_t , cur_scope) ;
			$$.constant = 0 ;
			$$.val = "" ;
			char left[100] ;
			if($1.constant != 0)
			{
				if(is_int($1.constant) && is_float(expr_t))
				{
					symbol_table_row* new = st_new_temp(st , T_FLOAT , cur_scope) ;
					char code[100] ;
					sprintf(code , "%s = (float)%s" , new -> name , $1.val) ;
					ic = ic_add(ic , NOT_GOTO , code , -1) ;
					$1.val = new -> name ;
				}
				sprintf(left , "%s" , $1.val) ;
			}
			else
			{
				symbol_table_row* l = coerce($1.temp , expr_t) ;
				sprintf(left , "%s" , l -> name) ;
			}
			char right[100] ;
			if($3.constant != 0)
			{
				if(is_int($3.constant) && is_float(expr_t))
				{
					symbol_table_row* new = st_new_temp(st , T_FLOAT , cur_scope) ;
					char code[100] ;
					sprintf(code , "%s = (float)%s" , new -> name , $3.val) ;
					ic = ic_add(ic , NOT_GOTO , code , -1) ;
					$3.val = new -> name ;
				}
				sprintf(right , "%s" , $3.val) ;
			}
			else
			{
				symbol_table_row* r = coerce($3.temp , expr_t) ;
				sprintf(right , "%s" , r -> name) ;
			}
			char code[100] ;
			sprintf(code , "%s = %s %c %s" , $$.temp -> name , left , $2 , right) ;
			ic = ic_add(ic , NOT_GOTO , code , -1) ;
		}
		$$.type = expr_t ; 
	}
	| TERM { 
		$$.type = $1.type ; 
		$$.temp = $1.temp ;
		$$.constant = $1.constant ;
		$$.val = $1.val ;
	}
	;
MDOP : '*' { $$ = '*' ; }
	| '/' { $$ = '/' ; }
	;
TERM : TERM MDOP FACTOR { 
		$$.temp = NULL ;
		$$.constant = 0 ;
		$$.type = -1 ;
		$$.val = "" ;
		int expr_t = expr_type($1.type , $3.type) ;
		if(expr_t == -1 || is_struct($1.type) || is_char($1.type) || is_char($3.type))
		{
			printf("Invalid operands for \'%c\' on line_no : %d\n\n", $2 , line_no) ;
			parse_error = 1 ;
		}
		else if(($1.temp != NULL && $1.temp -> type == ARRAY) || ($3.temp != NULL && $3.temp -> type == ARRAY))
		{
			printf("Arrays cannot be used as operands for '%c' on line no : %d .\n\n", $2 , line_no) ;
			parse_error ;
		}
		else
		{
			$$.temp =  st_new_temp(st , expr_t , cur_scope) ;
			$$.constant = 0 ;
			$$.val = "" ;
			char left[100] ;
			if($1.constant != 0)
			{
				if(is_int($1.constant) && is_float(expr_t))
				{
					symbol_table_row* new = st_new_temp(st , T_FLOAT , cur_scope) ;
					char code[100] ;
					sprintf(code , "%s = (float)%s" , new -> name , $1.val) ;
					ic = ic_add(ic , NOT_GOTO , code , -1) ;
					$1.val = new -> name ;
				}
				sprintf(left , "%s" , $1.val) ;
			}
			else
			{
				symbol_table_row* l = coerce($1.temp , expr_t) ;
				sprintf(left , "%s" , l -> name) ;
			}
			char right[100] ;
			if($3.constant != 0)
			{
				if(is_int($3.constant) && is_float(expr_t))
				{
					symbol_table_row* new = st_new_temp(st , T_FLOAT , cur_scope) ;
					char code[100] ;
					sprintf(code , "%s = (float)%s" , new -> name , $3.val) ;
					ic = ic_add(ic , NOT_GOTO , code , -1) ;
					$3.val = new -> name ;
				}
				sprintf(right , "%s" , $3.val) ;
			}
			else
			{
				symbol_table_row* r = coerce($3.temp , expr_t) ;
				sprintf(right , "%s" , r -> name) ;
			}
			char code[100] ;
			sprintf(code , "%s = %s %c %s" , $$.temp -> name , left , $2 , right) ;
			ic = ic_add(ic , NOT_GOTO , code , -1) ;
		}
		$$.type = expr_t ;
	}
	| FACTOR { 
		$$.type = $1.type ; 
		$$.temp = $1.temp ;
		$$.constant = $1.constant ;
		$$.val = $1.val ;
	}
	;
FACTOR : '(' EXPR ')'  { 
		$$.type = $2.type ; 
		$$.temp = $2.temp ; 
		$$.constant = $2.constant ;
		$$.val = $2.val ;
	}
	| V_INT { 
		$$.type = $1.type ; 
		$$.temp = NULL ;
		$$.constant = V_INT ;
		char* val = (char*) malloc(21*sizeof(char)) ;
		sprintf(val , "%d" , $1.i_val) ;
		$$.val = val ;
	}
	| V_FLOAT { 
		$$.constant = V_FLOAT ;
		$$.type = $1.type ; 
		$$.temp = NULL ;
		char* val = (char*) malloc(21*sizeof(char)) ;
		sprintf(val , "%f" , $1.f_val) ;
		$$.val = val ;
	}
	| V_CHAR { 
		$$.constant = V_CHAR ;
		$$.type = $1.type ; 
		$$.temp = NULL ;
		char* val = (char*) malloc(2*sizeof(char)) ;
		sprintf(val , "%c" , $1.c_val) ;
		$$.val = val ;
	}
	| LVALUE {		
		$$.type = $1.type ; 
		$$.temp = $1.ptr ;
		$$.constant = 0 ;
		$$.val = $1.val ;

		if($1.ptr != NULL)
		{
			symbol_table_row* resolved = resolve($1.ptr , $1.dimlist) ;
			if($1.offset != NULL)
			{
				symbol_table_row* temp = st_new_temp_from_row(st , resolved , cur_scope) ;
				char code[100] ;		
				sprintf(code , "%s = %s[%s]" , temp -> name , get_first($1.val) , $1.offset -> name) ;
				ic = ic_add(ic , NOT_GOTO , code , -1) ;
				$$.temp = temp ;
			}
		}
	}
	;
TYPE : T_INT { $$.type = T_INT ; cur_dt = T_INT ;}
	| T_FLOAT { $$.type = T_FLOAT ; cur_dt = T_FLOAT ;}
	| T_CHAR { $$.type = T_CHAR ; cur_dt = T_CHAR ;}
	;

WHILE_STMT : WHILE M '(' BOOL_EXPR ')' {
		$<e>$.falselist = NULL ;
		if($4.temp != NULL)
		{
			char code[100] ;
			sprintf(code , "if %s == 0 goto " , $4.temp -> name) ;
			$<e>$.falselist = list_add(NULL , nextquad) ;
			ic = ic_add(ic , GOTO , code , -1) ; // we dont know where to go yet .
		}
	} BLOCK {
		char code[100] ;
		sprintf(code , "goto %d" , $2) ;
		ic = ic_add(ic , GOTO , code , $2) ;
		$$.falselist = $<e>6.falselist ;
	}
	;
IF_STMT : IF '(' BOOL_EXPR ')'  { 
		$<e>$.falselist = NULL ;
		if($3.temp != NULL)
		{
			$<e>$.falselist = list_add(NULL , nextquad) ;
			char code[100] ;
			sprintf(code , "if %s == 0 goto " , $3.temp -> name) ;
			ic = ic_add(ic , GOTO , code , -1) ;
		}
	 } BLOCK { $$.falselist = $<e>5.falselist ; }
	;
IFELSE_STMT : IF_STMT { 		
		$<e>$.truelist = list_add(NULL , nextquad) ;
		char code[100] ;
		sprintf(code , "goto ") ;
		ic = ic_add(ic , GOTO , code , -1) ;
		ic = ic_backpatch(ic , $1.falselist , nextquad) ;
	 } ELSE BLOCK { $$.truelist = $<e>2.truelist ; }
	 ;
M : { $$ = nextquad ; }
	;

RELOP : LT { $$ = LT ;}
	| GT { $$ = GT ; }
	| LTE { $$ = LTE ; }
	| GTE { $$ = GTE ; }
	| EQ { $$ = EQ ; }
	;

BOOL_EXPR : BOOL_EXPR '|' AND_EXPR {
		if($1.temp != NULL && $3.temp != NULL)
		{
			int expr_t = expr_type($1.type , $3.type) ;
			symbol_table_row* left = coerce($1.temp , expr_t) ;
			symbol_table_row* right = coerce($3.temp , expr_t) ;
			symbol_table_row* res = st_new_temp(st , T_INT , cur_scope) ;
			char code[100] ;
			sprintf(code , "%s = %s | %s" , res -> name , $1.temp -> name , $3.temp -> name) ;
			ic = ic_add(ic , NOT_GOTO , code , -1) ;
			$$.temp = res ;
			$$.type = res -> eletype ;
			$$.constant = 0 ;
			$$.val = "" ;
		}
		else
		{
			printf("Unknown  operand / operands for '|' on line no : %d\n", line_no) ;
			parse_error = 1 ;
			$$.temp = NULL ;
			$$.type = -1 ;
			$$.constant = 0 ;
			$$.val = "" ;		
		}
	}
	| AND_EXPR{
		$$.type = $1.type ;
		$$.temp = $1.temp ;
		$$.constant = $1.constant ;
		$$.val = $1.val ;
	}
	;
AND_EXPR : AND_EXPR '&' BASE {
		if($1.temp != NULL && $3.temp != NULL)
		{
			int expr_t = expr_type($1.type , $3.type) ;
			symbol_table_row* left = coerce($1.temp , expr_t) ;
			symbol_table_row* right = coerce($3.temp , expr_t) ;
			symbol_table_row* res = st_new_temp(st , T_INT , cur_scope) ;
			char code[100] ;
			sprintf(code , "%s = %s & %s" , res -> name ,  $1.temp -> name , $3.temp -> name) ;
			ic = ic_add(ic , NOT_GOTO , code , -1) ;
			$$.temp = res ;
			$$.type = res -> eletype ;
			$$.constant = 0 ;
			$$.val = "" ;
		}
		else
		{
			printf("Unknown  operand / operands for '&' on line no : %d\n", line_no) ;
			parse_error = 1 ;
			$$.temp = NULL ;
			$$.type = -1 ;
			$$.constant = 0 ;
			$$.val = "" ;
		}
	}
	| BASE{
		$$.type = $1.type ;
		$$.temp = $1.temp ;
		$$.constant = $1.constant ;
		$$.val = $1.val ;
	}
	;

BASE : EXPR RELOP EXPR {
		$$.temp = NULL ;
		$$.constant = 0 ;
		$$.type = -1 ;
		$$.val = "" ;
		int expr_t = expr_type($1.type , $3.type) ;
		if(expr_t == -1 || is_struct($1.type) || is_char($1.type) || is_char($3.type))
		{
			printf("Invalid operands for \'%s\' on line_no : %d\n\n", relop_to_str($2) , line_no) ;
			parse_error = 1 ;
		}
		else if(($1.temp != NULL && $1.temp -> type == ARRAY) || ($3.temp != NULL && $3.temp -> type == ARRAY))
		{
			printf("Arrays cannot be used as operands for '%s' on line no : %d .\n\n", relop_to_str($2) , line_no) ;
			parse_error = 1 ;
		}
		else
		{
			$$.temp =  st_new_temp(st , expr_t , cur_scope) ;
			$$.constant = 0 ;
			$$.val = "" ;
			char left[100] ;
			if($1.constant != 0)
			{
				if(is_int($1.constant) && is_float(expr_t))
				{
					symbol_table_row* new = st_new_temp(st , T_FLOAT , cur_scope) ;
					char code[100] ;
					sprintf(code , "%s = (float)%s" , new -> name , $1.val) ;
					ic = ic_add(ic , NOT_GOTO , code , -1) ;
					$1.val = new -> name ;
				}
				sprintf(left , "%s" , $1.val) ;
			}
			else
			{
				symbol_table_row* l = coerce($1.temp , expr_t) ;
				sprintf(left , "%s" , l -> name) ;
			}
			char right[100] ;
			if($3.constant != 0)
			{
				if(is_int($3.constant) && is_float(expr_t))
				{
					symbol_table_row* new = st_new_temp(st , T_FLOAT , cur_scope) ;
					char code[100] ;
					sprintf(code , "%s = (float)%s" , new -> name , $3.val) ;
					ic = ic_add(ic , NOT_GOTO , code , -1) ;
					$3.val = new -> name ;
				}
				sprintf(right , "%s" , $3.val) ;
			}
			else
			{
				symbol_table_row* r = coerce($3.temp , expr_t) ;
				sprintf(right , "%s" , r -> name) ;
			}
			char code[100] ;
			sprintf(code , "%s = %s %s %s" , $$.temp -> name , left , relop_to_str($2) , right) ;
			ic = ic_add(ic , NOT_GOTO , code , -1) ;
		}
		$$.type = expr_t ;
	}
	;
%%

symbol_table_row* resolve(symbol_table_row* str , list* dimlist)
{	
	if(str == NULL)
		return NULL ;
	symbol_table_row* dup = (symbol_table_row*)	 malloc(sizeof(symbol_table_row)) ;
	dup -> type = str -> type ;
	dup -> eletype = str -> eletype ;
	dup -> next = NULL ;
	dup -> dimlist = str -> dimlist ;
	dup -> name = str -> name ;
	if(list_length(dimlist) == list_length(str -> dimlist))
	{
		dup -> dimlist = NULL ;
		if(is_struct(dup -> eletype))
			dup -> type = STRUCT_T ;
		else
			dup -> type = SIMPLE ;
		return dup ;
	}
	while(dimlist != NULL && dup -> dimlist != NULL)
	{
		dimlist = dimlist -> next ;
		dup -> dimlist = dup -> dimlist -> next ;
	}
	return dup ;
}
char* datatype_to_string(symbol_table_row* str)
{	
	if(str == NULL)
		return "(unknown)" ;
	char* res = (char*) malloc(100*sizeof(char)) ;
	memset(res , 0 , 100*sizeof(char)) ;
	if(str -> type == SIMPLE || str -> type == ARRAY)
	{
		if(str -> eletype == T_INT)
			res = strcat2(res , "int") ;
		if(str -> eletype == T_FLOAT)
			res = strcat2(res , "float") ;
		if(str -> eletype == T_CHAR)
			res = strcat2(res , "char") ;
		list* cur = str -> dimlist ;
		while(cur != NULL)
		{
			res = strcat2(res , "[]") ;
			cur = cur -> next ;
		}
	}
	else
	{
		struct_def_row* ret = sdf_find_row(sdf , str -> eletype) ;		
		res = strcat2(res , "struct ") ;
		res = strcat2(res , ret -> name) ;		
		list* cur = str -> dimlist ;
		while(cur != NULL)
		{
			res = strcat2(res , "[]") ;
			cur = cur -> next ;
		}
	}
	return res ;
}

int arr_length(arr_list* al)
{
	int len = 0 ;
	while(al != NULL)
	{
		len++ ;
		al = al -> next ;
	}
	return len ;
}

int arr_get_int(arr_list* al)
{
	if(al -> e.constant == 0)
		return -1 ;
	return atoi(al -> e.val) ;
}

list* arr_to_list(arr_list* al)
{
	list* ret = NULL ;
	while(al != NULL)
	{		
		ret = list_add(ret , arr_get_int(al)) ;
		al = al -> next ;
	}
	return list_reverse(ret) ;
}

symbol_table_row* sdf_offset(struct_def* sdf , int eletype , char* name) // offset of element eletype within the structure . (reverse from actual order)
{
	struct_def_row* sdfr = sdf_find_row(sdf , eletype) ;
	if(sdfr == NULL)
		return NULL ;
	symbol_table_row* cur = sdfr -> st -> list ;
	symbol_table_row* offset = NULL ;
	while(cur != NULL)
	{
		if(strcmp(cur -> name , name) == 0)
		{
			if(offset == NULL)
			{
				char code[100] ;
				symbol_table_row* temp = st_new_temp(st , T_INT , cur_scope) ;
				sprintf(code , "%s = 0" , temp -> name) ;
				ic = ic_add(ic , NOT_GOTO , code , -1) ;
				return temp ;
			}
			return offset ;
		}
		int size = get_size(cur -> eletype) ;
		if(cur -> dimlist != NULL)
		{
			int ttt = 1 ;
			list* d = cur -> dimlist ;
			while(d != NULL)
			{
				ttt *= d -> val ;
				d = d -> next ;
			}
			size = size * ttt ;
		}
		if(offset == NULL)
		{
			offset = st_new_temp(st , T_INT , cur_scope) ;
			char code[100] ;
			sprintf(code , "%s = %d" , offset -> name , size) ;
			ic = ic_add(ic , NOT_GOTO , code , -1) ;
		}
		else
		{
			symbol_table_row* temp = st_new_temp(st , T_INT , cur_scope) ;
			char code[100] ;
			sprintf(code , "%s = %s + %d" , temp -> name , offset -> name , size) ;
			offset = temp ;
			ic = ic_add(ic , NOT_GOTO , code , -1) ;
		}
		cur = cur -> next ;
	}
	return NULL ;
}

int sdf_struct_size(struct_def* sdf , int ind)
{
	struct_def_row* sdfr = sdf_find_row(sdf , ind) ;
	if(sdfr == NULL)
		return 0 ;
	symbol_table_row* cur = sdfr -> st -> list ;
	int size = 0 ;
	while(cur != NULL)
	{
		int cur_size = 0 ;
		if(cur -> eletype == T_INT)
			cur_size = 4 ;
		else if(cur -> eletype == T_FLOAT)
			cur_size = 8 ;
		else if(cur -> eletype == T_CHAR)
			cur_size = 2 ;
		else
			cur_size = sdf_struct_size(sdf , cur -> eletype) ;
		if(cur -> dimlist != NULL)
		{
			int arr_size = 1 ;
			list* dims = cur -> dimlist ;
			while(dims != NULL)
			{
				arr_size = arr_size*dims -> val ;
				dims = dims -> next ;
			}
			cur_size = cur_size*arr_size ;
		}
		size += cur_size ;
		cur = cur -> next ;
	}
	return size ;
}

symbol_table_row* add_offsets(symbol_table_row* o1 , symbol_table_row* o2)
{
	if(o1 == NULL && o2 == NULL)
		return NULL ;
	else if(o1 != NULL && o2 != NULL)
	{
		symbol_table_row* res = st_new_temp(st , T_INT , cur_scope) ;
		char code[100] ;
		sprintf(code , "%s = %s + %s" , res -> name , o1 -> name , o2 -> name) ;
		ic = ic_add(ic , NOT_GOTO , code , -1) ;
		return res ;
	}
	else if(o1 != NULL)
		return o1 ;
	return o2 ;
}

symbol_table_row* calculate_offset(arr_list* al , list* dimlist , int size) // dimlist is the dimension list of the declaration !
{	
	if(arr_length(al) > list_length(dimlist))
		return NULL ;
	if(dimlist == NULL || al == NULL)
		return NULL ;
	dimlist = dimlist -> next ;
	arr_list* i1 = al ;
	arr_list* i2 = al -> next ;	
	symbol_table_row* res = NULL ;
	while(i2 != NULL && dimlist != NULL)
	{
		symbol_table_row* t1 = st_new_temp(st , T_INT , cur_scope) ;
		char code[100] ;
		if(i1 -> e.constant == 0 )
			sprintf(code , "%s = %s * %d" , t1 -> name , i1 -> e.temp -> name , dimlist -> val) ; // t1 = i1*n2
		else
			sprintf(code , "%s = %s * %d" , t1 -> name , i1 -> e.val , dimlist -> val) ; // t1 = i1*n2
		ic = ic_add(ic , NOT_GOTO , code , -1) ;

		symbol_table_row* t2 = st_new_temp(st , T_INT , cur_scope) ;
		if(i2 -> e.constant == 0 )
			sprintf(code , "%s = %s + %s" , t2 -> name , t1 -> name , i2-> e.temp -> name) ; // t2 = t1 + i2
		else		
			sprintf(code , "%s = %s + %s" , t2 -> name , t1 -> name ,  i2 -> e.val) ; // t2 = t1 + i2
		ic = ic_add(ic , NOT_GOTO , code , -1) ;
		res = t2 ;

		arr_list* next = (arr_list*) malloc(sizeof(arr_list)) ;
		next -> e.temp = t2 ;
		next -> e.constant = 0 ;
		next -> e.val = "" ;
		next -> next = NULL ;

		i1 = next ;
		i2 = i2 -> next ;
		dimlist = dimlist -> next ;
	}
	int s = 1 ;
	while(dimlist != NULL)
	{
		s *= dimlist -> val ;
		dimlist = dimlist -> next ;
	}
	size *= s ;
	if(res == NULL)
	{
		res = i1 -> e.temp ;	
		symbol_table_row* t3 = st_new_temp(st , T_INT , cur_scope) ;
		char code[100] ;
		if(i1 -> e.constant == 0)
			sprintf(code , "%s = %s*%d" , t3 -> name , res -> name , size) ;
		else
			sprintf(code , "%s = %s*%d" , t3 -> name , i1 -> e.val , size) ;
		ic = ic_add(ic , NOT_GOTO , code , -1) ;
		res = t3 ;
	}
	else
	{
		char code[100] ;
		symbol_table_row* t3 = st_new_temp(st , T_INT , cur_scope) ;
		sprintf(code , "%s = %s*%d" , t3 -> name , res -> name , size) ;
		ic = ic_add(ic , NOT_GOTO , code , -1) ;
		res = t3 ;
	}
	return res ;
}

int get_size(int eletype)
{
	int size ;
	if(eletype == T_INT)
		size = 4 ;
	else if(eletype == T_FLOAT)
		size = 8 ;
	else if(eletype == T_CHAR)
		size = 2 ;
	else
		size = sdf_struct_size(sdf , eletype) ;
	return size ;
}

symbol_table_row* coerce(symbol_table_row* cur , int to_type)
{
	if(is_struct(to_type) || is_struct(cur -> eletype) || to_type == T_CHAR)
		return cur ; // cant coerce if to_type is struct .
	if(cur -> eletype == to_type)
		return cur ;
	if(cur -> eletype == T_INT && to_type == T_FLOAT)
	{
		symbol_table_row* new = st_new_temp(st , T_FLOAT , cur_scope) ;
		char code[100] ;
		sprintf(code , "%s = (float)%s" , new -> name , cur -> name) ;
		ic = ic_add(ic , NOT_GOTO , code , -1) ;
		return new ;
	}
}

char* type_map(int type)
{
	switch(type)
	{
		case T_INT:
			return "T_TINT" ;
		case T_FLOAT:
			return "T_FLOAT" ;
		case T_CHAR:
			return "T_CHAR" ;
		case V_INT:
			return "V_INT" ;
		case V_FLOAT:
			return "V_FLOAT" ;
		case V_CHAR :
			return "V_CHAR" ;
		default:
			return "struct" ;
	}
}

int equal_types(int t1 , int t2)
{
	if(is_char(t1) && is_char(t2))
		return 1 ;
	else if(is_int(t1) && is_int(t2))
		return 1 ;
	else if(is_float(t1) && is_float(t2))
		return 1 ;
	else if(t1 != -1 && t2 != -1)
		return t1 == t2 ;
	return 0 ;
}

char* relop_to_str(int type)
{
	if(type == LT)
		return "<" ;
	if(type == GT)
		return ">" ;
	if(type == LTE)
		return "<=" ;
	if(type == GTE)
		return ">=" ;
	if(type == EQ)
		return "==" ;
	return "(unknown)" ;
}