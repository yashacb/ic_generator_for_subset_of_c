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