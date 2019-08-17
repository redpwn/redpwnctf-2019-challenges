#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#define ANSI_BOLD "\033[1m"
#define ANSI_RED "\033[31m"
#define ANSI_GREEN "\033[32m"
#define ANSI_BLUE "\033[34m"
#define ANSI_NORM "\033[0m"
#define PAGE_SIZE 4096
#define US 300000

__attribute__((aligned(PAGE_SIZE)))
static char art_of_computer_programming[PAGE_SIZE];

static void protec(void)
{
	mprotect(art_of_computer_programming, PAGE_SIZE,
		 PROT_READ | PROT_WRITE | PROT_EXEC);
}

static void tex(void)
{
	char *s = art_of_computer_programming;
	memset(s, '\\', PAGE_SIZE);
	read(0, s, PAGE_SIZE);
	for (size_t i = 0; i < PAGE_SIZE; i++) {
		assert((s[i] >= 0x20 && s[i] < 0x7f) || s[i] == '\n');
	}
}

static void chec(void)
{
	char *s = art_of_computer_programming;

#if 0
	__asm__("movq %0, %%rsp"
		:
		: "a" (&s[PAGE_SIZE]));
#endif
	((void (*)(void)) s)();
}

int main(void)
{
	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
	setbuf(stderr, NULL);

	usleep(US);
	puts("[🔒] He " ANSI_RED ANSI_BOLD "protec" ANSI_NORM);
	protec();
	usleep(US);
	puts("[" ANSI_BOLD "Ω" ANSI_NORM " ] He " ANSI_GREEN ANSI_BOLD "TeX" ANSI_NORM);
	tex();
	usleep(US);
	puts("But " ANSI_BOLD "most" ANSI_NORM " importantly");
	usleep(US);
	puts("[💸] He " ANSI_BLUE ANSI_BOLD "chec" ANSI_NORM);
	usleep(US);
	chec();
}

