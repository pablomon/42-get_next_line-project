#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "get_next_line_utils.c"

#ifndef BUFFER_SIZE
#define	BUFFER_SIZE 10
#endif

struct s_buffer
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_processed;
} s_buffer;

int	process(struct s_buffer *buffer, char **total)
{
	char	*split;
	int		bytes;
	char 	*buf;
	char	*temp;
	int		size_left;

	bytes = (buffer->bytes_processed);
	buf = buffer->buffer;

	if (!buf)
		return (0);
	out("process: ");
	outn(&buf[bytes]);
	while(buf[bytes] == '\n')
		bytes++;
	size_left = ft_strlen(&buf[bytes]);
	out("bytes processed : ");
	outnbrn(bytes);
	out("size left :");
	outnbrn(size_left);
	if (size_left > 0)
	{
		split = *ft_split(&buf[bytes], '\n');
		bytes += ft_strlen(split);
		buffer->bytes_processed = bytes;
		temp = *total;
		*total = ft_strjoin(*total, split);
		free(temp);
		out("split = ");
		outn(split);
		if (ft_strlen(split) == size_left)
		{
			free(split);
			outn("exit a");
			return (0);
		}
		free(split);
		outn("exit b");
		return (1);
	}
	outn("exit c");
	return (0);
}

// Como manejar la memoria de line??
int	get_next_line(int fd, char **line)
{
	static struct s_buffer	buffer;
	char					*total;
	int						finished;
	int						n;

	total = (char*)malloc(1);
	total[0] = 0;
	finished = 0;

	out("\n- get next line -\n");
	while (!finished)
	{
		while (process(&buffer, &total))

		n = read(fd, buffer.buffer, BUFFER_SIZE);
		buffer.bytes_processed = 0;
		if (n == 0)
		{
			outn("-EOF-");
			return (0);
		}
		if (n < 0)
		{
			outn("-ERROR-");
			return (-1);
		}
		buffer.buffer[n] = 0;
	}
	*line = total;
	return (1);
}


int main(int argc, char const *argv[])
{
	int		fd = open("nums", O_RDONLY);
	// int		fd = open("lines", O_RDONLY);
	// int		fd = open("lorem", O_RDONLY);

	char *line;

	// get_next_line(fd, &line);
	// ft_putstr_fd("line: ", 1);
	// ft_putstr_fd(line, 1);
	// ft_putchar_fd('\n',1);
	// free(line);
	// get_next_line(fd, &line);
	// ft_putstr_fd("line: ", 1);
	// ft_putstr_fd(line, 1);
	// ft_putchar_fd('\n',1);
	while (get_next_line(fd, &line))
	{
		out("line: ");
		ft_putstr_fd(line, 1);
		ft_putchar_fd('\n',1);
		free(line);
	}
	close(fd);
	return 0;
}
