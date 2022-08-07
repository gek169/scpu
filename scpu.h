
#ifndef SCPU_MEM_SIZE
#define SCPU_MEM_SIZE 0x10000
#endif

#include <stdnoreturn.h>
int a,b,c,d, e,f, stp, pc;
int M[SCPU_MEM_SIZE];


#ifdef SCPU_TRUST_PROGRAM
//static inline int fetch(){return M[((unsigned)(pc++))];}
//static inline int Mread(int adr){return M[(unsigned)adr];}
//static inline void Mwrite(int adr, int val){M[(unsigned)adr] = val;}
//safe versions
#else
static inline int fetch(){return M[ ((unsigned)(pc++)) % SCPU_MEM_SIZE];}
static inline int Mread(int adr){return M[ ((unsigned)adr) % SCPU_MEM_SIZE];}
static inline void Mwrite(int adr, int val){M[ ((unsigned)adr) % SCPU_MEM_SIZE] = val;}
#endif

noreturn void scpu_hook0();
noreturn void scpu_hook1();
noreturn void scpu_hook2();
noreturn void scpu_hook3();
noreturn void scpu_hook4();
noreturn void scpu_hook5();
noreturn void scpu_hook6();
noreturn void scpu_hook7();
noreturn void scpu_hook8();
noreturn void scpu_hook9();
noreturn void scpu_hookA();
noreturn void scpu_hookB();
noreturn void scpu_hookC();
noreturn void scpu_hookD();
noreturn void scpu_hookE();
noreturn void scpu_hookF();


noreturn void scpu_die();



noreturn void fetch_decode();

//Immediate load (2)
noreturn void imlda(){ a=fetch();  fetch_decode();};
noreturn void imldb(){ b=fetch();  fetch_decode();};
noreturn void imldc(){ c=fetch();  fetch_decode();};
noreturn void imldd(){ d=fetch();  fetch_decode();};
noreturn void imlde(){ e=fetch();  fetch_decode();};
noreturn void imldf(){ f=fetch();  fetch_decode();};
//Addressed Load (2)
noreturn void adrlda(){  a=Mread(fetch()); fetch_decode();};
noreturn void adrldb(){  b=Mread(fetch()); fetch_decode();};
noreturn void adrldc(){  c=Mread(fetch()); fetch_decode();};
noreturn void adrldd(){  d=Mread(fetch()); fetch_decode();};
noreturn void adrlde(){  e=Mread(fetch()); fetch_decode();};
noreturn void adrldf(){  f=Mread(fetch()); fetch_decode();};
//Addressed Store (2)
noreturn void adrsta(){ Mwrite(fetch(),a);  fetch_decode();};
noreturn void adrstb(){ Mwrite(fetch(),b);  fetch_decode();};
noreturn void adrstc(){ Mwrite(fetch(),c);  fetch_decode();};
noreturn void adrstd(){ Mwrite(fetch(),d);  fetch_decode();};
noreturn void adrste(){ Mwrite(fetch(),e);  fetch_decode();};
noreturn void adrstf(){ Mwrite(fetch(),f);  fetch_decode();};

//Pointer'd Load (Pointer in A) (1)
noreturn void ptralda(){ a=Mread(a); fetch_decode();};
noreturn void ptraldb(){ b=Mread(a); fetch_decode();};
noreturn void ptraldc(){ c=Mread(a); fetch_decode();};
noreturn void ptraldd(){ d=Mread(a); fetch_decode();};
noreturn void ptralde(){ e=Mread(a); fetch_decode();};
noreturn void ptraldf(){ f=Mread(a); fetch_decode();};
//Pointer'd Store (Pointer in A or B) (1)
noreturn void ptrbsta(){ Mwrite(b,a); fetch_decode();};
noreturn void ptrastb(){ Mwrite(a,b);  fetch_decode();};
noreturn void ptrastc(){ Mwrite(a,c);  fetch_decode();};
noreturn void ptrastd(){ Mwrite(a,d);  fetch_decode();};
noreturn void ptraste(){ Mwrite(a,e);  fetch_decode();};
noreturn void ptrastf(){ Mwrite(a,f);  fetch_decode();};

