#include "ft_printf.h"

static	int	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' ||
		c == '\v' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

int			ft_atoi(char *str)
{
	int		index;
	int		is_minus;
	int		result;
	int		unico;

	result = 0;
	is_minus = 1;
	index = 0;
	unico = 0;
	while (is_space(str[index]))
		index++;
	while ((str[index] == '-' || str[index] == '+') && unico == 0)
	{
		if (str[index++] == '-')
			is_minus *= -1;
		unico++;
	}
	while (str[index] && (str[index] >= '0' && str[index] <= '9'))
	{
		result = result * 10 + (str[index] - '0');
		index++;
	}
	return (is_minus * result);
}

int			is_a_type(const char c)
{
	if (c == 'd' || c == 's' || c == 'c' || c == 'p' ||
		c == 'i' || c == 'u' || c == 'x' || c == 'X')
		return (1);
	return (0);
}

char		*ft_strdup(char *src)
{
	char	*ptr;
	int		i;

	i = 0;
	while (src[i])
		i++;
	if (!(ptr = malloc(sizeof(char) * i)))
		return (0);
	if (ptr)
	{
		i = 0;
		while (src[i])
		{
			ptr[i] = src[i];
			i++;
		}
		ptr[i] = 0;
		return (ptr);
	}
	else
		return (0);
}

int			is_a_flag(const char *s, int i, t_format *var)
{
	int k;

	k = var->prcsn;
	if (s[i] == '0' || s[i] == '-')
		return (1);
	return (0);
}
