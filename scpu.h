

#include <stdlib.h>
/*32 bit signed and unsigned integer types*/
typedef int it;
typedef unsigned int ut;
/*byte type*/
typedef unsigned char u8;
#define MEM_MASK 0xffFFff
/*pass in initial state*/
void scpu_run(it a, it b, it c, ut pc, ut stp, ut* M, it (*hook)(it,it,it,ut,ut,ut*)){


	while(1){
		unsigned char b1 = M[pc & MEM_MASK];
		unsigned char b2 = M[pc & MEM_MASK]/0x100;
		unsigned char b3 = M[pc & MEM_MASK]/0x10000;
		unsigned char b4 = M[pc & MEM_MASK]/0x1000000;
		pc++; pc &= MEM_MASK;
		switch(b1){
			/*IO and CPU control*/
			case 0:
			switch(b2){
				case 0: goto nextins;
				case 1: a = hook(a,b,c,pc,stp,M); goto nextins;
			}
			goto nextins;





			/*Loads and stores*/
			case 1:
			switch(b2){
				#define IMM_LOAD(reggie) {reggie = M[pc & MEM_MASK];pc++; goto nextins;}
				#define ADR_LOAD(reggie) {reggie = M[M[pc & MEM_MASK] & MEM_MASK];pc++; goto nextins;}
				#define IND_LOAD(reggie,reggie2) {reggie = M[reggie2 & MEM_MASK]; goto nextins;}
				#define ADR_STO(reggie) {M[M[pc & MEM_MASK] & MEM_MASK] = reggie;pc++; goto nextins;}
				#define IND_STO(reggie,reggie2) {M[reggie2 & MEM_MASK] = reggie; goto nextins;}
				case 0: /*immediate load*/ 
				switch(b3){
					case 0: IMM_LOAD(a)
					case 1: IMM_LOAD(b)
					case 2: IMM_LOAD(c)
					case 3: IMM_LOAD(pc)
					case 4: IMM_LOAD(stp)
				}
				goto nextins; 
				case 1: /*addressed load*/ 
				switch(b3){
					case 0: ADR_LOAD(a)
					case 1: ADR_LOAD(b)
					case 2: ADR_LOAD(c)
					case 3: ADR_LOAD(pc)
					case 4: ADR_LOAD(stp)
				}
				goto nextins;
				case 2: /*indirect load*/
				{
					switch(b3){
						case 0: /*load into a*/
						switch(b4){
							case 0: IND_LOAD(a,a) /*using the value in a*/
							case 1: IND_LOAD(a,b)
							case 2: IND_LOAD(a,c)
							case 3: IND_LOAD(a,pc)
							case 4: IND_LOAD(a,stp)
						}
						goto nextins;
						case 1: /*into b*/
						switch(b4){
							case 0: IND_LOAD(b,a) /*using the value in a*/
							case 1: IND_LOAD(b,b)
							case 2: IND_LOAD(b,c)
							case 3: IND_LOAD(b,pc)
							case 4: IND_LOAD(b,stp)
						}
						goto nextins;
						case 2: /*into c*/
						switch(b4){
							case 0: IND_LOAD(c,a) /*using the value in a*/
							case 1: IND_LOAD(c,b)
							case 2: IND_LOAD(c,c)
							case 3: IND_LOAD(c,pc)
							case 4: IND_LOAD(c,stp)
						}
						goto nextins;
						case 3: /*into pc*/
						switch(b4){
							case 0: IND_LOAD(pc,a) /*using the value in a*/
							case 1: IND_LOAD(pc,b)
							case 2: IND_LOAD(pc,c)
							case 3: IND_LOAD(pc,pc)
							case 4: IND_LOAD(pc,stp)
						}
						goto nextins;
						case 4: /*into stp*/
						switch(b4){
							case 0: IND_LOAD(stp,a) /*using the value in a*/
							case 1: IND_LOAD(stp,b)
							case 2: IND_LOAD(stp,c)
							case 3: IND_LOAD(stp,pc)
							case 4: IND_LOAD(stp,stp)
						}
						goto nextins;
					}
				}
				goto nextins; 
				case 3: goto nextins; /*addressed store*/
				switch(b3){
					case 0: ADR_STO(a)
					case 1: ADR_STO(b)
					case 2: ADR_STO(c)
					case 3: ADR_STO(pc)
					case 4: ADR_STO(stp)
				}
				goto nextins;		
				case 4: 
				switch(b3){
					case 0: /*store into M[a]*/
					switch(b4){
						case 0: IND_STO(a,a) /*using the value in a*/
						case 1: IND_STO(b,a)
						case 2: IND_STO(c,a)
						case 3: IND_STO(pc,a)
						case 4: IND_STO(stp,a)
					}
					goto nextins;
					case 1: /*into b*/
					switch(b4){
						case 0: IND_STO(a,b) /*using the value in a*/
						case 1: IND_STO(b,b)
						case 2: IND_STO(c,b)
						case 3: IND_STO(pc,b)
						case 4: IND_STO(stp,b)
					}
					goto nextins;
					case 2: /*into c*/
					switch(b4){
						case 0: IND_STO(a,c) /*using the value in a*/
						case 1: IND_STO(b,c)
						case 2: IND_STO(c,c)
						case 3: IND_STO(pc,c)
						case 4: IND_STO(stp,c)
					}
					goto nextins;
					case 3: /*into pc*/
					switch(b4){
						case 0: IND_STO(a,pc) /*using the value in a*/
						case 1: IND_STO(b,pc)
						case 2: IND_STO(c,pc)
						case 3: IND_STO(pc,pc)
						case 4: IND_STO(stp,pc)
					}
					goto nextins;
					case 4: /*into stp*/
					switch(b4){
						case 0: IND_STO(a,stp) /*using the value in a*/
						case 1: IND_STO(b,stp)
						case 2: IND_STO(c,stp)
						case 3: IND_STO(pc,stp)
						case 4: IND_STO(stp,stp)
					}
					goto nextins;
				}
				goto nextins; /*indirect store end*/
			}
			goto nextins;
			/*End of loads and stores*/

			
			case 2: /*register to register*/
#define REG_TO_REG(dest) switch(b3){case 0:dest=a;goto nextins;case 1:dest=b;goto nextins;case 2:dest=c;goto nextins;case 3:dest=pc;goto nextins;case 4:dest=stp;goto nextins;} goto nextins;
			switch(b2){
				case 0: REG_TO_REG(a)/*target register is A*/
				case 1: REG_TO_REG(b)
				case 2: REG_TO_REG(c)
				case 3: REG_TO_REG(pc)
				case 4: REG_TO_REG(stp)
				goto nextins;
			}
			goto nextins;
#undef REG_TO_REG




			case 3: /*Control flow, all are indirect*/
			switch(b2){
				case 0: /*is_zero*/
					switch(b3){ /*test?*/
						case 0: /*a==0?*/
							switch(b4){ /*assign?*/
								case 0: if(a==0) pc = a; goto nextins;
								case 1: if(a==0) pc = b; goto nextins;
								case 2: if(a==0) pc = c; goto nextins;
								case 3: if(a==0) pc = stp; goto nextins;
							}
						goto nextins;
						case 1: /*b==0?*/
							switch(b4){ /*assign?*/
								case 0: if(b==0) pc = a; goto nextins;
								case 1: if(b==0) pc = b; goto nextins;
								case 2: if(b==0) pc = c; goto nextins;
								case 3: if(b==0) pc = stp; goto nextins;
							}
						goto nextins;
						case 2: /*c==0?*/
							switch(b4){ /*assign?*/
								case 0: if(c==0) pc = a; goto nextins;
								case 1: if(c==0) pc = b; goto nextins;
								case 2: if(c==0) pc = c; goto nextins;
								case 3: if(c==0) pc = stp; goto nextins;
							}
						goto nextins;
						case 3: /*stp==0?*/
							switch(b4){ /*assign?*/
								case 0: if(stp==0) pc = a; goto nextins;
								case 1: if(stp==0) pc = b; goto nextins;
								case 2: if(stp==0) pc = c; goto nextins;
								case 3: if(stp==0) pc = stp; goto nextins;
							}
						goto nextins;
					}
				goto nextins;
				case 1: /*is_1*/
					switch(b3){ /*test?*/
						case 0: /*a==0?*/
							switch(b4){ /*assign?*/
								case 0: if(a==1) pc = a; goto nextins;
								case 1: if(a==1) pc = b; goto nextins;
								case 2: if(a==1) pc = c; goto nextins;
								case 3: if(a==1) pc = stp; goto nextins;
							}
						goto nextins;
						case 1: /*b==0?*/
							switch(b4){ /*assign?*/
								case 0: if(b==1) pc = a; goto nextins;
								case 1: if(b==1) pc = b; goto nextins;
								case 2: if(b==1) pc = c; goto nextins;
								case 3: if(b==1) pc = stp; goto nextins;
							}
						goto nextins;
						case 2: /*c==0?*/
							switch(b4){ /*assign?*/
								case 0: if(c==1) pc = a; goto nextins;
								case 1: if(c==1) pc = b; goto nextins;
								case 2: if(c==1) pc = c; goto nextins;
								case 3: if(c==1) pc = stp; goto nextins;
							}
						goto nextins;
						case 3: /*stp==0?*/
							switch(b4){ /*assign?*/
								case 0: if(stp==1) pc = a; goto nextins;
								case 1: if(stp==1) pc = b; goto nextins;
								case 2: if(stp==1) pc = c; goto nextins;
								case 3: if(stp==1) pc = stp; goto nextins;
							}
						goto nextins;
					}
				goto nextins;
				case 2: /*is_not_zero*/
					switch(b3){ /*test?*/
						case 0: /*a==0?*/
							switch(b4){ /*assign?*/
								case 0: if(a) pc = a; goto nextins;
								case 1: if(a) pc = b; goto nextins;
								case 2: if(a) pc = c; goto nextins;
								case 3: if(a) pc = stp; goto nextins;
							}
						goto nextins;
						case 1: /*b==0?*/
							switch(b4){ /*assign?*/
								case 0: if(b) pc = a; goto nextins;
								case 1: if(b) pc = b; goto nextins;
								case 2: if(b) pc = c; goto nextins;
								case 3: if(b) pc = stp; goto nextins;
							}
						goto nextins;
						case 2: /*c==0?*/
							switch(b4){ /*assign?*/
								case 0: if(c) pc = a; goto nextins;
								case 1: if(c) pc = b; goto nextins;
								case 2: if(c) pc = c; goto nextins;
								case 3: if(c) pc = stp; goto nextins;
							}
						goto nextins;
						case 3: /*stp==0?*/
							switch(b4){ /*assign?*/
								case 0: if(stp) pc = a; goto nextins;
								case 1: if(stp) pc = b; goto nextins;
								case 2: if(stp) pc = c; goto nextins;
								case 3: if(stp) pc = stp; goto nextins;
							}
						goto nextins;
					}
				goto nextins;
				case 3: /*is -1*/
					switch(b3){ /*test?*/
						case 0: /*a==0?*/
							switch(b4){ /*assign?*/
								case 0: if(a==-1) pc = a; goto nextins;
								case 1: if(a==-1) pc = b; goto nextins;
								case 2: if(a==-1) pc = c; goto nextins;
								case 3: if(a==-1) pc = stp; goto nextins;
							}
						goto nextins;
						case 1: /*b==0?*/
							switch(b4){ /*assign?*/
								case 0: if(b==-1) pc = a; goto nextins;
								case 1: if(b==-1) pc = b; goto nextins;
								case 2: if(b==-1) pc = c; goto nextins;
								case 3: if(b==-1) pc = stp; goto nextins;
							}
						goto nextins;
						case 2: /*c==0?*/
							switch(b4){ /*assign?*/
								case 0: if(c==-1) pc = a; goto nextins;
								case 1: if(c==-1) pc = b; goto nextins;
								case 2: if(c==-1) pc = c; goto nextins;
								case 3: if(c==-1) pc = stp; goto nextins;
							}
						goto nextins;
						case 3: /*stp==0?*/
							switch(b4){ /*assign?*/
								case 0: if(stp==~(ut)0) pc = a; goto nextins;
								case 1: if(stp==~(ut)0) pc = b; goto nextins;
								case 2: if(stp==~(ut)0) pc = c; goto nextins;
								case 3: if(stp==~(ut)0) pc = stp; goto nextins;
							}
						goto nextins;
					}
				goto nextins;
			}
			goto nextins;

			case 4: /*Math!*/
#define DOMATH(op,dst,src) dst = dst op src; goto nextins;
#define DOMATHS(op,dst) dst = op dst; goto nextins;
#define DOMATH_SRC_NOTZERO(op,dst,src) if(src) dst = dst op src; goto nextins;

			switch(b2){ /*operation*/
				case 0:
					switch(b3){ /*dst*/
						case 0: 
							switch(b4){
								case 0: DOMATH(+,a,a)
								case 1: DOMATH(+,a,b)
								case 2: DOMATH(+,a,c)
								case 3: DOMATH(+,a,pc)
								case 4: DOMATH(+,a,stp)
							}
						goto nextins;
						case 1: 
							switch(b4){
								case 0: DOMATH(+,b,a)
								case 1: DOMATH(+,b,b)
								case 2: DOMATH(+,b,c)
								case 3: DOMATH(+,b,pc)
								case 4: DOMATH(+,b,stp)
							}
						goto nextins;			
						case 2: 
							switch(b4){
								case 0: DOMATH(+,c,a)
								case 1: DOMATH(+,c,b)
								case 2: DOMATH(+,c,c)
								case 3: DOMATH(+,c,pc)
								case 4: DOMATH(+,c,stp)
							}
						goto nextins;
						case 3: 
							switch(b4){
								case 0: DOMATH(+,pc,a)
								case 1: DOMATH(+,pc,b)
								case 2: DOMATH(+,pc,c)
								case 3: DOMATH(+,pc,pc)
								case 4: DOMATH(+,pc,stp)
							}
						goto nextins;
						case 4: 
							switch(b4){
								case 0: DOMATH(+,stp,a)
								case 1: DOMATH(+,stp,b)
								case 2: DOMATH(+,stp,c)
								case 3: DOMATH(+,stp,pc)
								case 4: DOMATH(+,stp,stp)
							}
						goto nextins;
					}
				goto nextins; /*add*/


				case 1:
					switch(b3){ /*dst*/
						case 0: 
							switch(b4){
								case 0: DOMATH(-,a,a)
								case 1: DOMATH(-,a,b)
								case 2: DOMATH(-,a,c)
								case 3: DOMATH(-,a,pc)
								case 4: DOMATH(-,a,stp)
							}
						goto nextins;
						case 1: 
							switch(b4){
								case 0: DOMATH(-,b,a)
								case 1: DOMATH(-,b,b)
								case 2: DOMATH(-,b,c)
								case 3: DOMATH(-,b,pc)
								case 4: DOMATH(-,b,stp)
							}
						goto nextins;			
						case 2: 
							switch(b4){
								case 0: DOMATH(-,c,a)
								case 1: DOMATH(-,c,b)
								case 2: DOMATH(-,c,c)
								case 3: DOMATH(-,c,pc)
								case 4: DOMATH(-,c,stp)
							}
						goto nextins;
						case 3: 
							switch(b4){
								case 0: DOMATH(-,pc,a)
								case 1: DOMATH(-,pc,b)
								case 2: DOMATH(-,pc,c)
								case 3: DOMATH(-,pc,pc)
								case 4: DOMATH(-,pc,stp)
							}
						goto nextins;
						case 4: 
							switch(b4){
								case 0: DOMATH(-,stp,a)
								case 1: DOMATH(-,stp,b)
								case 2: DOMATH(-,stp,c)
								case 3: DOMATH(-,stp,pc)
								case 4: DOMATH(-,stp,stp)
							}
						goto nextins;
					}
				goto nextins; /*sub*/

				case 2:
					switch(b3){ /*dst*/
						case 0: 
							switch(b4){
								case 0: DOMATH(*,a,a)
								case 1: DOMATH(*,a,b)
								case 2: DOMATH(*,a,c)
								case 3: DOMATH(*,a,pc)
								case 4: DOMATH(*,a,stp)
							}
						goto nextins;
						case 1: 
							switch(b4){
								case 0: DOMATH(*,b,a)
								case 1: DOMATH(*,b,b)
								case 2: DOMATH(*,b,c)
								case 3: DOMATH(*,b,pc)
								case 4: DOMATH(*,b,stp)
							}
						goto nextins;			
						case 2: 
							switch(b4){
								case 0: DOMATH(*,c,a)
								case 1: DOMATH(*,c,b)
								case 2: DOMATH(*,c,c)
								case 3: DOMATH(*,c,pc)
								case 4: DOMATH(*,c,stp)
							}
						goto nextins;
						case 3: 
							switch(b4){
								case 0: DOMATH(*,pc,a)
								case 1: DOMATH(*,pc,b)
								case 2: DOMATH(*,pc,c)
								case 3: DOMATH(*,pc,pc)
								case 4: DOMATH(*,pc,stp)
							}
						goto nextins;
						case 4: 
							switch(b4){
								case 0: DOMATH(*,stp,a)
								case 1: DOMATH(*,stp,b)
								case 2: DOMATH(*,stp,c)
								case 3: DOMATH(*,stp,pc)
								case 4: DOMATH(*,stp,stp)
							}
						goto nextins;
					}
				goto nextins; /*mul*/

				
				case 3:
					switch(b3){ /*dst*/
						case 0: 
							switch(b4){
								case 0: DOMATH_SRC_NOTZERO(/,a,a)
								case 1: DOMATH_SRC_NOTZERO(/,a,b)
								case 2: DOMATH_SRC_NOTZERO(/,a,c)
								case 3: DOMATH_SRC_NOTZERO(/,a,pc)
								case 4: DOMATH_SRC_NOTZERO(/,a,stp)
							}
						goto nextins;
						case 1: 
							switch(b4){
								case 0: DOMATH_SRC_NOTZERO(/,b,a)
								case 1: DOMATH_SRC_NOTZERO(/,b,b)
								case 2: DOMATH_SRC_NOTZERO(/,b,c)
								case 3: DOMATH_SRC_NOTZERO(/,b,pc)
								case 4: DOMATH_SRC_NOTZERO(/,b,stp)
							}
						goto nextins;			
						case 2: 
							switch(b4){
								case 0: DOMATH_SRC_NOTZERO(/,c,a)
								case 1: DOMATH_SRC_NOTZERO(/,c,b)
								case 2: DOMATH_SRC_NOTZERO(/,c,c)
								case 3: DOMATH_SRC_NOTZERO(/,c,pc)
								case 4: DOMATH_SRC_NOTZERO(/,c,stp)
							}
						goto nextins;
						case 3: 
							switch(b4){
								case 0: DOMATH_SRC_NOTZERO(/,pc,a)
								case 1: DOMATH_SRC_NOTZERO(/,pc,b)
								case 2: DOMATH_SRC_NOTZERO(/,pc,c)
								case 3: DOMATH_SRC_NOTZERO(/,pc,pc)
								case 4: DOMATH_SRC_NOTZERO(/,pc,stp)
							}
						goto nextins;
						case 4: 
							switch(b4){
								case 0: DOMATH_SRC_NOTZERO(/,stp,a)
								case 1: DOMATH_SRC_NOTZERO(/,stp,b)
								case 2: DOMATH_SRC_NOTZERO(/,stp,c)
								case 3: DOMATH_SRC_NOTZERO(/,stp,pc)
								case 4: DOMATH_SRC_NOTZERO(/,stp,stp)
							}
						goto nextins;
					}
				goto nextins; /*div*/
				case 4:
					switch(b3){ /*dst*/
						case 0: 
							switch(b4){
								case 0: DOMATH_SRC_NOTZERO(%,a,a)
								case 1: DOMATH_SRC_NOTZERO(%,a,b)
								case 2: DOMATH_SRC_NOTZERO(%,a,c)
								case 3: DOMATH_SRC_NOTZERO(%,a,pc)
								case 4: DOMATH_SRC_NOTZERO(%,a,stp)
							}
						goto nextins;
						case 1: 
							switch(b4){
								case 0: DOMATH_SRC_NOTZERO(%,b,a)
								case 1: DOMATH_SRC_NOTZERO(%,b,b)
								case 2: DOMATH_SRC_NOTZERO(%,b,c)
								case 3: DOMATH_SRC_NOTZERO(%,b,pc)
								case 4: DOMATH_SRC_NOTZERO(%,b,stp)
							}
						goto nextins;			
						case 2: 
							switch(b4){
								case 0: DOMATH_SRC_NOTZERO(%,c,a)
								case 1: DOMATH_SRC_NOTZERO(%,c,b)
								case 2: DOMATH_SRC_NOTZERO(%,c,c)
								case 3: DOMATH_SRC_NOTZERO(%,c,pc)
								case 4: DOMATH_SRC_NOTZERO(%,c,stp)
							}
						goto nextins;
						case 3: 
							switch(b4){
								case 0: DOMATH_SRC_NOTZERO(%,pc,a)
								case 1: DOMATH_SRC_NOTZERO(%,pc,b)
								case 2: DOMATH_SRC_NOTZERO(%,pc,c)
								case 3: DOMATH_SRC_NOTZERO(%,pc,pc)
								case 4: DOMATH_SRC_NOTZERO(%,pc,stp)
							}
						goto nextins;
						case 4: 
							switch(b4){
								case 0: DOMATH_SRC_NOTZERO(%,stp,a)
								case 1: DOMATH_SRC_NOTZERO(%,stp,b)
								case 2: DOMATH_SRC_NOTZERO(%,stp,c)
								case 3: DOMATH_SRC_NOTZERO(%,stp,pc)
								case 4: DOMATH_SRC_NOTZERO(%,stp,stp)
							}
						goto nextins;
					}
				goto nextins; /*mod*/
				case 5:
					switch(b3){ /*dst*/
						case 0: 
							switch(b4){
								case 0: DOMATH(&,a,a)
								case 1: DOMATH(&,a,b)
								case 2: DOMATH(&,a,c)
								case 3: DOMATH(&,a,pc)
								case 4: DOMATH(&,a,stp)
							}
						goto nextins;
						case 1: 
							switch(b4){
								case 0: DOMATH(&,b,a)
								case 1: DOMATH(&,b,b)
								case 2: DOMATH(&,b,c)
								case 3: DOMATH(&,b,pc)
								case 4: DOMATH(&,b,stp)
							}
						goto nextins;			
						case 2: 
							switch(b4){
								case 0: DOMATH(&,c,a)
								case 1: DOMATH(&,c,b)
								case 2: DOMATH(&,c,c)
								case 3: DOMATH(&,c,pc)
								case 4: DOMATH(&,c,stp)
							}
						goto nextins;
						case 3: 
							switch(b4){
								case 0: DOMATH(&,pc,a)
								case 1: DOMATH(&,pc,b)
								case 2: DOMATH(&,pc,c)
								case 3: DOMATH(&,pc,pc)
								case 4: DOMATH(&,pc,stp)
							}
						goto nextins;
						case 4: 
							switch(b4){
								case 0: DOMATH(&,stp,a)
								case 1: DOMATH(&,stp,b)
								case 2: DOMATH(&,stp,c)
								case 3: DOMATH(&,stp,pc)
								case 4: DOMATH(&,stp,stp)
							}
						goto nextins;
					}

				goto nextins; /*and*/
				case 6:
					switch(b3){ /*dst*/
						case 0: 
							switch(b4){
								case 0: DOMATH(|,a,a)
								case 1: DOMATH(|,a,b)
								case 2: DOMATH(|,a,c)
								case 3: DOMATH(|,a,pc)
								case 4: DOMATH(|,a,stp)
							}
						goto nextins;
						case 1: 
							switch(b4){
								case 0: DOMATH(|,b,a)
								case 1: DOMATH(|,b,b)
								case 2: DOMATH(|,b,c)
								case 3: DOMATH(|,b,pc)
								case 4: DOMATH(|,b,stp)
							}
						goto nextins;			
						case 2: 
							switch(b4){
								case 0: DOMATH(|,c,a)
								case 1: DOMATH(|,c,b)
								case 2: DOMATH(|,c,c)
								case 3: DOMATH(|,c,pc)
								case 4: DOMATH(|,c,stp)
							}
						goto nextins;
						case 3: 
							switch(b4){
								case 0: DOMATH(|,pc,a)
								case 1: DOMATH(|,pc,b)
								case 2: DOMATH(|,pc,c)
								case 3: DOMATH(|,pc,pc)
								case 4: DOMATH(|,pc,stp)
							}
						goto nextins;
						case 4: 
							switch(b4){
								case 0: DOMATH(|,stp,a)
								case 1: DOMATH(|,stp,b)
								case 2: DOMATH(|,stp,c)
								case 3: DOMATH(|,stp,pc)
								case 4: DOMATH(|,stp,stp)
							}
						goto nextins;
					}
				goto nextins; /*or*/
				case 7:
					switch(b3){ /*dst*/
						case 0: 
							switch(b4){
								case 0: DOMATH(^,a,a)
								case 1: DOMATH(^,a,b)
								case 2: DOMATH(^,a,c)
								case 3: DOMATH(^,a,pc)
								case 4: DOMATH(^,a,stp)
							}
						goto nextins;
						case 1: 
							switch(b4){
								case 0: DOMATH(^,b,a)
								case 1: DOMATH(^,b,b)
								case 2: DOMATH(^,b,c)
								case 3: DOMATH(^,b,pc)
								case 4: DOMATH(^,b,stp)
							}
						goto nextins;			
						case 2: 
							switch(b4){
								case 0: DOMATH(^,c,a)
								case 1: DOMATH(^,c,b)
								case 2: DOMATH(^,c,c)
								case 3: DOMATH(^,c,pc)
								case 4: DOMATH(^,c,stp)
							}
						goto nextins;
						case 3: 
							switch(b4){
								case 0: DOMATH(^,pc,a)
								case 1: DOMATH(^,pc,b)
								case 2: DOMATH(^,pc,c)
								case 3: DOMATH(^,pc,pc)
								case 4: DOMATH(^,pc,stp)
							}
						goto nextins;
						case 4: 
							switch(b4){
								case 0: DOMATH(^,stp,a)
								case 1: DOMATH(^,stp,b)
								case 2: DOMATH(^,stp,c)
								case 3: DOMATH(^,stp,pc)
								case 4: DOMATH(^,stp,stp)
							}
						goto nextins;
					}
				goto nextins; /*xor*/
				case 8:
					switch(b3){ /*dst*/
						case 0: DOMATHS(~,a)
						case 1: DOMATHS(~,b)
						case 2: DOMATHS(~,c)
						case 3: DOMATHS(~,pc)
						case 4: DOMATHS(~,stp)
						goto nextins;
					}
				goto nextins; /*neg*/
				case 9:
					switch(b3){ /*dst*/
						case 0: DOMATHS(!,a)
						case 1: DOMATHS(!,b)
						case 2: DOMATHS(!,c)
						case 3: DOMATHS(!,pc)
						case 4: DOMATHS(!,stp)
						goto nextins;
					}
				goto nextins; /*not*/
				case 0xa:
					switch(b3){ /*dst*/
						case 0: DOMATHS(!!,a)
						case 1: DOMATHS(!!,b)
						case 2: DOMATHS(!!,c)
						case 3: DOMATHS(!!,pc)
						case 4: DOMATHS(!!,stp)
						goto nextins;
					}
				goto nextins; /*boolify*/
				case 0xb:
					switch(b3){ /*dst*/
						case 0: 
							switch(b4){
								case 0: DOMATH(||,a,a)
								case 1: DOMATH(||,a,b)
								case 2: DOMATH(||,a,c)
								case 3: DOMATH(||,a,pc)
								case 4: DOMATH(||,a,stp)
							}
						goto nextins;
						case 1: 
							switch(b4){
								case 0: DOMATH(||,b,a)
								case 1: DOMATH(||,b,b)
								case 2: DOMATH(||,b,c)
								case 3: DOMATH(||,b,pc)
								case 4: DOMATH(||,b,stp)
							}
						goto nextins;			
						case 2: 
							switch(b4){
								case 0: DOMATH(||,c,a)
								case 1: DOMATH(||,c,b)
								case 2: DOMATH(||,c,c)
								case 3: DOMATH(||,c,pc)
								case 4: DOMATH(||,c,stp)
							}
						goto nextins;
						case 3: 
							switch(b4){
								case 0: DOMATH(||,pc,a)
								case 1: DOMATH(||,pc,b)
								case 2: DOMATH(||,pc,c)
								case 3: DOMATH(||,pc,pc)
								case 4: DOMATH(||,pc,stp)
							}
						goto nextins;
						case 4: 
							switch(b4){
								case 0: DOMATH(||,stp,a)
								case 1: DOMATH(||,stp,b)
								case 2: DOMATH(||,stp,c)
								case 3: DOMATH(||,stp,pc)
								case 4: DOMATH(||,stp,stp)
							}
						goto nextins;
					}
				goto nextins; /*logor*/
				case 0xc:
					switch(b3){ /*dst*/
						case 0: 
							switch(b4){
								case 0: DOMATH(&&,a,a)
								case 1: DOMATH(&&,a,b)
								case 2: DOMATH(&&,a,c)
								case 3: DOMATH(&&,a,pc)
								case 4: DOMATH(&&,a,stp)
							}
						goto nextins;
						case 1: 
							switch(b4){
								case 0: DOMATH(&&,b,a)
								case 1: DOMATH(&&,b,b)
								case 2: DOMATH(&&,b,c)
								case 3: DOMATH(&&,b,pc)
								case 4: DOMATH(&&,b,stp)
							}
						goto nextins;			
						case 2: 
							switch(b4){
								case 0: DOMATH(&&,c,a)
								case 1: DOMATH(&&,c,b)
								case 2: DOMATH(&&,c,c)
								case 3: DOMATH(&&,c,pc)
								case 4: DOMATH(&&,c,stp)
							}
						goto nextins;
						case 3: 
							switch(b4){
								case 0: DOMATH(&&,pc,a)
								case 1: DOMATH(&&,pc,b)
								case 2: DOMATH(&&,pc,c)
								case 3: DOMATH(&&,pc,pc)
								case 4: DOMATH(&&,pc,stp)
							}
						goto nextins;
						case 4: 
							switch(b4){
								case 0: DOMATH(&&,stp,a)
								case 1: DOMATH(&&,stp,b)
								case 2: DOMATH(&&,stp,c)
								case 3: DOMATH(&&,stp,pc)
								case 4: DOMATH(&&,stp,stp)
							}
						goto nextins;
					}
				goto nextins; /*logand*/
			}
			goto nextins;
			case 5:/* TODO */
			break;

		} /*end of that great big switch case for b1*/
		nextins:;
	} /*End of that great big while loop that encompasses the entire emulator.*/
	return;
}
