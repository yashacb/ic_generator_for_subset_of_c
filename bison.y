%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "scope.c"

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
	int val ;
}expr ;
//

%}

%union{
	decl d ;
	expr e ;
	id i ;
	list* l ;
}

%define parse.error verbose

%token <d> T_INT
%token <d> T_FLOAT
%token <d> T_CHAR
%token <d> T_STRUCT
%token <i> ID
%token <e> NUM

%type <d> DECL_LIST
%type <d> DECL
%type <d> VAR_LIST
%type <d> VAR
%type <l> DIM_LIST

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
			printf("Semantic error : Redeclaration of variable %s in scope id : %d\n" , $1.val , cur_scope) ;
			exit(0) ;
		}
		st_add(st , $1.val , cur_dt , -1 , NULL , cur_scope) ;
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
DIM_LIST : '[' NUM ']' {
		$$ = list_add(NULL , $2.val) ;
	}
	| DIM_LIST '[' NUM ']' {
		$$ = list_add($1 , $3.val) ;
	}
	; 
%%

