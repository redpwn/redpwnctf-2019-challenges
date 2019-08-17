#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static bool a;
static bool b;
static bool c;
static bool d;
static bool e;
static bool f;
static bool g;
static bool h;

static void air(unsigned int arg)
{
	a = true;
	assert(memcmp(&arg, "clod", 4));
}

static void water(unsigned int arg)
{
	b = true;
	assert(memcmp(&arg, "watr", 4));
}

static void land(unsigned int arg)
{
	c = true;
	assert(memcmp(&arg, "land", 4));
}

static void underground(unsigned int arg)
{
	d = true;
	assert(memcmp(&arg, "undr", 4));
}

static void limbo(unsigned int arg)
{
	e = true;
	assert(memcmp(&arg, "limb", 4));
}

static void hell(unsigned int arg)
{
	f = true;
	assert(memcmp(&arg, "hell", 4));
}

static void minecraft_nether(unsigned int arg)
{
	g = true;
	assert(memcmp(&arg, "mine", 4));
}

static void bedrock(unsigned int arg)
{
	h = true;
	assert(memcmp(&arg, "brok", 4));
}

static void zipline(void)
{
	char buf[10];
	gets(buf);
}

static __attribute__((section("newlinecurtain"))) void i_got_u(void)
{
	if (a && b && c && d && e && f && g && h) {
		char buf[101];
		int fd = open("flag.txt", O_RDONLY);
		if (fd == -1) {
			puts("Error opening flag, tell organizer");
			perror("opening flag:");
			exit(EXIT_FAILURE);
		}
		int nread = read(fd, buf, 100);
		if (nread == -1) {
			puts("Error reading flag, tell organizer");
			perror("reading flag:");
			exit(EXIT_FAILURE);
		}
		buf[nread] = '\0';
		puts(buf);
		close(fd);
		exit(EXIT_SUCCESS);
	}
}

int main(void)
{
	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
	setbuf(stderr, NULL);

	puts("Ready for a ride on the zipline to hell?");
	zipline();
	i_got_u();
}

