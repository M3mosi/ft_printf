#include "ft_printf.h"

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

int				ft_counter(const char *s, int i, char buffer[100000], t_format *var, int precision)
{
	int j;

	j = 0;
    buffer[0] = 0;
    while(s[i] <= '9' && s[i] >= '0')
        buffer[j++] = s[i++];
    buffer[j] = 0;
    if(buffer[0] && precision == -1)
        var->width = ft_atoi(buffer);
	else if(buffer[0] && !precision)
        var->prcsn = ft_atoi(buffer);
	return (i);
}

int 			is_a_flag(const char *s, int i, t_format *var)
{
	if ((s[i] == '0' || s[i] == '-') && (i == var->i_start))
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

void 			ft_base_conv(unsigned int orig, char *addr, int maiusc, int radice)
{
	char *list;
	int i;
	char *dest;

	i = 0;
	if(maiusc)
		list = EXA_MAX;
	else
		list = EXA_MIN;
	dest = addr;
	while(orig != 0)
	{
		dest[i++] = list[orig % 16];
		orig /= 16;
	}
	if (radice)
	{
		dest[i++] = '0';
		dest[i++] = '1';
		dest[i++] = 'x';
		dest[i++] = '0';
	}	
	dest[i] = 0;
	dest = str_reverse(dest, i);
	
}

void			space_printer(int n, char zero)
{
	int i;

	i = 0;
	if(zero != '0')
		while (i++ < n)
			write(1," ", 1);
	else
		while (i++ < n)
			write(1,"0", 1);
}

void			ft_pprint(t_format *var)
{
	if ((var->width - 1 ) > 0)
	{
		var->totale += var->width;
		if(var->flag != '-')
		{
			space_printer((var->width) - 1, var->flag);
			write(1, "%", 1);;
		}
		else if(var->flag)
		{
			write(1, "%", 1);;
			space_printer((var->width) - 1, var->flag);
		}
	}
	else
	{
		var->totale += 1;
		write(1, "%", 1);
	}		
}

void 			strprint(char *c,int len)
{
	int i;

	i = 0;
	if (len == -1)
		len = ft_strlen(c);
	while (c[i] && i < len)
		write(1, &c[i++], 1);
}

void 			ft_putc(t_format *var)
{
	char c;

	c = va_arg(var->arg_lst, int);
	//if(var->prcsn != 0)
		//write(1, &c, 1);
	if ((var->width - 1 ) > 0)
	{
		var->totale += var->width;
		if(!var->flag)
		{
			space_printer((var->width) - 1, var->flag);
			write(1, &c, 1);
		}
		else if(var->flag == '-')
		{
			write(1, &c, 1);
			space_printer((var->width) - 1, var->flag);
		}
	}
	else
	{
		var->totale += 1;
		write(1, &c, 1);
	}	
}

void 			ft_print_str(t_format *var)
{
	char *s;
	int len;

	s = va_arg(var->arg_lst, char *);
	len = ft_strlen(s);
	if (var->prcsn != -1 && var->prcsn < len)
		len = var->prcsn;
	if ((var->width - len ) > 0)
	{
		var->totale += var->width;
		if(var->flag != '-')
		{
			space_printer((var->width) - len, var->flag);
			strprint(s, var->prcsn);
		}
		else if(var->flag == '-')
		{
			strprint(s, var->prcsn);
			space_printer((var->width) - len, var->flag);
		}
	}
	else
	{
		var->totale += len;
		
		strprint(s, var->prcsn);
	}	
}

void 			prnt_int(t_format *var)
{
	char *s;
	int n;
	int len;

	n = va_arg(var->arg_lst, int);
	s = ft_itoa(n);
	len = ft_strlen(s);
	if ((var->width - len ) > 0)
	{
		var->totale += var->width;
		if(var->flag != '-')
		{
			space_printer((var->width) - len, var->flag);
			strprint(s, -1);
		}
		else if(var->flag == '-')
		{
			strprint(s, -1);
			space_printer((var->width) - ft_strlen(s), var->flag);
		}
	}
	else
	{
		strprint(s, len);
		var->totale = var->totale + len;
	}
	free(s);
}	

void			prnt_esa(t_format *var, int maiusc)
{
	unsigned int s;
	char p[10000];
	
	s = va_arg(var->arg_lst, unsigned int);
	ft_base_conv(s, p, maiusc, 0);
	var->totale += ft_strlen(p);
	if ((var->width - ft_strlen(p) ) > 0)
	{
		var->totale = var->width;
		if(!var->flag)
		{
			space_printer((var->width) - ft_strlen(p), var->flag);
			strprint(p, var->prcsn);
		}
		else if(var->flag == '-')
		{
			strprint(p, var->prcsn);
			space_printer((var->width) - ft_strlen(p), var->flag);
		}
		
	}
}

void 			prnt_unint(t_format *var)
{
	char *s;
	unsigned int n;
	n = va_arg(var->arg_lst, unsigned int);
	s = ft_uns_itoa(n);
	var->totale = ft_strlen(s);
	if ((var->width - ft_strlen(s) ) > 0)
	{
		var->totale = var->width;
		if(!var->flag)
		{
			space_printer((var->width) - ft_strlen(s), var->flag);
			strprint(s, var->prcsn);
		}
		else if(var->flag == '-')
		{
			strprint(s, var->prcsn);
			space_printer((var->width) - ft_strlen(s), var->flag);
		}
	}
	else 
		strprint(s, var->prcsn);
	free(s);
}

void 			prnt_point(t_format *var)
{
	size_t hex;
	char s[10000];

	hex = va_arg(var->arg_lst, size_t);
	ft_base_conv(hex, s, 0, 1);
	var->totale += ft_strlen(s);
	if ((var->width - ft_strlen(s) ) > 0)
	{
		var->totale = var->width;
		if(!var->flag)
		{
			space_printer((var->width) - ft_strlen(s), var->flag);
			strprint(s, var->prcsn);
		}
		else if(var->flag == '-')
		{
			strprint(s, var->prcsn);
			space_printer((var->width) - ft_strlen(s), var->flag);
		}
	}
	else 
		strprint(s, var->prcsn);
}
