%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "func.c"
#include "mystring.c"

symbol_table_row* resolve(symbol_table_row* str , list* dimlist) ;
char* datatype_to_string(symbol_table_row* str) ;

int expr_type(int t1 , int t2) ;
int is_int(int t) ;
int is_array(int t) ;
int is_struct(int t) ;

func_table* ft = NULL ;
symbol_table* st = NULL ;
struct_def* sdf = NULL ;
scope_stack* sstk = NULL ;
scope_map* sm = NULL ;
int ind_dim = 0 ;

int line_no = 1 ;
int cur_scope = 0 ;
int cur_dt = 0 ;
int sdt ;
func_table_row* cur_func_ptr = NULL ; // the functions which is being defiend 
func_table_row* call_func_ptr = NULL ; // the functions which is being called

char* to_str_eletype(int type) ;

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

typedef struct id{
	int type ;
	char* val ;
	symbol_table_row* ptr ;
	symbol_table* st ;
	list* dimlist ; // this is used in lvalue .
}id ;

typedef struct expr{
	int type ;
}expr ;

typedef struct constant{
	int type ;
	int i_val ;
	float f_val ;
	char c_val ;
} constant;
//

%}

%union{
	decl d ;
	expr e ;
	constant c ;
	id i ;
	list* l ;
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

%type <d> TYPE
%type <d> DECL_LIST
%type <d> DECL
%type <d> SVAR_LIST
%type <d> VAR_LIST
%type <d> VAR
%type <d> VAR_CHECK
%type <d> SVAR_CHECK
%type <l> DIM_LIST
%type <l> ARR_LIST
%type <c> ASG
%type <i> LVALUE
%type <i> LVALUE_CHECK
%type <e> EXPR
%type <e> TERM
%type <e> FACTOR
%type <f> FUNC_DEF
%type <f> FUNC_CALL
%type <np> PARAM_LIST
%type <np> ARG_LIST

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
		sstk_push(sstk , cur_scope) ;
		cur_scope = sm_get_scope() ;
		sm = sm_add(sm , cur_scope , st) ;
		st = sm_find(sm , cur_scope) ;
	} '(' PARAM_LIST ')' {
		cur_func_ptr -> param_list = st_new() ;
		cur_func_ptr -> param_list -> list = st -> list ;		
		cur_func_ptr -> num_param = $5 ;
	} '{' STMTS '}' { 
		cur_func_ptr -> local_list = st ;
		cur_scope = sstk_pop(sstk) ;
		st = sm_find(sm , cur_scope) ;
		cur_func_ptr = NULL ;
		$$ = NULL ; }
	;
PARAM_LIST : TYPE VAR {
		$2.ptr -> eletype = $1.type ;
	} ',' PARAM_LIST { $$ = 1 +  $5 ; }
	| TYPE VAR {
		$2.ptr -> eletype = $1.type ;
		$$ = 1 ;
	}
	| T_STRUCT ID ID SVAR_CHECK ARR_LIST { 
		$$ = 1 ; 
		st_add(st , $3.val , STRUCT_T , $4.type , $5 , cur_scope) ;
	}
	| T_STRUCT ID ID SVAR_CHECK ARR_LIST  ',' PARAM_LIST { 
		$$ = 1 + $7 ; 
		st_add(st , $3.val , STRUCT_T , $4.type , $5 , cur_scope) ;
	}
	| { $$ = 0 ; }
	;
FUNC_CALL : ID { 
		call_func_ptr = ft_find(ft , $1.val) ;		
		if(call_func_ptr == NULL)
		{
			printf("Unknown function '%s' on line_no : %d .\n", $1.val , line_no) ;
		}
	}'(' ARG_LIST ')' ';' { $$ = NULL ;}
	;
