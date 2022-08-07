

#include <stdlib.h>
typedef short it;
typedef unsigned short ut;

/*pass in initial state*/
void scpu_run(it a, it b, it c, ut pc, ut stp, ut* M, it (*hook)(it,it,it,ut,ut,ut*)){

	/*pc and stp are also called d and e*/
	while(1){
		ut opcode = M[pc++];
		switch(opcode){
			case 0: break;	/*nop*/
			/*hook function*/
			case 1: a = hook(a,b,c,pc,stp,M);break;
			/*Immediate into register*/
			case 2:	a = M[pc++]; break;
			case 3:	b = M[pc++]; break;
			case 4:	c = M[pc++]; break;
			case 5:	pc = M[pc]; break;	/*Also called "JMP"*/
			case 6:	stp = M[pc++]; break;
			/*Load from address into register*/
			case 7:	a = M[M[pc++]]; break;
			case 8:	b = M[M[pc++]]; break;
			case 9:	c = M[M[pc++]]; break;
			/*Store to address*/
			case 10:	M[M[pc++]] = a; break;
			case 11:	M[M[pc++]] = b; break;
			case 12:	M[M[pc++]] = c; break;
			/*Pointer deref load*/
			case 13: a = M[a]; break;
			case 14: a = M[b]; break;
			case 15: a = M[c]; break;

			case 16: b = M[a]; break;
			case 17: b = M[b]; break;
			case 18: b = M[c]; break;

			case 19: c = M[a]; break;
			case 20: c = M[b]; break;
			case 21: c = M[c]; break;
			/*Pointer deref store*/
			case 22: M[a] = a; break;
			case 23: M[a] = b; break;
			case 24: M[a] = c; break;

			case 25: M[b] = a; break;
			case 26: M[b] = b; break;
			case 27: M[b] = c; break;

			case 28: M[c] = a; break;
			case 29: M[c] = b; break;
			case 30: M[c] = c; break;
			/*Register-register*/
			case 31: a = b;break;
			case 32: a = c;break;
			case 33: a = pc;break;
			case 34: a = stp;break;

			case 35: b = a;break;
			case 36: b = c;break;
			case 37: b = pc;break;
			case 38: b = stp;break;

			case 39: c = a;break;
			case 40: c = b;break;
			case 41: c = pc;break;
			case 42: c = stp;break;

			case 43: pc = a;break;
			case 44: pc = b;break;
			case 45: pc = c;break;
			case 46: pc = stp;break;

			case 47: stp = a;break;
			case 48: stp = b;break;
			case 49: stp = c;break;
			case 50: stp = pc;break;
			/*Math*/
			case 51: a+=b;break;
			case 52: a-=b;break;
			case 53: a*=b;break;
			case 54: if(b) a = a / b;break;
			case 55: if(b) a = (ut)a / (ut)b;break;
			case 56: if(b) a = a % b;break;
			case 57: if(b) a = (ut)a % (ut)b;break;
			case 58: a = ~a;break;
			case 59: a = a & b;break;
			case 60: a = a | b;break;
			case 61: a = !!a;break;
			case 62: a = a && b;break;
			case 63: a = a || b;break;
			/*conditional jump immediate*/
			case 64:
			{
				ut val = M[pc++];
				pc = (!!a) * val + (!a)*pc;
			}
			break;
			/*conditional jump to b*/
			case 65:
			pc = (!!a) * b + (!a)*pc;
			break;
			case 66: goto end; /*End!*/
		}
	}
	end:
	return;
}
