#include "ft_printf.h"

static void		ft_conv(char *a, int n, int len)
{
	if (n >= 0)
	{
		while (len-- > 0)
		{
			a[len] = (n % 10) + 48;
			n /= 10;
		}
	}
	else
	{
		n *= -1;
		a[0] = '-';
		while (len-- > 1)
		{
			a[len] = (n % 10) + 48;
			n /= 10;
		}
	}
}

char			*ft_itoa(int n)
{
	char	*a;
	int		len;

	len = n_len(n);
	if (n < 0)
		len++;
	if (n == MIN_INT)
		return (ft_strdup("2147483648"));
	if (!(a = (char *)malloc(len + 1 * sizeof(char))))
		return (NULL);
	a[len] = 0;
	ft_conv(a, n, len);
	return (a);
}

char			*str_reverse(char *c, int len)
{
	int		i;
	char	temp;

	i = 0;
	while (i < --len)
	{
		temp = c[i];
		c[i++] = c[len];
		c[len] = temp;
	}
	return (c);
}

void			ft_base_conv(unsigned long int orig, char *addr,
int maiusc, int radice)
{
	char	*list;
	int		i;
	char	*dest;

	i = 0;
	if (maiusc)
		list = EXA_MAX;
	else
		list = EXA_MIN;
	dest = addr;
	while (orig != 0)
	{
		dest[i++] = list[orig % 16];
		orig /= 16;
	}
	if (radice)
	{
		dest[i++] = 'x';
		dest[i++] = '0';
	}
	dest[i] = 0;
	dest = str_reverse(dest, i);
}

void			ft_star_support(t_format *var)
{
	if (var->star_width)
	{
		var->width = va_arg(var->arg_lst, int);
		if (var->width < 0)
		{
			var->width *= -1;
			var->flag = '-';
		}
	}
	if (var->star_prec)
	{
		var->prcsn = va_arg(var->arg_lst, int);
		if (var->prcsn < 0)
		{
			var->prcsn = -1;
			var->flag = '-';
		}
	}
}
