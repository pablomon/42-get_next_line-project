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
	int			buffer_offset;

	position = 0;
	prev = (char*)malloc(0); // me aseguro de que siempre se pueda liberar
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) != 0)
	{
		if (bytes_read < 0)
			return (-1);
		if (position + bytes_read < last_position)
		{
			position += bytes_read;
			ft_putstr_fd("pos: ",1);
			ft_putnbr_fd(position, 1);
			ft_putstr_fd("\n",1);
			continue;
		}
		buffer_offset = 0;
		while (position + buffer_offset < last_position )
			buffer_offset++;
		if (buffer[buffer_offset + 1] == '\n')
		{
			ft_putstr_fd("aqui",1);
			last_position++;
			return (1);
		}
		chunk = buffer + buffer_offset;
		ft_putstr_fd(chunk,1);
		// suma a la linea acumulada.
		chunk = *ft_split(chunk, '\n');
		join = ft_strjoin(prev, chunk);
		free(prev);
		prev = join;
		*line = prev;
		position = position + ft_strlen(chunk);
		last_position = position;
		if (ft_strlen(chunk) < bytes_read)
		// fin de linea
		{
			free(chunk);
			ft_putstr_fd("last pos: ",1);
			ft_putnbr_fd(last_position, 1);
			ft_putstr_fd("\n",1);
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
	while (get_next_line(fd, line))
	{
		ft_putstr_fd(*line, 1);
		ft_putchar_fd('\n',1);
	}
	close(fd);
	return 0;
}
