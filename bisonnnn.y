WHILE_STMT : WHILE '(' BOOL_EXPR ')' 
	;


BOOL_EXPR : BOOL_EXPR '|' AND_EXPR {
		if($1.temp != NULL && $3.temp != NULL)
		{
			int expr_t = expr_type($1.type , $3.type)
			symbol_table_row* left = coerce($1.temp , expr_t) ;
			symbol_table_row* right = coerce($3.temp , expr_t) ;
			symbol_table_row* res = st_new_temp(st , T_TINT , cur_scope) ;
			char code[100] ;
			sprintf(code , "%s = %s | %s" , res -> name , left -> name , right -> name) ;
			ic = ic_add(ic , NOT_GOTO , code , -1) ;
		}
		else
		{
			printf("Unknown  operand / operands for '|' on line no : %d\n", line_no) ;
		}
	}
	| AND_EXPR {
		$$.type = $1.type ;
		$$.temp = $1.temp ;
		$$.constant = $1.constant ;
		$$.val = $1.val ;
	}
	;
AND_EXPR : AND_EXPR '&' BASE {
		if($1.temp != NULL && $3.temp != NULL)
		{
			int expr_t = expr_type($1.type , $3.type)
			symbol_table_row* left = coerce($1.temp , expr_t) ;
			symbol_table_row* right = coerce($3.temp , expr_t) ;
			symbol_table_row* res = st_new_temp(st , T_TINT , cur_scope) ;
			char code[100] ;
			sprintf(code , "%s = %s & %s" , res -> name , left -> name , right -> name) ;
			ic = ic_add(ic , NOT_GOTO , code , -1) ;
		}
		else
		{
			printf("Unknown  operand / operands for '&' on line no : %d\n", line_no) ;
		}
	}
	;
