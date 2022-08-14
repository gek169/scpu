#include <stdlib.h>
/*32 bit signed and unsigned integer types*/
typedef int it;
typedef unsigned int ut;
/*byte type*/
typedef unsigned char u8;

/*Implement these two functions to work with your bus!*/
u8 read_scpu(ut addr);
void write_scpu(ut addr, u8 val);


void run_scpu(ut a, ut b, ut c, ut stp, ut pc){
	/*control insns*/
	while(1){
		switch(read_scpu(pc++)){
			default:case 0: break;
			case 255: return;

			/*IMM LOADS=============================================*/
			case 1: 
			a = ((ut)read_scpu(pc)) +
				((ut)read_scpu(pc+1) << 8) +
				((ut)read_scpu(pc+2) << 16) +
				((ut)read_scpu(pc+3) << 24); 
			pc+=4; break; 

			case 2: 
			b = ((ut)read_scpu(pc)) +
				((ut)read_scpu(pc+1) << 8) +
				((ut)read_scpu(pc+2) << 16) +
				((ut)read_scpu(pc+3) << 24); 
			pc+=4; break; 
			
			case 3: 
			c = ((ut)read_scpu(pc)) +
				((ut)read_scpu(pc+1) << 8) +
				((ut)read_scpu(pc+2) << 16) +
				((ut)read_scpu(pc+3) << 24); 
			pc+=4; break; 

			case 4:
			stp = ((ut)read_scpu(pc)) +
				((ut)read_scpu(pc+1) << 8) +
				((ut)read_scpu(pc+2) << 16) +
				((ut)read_scpu(pc+3) << 24); 
			pc+=4; break;

			case 5:
			pc = ((ut)read_scpu(pc)) +
				((ut)read_scpu(pc+1) << 8) +
				((ut)read_scpu(pc+2) << 16) +
				((ut)read_scpu(pc+3) << 24); 
			/*Don't increase PC after that!*/
			break;


			/*ADR LOADS==========================================================================*/
			case 6:
			{ut tmp;
			tmp =  ((ut)read_scpu(pc)) +
					((ut)read_scpu(pc+1) << 8) +
					((ut)read_scpu(pc+2) << 16) +
					((ut)read_scpu(pc+3) << 24); 
				pc+=4;
				a = ((ut)read_scpu(tmp)) +
					((ut)read_scpu(tmp+1) << 8) +
					((ut)read_scpu(tmp+2) << 16) +
					((ut)read_scpu(tmp+3) << 24); 
			}
			break;
			case 7:
			{ut tmp;
			tmp =  ((ut)read_scpu(pc)) +
					((ut)read_scpu(pc+1) << 8) +
					((ut)read_scpu(pc+2) << 16) +
					((ut)read_scpu(pc+3) << 24); 
				pc+=4;
				b = ((ut)read_scpu(tmp)) +
					((ut)read_scpu(tmp+1) << 8) +
					((ut)read_scpu(tmp+2) << 16) +
					((ut)read_scpu(tmp+3) << 24); 
			}
			break;
			case 8:
			{ut tmp;
			tmp =  ((ut)read_scpu(pc)) +
					((ut)read_scpu(pc+1) << 8) +
					((ut)read_scpu(pc+2) << 16) +
					((ut)read_scpu(pc+3) << 24); 
				pc+=4;
				c = ((ut)read_scpu(tmp)) +
					((ut)read_scpu(tmp+1) << 8) +
					((ut)read_scpu(tmp+2) << 16) +
					((ut)read_scpu(tmp+3) << 24); 
			}
			break;
			/*IND LOADS (THROUGH A)======================================================*/
			case 9:
			{
				a = ((ut)read_scpu(a)) +
					((ut)read_scpu(a+1) << 8) +
					((ut)read_scpu(a+2) << 16) +
					((ut)read_scpu(a+3) << 24); 
			}
			break;
			case 10:
			{
				b = ((ut)read_scpu(a)) +
					((ut)read_scpu(a+1) << 8) +
					((ut)read_scpu(a+2) << 16) +
					((ut)read_scpu(a+3) << 24); 
			}
			break;
			case 11:
			{
				c = ((ut)read_scpu(a)) +
					((ut)read_scpu(a+1) << 8) +
					((ut)read_scpu(a+2) << 16) +
					((ut)read_scpu(a+3) << 24); 
			}
			break;

			/*IND LOADS (THROUGH B)======================================================*/
			case 12:
			{
				a = ((ut)read_scpu(b)) +
					((ut)read_scpu(b+1) << 8) +
					((ut)read_scpu(b+2) << 16) +
					((ut)read_scpu(b+3) << 24); 
			}
			break;
			case 13:
			{
				b = ((ut)read_scpu(b)) +
					((ut)read_scpu(b+1) << 8) +
					((ut)read_scpu(b+2) << 16) +
					((ut)read_scpu(b+3) << 24); 
			}
			break;
			case 14:
			{
				c = ((ut)read_scpu(b)) +
					((ut)read_scpu(b+1) << 8) +
					((ut)read_scpu(b+2) << 16) +
					((ut)read_scpu(b+3) << 24); 
			}
			break;



			/*IND LOADS (THROUGH C)======================================================*/
			case 15:
			{
				a = ((ut)read_scpu(c)) +
					((ut)read_scpu(c+1) << 8) +
					((ut)read_scpu(c+2) << 16) +
					((ut)read_scpu(c+3) << 24); 
			}
			break;
			case 16:
			{
				b = ((ut)read_scpu(c)) +
					((ut)read_scpu(c+1) << 8) +
					((ut)read_scpu(c+2) << 16) +
					((ut)read_scpu(c+3) << 24); 
			}
			break;
			case 17:
			{
				c = ((ut)read_scpu(c)) +
					((ut)read_scpu(c+1) << 8) +
					((ut)read_scpu(c+2) << 16) +
					((ut)read_scpu(c+3) << 24); 
			}
			break;


			/*ADR STORES====================================*/
			case 18:
			{ut tmp;
 				tmp = ((ut)read_scpu(pc)) +
					((ut)read_scpu(pc+1) << 8) +
					((ut)read_scpu(pc+2) << 16) +
					((ut)read_scpu(pc+3) << 24);
				write_scpu(tmp,a); 
				write_scpu(tmp+1,a>>8); 
				write_scpu(tmp+2,a>>16); 
				write_scpu(tmp+3,a>>24); 
			}
			break;
			case 19:
			{ut tmp;
 				tmp = ((ut)read_scpu(pc)) +
					((ut)read_scpu(pc+1) << 8) +
					((ut)read_scpu(pc+2) << 16) +
					((ut)read_scpu(pc+3) << 24);
				write_scpu(tmp,b); 
				write_scpu(tmp+1,b>>8); 
				write_scpu(tmp+2,b>>16); 
				write_scpu(tmp+3,b>>24); 
			}
			break;
			case 20:
			{ut tmp;
 				tmp = ((ut)read_scpu(pc)) +
					((ut)read_scpu(pc+1) << 8) +
					((ut)read_scpu(pc+2) << 16) +
					((ut)read_scpu(pc+3) << 24);
				write_scpu(tmp,c); 
				write_scpu(tmp+1,c>>8); 
				write_scpu(tmp+2,c>>16); 
				write_scpu(tmp+3,c>>24); 
			}
			break;

			/*IND STORES (THROUGH A)===========================================*/
			case 21:
				write_scpu(a,  a); 
				write_scpu(a+1,a>>8); 
				write_scpu(a+2,a>>16); 
				write_scpu(a+3,a>>24); 
			break;
			case 22:
				write_scpu(a,  b); 
				write_scpu(a+1,b>>8); 
				write_scpu(a+2,b>>16); 
				write_scpu(a+3,b>>24); 
			break;
			case 23:
				write_scpu(a,  c); 
				write_scpu(a+1,c>>8); 
				write_scpu(a+2,c>>16); 
				write_scpu(a+3,c>>24); 
			break;
			/*IND STORES (THROUGH B)===========================================*/
			case 24:
				write_scpu(b,  a); 
				write_scpu(b+1,a>>8); 
				write_scpu(b+2,a>>16); 
				write_scpu(b+3,a>>24); 
			break;
			case 25:
				write_scpu(b,  b); 
				write_scpu(b+1,b>>8); 
				write_scpu(b+2,b>>16); 
				write_scpu(b+3,b>>24); 
			break;
			case 26:
				write_scpu(b,  c); 
				write_scpu(b+1,c>>8); 
				write_scpu(b+2,c>>16); 
				write_scpu(b+3,c>>24); 
			break;
			/*IND STORES (THROUGH C)===========================================*/
			case 27:
				write_scpu(c,  a); 
				write_scpu(c+1,a>>8); 
				write_scpu(c+2,a>>16); 
				write_scpu(c+3,a>>24); 
			break;
			case 28:
				write_scpu(c,  b); 
				write_scpu(c+1,b>>8); 
				write_scpu(c+2,b>>16); 
				write_scpu(c+3,b>>24); 
			break;
			case 29:
				write_scpu(c,  c); 
				write_scpu(c+1,c>>8); 
				write_scpu(c+2,c>>16); 
				write_scpu(c+3,c>>24); 
			break;
			/*REG REG TRANSFER*/
			case 30: a=b; break;
			case 31: a=c; break;
			case 32: a=stp; break;
			case 33: a=pc; break;

			case 34: b=a; break;
			case 35: b=c; break;
			case 36: b=stp; break;
			case 37: b=pc; break;

			case 38: c=a; break;
			case 39: c=b; break;
			case 40: c=stp; break;
			case 41: c=pc; break;

			case 42: stp=a; break;
			case 43: stp=b; break;
			case 44: stp=c; break;
			case 45: stp=pc; break;

			case 46: pc=a; break;
			case 47: pc=b; break;
			case 48: pc=c; break;
			case 49: pc=stp; break;
			/*PUSH======================================*/
			case 50:
			write_scpu(stp,  a); 
			write_scpu(stp+1,a>>8); 
			write_scpu(stp+2,a>>16); 
			write_scpu(stp+3,a>>24);
			stp+=4;
			break;
			case 51:
			write_scpu(stp,  b); 
			write_scpu(stp+1,b>>8); 
			write_scpu(stp+2,b>>16); 
			write_scpu(stp+3,b>>24);
			stp+=4;
			break;
			case 52:
			write_scpu(stp,  c); 
			write_scpu(stp+1,c>>8); 
			write_scpu(stp+2,c>>16); 
			write_scpu(stp+3,c>>24);
			stp+=4;
			break;
			/*POP=====================================*/
			case 53:
			stp-=4;
			{a =((ut)read_scpu(stp)) +
				((ut)read_scpu(stp+1) << 8) +
				((ut)read_scpu(stp+2) << 16) +
				((ut)read_scpu(stp+3) << 24);
			}
			break;
			case 54:
			stp-=4;
			{b =((ut)read_scpu(stp)) +
				((ut)read_scpu(stp+1) << 8) +
				((ut)read_scpu(stp+2) << 16) +
				((ut)read_scpu(stp+3) << 24);
			}
			break;
			case 55:
			stp-=4;
			{c =((ut)read_scpu(stp)) +
				((ut)read_scpu(stp+1) << 8) +
				((ut)read_scpu(stp+2) << 16) +
				((ut)read_scpu(stp+3) << 24);
			}
			break;
			/*CALL A=======================================*/
			case 56:
			{
			write_scpu(stp,  pc); 
			write_scpu(stp+1,pc>>8); 
			write_scpu(stp+2,pc>>16); 
			write_scpu(stp+3,pc>>24);
			stp+=4;
			pc = a;
			}
			break;
			/*RET=========================================*/
			case 57:
			stp-=4;
			{pc=((ut)read_scpu(stp)) +
				((ut)read_scpu(stp+1) << 8) +
				((ut)read_scpu(stp+2) << 16) +
				((ut)read_scpu(stp+3) << 24);
			}
			break;
			/*MATH!*/
			case 58: a+=b; break;
			case 59: a-=b; break;
			case 60: a*=b; break;
			case 61: a&=b; break;
			case 62: a|=b; break;
			case 63: a^=b; break;
			case 64: a = ~a; break;
			case 65: a = !!a; break;
			case 66: a = a && b; break;
			case 67: a = a || b; break;
			case 68: if(b) a /= b; break;
			case 69: if(b) a %= b; break;
			case 70: a = a<<b; break;
			case 71: a = a>>b; break;
			case 72: a = (a == b); break;
			case 73: a = (a < b); break;
			case 74: a = (a > b); break;
			case 75: a = ((it)a < (it)b); break;
			case 76: a = ((it)a > (it)b); break;
			/*CONDITIONAL JUMP*/
			case 77: if(a) pc=b; break;
			case 78: if(!a) pc=b; break;
			case 79: if(a) pc=c; break;
			case 80: if(!a) pc=c; break;
			/*SIGNED DIVISION*/
			case 81: if(b) a = (it)a / (it)b;
			case 82: if(b) a = (it)a % (it)b;
		}
	}
}
