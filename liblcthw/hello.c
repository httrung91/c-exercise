#include <stdio.h>

int main(int argc, char *argv[])
{
	int i = 0;
	int j = 0;
	for (i = j = 0; j < 10; i = j = j + 1) {
		printf("loop: %d, %d\n", i, j);
	}

	return 0;
}
