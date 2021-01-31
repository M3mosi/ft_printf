#include "ft_printf.h"

int		ft_strlen(const char *str)
{
	int		len;

	len = 0;
	while (str[len])
		len++;
	if (len == 0)
		return (0);
	return (len);
}

char	*ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		ft_counter(const char *s, int i, char buffer[100000], t_format *var)
{
	int j;

	j = 0;
	buffer[0] = 0;
	while (s[i] <= '9' && s[i] >= '0')
		buffer[j++] = s[i++];
	buffer[j] = 0;
	if (buffer[0] && var->prcsn == -1)
		var->width = ft_atoi(buffer);
	else if (buffer[0] && !var->prcsn)
		var->prcsn = ft_atoi(buffer);
	return (i);
}

int		ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}

int		n_len(int n)
{
	int i;

	i = 1;
	if (n < 0)
		n *= -1;
	while (i < 10)
	{
		if (ft_isdigit(n + 48))
			break ;
		n = n / 10;
		i++;
	}
	return (i);
}
