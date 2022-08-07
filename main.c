

#include <stdio.h>
#include <stdlib.h>
#include "scpu.h"
#include <string.h>
#include "stringutil.h"
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
	char name[64];
} vardecl;

typedef struct {
	char name[64];
	char value[65535];
} macrodecl;


#define MAX_VARS 1024
#define MAX_MACROS 1024
vardecl vars[MAX_VARS];
unsigned nvars = 0;
macrodecl macros[MAX_MACROS];
unsigned nmacros = 0;

unsigned get_var(char* name){
	unsigned i = 0;
	for(i=0; i < nvars; i++)
	{
		vars[i].name[63] = '\0';
		if(strcmp(name, vars[i].name) == 0) return i;
	}
	return MAX_VARS;
}

void add_var(char* name, it value){
	unsigned v = get_var(name);
	if(v != MAX_VARS){
		vars[v].value = value;
		return;
	}
	/**/
	if(nvars == MAX_VARS) return;
	strcpy(vars[nvars].name, name);
	vars[nvars].value = value;
	nvars++;
	return;
}

unsigned get_macro(char* name){
	unsigned i = 0;
	for(i=0; i < nmacros; i++)
	{
		macros[i].name[63] = '\0';
		if(strcmp(name, macros[i].name) == 0) return i;
	}
	return MAX_MACROS;
}

void add_macro(char* name, char* value){
	unsigned v = get_macro(name);
	if(v != MAX_MACROS){
		strcpy((char*)macros[v].value, value);
		return;
	}
	/**/
	if(nmacros == MAX_MACROS) return;
	strcpy((char*)macros[nmacros].name, name);
	strcpy((char*)macros[v].value, value);
	nmacros++;
	return;
}

int main(int argc, char** argv){
	FILE* f;
	unsigned long len;
	if(argc < 2) return 1;

	f = fopen(argv[1],"r");
	if(!f) return 1;

	/*TODO: read assembly language program line-by-line and create macros.*/
	M = calloc(0x10000,2) /*128k of shorts*/;

	read_file_into_alloced_buffer(f,&len);

	/*Read lines of file one at a time.*/
	
	return 0;
}
