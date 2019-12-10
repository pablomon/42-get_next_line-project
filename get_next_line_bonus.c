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

void	init_gnl(char **buffer)
{
	if (*buffer)
		return;
	*buffer = (char*)malloc(sizeof(char*) * (BUFFER_SIZE + 1));
	*buffer[0] = 0;
}

int	process_buffer(char **line, char *buffer)
{
	char	*temp;
	char	*carved;
	int		newline_found;

	newline_found = 0;
	temp = *line;
	carved = extract_line(buffer, &newline_found);
	*line = ft_strjoin(*line, carved);
	free (temp);
	free (carved);
	return newline_found;
}

int	get_next_line(int fd, char **line)
{
	static char	*buffer[4096];
	int			n;
	int			newline_found;

	if (!buffer[fd])
	{
		buffer[fd] = (char*)malloc(sizeof(char*) * (BUFFER_SIZE + 1));
		buffer[fd][0] = 0;
	}
	newline_found = 0;
	*line = ft_strdup("");
	while (!newline_found)
	{
		while (ft_strlen(buffer[fd]) > 0)
		{
			if (process_buffer(line, buffer[fd]))
				return (1);
		}
		if ((n = read(fd, buffer[fd], BUFFER_SIZE)) <= 0)
			return (check_error(n));
		buffer[fd][n] = 0;
	}
	return (0);
}

