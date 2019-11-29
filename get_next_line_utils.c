#include <stdlib.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	char c;

	if (s)
	{
		while (*s)
		{
			c = *s;
			ft_putchar_fd(c, fd);
			s++;
		}
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	n = n % 10 + 48;
	write(fd, &n, 1);
}

size_t	ft_wordcount(char const *str, char delimiter)
{
	size_t	i;
	size_t	w;

	i = 0;
	w = 0;
	while (str[i])
	{
		if (str[i] != delimiter)
			w += 1;
		while (str[i] != delimiter && str[i + 1])
			i += 1;
		i += 1;
	}
	return (w);
}

size_t		ft_strlen(const char *str)
{
	size_t	s;

	s = 0;
	while (str[s])
		s++;
	return (s);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	char *ptr;

	ptr = dest;
	while (n > 0 && *src != '\0')
	{
		if (*src)
			*dest = *src;
		else
			*dest = '\0';
		dest++;
		src++;
		n--;
	}
	*dest = '\0';
	return (ptr);
}

char	**ft_split(char const *str, char delimiter)
{
	unsigned int	i;
	unsigned int	j;
	char			**list;

	if (str == NULL)
		return (NULL);
	list = (char**)malloc(sizeof(char*) * (ft_wordcount(str, delimiter) + 1));
	if (!list)
		return (NULL);
	j = 0;
	while (*str != 0)
	{
		i = 0;
		while (str[i] != delimiter && str[i] != 0)
			i++;
		if (i)
		{
			list[j++] = ft_strncpy((char*)malloc(i + 1), str, i);
			str = &str[i];
		}
		else
			str++;
	}
	list[j] = NULL;
	return (list);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	int		i;
	int		len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(joined = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (*s1)
	{
		joined[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		joined[i] = *s2;
		s2++;
		i++;
	}
	joined[i] = '\0';
	return (joined);
}
