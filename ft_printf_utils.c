#include "ft_printf_lib.h"

int				ft_strlen(const char *str)
{
	int		len;

	len = 0;
	while (str[len])
		len++;
	if (len == 0)
		return (0);
	return (len);
}

char			*ft_strcpy(char *dest, char *src)
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

int 			is_a_flag(const char *s, int i, t_format *var)
{
	if ((s[i] == '0' || s[i] == '-') && (i == (var->i_start + 1)))
		return (1);
	return (0);
}

static	int		is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' ||
		c == '\v' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

int				ft_atoi(char *str)
{
	int		index;
	int		is_minus;
	int		result;
	int     unico;

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

int 			is_a_type(const char c)
{
	if (c == 'd' || c == 's' || c == 'c' || c == 'p' ||
		c == 'i' || c == 'u' || c == 'x' || c == 'X')
		return (1);
	return (0);
}

char			*ft_strdup(char *src)
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

int				ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}

static int		n_len(int n)
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

void 			ft_putc(t_format *var)
{
	char c;

	c = va_arg(var->arg_lst, int);
	write(1, &c, 1);
}

char			*ft_itoa(int n)
{
	char	*a;
	int		len;

	len = n_len(n);
	if (n < 0)
		len++;
	if (n == MIN_INT)
		return (ft_strdup("-2147483648"));
	if (!(a = (char *)malloc(len + 1 * sizeof(char))))
		return (NULL);
	a[len] = 0;
	ft_conv(a, n, len);
	return (a);
}

char 			*str_reverse(char *c, int len)
{
	int i;
	char temp;

	i = 0;
	while(i < --len)
	{
		temp = c[i];
		c[i++] = c[len];
		c[len] = temp;
	}
	return (c);
}

void 			ft_base_conv(unsigned int orig, char *addr)
{
	char *list;
	char buffer[50];
	int i = 0;
	char *dest;

	i = 0;
	list = EXA_MAX;
	dest = addr;
	while(orig != 0)
	{
		dest[i++] = list[orig % 16];
		orig /= 16;
	}
	dest[i++] = '0';
	dest[i++] = '1';
	dest[i++] = 'x';
	dest[i++] = '0';
	dest[i] = 0;
	dest = str_reverse(dest, i);
}

void 			ft_print_str(t_format *var)
{
	char *s;

	s = va_arg(var->arg_lst, char *);
	var->totale = ft_strlen(s);
	while(*s)
		write(1,&(*s++),1);
}

void 			strprint(char *c)
{
	while(*c)
		write(1,&(*c++),1);
}

void 			prnt_int(t_format *var)
{
	char *s;
	int n;
	n = va_arg(var->arg_lst, int);
	s = ft_itoa(n);
	var->totale = ft_strlen(s);
	while(*s)
		write(1,&(*s++),1);
}	

void 			prnt_unint(t_format *var)
{
	char *s;
	unsigned int n;
	n = va_arg(var->arg_lst, unsigned int);
	s = ft_uns_itoa(n);
	var->totale = ft_strlen(s);
	while(*s)
		write(1,&(*s++),1);
}

void 			prnt_point(t_format *var)
{
	size_t s;
	char waitingroom[1000];

	s = va_arg(var->arg_lst, size_t);
	ft_base_conv(s,waitingroom);
	var->totale += ft_strlen(waitingroom);
	printf("||%d||",var->totale);
	strprint(waitingroom);
}
