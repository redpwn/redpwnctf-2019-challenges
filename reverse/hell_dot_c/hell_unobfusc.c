#include <stdio.h>
#include <stdlib.h>

#define ARRAY_LEN(arr) (sizeof(arr) / 0[arr])

#define S struct s

S {
	S *s;
};

static S *succ(S *num)
{
	S *tmp;
	tmp = num;
	num = malloc(sizeof(S));
	num->s = tmp;
	return num;
}

static int peano2int(S *num)
{
	int x = 0;

	for (; num; num = num->s, x++);
	return x;
}

static S *int2peano(int num)
{
	S *s = 0;

	for (int i = 0; i < num; i++) {
		s = succ(s);
	}
	return s;
}

static int peanocmp(S *n1, S *n2)
{
	for (; n1 && n2; n1 = n1->s, n2 = n2->s);
	return n1 || n2;
}

static void duff(int *p, size_t size)
{
	register int n = (size + 7) / 8;

	switch (size % 8)
	{
		case 0:        do {  *p ^= 0x63; p++;
				       case 7:              *p ^= 48; p++;
				       case 6:
				       case 5:              *p <<= 4; p++;
				       case 4:              *p <<= 2; p++;
				       case 3:              *p *= 55; p++;
				       case 2:              *p -= -97; p++;
				       case 1:              *p += 44; p++;
			       } while (--n > 0);
	}
}

static void duffcpy(int *dst, char *src, size_t size)
{
	register int n = (size + 7) / 8;

	switch (size % 8)
	{
		case 0:        do {  *dst++ = *src++;
				       case 7:              *dst++ = *src++;
				       case 6:              *dst++ = *src++;
				       case 5:              *dst++ = *src++;
				       case 4:              *dst++ = *src++;
				       case 3:              *dst++ = *src++;
				       case 2:              *dst++ = *src++;
				       case 1:              *dst++ = *src++;
			       } while (--n > 0);
	}
}

static int check(int *nums, size_t size)
{
	S *arr[1024] =
#include "encrypted.inc"
	;
	S *p;

	for (int i = 0; i < size; i++) {
		p = int2peano(nums[i]);
		if (peanocmp(p, arr[i])) {
			return 0;
		}
	}
	return 1;
}

int main(void)
{
	static char buf[1024];
	static int ibuf[1024];

	fgets(buf, sizeof(buf), stdin);
	duffcpy(ibuf, buf, sizeof(buf));
	duff(ibuf, sizeof(buf));
	return !check(ibuf, sizeof(buf));
}
