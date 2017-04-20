typedef struct inter_code
{
	int quad ;
	int type ; // goto present or not .
	char* code ;
	int goto_quad ; // used if goto is present .
	struct inter_code* next ;	
}inter_code;

enum ic_type{
	GOTO , NOT_GOTO
} ;

int nextquad = 1 ;

inter_code* ic_add(inter_code* ic , int type , char* code , int goto_quad)
{
	inter_code* new = (inter_code*) malloc(sizeof(inter_code)) ;
	new -> quad = nextquad++ ;
	new -> type = type ;
	new -> code = dupstr(code) ;
	new -> goto_quad = goto_quad ;
	if(ic == NULL)
		return new ;
	else
	{
		inter_code* cur = ic ;
		while(cur -> next != NULL)
			cur = cur -> next ;
		cur -> next = new ;
		new -> next = 0 ;
		return ic ;
	}	
}

void ic_print(inter_code* ic)
{
	while(ic != NULL)
	{
		printf("%-2d : %s\n", ic -> quad , ic -> code) ;
		ic = ic -> next ;
	}
}

inter_code* ic_get(inter_code* ic , int quad)
{
	if(ic == NULL)
		return NULL ;
	if(ic -> quad == quad)
		return ic ;
	return ic_get(ic -> next , quad) ;
}

inter_code* ic_backpatch(inter_code* ic , list* quads , int to_quad)
{	
	list* cur = quads ;
	while(cur != NULL)
	{		
		inter_code* i = ic_get(ic , cur -> val) ;
		sprintf(i -> code , "%s%d" , i -> code , to_quad) ;
		i -> goto_quad = to_quad ;
		cur = cur -> next ;
	}
	return ic ;
}