#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <iostream>

#include "nvdimm.h"
using namespace std;

#define MSIZE 4096

extern linkedList *list; 

// class
template <typename T>
class Nvdimm {
	public:
		void *operator new[](size_t size);
		void operator delete[](void *adr);

		T &operator[](int idx);
		Nvdimm& operator=(T data);
};

// new[]
template <typename T>
void *Nvdimm<T>::operator new[](size_t size) {
	printf("new[] \n");
	
	int i, temp, _cnt;
	char *nv_ptr;
	
	temp = size / (MSIZE);

	_cnt = temp+1;
	size = _cnt * MSIZE;

	create_node(list);

// 16 : real_malloc meta size
// 48 : node meta size
	nv_ptr = new char[size-48-16];
	
	list->cur->data.location = nv_ptr;
	list->cur->data.cnt = _cnt;
	list->cur->data.valid = 2;

//	printf("new meta location \t: %p\n", list->cur);
//	printf("new location \t\t: %p\n", nv_ptr);

	return nv_ptr;
}

// delete
template <typename T>
void Nvdimm<T>::operator delete[](void *adr) {
	printf("delete \n\n");

	node *p = list->head;
	
	while(p != NULL) {
		if(p->data.location == adr) 
			break;
		p = p->next;
	}
	if(p == NULL) {
		printf("p error\n");
		exit(1);
	}

	if(p->data.valid == 0) {
		while(p != NULL) {
			if(p->data.valid == 1) 
				break;
			p = p->real_data_next;
		}

		if(p->data.valid == 0) {
			printf("nv_read error!(segmentation fault!)\n");
			exit(2);
		}
	}

	p->data.valid = 0;
}

// nv_read
template <typename T>	
T &Nvdimm<T>::operator[](int idx) {
	node *p = list->head;
	T *tptr;

	printf("nv_read\n");
	
	while(p != NULL) {
		if(p->data.location == (void*)this) 
			break;
		p = p->next;
	}
	if(p == NULL) {
		printf("p error\n");
		exit(1);
	}

	if(p->data.valid == 0) {
		while(p != NULL) {
			if(p->data.valid == 1) 
				break;
			p = p->real_data_next;
		}

		if(p->data.valid == 0) {
			printf("nv_read error!(segmentation fault!)\n");
			exit(2);
		}
	}

	tptr = (T*)p->data.location;

	return tptr[idx];
}

// nv_write
template <typename T>
Nvdimm<T>& Nvdimm<T>::operator=(T data) {
	void *temp_ptr;
	T* tptr;
	node *p = list->head, *prev;

	printf("nv_write\n");

	while(p != NULL) {
		if(p->data.location == (void*)this) 
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
		prev = p;
		
		temp_ptr = new Nvdimm<T>[sizeof(data)];

		p = list->cur;
		prev->real_data_next = p;

		p->data.location = temp_ptr;

		tptr = (T*)p->data.location;
		*tptr = data;
		p->data.valid = 1;
	} else {
		printf("nv_write error!(segmentation fault!)\n");
		exit(2);
	}
	
	return *this;
}

