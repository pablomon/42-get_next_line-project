#include "get_next_line.h"

void	move_str_left(char *str, unsigned int n)
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

char	*carve_line(char *str, int *newline_found)
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
			*newline_found = 1;
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
	cut[size] = 0;
	move_str_left(str, size + 1);
	return (cut);
}

int	get_next_line(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*temp;
	char		*carved;
	int			n;
	int			newline_found;

	buffer[BUFFER_SIZE] = 0;
	newline_found = 0;
	*line = ft_strdup("");
	while (!newline_found)
	{
		while (ft_strlen(buffer) > 0)
		{
			temp = *line;
			carved = carve_line(buffer, &newline_found);
			*line = ft_strjoin(*line, carved);
			free (temp);
			free (carved);
			if (newline_found)
				return (1);
		}
		n = read(fd, buffer, BUFFER_SIZE);
		if (n == 0)
		{
			return (0);
		}
		if (n < 0)
		{
			return (-1);
		}
	}
	return (0);
}

