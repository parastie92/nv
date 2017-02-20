#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>

#include "nvdimm.h"

#define MSIZE 4096 // 4080 + 16 = 4K

linkedList *list;

void create_node(linkedList *L) {
	node *newNode = (node *)malloc(sizeof(node)); 
	newNode->next = NULL;
	newNode->real_data_next = NULL;

	if(L->head == NULL && L->tail == NULL) 
		L->head = L->tail = newNode;	
	else { 
		L->tail->next = newNode; 
		L->tail = newNode; 
	} 

	L->cur = newNode;
}

void deleteLastNode(linkedList *L) {
	node *p = L->head; 
	
	while(p->next->next != NULL)
		p = p->next; 

	p->next = p->next->next; 
	L->tail = p;
}

void deleteNode(linkedList *L) {
	node *p = L->head; 
	
	while(p->next->next != NULL)
		p = p->next; 

	p->next = p->next->next; 
	L->tail = p;
}

void printNodes() {
	node *p = list->head;	
	
	while(p != NULL) {
		printf("[%d, %d, %p] ", p->data.valid, p->data.cnt, p->data.location);
		p = p->next; 
	}

	putchar('\n');
	putchar('\n');
}

void nv_init(void) {
	list = (linkedList*)malloc(sizeof(linkedList));
	list->cur = NULL;
	list->head = NULL;
	list->tail = NULL;
}

extern "C" void *__wrap_malloc(size_t size) {
	int i, temp, _cnt;
	char *nv_ptr;

	temp = size / (MSIZE);

	_cnt = temp+1;
	size = _cnt * MSIZE;

	create_node(list);

// 16 : real_malloc meta size
// 32 : node meta size
	nv_ptr = (char*)malloc(size-32-16);
	
	list->cur->data.location = nv_ptr;
	list->cur->data.cnt = _cnt;
	list->cur->data.valid = 2;

	if(nv_ptr == 0)
		return 0;

	printf("malloc meta location \t: %p\n", list->cur);
	printf("malloc location \t: %p\n", nv_ptr);

	return nv_ptr;
}

extern "C" void *__wrap_free(void *ptr) {
	node *p = list->head;

	while(p != NULL) {
		if(p->data.location == (void*)ptr)
			break;
		p = p->next;
	}

	if(p == NULL) {
		printf("p error\n");
		exit(1);
	}
		
	p->data.valid = 0;
	
	printf("free \n");
}

