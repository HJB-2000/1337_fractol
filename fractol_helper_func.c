#include "fractol.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
    if (!s1 || !s2 || n < 0)
        return 0;
	while (n > 0)
	{
		if (*s1 == '\0' || *s2 == '\0')
			return ((unsigned char)*s1 - (unsigned char)*s2);
		if ((unsigned char)*s1 != (unsigned char)*s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}

void    my_putstr(char *str)
{
    int i = 0;

    if (!str)
        return ;
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
    return ;
}