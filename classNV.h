#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <iostream>

#include "nvdimm.h"
using namespace std;

extern linkedList *list; 

// class
template <typename T>
class Nvdimm {
	public:
		T *ptr;
		
		T& operator[](int idx);
		Nvdimm& operator=(T data);
};

// nv_read
template <typename T>	
T& Nvdimm<T>::operator[](int idx) {
	return ptr[idx];
}

// nv_write
template <typename T>
Nvdimm<T>& Nvdimm<T>::operator=(T data) {
	void *temp_ptr;
	T* tptr;
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
	
	// valid2 = only malloc
	// valid1 = already write
	if(p->data.valid == 2) {
		tptr = (T*)p->data.location;
		*tptr = data;
		p->data.valid = 1;
	} else if(p->data.valid == 1) {
		p->data.valid = 0;
		
		temp_ptr = (char*)__wrap_malloc(sizeof(data));
		
		p = list->cur;
		p->data.location = temp_ptr;
		ptr = (T*)temp_ptr;

		tptr = (T*)p->data.location;
		*tptr = data;
		p->data.valid = 1;
	} else {
		printf("nv_write error!\n");
		exit(1);
	}

	printf("write location \t\t: %p\n", p->data.location);
	
	return *this;
}

