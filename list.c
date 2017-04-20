typedef struct list
{
	int val ;
	struct list* next ;
}list ;

list* list_add(list* head , int val)
{
	list* new_node = (list*) malloc(sizeof(list)) ;
	new_node -> next = head ;
	new_node -> val = val ;
	return new_node ;
}

list* list_reverse(list* head)
{
	if(head == NULL || head -> next == NULL)
		return head ;
	list* res = list_reverse(head -> next) ;
	head -> next -> next = head ;
	head -> next = NULL ;
	return res ;
}

int list_equal(list* a , list* b)
{
	if((a == NULL && b != NULL) || (a != NULL && b == NULL))
		return 0 ;
	if(a == NULL && b == NULL)
		return 1 ;
	if(a -> val == b -> val)
		return list_equal(a -> next , b -> next) ;
	return 0 ;
}

void list_print(list* head)
{
	if(head == NULL)
		return ;
	printf("[ ") ;
	while(head != NULL)
	{
		printf("%d", head -> val) ;
		head = head -> next ;
		if(head != NULL)
			printf(" , ") ;
	}
	printf(" ]");
}

int list_length(list* head)
{
	if(head == NULL)
		return 0 ;
	return 1 + list_length(head -> next) ;
}

list* list_merge(list* a , list* b)
{
	if(a == NULL && b == NULL)
		return NULL ;
	if(a == NULL)
		return b ;
	if(b == NULL)
		return a ;
	list* res = a ;
	while(a -> next != NULL)
		a = a -> next ;
	a -> next = b ;
	return res ;
}