#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "get_next_line_utils.c"

#ifndef BUFFER_SIZE
		int BUFFER_SIZE = 500;
#endif

int	get_next_line(int fd, char **line)
{
	static int	total_bytes;
	int 		n;
	char		buffer[BUFFER_SIZE]; // por qué no char* ?
	char		*chunk;
	char		*next_line;
	char		*temp;

	next_line = (char*)malloc(0); // me aseguro de que siempre se pueda liberar
	while ((n = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		// suma a la linea acumulada.
		chunk = *ft_split(buffer, '\n');
		temp = next_line;
		next_line = ft_strjoin(next_line, chunk);
		free(chunk);
		free(temp);
		if (n < BUFFER_SIZE)
		// termina y devuelve
		{
			printf("%s\n", next_line);
			return (0);
		}
	}

	return (0);
}

int main(int argc, char const *argv[])
{
	char	*path = "nums";
	// char	*path = "lines";
	// char	*path = "lorem";
	int		fd = open(path, O_RDONLY);
	char	**line;
	get_next_line(fd, line);
	close(fd);
	return 0;
}
