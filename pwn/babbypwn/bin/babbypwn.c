#include <stdio.h>
#include <unistd.h>

static void sleep_puts(const char *s)
{
	sleep(2);
	puts(s);
}

int main(void)
{
	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
	setbuf(stderr, NULL);
	sleep_puts("So you want the flag, I see");
	sleep_puts("You should stop");
	sleep_puts("Stealing is wrong");
	sleep_puts("You wouldn't steal a car");
	sleep_puts("Well...");
	sleep_puts("Okay");
	sleep_puts("But know this");
	sleep_puts("You are irredeemably a bad person");
	puts("flag{st341ing_is_wr0ng}");
}

