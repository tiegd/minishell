#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *env;

	env = getenv("PATH");
	printf("%s\n", env);

	return 0;
}