#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// "70517"
bool check(int x)
{
	return x * 10 + 5 == 705175;
}

int main(void)
{
	printf("Enter access code: ");
	int num;
	scanf("%d", &num);
	if (check(num)) {
		puts("Access granted");
	} else {
		puts("Bzzzzrrrppp");
	}
}
