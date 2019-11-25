#include <stdio.h>
#include <stdlib.h>

int	get_next_line(int fd, char **line)
{

}

int main(int argc, char const *argv[])
{
	#ifndef BUFFER_SIZE
		printf("BUFFER_SIZE not defined at compilation time. Exiting.\n");
		char **line;
		get_next_line(1, line);
		printf("%s\n", line);
	#else
		printf("BUFFER_SIZE = %d.\n", BUFFER_SIZE);
	#endif



	return 0;
}
