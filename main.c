

#include <stdio.h>
#include <stdlib.h>
#include "scpu.h"




int main(int argc, char** argv){
	FILE* f;
	if(argc < 2) return 1;

	f = fopen(argv[1],"r");

	if(!f) return 1;

	/*TODO: read entire image into memory.*/
	return 0;
}