//astp stpa (1)
noreturn void astp(){ a = stp; fetch_decode();};
noreturn void stpa(){ stp = a; fetch_decode();};
//jmpa (1)
noreturn void jmpa(){ pc = a; fetch_decode();};
//jmp (2)
noreturn void jmp(){ pc = fetch(); fetch_decode();};
//Push pop register (1)
noreturn void pusha(){  Mwrite(stp++,a); fetch_decode();};
noreturn void pushb(){  Mwrite(stp++,b); fetch_decode();};
noreturn void pushc(){  Mwrite(stp++,c); fetch_decode();};
noreturn void pushd(){  Mwrite(stp++,d); fetch_decode();};
noreturn void pushe(){  Mwrite(stp++,e); fetch_decode();};
noreturn void pushf(){  Mwrite(stp++,f); fetch_decode();};
noreturn void pushpc(){ Mwrite(stp++,pc); fetch_decode();};

noreturn void popa(){  a = Mread(--stp); fetch_decode();};
noreturn void popb(){  b = Mread(--stp); fetch_decode();};
noreturn void popc(){  c = Mread(--stp); fetch_decode();};
noreturn void popd(){  d = Mread(--stp); fetch_decode();};
noreturn void pope(){  e = Mread(--stp); fetch_decode();};
noreturn void popf(){  f = Mread(--stp); fetch_decode();};
noreturn void poppc(){ pc = Mread(--stp); fetch_decode();}; //(Also called "ret")
//Function call immediate (2)
noreturn void imcall(){ Mwrite(stp++,pc); pc=fetch(); fetch_decode();};
//Function call Indirect (1)
noreturn void calla(){ Mwrite(stp++,pc); pc=a; fetch_decode();};
//Swap Registers
noreturn void aeqb(){ a=b; fetch_decode();};
noreturn void aeqc(){ a=c; fetch_decode();};
noreturn void aeqd(){ a=d; fetch_decode();};
noreturn void aeqe(){ a=e; fetch_decode();};
noreturn void aeqf(){ a=f; fetch_decode();};

noreturn void beqa(){ b=a; fetch_decode();};
noreturn void beqc(){ b=c; fetch_decode();};
noreturn void beqd(){ b=d; fetch_decode();};
noreturn void beqe(){ b=e; fetch_decode();};
noreturn void beqf(){ b=f; fetch_decode();};

noreturn void ceqa(){ c=a; fetch_decode();};
noreturn void ceqb(){ c=b; fetch_decode();};
noreturn void ceqd(){ c=d; fetch_decode();};
noreturn void ceqe(){ c=e; fetch_decode();};
noreturn void ceqf(){ c=f; fetch_decode();};

noreturn void deqa(){ d=a; fetch_decode();};
noreturn void deqb(){ d=b; fetch_decode();};
noreturn void deqc(){ d=c; fetch_decode();};
noreturn void deqe(){ d=e; fetch_decode();};
noreturn void deqf(){ d=f; fetch_decode();};

noreturn void eeqa(){ e=a; fetch_decode();};
noreturn void eeqb(){ e=b; fetch_decode();};
noreturn void eeqc(){ e=c; fetch_decode();};
noreturn void eeqd(){ e=d; fetch_decode();};
noreturn void eeqf(){ e=f; fetch_decode();};

noreturn void feqa(){ f=a; fetch_decode();};
noreturn void feqb(){ f=b; fetch_decode();};
noreturn void feqc(){ f=c; fetch_decode();};
noreturn void feqd(){ f=d; fetch_decode();};
noreturn void feqe(){ f=e; fetch_decode();};
//Math (1)
noreturn void add(){  a += b; fetch_decode();}
noreturn void sub(){  a -= b; fetch_decode();}
noreturn void mul(){  a *= b; fetch_decode();}
noreturn void div(){  if(b)a = a / b; fetch_decode();}
noreturn void udiv(){ if(b)a = (unsigned)a / (unsigned)b;	fetch_decode();}
noreturn void mod(){  if(b)a = a % b; fetch_decode();}
noreturn void umod(){ if(b)a = (unsigned)a % (unsigned)b; fetch_decode();}
noreturn void lshift(){ a <<= b; fetch_decode();}
noreturn void rshift(){ a >>= b; fetch_decode();}
noreturn void and(){ a = a & b; fetch_decode();}
noreturn void or(){  a = a | b; fetch_decode();}
noreturn void xor(){ a = a^b; fetch_decode();}
noreturn void neg(){ a = ~a; fetch_decode();}
noreturn void boolify(){ a = !!a; fetch_decode();}
noreturn void incra(){ a++; fetch_decode();}
noreturn void decra(){ a--; fetch_decode();}


