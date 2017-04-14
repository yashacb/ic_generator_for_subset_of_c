%{
int yylex(void) ;

#include "bison.tab.c"

%}
id [a-zA-Z][a-zA-Z0-9_]*

%%

"int" 	{
		// printf("Lex : Int detected\n") ; 
		yylval.d.type = T_INT ;
		return T_INT ;
		}
"float" {
		// printf("Lex : Float detected\n") ; 
		yylval.d.type = T_FLOAT ;
		return T_FLOAT ;
		}
"char" {
		// printf("Lex : Char detected\n") ; 
		yylval.d.type = T_CHAR ;
		return T_CHAR ;
		}
"struct" {
		// printf("Lex : Struct detected\n") ; 
		yylval.d.type = T_STRUCT ;
		return T_STRUCT ;
		}
"," 	{
		// printf("Lex : , detected\n") ; 
		return ',' ; 
		}
";" 	{
		// printf("Lex : ; detected\n") ; 
		return ';' ; 
		}
"[" 	{
		// printf("Lex : [ detected\n") ; 
		return '[' ; 
		}
"]" 	{
		// printf("Lex : ] detected\n") ; 
		return ']' ; 
		}
"(" 	{
		// printf("Lex : () detected\n") ; 
		return '(' ; 
		}
")" 	{
		// printf("Lex : ) detected\n") ; 
		return ')' ; 
		}
"{" 	{
		// printf("Lex : { detected\n") ; 
		return '{' ; 
		}
"}" 	{
		// printf("Lex : } detected\n") ; 
		return '}' ; 
		}
"=" 	{
		// printf("Lex : = detected\n") ; 
		return '=' ; 
		}
"*" 	{
		// printf("Lex : * detected\n") ; 
		return '*' ; 
		}
"+" 	{
		// printf("Lex : * detected\n") ; 
		return '+' ; 
		}
"/" 	{
		// printf("Lex : * detected\n") ; 
		return '/' ; 
		}
"-" 	{
		// printf("Lex : * detected\n") ; 
		return '-' ; 		
		}
{id}	{
		char* copy = (char*) malloc(sizeof(strlen(yytext) + 1)) ;
		strcpy(copy , yytext) ;
		yylval.i.val = copy ;
		yylval.i.type = cur_dt ;
		// printf("Lex : %s detected\n" , yytext) ; 
		return ID ;
		}
[0-9]*"."[0-9]+ {
			yylval.c.type = V_INT ;
			yylval.c.f_val = atof(yytext) ;
			return V_FLOAT ;
	   }		
[0-9]+ {
			yylval.c.type = V_INT ;
			yylval.c.i_val = atoi(yytext) ;
			return V_INT ;
	   }
"'"[a-zA-Z0-9_]"'" {
			yylval.c.type = V_CHAR ;
			yylval.c.c_val = yytext[1] ;
			return V_CHAR ;
		}
"." 	{
		// printf("Lex : . detected\n") ; 
		return '.' ; 
		}
"\n"    { line_no++ ;}
.	 ;

%%


char* to_str_data_type(int type)
{
	if(type == SIMPLE)
		return "simple" ;
	if(type == ARRAY)
		return "array" ;
	if(type == STRUCT_T)
		return "struct" ;
	return "" ;
}

int is_array(int t)
{
	return t == ARRAY ;
}

char* to_str_eletype(int type)
{
	if(type == T_INT)
		return "int" ;
	if(type == T_FLOAT)
		return "float" ;
	if(type == T_CHAR)
		return "char" ;
	return "struct" ;
}

int is_char(int t)
{
	return t == T_CHAR || t == V_CHAR ;
}

int is_int(int t)
{
	return t == T_INT || t == V_INT ;
}

int is_float(int t)
{
	return t == T_FLOAT || t == V_FLOAT ;
}

int is_struct(int t)
{
	return !is_int(t) && !is_char(t) && !is_float(t) ;
}

int expr_type(int t1 , int t2)
{
	if(is_struct(t1) && is_struct(t2))
	{
		if(t1 == t2)
			return t1 ;
		return -1 ;
	}
	if(is_struct(t1) || is_struct(t2))
		return -1 ; // error 

	if(is_char(t1) && is_char(t2))
		return T_CHAR ;
	if(is_char(t1) || is_char(t2))
		return -1 ; // error 
	if(is_float(t1) || is_float(t2))
		return T_FLOAT ;
	if(is_int(t1) || is_int(t2))
		return T_INT ;
}

int main()
{
	st = st_new() ;
	sdf = sdf_new() ;
	sstk = sstk_new() ;
	sm = sm_new(cur_scope , st) ;
	st = sm_find(sm , cur_scope) ;
	ft = ft_new(NULL) ;
	yyparse() ;
	sm_print_table(sm) ;
	printf("\n\n") ;
	sdf_print(sdf) ;
	printf("\n") ;
	ft_print(ft) ;
	printf("\nParse successful\n");
}