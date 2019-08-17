#include <limits.h>
#include <stdio.h>
#include <unistd.h>

__attribute__((unused))
static const char manifesto[] =
"/sh/nn/hshsi//h////hihbsiihnbs/n/shi/siiin/shbnih//isihbhii//hihiibshnh//n/"
"bsn/ihhn/ii/bs/hninsbbshi//b/nnb/nhi/s//nnsbnhi///iiih/sns/sh/bhnins/in///s"
"bssbisnhihnis/ssh/b/h//bhi/bhhnbn//i/ihbihs///nhbnihnii/n/h/hnhs/hbis////bn"
"///n/ssb//b//sshinis/////////sbi/bbsnih/b/nbi/in///s/sbnibiiih//ibb/nihb/bn"
"bn/b/ssh/bi/iinnni/n////h/hb/ih//ni/i/ibhnbhnbbnhnhb///si/ih//ibi/n/bsn/i/h"
"b/hs//ihs/h//i/bish/nbnn/nnss//b/i/bs///i//hsssiihbisnb/nnh//i/hhi/nn//inss"
"/ssshis//ishbsnhb/n/bsn/shnib/bsh/inbshs//snbhiiisnhihshbnsb//s/s/////b/sb/"
"/h/s/hi/nnn/hn//bsh/bibhs//i/nisi/s/bhshnn/snsibsb//i//hshhbhsbs////s/i/s/b"
"snhbbshbi/bih/i/shsn/hbnnhb//hsbinib//s/hnb/h///b/ii//nhhb/ss/bsbh//in//hb/"
"n/i/n///ns/i/inb/bhbni/bnhininbih/bb/sni/b/b//bb//ns/n///nsnbs/n/s/ih/bs///"
"snhns/s/s//ihs/hbshhsin//s///i/hssh/bbb//nshh//hib/s//hhbihs//hs/sh/hbhsb/s"
"shh/hisib//b/ib/ih/is/nbs//bnh/hhbhs/n/n/bb/hihbbbhbni/hnsh/h/ii//hnnh//shn"
"/hbbbbihh/bh/bnihi/ihhb//hsn/s//ih/sishinbb///ssh/hnbnh/bbihnbhnnn/i/i/n/hs"
"//h////nih/is/ns//nhbb/ih//bin//sh";

__attribute__((unused))
static void sub_1258(void)
{
	__asm__("int3");
}

__attribute__((unused))
static void sub_1263(void)
{
	__asm__("int3");
}

__attribute__((unused))
static void sub_1289(void)
{
	__asm__("int3");
}

__attribute__((unused))
static void sub_1337(void)
{
	__asm__("syscall");
}

__attribute__((unused))
static void sub_1358(void)
{
	__asm__("int3");
}

static size_t get_int(void)
{
	size_t num;

	scanf("%zu", &num);
	getchar();
	return num;
}

int main(void)
{
	char buf[1];
	size_t num_bytes;

	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
	setbuf(stderr, NULL);

	printf("[#] number of bytes: ");
	num_bytes = get_int();
	read(num_bytes, buf, 100000);
}