void (*instruction_functions[])(void) = {
//0-5




	imlda,
	imldb,
	imldc,
	imldd,
	imlde,
	imldf,
//6-11



	adrlda,
	adrldb,
	adrldc,
	adrldd,
	adrlde,
	adrldf,



//12-17
	adrsta,
	adrstb,
	adrstc,
	adrstd,
	adrste,
	adrstf,



//18-23
	ptralda,
	ptraldb,
	ptraldc,
	ptraldd,
	ptralde,
	ptraldf,



//24-29
	ptrbsta,
	ptrastb,
	ptrastc,
	ptrastd,
	ptraste,
	ptrastf,



//30-31
astp,
stpa,







//32-33
jmpa,
jmp,







//34-40
pusha,
pushb,
pushc,
pushd,
pushe,
pushf,
pushpc,


//41-47
popa,
popb,
popc,
popd,
pope,
popf,
poppc,


//48,49
imcall, 
calla,







//50-59
aeqb,
aeqc,
aeqd,
aeqe,
aeqf,
beqa,
beqc,
beqd,
beqe,
beqf,









//60-69
ceqa,
ceqb,
ceqd,
ceqe,
ceqf,
deqa,
deqb,
deqc,
deqe,
deqf,









//70-79
eeqa,
eeqb,
eeqc,
eeqd,
eeqf,
feqa,
feqb,
feqc,
feqd,
feqe,









//80-88
add,
sub,
mul,
div,
udiv,
mod,
umod,
lshift,
rshift,
//89-91
and,
or,
xor,






//92-95
neg,
boolify,
incra,
decra,
//rest of the array
//96-99
scpu_hook0,scpu_hook1,scpu_hook2,scpu_hook3,
//100-107
scpu_hook4,scpu_hook5,scpu_hook6,scpu_hook7,
scpu_hook8,scpu_hook9,scpu_hookA,scpu_hookB,
//108-115
scpu_hookC,scpu_hookD,scpu_hookE,scpu_hookF,
fetch_decode,fetch_decode,fetch_decode,fetch_decode,
//116-123
fetch_decode,fetch_decode,fetch_decode,fetch_decode,
fetch_decode,fetch_decode,fetch_decode,fetch_decode,
//124-131
fetch_decode,fetch_decode,fetch_decode,fetch_decode,
fetch_decode,fetch_decode,fetch_decode,fetch_decode,

fetch_decode,fetch_decode,fetch_decode,fetch_decode,
fetch_decode,fetch_decode,fetch_decode,fetch_decode,
fetch_decode,fetch_decode,fetch_decode,fetch_decode,
fetch_decode,fetch_decode,fetch_decode,fetch_decode,
fetch_decode,fetch_decode,fetch_decode,fetch_decode,
fetch_decode,fetch_decode,fetch_decode,fetch_decode,
fetch_decode,fetch_decode,fetch_decode,fetch_decode,
fetch_decode,fetch_decode,fetch_decode,fetch_decode,
fetch_decode,fetch_decode,fetch_decode,fetch_decode,
fetch_decode,fetch_decode,fetch_decode,fetch_decode,
fetch_decode,fetch_decode,fetch_decode,fetch_decode,
fetch_decode,fetch_decode,fetch_decode,fetch_decode,
fetch_decode,fetch_decode,fetch_decode,fetch_decode,
fetch_decode,fetch_decode,fetch_decode,fetch_decode,
fetch_decode,fetch_decode,fetch_decode,fetch_decode,
fetch_decode,fetch_decode,fetch_decode,fetch_decode,
fetch_decode,fetch_decode,fetch_decode,fetch_decode,
fetch_decode,fetch_decode,fetch_decode,fetch_decode,
fetch_decode,fetch_decode,fetch_decode,fetch_decode,
fetch_decode,fetch_decode,fetch_decode,fetch_decode,
fetch_decode,fetch_decode,fetch_decode,fetch_decode
};


noreturn void fetch_decode(){
	int opcode = fetch();
	instruction_functions[opcode&0x7f]();
}

noreturn void startSCPUMachine(int _a, int _b, int _c, int _d, int _e, int _f, int _stp, int _pc){
	pc = _pc;
	a = _a;
	b = _b;
	c = _c;
	d = _d;
	e = _e;
	f = _f;
	stp = _stp;
	fetch_decode();
}



