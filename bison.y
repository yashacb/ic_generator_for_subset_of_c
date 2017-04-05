%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "scope.c"
#include "mystring.c"
int st_find_lvalue(symbol_table* st , struct_def* sdf , char* lvalue , int scope) ;

symbol_table* st = NULL ;
struct_def* sdf = NULL ;
scope_stack* sstk = NULL ;
scope_map* sm = NULL ;

int line_no = 1 ;
int cur_scope = 0 ;
int cur_dt = 0 ;

void yyerror (char const *s)
{
	printf("Parse error on line no. %d : %s\n" , line_no , s) ;
}

// Union types
typedef struct decl{
	int type ;
}decl ;

typedef struct id{
	int type ;
	char* val ;
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
%type <d> VAR_LIST
%type <d> VAR
%type <l> DIM_LIST
%type <c> ASG
%type <i> LVALUE
%type <c> EXPR

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
	| ID {
		if(st_find_strict(st , $1.val , cur_scope) != NULL)
		{
			printf("Semantic error : Redeclaration of variable %s on line no : %d\n" , $1.val , line_no) ;
			exit(0) ;
		}
		int ind = sdf_find(sdf , $<i>0.val) ; // This index is from the last !!
		if(ind != -1)
			st_add(st , $1.val , cur_dt , ind , NULL , cur_scope) ;
		else
		{
			printf("Seamntic error : Unknown type : \" struct %s \" on line no : %d\n", $<i>0.val , line_no) ;
			exit(0) ;
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
VAR : ID {
		if(st_find_strict(st , $1.val , cur_scope) != NULL)
		{
			printf("Semantic error : Redeclaration of variable %s in scope id : %d\n" , $1.val , cur_scope) ;
			exit(0) ;
		}
		st_add(st , $1.val , SIMPLE , $1.type , NULL , cur_scope) ;
		$$.type = $1.type ;
	}
	| ID DIM_LIST{
		if(st_find_strict(st , $1.val , cur_scope) != NULL)
		{
			printf("Semantic error : Redeclaration of variable %s in scope id : %d\n" , $1.val , cur_scope) ;
			exit(0) ;
		}
		st_add(st , $1.val , ARRAY , $1.type , list_reverse($2) , cur_scope) ;
	}
	;
DIM_LIST : '[' V_INT ']' {
		$$ = list_add(NULL , $2.i_val) ;
	}
	| DIM_LIST '[' V_INT ']' {
		$$ = list_add($1 , $3.i_val) ;
	}
	; 
ASG : LVALUE {
		char* dup = dupstr($1.val) ;
		if(st_find_lvalue(st , sdf , dup , cur_scope) == 0)
		{
			printf("Semantic error : Unable to resolve lvalue : %s on line no : %d .\n", $1.val , line_no) ;
			exit(0) ;
		}
	} '=' EXPR ';' { $$.type = $1.type ;}
	;
LVALUE : LVALUE '.' ID{
		$$.type = $3.type ;
		char* temp = strcat2($1.val , ".") ;
		$$.val = strcat2(temp , $3.val) ;
	}
	| ID { $$.type = $1.type ; 
		$$.val = dupstr($1.val) ;
	 }
	;
EXPR : V_INT
	| V_FLOAT
	| V_CHAR
	;
%%
 // check if lvalue can be formed from the symbol table and struct table. This function modifies lvalue. 
int st_find_lvalue(symbol_table* st , struct_def* sdf , char* lvalue , int scope)
{
	char* token = strtok(lvalue , ".") ;
	symbol_table* cur = st ;
	while(token != NULL)
	{
		symbol_table_row* row = st_find(cur , token , scope) ;
		if(row == NULL)
			return 0 ;
		else
		{
			token = strtok(NULL , ".") ;
			if(row -> type != T_STRUCT)
				break ;
			cur = sdf_find_row(sdf , row -> eletype) ;
		}
	}
	if(token == NULL)
		return 1 ;
	return 0 ;
}