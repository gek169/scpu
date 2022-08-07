

#include <stdio.h>
#include <stdlib.h>
#include "scpu.h"


/*it (*hook)(it,it,it,ut,ut,ut*)*/

it hfunc(it a, it b, it c, it pc, it stp, ut* M){
	if(a == 0)
		putchar(b);
	if(a == 1)
		return getchar();
	return 0;
}

ut* M = NULL;

typedef struct {
	it value;
	unsigned char name[64];
} vardecl;

typedef struct {
	unsigned char name[64];
	unsigned char value[65535];
} macrodecl;

vardecl vars[65535];
macrodecl macros[65535];

int main(int argc, char** argv){
	FILE* f;
	if(argc < 2) return 1;

	f = fopen(argv[1],"r");

	if(!f) return 1;

	/*TODO: read assembly language program line-by-line and create macros.*/
	M = calloc(0x10000,2) /*128k of shorts*/;
	return 0;
}
