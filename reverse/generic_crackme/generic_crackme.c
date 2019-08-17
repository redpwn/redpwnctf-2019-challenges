#include <stdbool.h>
#include <stdio.h>

int inc(int x) {
	return x + 1;
}

// "doggy"
bool check(char *password) {
	if (inc(password[0]) != 'e') {
		return false;
	}
	if (inc(password[1]) != 'p') {
		return false;
	}
	if (inc(password[2]) != 'h') {
		return false;
	}
	if (inc(password[3]) != 'h') {
		return false;
	}
	if (inc(password[4]) != 'z') {
		return false;
	}
	return true;
}

int main(void)
{
	puts("plz enter password plz:");
	char buf[100];
	fgets(buf, sizeof(buf), stdin);
	if (check(buf)) {
		puts("good job kthxbye");
	} else {
		puts("lolno");
	}
}
