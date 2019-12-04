#ifndef BUFFER_SIZE
#define	BUFFER_SIZE 1
#endif

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int	get_next_line(int fd, char **line);
void	move_str_left(char *str, unsigned int n);
char	*carve_line(char *str, int *newline_found);
char	*ft_strdup(const char *s1);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	outn(char *s);
void	out(char *s);
void	ft_putnbr_fd(int n, int fd);
void	outnbr(int nbr);
void 	outnbrn(int nbr);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
