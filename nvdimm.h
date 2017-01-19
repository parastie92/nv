#ifndef _NVDIMM_H_
#define _NVDIMM_H_

#include <sys/types.h>

// struct def
typedef struct nv_malloc_meta {
	void *location;
	int cnt;
	int valid;
}nv_meta;

typedef struct list {
	struct node *cur;
	struct node *head;
	struct node *tail; 
}linkedList; 

typedef struct node {	
	nv_meta data; 
	struct node *next; 
}node; 

// functions
extern "C" void *__real_malloc(size_t size);
extern "C" void *__real_free(void *ptr);

void create_node(linkedList *L);
void deleteLastNode(linkedList *L);
void printNodes();

void nv_init(void);

extern "C" void *__wrap_malloc(size_t size);
extern "C" void *__wrap_free(void *ptr);

#endif
