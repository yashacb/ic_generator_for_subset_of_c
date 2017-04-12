%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "scope.c"
#include "mystring.c"
symbol_table_row* st_find_lvalue(symbol_table* st , struct_def* sdf , char* lvalue , int scope) ;
int expr_type(int t1 , int t2) ;
int is_int(int t) ;
int is_array(int t) ;
int is_struct(int t) ;

symbol_table* st = NULL ;
struct_def* sdf = NULL ;
scope_stack* sstk = NULL ;
scope_map* sm = NULL ;
symbol_table_row* cur_lval = NULL ;
int ind_dim = 0 ;

int line_no = 1 ;
int cur_scope = 0 ;
int cur_dt = 0 ;
int sdt ;

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
}

%define parse.error verbose

%token <d> T_INT
%token <d> T_FLOAT
%token <d> T_CHAR
%token <d> T_STRUCT
%token <i> ID
%token <c> V_INT
%token <c> V_FLOAT
%token <c> V_CHAR

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

%start STMTS

%%

STMTS : DECL STMTS
	| '{' { sstk_push(sstk , cur_scope) ;
		cur_scope = sm_get_scope() ;
		sm = sm_add(sm , cur_scope , st) ;
		st = sm_find(sm , cur_scope) ;
	} STMTS '}' { cur_scope = sstk_pop(sstk) ; 
		st = sm_find(sm , cur_scope) ;
	} STMTS
	| ASG STMTS
	|
	;
DECL_LIST :  DECL_LIST DECL
		| DECL
		;
DECL :   T_INT { cur_dt = T_INT ;} VAR_LIST ';'
	| T_FLOAT { cur_dt = T_FLOAT ;} VAR_LIST ';'
	| T_CHAR { cur_dt = T_CHAR ;} VAR_LIST ';'
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
		st_add(st , $1.val , STRUCT_T , $2.type , $3 , cur_scope) ;
	}
	| SVAR_LIST ',' ID VAR_CHECK  { 
		$$.type = $1.type ; 
		st_add(st , $3.val , STRUCT_T , $1.type , NULL , cur_scope) ;
	}
	;
SVAR_CHECK : {
		if(st_find_strict(st , $<i>0.val , cur_scope) != NULL)
		{
			printf("Redeclaration of variable %s on line no : %d\n" , $<i>0.val , line_no) ;
			exit(0) ;
		}
		int ind = sdf_find(sdf , $<i>-1.val) ; // This index is from the last !!
		if(ind != -1)
			; // :p
		else
		{
			printf("Cannot resolve type of variable %s on line no : %d\n" , $<i>0.val , line_no) ;
			exit(0) ;
		}
		$$.type = ind ;
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
		st_add(st , $1.val , SIMPLE , $1.type , NULL , cur_scope) ;
	}
	| ID VAR_CHECK DIM_LIST { 
		$$.type = $1.type ; 
		st_add(st , $1.val , ARRAY , $1.type , list_reverse($3) , cur_scope) ;
	}
	;
VAR_CHECK : 
	{
		if(st_find_strict(st , $<i>0.val , cur_scope) != NULL)
		{
			printf("Redeclaration of variable %s in scope id : %d\n" , $<i>0.val , cur_scope) ;
			exit(0) ;
		}
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
			printf(" Assignment of incompatible types on line no : %d .\n", line_no) ;
			exit(0) ;
		}
		$$.type = $1.type ; 
	}
	;
LVALUE : ID  ARR_LIST { $<i>$.st = st ; } LVALUE_CHECK {
		$$.type = $4.type ;
		$$.ptr = $4.ptr ;
		$$.st = $4.st ;
		$$.val = $4.val ;
	}
	| LVALUE '.' ID ARR_LIST { $<i>$.st = $1.st ; } LVALUE_CHECK {
		$$.ptr = $6.ptr ;
		$$.st = $6.st ;
		$$.val = $6.val ;
		$$.type = $6.type ;
	}
	;
LVALUE_CHECK : {
		char* val = $<i>-2.val ;
		list* cur = $<l>-1 ;
		symbol_table* cur_st = $<i>0.st ;
		symbol_table_row* res = st_find(cur_st , val , cur_scope) ;
		// Error checking can be improved .
		if(res == NULL)
		{
			printf("%s not found in current scope on line no : %d\n", val , cur_scope) ;
			exit(0) ;
		}
		list* dimlist = res -> dimlist ;
		if(list_length(cur) < list_length(dimlist))
		{
			printf("Incorrect dimensions of %s on line no : %d\n", val , line_no) ;
			exit(0) ;
		}
		if(list_length(cur) > list_length(dimlist))
		{
			printf("Incorrect dimensions of %s on line no : %d\n", val , line_no) ;
			exit(0) ;
		}
		while(cur != NULL && dimlist != NULL)
		{
			if(cur -> val != -1)
			{
				if(cur -> val >= dimlist -> val)
				{
					printf("Array index out of bounds for %s on line no : %d\n", val , line_no) ;
					exit(0) ;
				}
			}
			cur = cur -> next ;
			dimlist = dimlist -> next ;
		}
		$$.ptr = res ;
		$$.val = val ;
		$$.type = res -> eletype ;
		if(res -> type == STRUCT_T)
			$$.st = sdf_find_row(sdf , res -> eletype) ;
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
%%

// check if lvalue can be formed from the symbol table and struct table. This function modifies lvalue. 
symbol_table_row* st_find_lvalue(symbol_table* st , struct_def* sdf , char* lvalue , int scope)
{
	char* token = strtok(lvalue , ".") ;
	symbol_table* cur = st ;
	symbol_table_row* row = NULL ;
	while(token != NULL)
	{
		row = st_find(cur , token , scope) ;
		if(row == NULL)
			return row ;
		else
		{
			token = strtok(NULL , ".") ;
			if(row -> type != STRUCT_T)
				break ;
			cur = sdf_find_row(sdf , row -> eletype) ;
		}
	}
	if(token == NULL)
		return row ;
	return NULL ;
}