ARG_LIST : ARG_LIST ',' LVALUE { 
		$$ = $1 + 1 ; 
		if(call_func_ptr != NULL)
		{
			int num_param = call_func_ptr -> num_param ;
			symbol_table_row* expected = ft_get_param(call_func_ptr , num_param - 1 - $$) ;
			symbol_table_row* found = resolve($3.ptr , $3.dimlist) ;
			if(st_compare(expected , found) != 1)
			{
				printf("Incorrect argument %d for function '%s' on line no : %d .\n", $$ , call_func_ptr -> name , line_no) ;
				printf("Expected %s , but found %s\n" , datatype_to_string(expected) , datatype_to_string(found)) ;
			}
		}
	}
	| LVALUE  { 
		$$ = 0 ; 
		if(call_func_ptr != NULL)
		{
			int num_param = call_func_ptr -> num_param ;
			symbol_table_row* expected = ft_get_param(call_func_ptr , num_param - 1 - $$) ;
			symbol_table_row* found = resolve($1.ptr , $1.dimlist) ;
			if(st_compare(expected , found) != 1)
			{
				printf("Incorrect argument type for function '%s' on line no : %d\n", call_func_ptr -> name , line_no) ;
				printf("Expected %s , but found %s\n\n" , datatype_to_string(expected) , datatype_to_string(found)) ;
			}
		}
	}
	;

STMTS : DECL STMTS
	| '{' { sstk_push(sstk , cur_scope) ;
		cur_scope = sm_get_scope() ;
		sm = sm_add(sm , cur_scope , st) ;
		st = sm_find(sm , cur_scope) ;
	} STMTS '}' { cur_scope = sstk_pop(sstk) ; 
		st = sm_find(sm , cur_scope) ;
	} STMTS
	| ASG STMTS
	| FUNC_CALL STMTS
	|
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
			st_add(st , $1.val , STRUCT_T , $2.type , $3 , cur_scope) ;
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
			}
			$$.type = ind ;
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
		int expr_t = expr_type($1.type , $3.type) ;
		if(expr_t == -1)
		{
			printf("Assignment of incompatible types on line no : %d .\n", line_no) ;
			printf("Assigning '%s' to '%s' \n\n", datatype_to_string(resolve($1.ptr , $1.dimlist)) 
				, to_str_eletype($3.type)) ;
		}
		$$.type = $1.type ; 
	}
	;
LVALUE : ID  ARR_LIST { $<i>$.st = st ; } LVALUE_CHECK {
		$$.type = $4.type ;
		$$.ptr = $4.ptr ;
		$$.st = $4.st ;
		$$.val = $4.val ;
		$$.dimlist = $2 ;
		$$.val = (char*) malloc(30*sizeof(30)) ;
		$$.val = strcat2($$.val , $1.val) ;
		list* cur = $2 ;
		while(cur != NULL)
		{
			cur = cur -> next ;
			$$.val = strcat2($$.val , "[]") ;
		}
	}
	| LVALUE '.' ID ARR_LIST { $<i>$.st = $1.st ; } LVALUE_CHECK {		
		$$.type = $6.type ;
		$$.ptr = $6.ptr ;
		$$.st = $6.st ;		
		$$.val = dupstr($1.val) ;
		$$.val = strcat2($$.val , ".") ;
		$$.val = strcat2($$.val , $3.val) ;
		list* cur = $4 ;
		while(cur != NULL)
		{
			cur = cur -> next ;
			$$.val = strcat2($$.val , "[]") ;
		}
		$$.dimlist = $4 ;
		if(list_length($1.dimlist) < list_length($1.ptr -> dimlist))
		{
			printf("Cannot de-reference a non-struct type '%s' on line no : %d\n", $1.val , line_no) ;
			$$.type = -1 ;
		}
	}
	;
