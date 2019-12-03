#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "get_next_line_utils.c"

#ifndef BUFFER_SIZE
#define	BUFFER_SIZE 5
#endif

int	append_chunk(char **total, char *chunk)
{
	char	*split;
	char	*join;

	split = *ft_split(chunk, '\n');
	if (*total == NULL)
		*total = (char*)malloc(0);
	join = ft_strjoin(*total, split);
	free(*total);
	*total = join;
	return (ft_strlen(split));
}

int	get_next_line(int fd, char **line)
{
	static int	last_pos;
	char	buffer[BUFFER_SIZE];
	int		bytes_read;
	int		pos;
	int		n;

	pos = 0;
	ft_putstr_fd("last pos:",1);
	ft_putnbr_fd(last_pos,1);
	ft_putstr_fd("\n",1);
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		ft_putstr_fd("buffer : ", 1);
		ft_putstr_fd(buffer, 1);
		ft_putstr_fd("\n", 1);
		n = 0;
		if (last_pos != 0)
		{
			if (pos + bytes_read < last_pos + 1)
			{
				pos += bytes_read;
				ft_putstr_fd("pos:",1);
				ft_putnbr_fd(pos,1);
				ft_putchar_fd('\n',1);
				continue;
			}
			else
			{
				while (pos + n < last_pos + 1)
				{
					n++;
					ft_putstr_fd("n:",1);
					ft_putnbr_fd(n,1);
					ft_putchar_fd('\n',1);
				}
			}
		}
		write(1, &buffer[n], 1);
		if (buffer[n] == '\n')
		{
			ft_putstr_fd("buffer[n] == '\n'",1);
			pos++;
			break;
		}
		n = append_chunk(line, &buffer[n]);
		ft_putstr_fd(*line,1);
		ft_putstr_fd("\n",1);
		pos += n;
		if (n < bytes_read)
			break;
	}
	last_pos += pos;
	if (bytes_read < 0)
		return (-1);
	if (bytes_read == 0)
	{
		//code end of file
	}
	return (1);
}

int main(int argc, char const *argv[])
{
	int		fd = open("nums", O_RDONLY);
	// int		fd = open("lines", O_RDONLY);
	// int		fd = open("lorem", O_RDONLY);

	// char *line = (char*)malloc(0);
	char *line = NULL;

	get_next_line(fd, &line);
	ft_putstr_fd("*line: ", 1);
	ft_putstr_fd(line, 1);
	ft_putchar_fd('\n',1);
	free(line);
	get_next_line(fd, &line);
	ft_putstr_fd("*line: ", 1);
	ft_putstr_fd(line, 1);
	ft_putchar_fd('\n',1);
	// while (get_next_line(fd, line))
	// {
	// 	ft_putstr_fd(*line, 1);
	// 	ft_putchar_fd('\n',1);
	// }
	close(fd);
	return 0;
}
