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
"{" 	{
		// printf("Lex : { detected\n") ; 
		return '{' ; 
		}
"}" 	{
		// printf("Lex : } detected\n") ; 
		return '}' ; 
		}
{id}	{
		char* copy = (char*) malloc(sizeof(strlen(yytext) + 1)) ;
		strcpy(copy , yytext) ;
		yylval.i.val = copy ;
		yylval.i.type = cur_dt ;
		// printf("Lex : Id detected\n") ; 
		return ID ;
		}
[0-9]+ {
			yylval.e.type = T_INT ;
			yylval.e.val = atoi(yytext) ;
			return NUM ;
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
	return "struct" ;
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

int main()
{
	st = st_new() ;
	sdf = sdf_new() ;
	sstk = sstk_new() ;
	sm = sm_new(cur_scope , st) ;
	st = sm_find(sm , cur_scope) ;
	yyparse() ;
	sm_print(sm) ;
}