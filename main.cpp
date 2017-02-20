#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <iostream>
#include <string>

#include "nvdimm.h"
#include "classNV.h"

int main() {
	nv_init();

//  Nvdimm template
//	Nvdimm<char> *nv0 = new Nvdimm<char>[10];
	
//	Nvdimm<int> nv0;
//	printf("nv0 : \t%d\n", nv0[0]);


/*case 1*/
	printf("\n-----------------------case1------------------------\n\n");
	Nvdimm<char> *nv1;
	nv1 = new Nvdimm<char>[sizeof(char)];
	nv1[0] = 'a';
	printf("nv1 p   :\t%p\n", nv1);
	printf("nv1 val :\t%c\n", (*nv1)[0]);
	printNodes();

	Nvdimm<char> *nv2;
	nv2 = new Nvdimm<char>[12];
	nv2[0] = 'b';
	printf("nv2 p   :\t%p\n", nv2);
	printf("nv2 val :\t%c\n", (*nv2)[0]);
	printNodes();

	nv1[0] = 'c';
	printf("nv1 p   :\t%p\n", nv1);
	printf("nv1 val :\t%c\n", (*nv1)[0]);
	printNodes();

	delete[](nv1);
	printNodes();

/*case 2*/

	printf("\n-----------------------case2------------------------\n\n");
	Nvdimm<int> *nv3 = new Nvdimm<int>[15];
	nv3[0] = 12345;
	printf("nv3 p	:\t%p\n", nv3);
	printf("nv3 val :\t%d\n", (*nv3)[0]);
	printNodes();
	
	Nvdimm<int> *nv4 = new Nvdimm<int>[20000];
	printf("nv4 p	:\t%p\n", nv4);
	
	nv3[0] = 67890;
	printf("nv3 p	:\t%p\n", nv3);
	printf("nv3 val :\t%d\n", (*nv3)[0]);
	printNodes();

	nv4[0] = 999;
	printf("nv4 p	:\t%p\n", nv4);
	printf("nv4 val :\t%d\n", (*nv4)[0]);
	printNodes(); 

/*case 3*/
/*	printf("\n-----------------------case3------------------------\n\n");
	Nvdimm<char*> nv5;
	nv5.ptr = (char**)malloc(50);
	nv5 = "Hello I'm nv5";
	printf("nv5 val :\t%s\n", nv5[0]);
	printNodes();
	
	free(nv5.ptr);
	printNodes();

	Nvdimm<char*> nv6;
	nv6.ptr = (char**)malloc(5000);
	printNodes();

	free(nv6.ptr);
	printNodes();

	printf("nv6 val :\t%s\n", nv6[0]);
	nv6 = "Hello I'm nv6";
	printf("nv6 val :\t%s\n", nv6[0]);
	printNodes(); */

	return 0;
}

