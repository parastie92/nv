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
	// if valid = 0, then real_data_next point to real data
	struct node *real_data_next; 
}node; 

// functions
void create_node(linkedList *L);
void deleteLastNode(linkedList *L);
void printNodes();

void nv_init(void);

#endif
