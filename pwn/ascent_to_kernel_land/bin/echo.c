#include "types.h"
#include "stat.h"
#include "user.h"

#define HEXDIGIT(c)                                                            \
	((c) <= '9' ? (c) - '0' : (c) <= 'Z' ? (c) - 'A' + 10 : (c) - 'a' + 10)

static void putchar(char c)
{
	write(1, &c, 1);
}

int main(int argc, char *argv[])
{
	int i, j, nflag = 0;
	unsigned int x;

	if (!strcmp(argv[1], "-n")) {
		nflag = 1;
		argv++;
		argc--;
	}
	for (i = 1; i < argc; i++) {
		for (j = 0; argv[i][j]; j++) {
			if (argv[i][j] == '\\') {
				j++;
				if (argv[i][j] == 'x') {
					j++;
					x = HEXDIGIT(argv[i][j]) * 0x10
					    + HEXDIGIT(argv[i][j + 1]);
					putchar(x);
					j++;
					continue;
				}
			}
			putchar(argv[i][j]);
		}
		if (i + 1 != argc) {
			putchar(' ');
		}
	}
	if (!nflag) {
		putchar('\n');
	}
	exit();
}
