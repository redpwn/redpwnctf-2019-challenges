#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

static void die(void)
{
	kill(-getppid(), SIGINT);
	exit(1);
}

int main(void)
{
	unsigned char c;

	for (;;) {
		ssize_t n = read(0, &c, 1);
		if (n == 0) {
			die();
		}
		if (n == -1 || c == '') {
			continue;
		}
		n = write(1, &c, 1);
		if (n != 1) {
			die();
		}
	}
}
