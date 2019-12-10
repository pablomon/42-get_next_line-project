#include "get_next_line.h"

void	move_str_left(char *str, unsigned int n)
{
	char *ptr;
	unsigned int l;

	l = BUFFER_SIZE - n;
	ptr = &str[n];
	ft_memcpy(str, ptr, l);
	str[l] = 0;
}

char		*extract_line(char *str, int *newline_found)
{
	unsigned int	size;
	char			*cut;

	if (str == NULL)
		return (NULL);
	size = 0;
	*newline_found = 0;
	while (str[size])
	{
		if (str[size] == '\n')
		{
			*newline_found = 1;
			break ;
		}
		size++;
	}
	cut = ft_substr(str, 0, size);
	move_str_left(str, size + *newline_found);
	return (cut);
}

static int	check_error(int n)
{
	if (n < 0)
		return (-1);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*extracted;
	int			n;
	int			newline_found;

	newline_found = 0;
	*line = ft_strdup("");
	while (!newline_found)
	{
		while (buffer[0])
		{
			extracted = extract_line(buffer, &newline_found);
			*line = ft_strjoin(*line, extracted);
			free(extracted);
			if (newline_found)
				return (1);
		}
		if ((n = read(fd, buffer, BUFFER_SIZE)) <= 0)
			return (check_error(n));
		buffer[n] = 0;
	}
	return (0);
}
