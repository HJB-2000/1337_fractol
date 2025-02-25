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

static	int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}


double ft_atoi(const char *str)
{
    int sign = 1;
    double result = 0.0;
    double fraction = 0.0;
    int decimal_places = 0;

    while (ft_isspace(*str))
        str++;
    if (*str == '-')
        sign = -1;
    if (*str == '+' || *str == '-')
        str++;
    while (*str >= '0' && *str <= '9')
    {
        if (result > (LLONG_MAX - (*str - '0')) / 10)
        {
            if (sign == -1)
                return 0.0; // Underflow
            else
                return -1.0; // Overflow
        }
        result = result * 10 + (*str - '0');
        str++;
    }
    if (*str == '.')
    {
        str++;
        while (*str >= '0' && *str <= '9')
        {
            fraction = fraction * 10 + (*str - '0');
            decimal_places++;
            str++;
        }
        result += fraction / pow(10, decimal_places);
    }
    return result * sign;
}
