#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "get_next_line_utils.c"

#ifndef BUFFER_SIZE
#define	BUFFER_SIZE 5
#endif

struct s_buffer
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_processed;
} s_buffer;

int	process(struct s_buffer *buffer, char **total)
{
	char	*split;
	int		*bytes;
	char 	*buf;
	char	*temp;
	int		size_left;

	bytes = &(buffer->bytes_processed);
	buf = buffer->buffer;

	if (ft_strlen(buf) == 0)
		return (0);
	out("process: ");
	outn(&buf[*bytes]);
	size_left = ft_strlen(&buf[*bytes]);
	out("bytes processed : ");
	outnbrn(*bytes);
	out("size left :");
	outnbrn(size_left);
	while (buf[*bytes] == '\n')
	{
			outn("X");
			*bytes = *bytes + 1;
			if (*bytes == BUFFER_SIZE)
			{
				outn("exit n");
				return (1);
			}
	}
	if (buf[*bytes] == '\n')
	{
		while((*bytes < BUFFER_SIZE) && (buf[*bytes] == '\n'))
		{

		}
	}
	if (size_left > 0)
	{
		split = *ft_split(&buf[*bytes], '\n');
		*bytes += ft_strlen(split);
		buffer->bytes_processed = *bytes;
		temp = *total;
		out("split = ");
		outn(split);
		*total = ft_strjoin(temp, split);
		free(temp);
		if (ft_strlen(split) >= size_left)
		{
			free(split);
			outn("exit a");
			return (0);
		}
		free(split);
		outn("exit b");
		return (1);
	}
	outn("exit C");
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static struct s_buffer	buffer;
	char					*total;
	int						found_line;
	int						n;

	total = (char*)malloc(1);
	total[0] = 0;
	found_line = 0;
	n = 1;

	out("\n- get next line -\n");
	while (n > 0)
	{
		if (process(&buffer, &total))
			break;
		n = read(fd, buffer.buffer, BUFFER_SIZE);
		buffer.bytes_processed = 0;
		buffer.buffer[n] = 0;
	}
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
	*line = total;
	return (1);
}


int main(int argc, char const *argv[])
{
	int		fd = open("nums", O_RDONLY);
	// int		fd = open("lines", O_RDONLY);
	// int		fd = open("lorem", O_RDONLY);

	char *line;

	for (size_t i = 0; i < 3; i++)
	{
		get_next_line(fd, &line);
		ft_putstr_fd("line: ", 1);
		ft_putstr_fd(line, 1);
		ft_putchar_fd('\n',1);
		free(line);
	}

	// while (get_next_line(fd, &line))
	// {
	// 	out("line: ");
	// 	ft_putstr_fd(line, 1);
	// 	ft_putchar_fd('\n',1);
	// 	free(line);
	// }
	close(fd);
	return 0;
}
