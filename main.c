

#include <stdio.h>
#include <stdlib.h>
#include "scpu2.h"
#include <string.h>
#include "stringutil.h"
/*it (*hook)(it,it,it,ut,ut,ut*)*/


ut* M = NULL;
u8* filedata;
u8 read_scpu(ut addr){
	if(addr == 0x10001) {printf("Enter Character:\r\n");return getchar();}
	else return M[addr & 0xffFF];
}
void write_scpu(ut addr, u8 val){
	if(addr == 0x10001) putchar(val);
	else
	M[addr & 0xffFF] = val;
}


int main(int argc, char** argv){
	FILE* f;
	unsigned long len;
	if(argc < 2) return 1;

	f = fopen(argv[1],"rb");
	if(!f) return 1;

	/*TODO: read assembly language program line-by-line and create macros, instead of compiling a program.*/
	M = calloc(0x10000,1) /*64k*/;
	if(!M) return 1;
	filedata = read_file_into_alloced_buffer(f,&len);
	if(len > 0x10000) memcpy(M, filedata, 0x10000);
	else
	memcpy(M, filedata, len);
	printf("Starting system...\r\n");
	run_scpu(0,0,0,0,0);
}
