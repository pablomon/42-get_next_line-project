#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "get_next_line_utils.c"

#ifndef BUFFER_SIZE
#define	BUFFER_SIZE 1
#endif

void	move_str_left(char *str, int n)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (ft_strlen(str) < 2)
	{
		if (ft_strlen(str) == 1)
			str[0] = 0;
		return;
	}
	while (i < n)
	{
		j = 0;
		while (str[j])
		{
			if (str[j + 1])
				str[j] = str[j + 1];
			else
				str[j] = 0;
			j++;
		}
		i++;
	}
}

// por que no funciona un **char con char[] ???
char	*carve_line(char *str)
{
	unsigned int	size;
	unsigned int	i;
	char			*cut;

	if (str == NULL)
		return (NULL);
	size = 0;
	while (str[size])
	{
		if (str[size] == '\n')
		{
			size++;
			break;
		}
		size++;
	}
	if (!(cut = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		cut[i] = str[i];
		i++;
	}
	cut[i] = 0;
	move_str_left(str, size);
	return (cut);
}

int	get_next_line(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE];
	char		*newline;
	char		*temp;
	char		*carved;
	int			n;

	newline = ft_strdup("");
	while (newline[ft_strlen(newline) - 1] != '\n')
	{
		while (ft_strlen(buffer) > 0)
		{
			temp = newline;
			carved = carve_line(buffer);
			newline = ft_strjoin(newline, carved);
			free (temp);
			free (carved);
			if (newline[ft_strlen(newline) - 1] == '\n')
			{
				*line = newline;
				return (1);
			}
		}
		n = read(fd, buffer, BUFFER_SIZE);
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
	}
}

int main(int argc, char const *argv[])
{
	// int		fd = open("nums", O_RDONLY);
	// int		fd = open("lines", O_RDONLY);
	int		fd = open("lorem", O_RDONLY);

	char *line;

	// get_next_line(fd, &line);

	// for (size_t i = 0; i < 3; i++)
	// {
	// 	get_next_line(fd, &line);
	// 	ft_putstr_fd("line: ", 1);
	// 	ft_putstr_fd(line, 1);
	// 	ft_putchar_fd('\n',1);
	// 	free(line);
	// }

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
