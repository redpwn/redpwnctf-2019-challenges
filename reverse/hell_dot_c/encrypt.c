#include <stdio.h>
#include <stdlib.h>

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

static void print_ints(int *nums, size_t size)
{
	for (size_t i = 0; i < size; i++) {
		printf("%d%c", nums[i], i + 1 == size ? '\n' : ' ');
	}
}

static void print_succ_int(int num)
{
	if (num) {
		printf("succ(");
		print_succ_int(num - 1);
		printf(")");
	} else {
		printf("0");
	}
}

static void print_succ_ints(int *nums, size_t size)
{
	printf("{\n");
	for (size_t i = 0; i < size; i++) {
		print_succ_int(nums[i]);
		printf(",\n");
	}
	printf("}\n");
}

int main(void)
{
	static char buf[1024];
	static int ibuf[1024];

	fgets(buf, sizeof(buf), stdin);
	duffcpy(ibuf, buf, sizeof(buf));
	duff(ibuf, sizeof(buf));
	print_succ_ints(ibuf, sizeof(buf));
}