LVALUE_CHECK : {
		char* val = $<i>-2.val ;
		list* cur = $<l>-1 ;
		symbol_table* cur_st = $<i>0.st ;
		symbol_table_row* res = st_find(cur_st , val , cur_scope) ;
		if(res == NULL)
		{
			$$.type = -1 ;
		}
		else
		{
			list* dimlist = res -> dimlist ;
			if(list_length(cur) > list_length(dimlist))
			{
				printf("Number of dimensions exceeded for '%s' on line no : %d .\n", val , line_no) ;
				printf("Declared dimensions : %d . Found dimensions : %d\n\n", list_length(dimlist) , list_length(cur)) ;
			}
			while(cur != NULL && dimlist != NULL)
			{
				if(cur -> val != -1)
				{
					if(cur -> val >= dimlist -> val)
					{
						printf("Array index out of bounds for '%s' on line no : %d . \n", val , line_no) ;
						printf("Actual size : %d . Found index : %d\n\n", dimlist -> val , cur -> val) ;
					}
				}
				cur = cur -> next ;
				dimlist = dimlist -> next ;
			}
		}
		$$.ptr = res ;
		$$.val = val ;
		$$.type = res != NULL ? res -> eletype : -1 ;
		if(res != NULL && res -> type == STRUCT_T)
			$$.st = sdf_find_row(sdf , res -> eletype) -> st ;
		else
			$$.st = NULL ;
	}
	;
ARR_LIST : { $$ = NULL ; }
	| '[' V_INT ']' ARR_LIST { 
		if($2.i_val < 0) 
		{
			printf("Array index out of bounds on line no : %d\n", line_no) ;
			exit(0) ;
		}
		$$ = list_add($4 , $2.i_val) ;
	}
	| '[' LVALUE  ']' ARR_LIST {
		if($2.ptr -> eletype != T_INT)
		{
			printf("Array index is not an integer on line no : %d\n", line_no) ;
			exit(0) ;
		}
		$$ = list_add($4 , -1) ;		
	}
	;
EXPR : EXPR '+' TERM { 
		int expr_t = expr_type($1.type , $3.type) ;
		if(expr_t == -1 || is_struct($1.type))
		{
			printf("Invalid operands for \'+\' on line_no : %d\n", line_no) ;
			exit(0) ;
		}
		$$.type = expr_t ; 
	}
	| EXPR '-' TERM{ 
		int expr_t = expr_type($1.type , $3.type) ;
		if(expr_t == -1 || is_struct($1.type))
		{
			printf("Invalid operands for \'-\' on line_no : %d\n", line_no) ;
			exit(0) ;
		}
		$$.type = expr_t ; 
	}
	| TERM { $$.type = $1.type ; }
	;
TERM : TERM '*' FACTOR { 
		int expr_t = expr_type($1.type , $3.type) ;
		if(expr_t == -1 || is_struct($1.type))
		{
			printf("Invalid operands for \'*\' on line_no : %d\n", line_no) ;
			exit(0) ;
		}
		$$.type = expr_t ; 
	}
	| TERM '/' FACTOR { 
		int expr_t = expr_type($1.type , $3.type) ;
		if(expr_t == -1 || is_struct($1.type))
		{
			printf("Invalid operands for \'/\' on line_no : %d\n", line_no) ;
			exit(0) ;
		}
		$$.type = expr_t ; 
	}
	| FACTOR { $$.type = $1.type ; }
	;
FACTOR : '(' EXPR ')' { $$.type = $2.type ; }
	| V_INT { $$.type = $1.type ; }
	| V_FLOAT { $$.type = $1.type ; }
	| V_CHAR { $$.type = $1.type ; }
	| LVALUE {$$.type = $1.type ; }
	;

TYPE : T_INT { $$.type = T_INT ; cur_dt = T_INT ;}
	| T_FLOAT { $$.type = T_FLOAT ; cur_dt = T_FLOAT ;}
	| T_CHAR { $$.type = T_CHAR ; cur_dt = T_CHAR ;}
	;

%%

symbol_table_row* resolve(symbol_table_row* str , list* dimlist)
{	
	symbol_table_row* dup = (symbol_table_row*)	 malloc(sizeof(symbol_table_row)) ;
	dup -> type = str -> type ;
	dup -> eletype = str -> eletype ;
	dup -> next = NULL ;
	dup -> dimlist = str -> dimlist ;
	dup -> name = str -> name ;
	if(list_length(dimlist) == list_length(str -> dimlist))
	{
		dup -> dimlist = NULL ;
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