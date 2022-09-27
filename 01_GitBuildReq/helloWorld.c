#include <stdio.h>

#define MAX_SIZE 30

int main() {
	char s[30] = {};
	scanf("%29[^\n]s", s);
	printf("Hello, %s!\n", s);
	return 0;
}

