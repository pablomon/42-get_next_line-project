#ifndef BUFFER_SIZE
#define	BUFFER_SIZE 6
#endif

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int		get_next_line(int fd, char **line);
void	move_str_left(char *str, unsigned int n);
char	*extract_line(char *str, int *newline_found);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t n);

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	outn(char *s);
void	out(char *s);
void	ft_putnbr_fd(int n, int fd);
void	outnbr(int nbr);
void 	outnbrn(int nbr);
