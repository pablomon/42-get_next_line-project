#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void modify1(char** str)
{
	char *ptr;
	char *a = *str;
	ptr = a;
	for (size_t i = 0; i < 5; i++)
	{
		*a = 'x';
		// write(1, &*a, 1);
		a++;
	}

	*str = ptr;
}

void modify2(char** str)
{

}

int main(int argc, char const *argv[])
{
	char	*char1 = "cahr 1";
	char	*char2;
	char	char3[] = "perrafiel";
	char	*char4 = (char*)malloc(20);
	char	*char5 = NULL;
	for (size_t i = 0; i < 5; i++)
	{
		char4[i] = 'a';
	}

	char *str = char4;
	modify1(&str);
	printf("%s\n", str);

	return 0;
}
