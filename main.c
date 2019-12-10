#include "get_next_line.h"

int main(void)
{
	// int		fd = open("nums", O_RDONLY);
	// int		fd = open("lines", O_RDONLY);
	// int		fd = open("lorem", O_RDONLY);
	int		fd = open("test", O_RDONLY);

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
