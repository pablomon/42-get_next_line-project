#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "get_next_line_utils.c"

#ifndef BUFFER_SIZE
#define	BUFFER_SIZE 1
#endif

int	get_next_line(int fd, char **line)
{
	static int	last_position;
	int 		bytes_read;
	int			position;
	char		buffer[BUFFER_SIZE]; // por qué no char* ?
	char		*chunk;
	char		*prev;
	char		*join;

	position = 0;
	prev = (char*)malloc(0); // me aseguro de que siempre se pueda liberar
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) != 0)
	{
		if (bytes_read < 0)
			return (-1);
		if (position + bytes_read < last_position)
		{

		}
		else
		{
			/* code */
		}
		if (buffer[0] == '\n')
			return (1);
		// suma a la linea acumulada.
		chunk = *ft_split(buffer, '\n');
		join = ft_strjoin(prev, chunk);
		free(prev);
		prev = join;
		*line = prev;
		if (ft_strlen(chunk) < BUFFER_SIZE)
		// termina y devuelve
		{
			free(chunk);
			ft_putstr_fd("- linea -\n",1);
			return (1);
		}
	}
	ft_putstr_fd("- EOF -\n",1);
	return (0);
}

int main(int argc, char const *argv[])
{
	int		fd = open("nums", O_RDONLY);
	// int		fd = open("lines", O_RDONLY);
	// int		fd = open("lorem", O_RDONLY);

	char	**line;
	char	*ptr;
	*line = ptr;
	get_next_line(fd, line);
	ft_putstr_fd(*line, 1);
	close(fd);
	return 0;
}
