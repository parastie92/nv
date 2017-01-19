#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <iostream>
#include <string>

#include "nvdimm.h"
#include "classNV.h"
using namespace std;

int main() {
	nv_init();
	
/*case 1*/
	printf("\n-----------------------case1------------------------\n\n");
	Nvdimm<char> nv1;
	nv1.ptr = (char*)malloc(sizeof(char));
	nv1 = 'a';
	printf("nv1 val :\t%c\n", nv1[0]);
	printNodes();

	Nvdimm<char> nv2;
	nv2.ptr = (char*)malloc(12);
	nv2 = 'b';
	printf("nv2 val :\t%c\n", nv2[0]);
	printNodes();

	nv1 = 'c';
	printf("nv1 val :\t%c\n", nv1[0]);
	printNodes();

/*case 2*/
	printf("\n-----------------------case2------------------------\n\n");
	Nvdimm<int> nv3;
	nv3.ptr = (int*)malloc(15);
	nv3 = 12345;
	printf("nv3 val :\t%d\n", nv3[0]);
	printNodes();
	
	Nvdimm<int> nv4;
	nv4.ptr = (int*)malloc(20000);
	
	nv3 = 67890;
	printf("nv3 val :\t%d\n", nv3[0]);
	printNodes();

	nv4 = 999;
	printf("nv4 val :\t%d\n", nv4[0]);
	printNodes();

/*case 3*/
	printf("\n-----------------------case3------------------------\n\n");
	Nvdimm<char*> nv5;
	nv5.ptr = (char**)malloc(50);
	nv5 = "Hello I'm nv5";
	printf("nv5 val :\t%s\n", nv5[0]);
	printNodes();
	
	free(nv1.ptr);
	free(nv2.ptr);
	free(nv3.ptr);
	free(nv4.ptr);
	free(nv5.ptr);
	printNodes();

	Nvdimm<char*> nv6;
	nv6.ptr = (char**)malloc(5000);
	printNodes();

	free(nv6.ptr);
	printNodes();

	nv6 = "Hello I'm nv6";
	printf("nv6 val :\t%s\n", nv6[0]);
	printNodes();

	return 0;
}

