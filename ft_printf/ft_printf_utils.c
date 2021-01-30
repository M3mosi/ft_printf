/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgiovo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 18:29:11 by sgiovo            #+#    #+#             */
/*   Updated: 2021/01/30 18:29:13 by sgiovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (buffer[0] && precision == -1)
		var->width = ft_atoi(buffer);
	else if (buffer[0] && !precision)
		var->prcsn = ft_atoi(buffer);
	return (i);
}

int 			is_a_flag(const char *s, int i, t_format *var)
{
	int k;

	k = var->prcsn;
	if (s[i] == '0' || s[i] == '-')
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
		return (ft_strdup("2147483648"));
	if (!(a = (char *)malloc(len + 1 * sizeof(char))))
		return (NULL);
	a[len] = 0;
	ft_conv(a, n, len);
	return (a);
}

char 			*str_reverse(char *c, int len)
{
	int		i;
	char	temp;

	i = 0;
	while(i < --len)
	{
		temp = c[i];
		c[i++] = c[len];
		c[len] = temp;
	}
	return (c);
}

void 			ft_base_conv(unsigned long int orig, char *addr, int maiusc, int radice, int nuller)
{
	char	*list;
	int		i;
	char	*dest;

	i = 0;
	if (nuller)
		{
			dest = ft_strdup("0x0");
			return ;
		}
	if (maiusc)
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

void			space_printer(int n, char zero)
{
	int		i;

	i = 0;
	if (zero != '0')
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
		if (var->flag != '-')
		{
			space_printer((var->width) - 1, var->flag);
			write(1, "%", 1);;
		}
		else if (var->flag)
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
	int	i;

	i = 0;
	if (len == -1)
		len = ft_strlen(c);
	while (c[i] && i < len)
		write(1, &c[i++], 1);
}

void 			ft_putc(t_format *var)
{
	char c;

	ft_star_support(&(*var));
	c = va_arg(var->arg_lst, int);
	if ((var->width - 1 ) > 0)
	{
		var->totale += var->width;
		if (!var->flag)
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

int				max_value(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

void			ft_print_str_support(t_format *var, char *s, int len)
{
	if (var->prcsn != -1 && var->prcsn < len)
		len = var->prcsn;
	if (var->width > len)
	{
		var->totale += var->width;
		if(var->flag != '-')
		{
			space_printer((var->width) - len, var->flag);
			strprint(s, var->prcsn);
		}
		else if (var->flag == '-')
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
void 			ft_print_str(t_format *var)
{
	char *s;
	int len;

	ft_star_support(&(*var));
	if (!(s = va_arg(var->arg_lst, char *)))
		s = ft_strdup("(null)");
	len = ft_strlen(s);
	ft_print_str_support(&(*var), s, len);	
}
void			ft_prnt_int_support(int *minus, t_format *var, char *s, int len, int n)
{
	if (*minus)
		write(1, "-", *minus--);
	if (var->prcsn != 0)
		strprint(s, -1);	
	if ((var->width > len || var->prcsn > len) && var->flag == '-')
	{
		if (var->width > var->prcsn)
			var->totale += var->width;
			if (n < 0 )
			{
				if (var->prcsn - len > 0)
					space_printer(var->width - var->prcsn - 1, var->flag);
				else
					space_printer((var->width  -  len ), var->flag);
			}
			else
				space_printer((var->width  - max_value(var->prcsn, len)), var->flag);		
	}
	if (var->width <=len && var->prcsn <= len && var->prcsn != 0)
		var->totale += len;
}
void 			ft_prnt_int_support_b (int *minus, t_format *var, int *len, int n)
{
	if ((var->width > *len ) && var->flag != '-')
		if (var-> width > var->prcsn)
		{
			var->totale += var->width;
			if (n < 0 && var->flag == '0')
			{
				write(1, "-",1);
				*minus -= 1;
				if (var->prcsn - *len > 0)
					space_printer(var->width - var->prcsn, var->flag);
				else
					space_printer((var->width  -  *len), var->flag);
			}
			else 
			{
				if (var->prcsn > *len)
					space_printer(var->width - var->prcsn - *minus, var->flag);
				else
					space_printer((var->width  -  *len), var->flag);
			}
		}
}

void			ft_prnt_int_support_c(int *minus, t_format *var, int len, int n)
{
	if (var->prcsn > len)
	{
		if (var->prcsn > var-> width)
			var->totale += var->prcsn + *minus;
		if (n >= 0)
			space_printer(var->prcsn - len, '0');
		else
		{
			write(1, "-",1);
			space_printer(var->prcsn - len + *minus , '0');
			*minus -= 1;
		}
	}		
}
void			ft_prnt_int_support_final(int *minus, t_format *var, char **s, int *len, int *n)
{
	if (var->prcsn >= 1 && var->flag == '0')
		var->flag = 0;
	if (var->prcsn == 0)
		*s = 0;
	if (*n >= 0)
		*len = ft_strlen(*s = ft_itoa(*n));
	else
	{
		*len = (ft_strlen(*s = ft_itoa(*n * -1))) + 1;
		*minus += 1;
	}
		if (var->prcsn == 0)
	{
		*s = 0;
		*len = 0;
	}
}
void 			prnt_int(t_format *var)
{
	char	*s;
	int		n;
	int		len;
	int		minus;

	minus = 0;
	ft_star_support(&(*var));
	n = va_arg(var->arg_lst, int);
	ft_prnt_int_support_final(&minus, &(*var), &s, &len, &n);
	ft_prnt_int_support_b(&minus, &(*var), &len, n);
	ft_prnt_int_support_c(&minus, &(*var), len, n);
	ft_prnt_int_support(&minus, &(*var), s, len, n);
	free(s);
}

void 			prnt_esa_support(t_format *var, int len, char *p, int n)
{
	if (var->prcsn > len)
	{
		if (var->prcsn > var-> width)
			var->totale += var->prcsn;
		if (n >= 0)
			space_printer(var->prcsn - len, '0');
		else
		{
			write(1, "-", 1);
			space_printer(var->prcsn - len, '0');
		}
	}		
	if (var->prcsn != 0)
		strprint(p, -1);	
	if 	((var->width > len || var->prcsn > len) && var->flag == '-')
	{
		if (var->width > var->prcsn)
		{
			var->totale += var->width;
			space_printer((var->width  - max_value(var->prcsn, len)), var->flag);
		}
	}
	if (var->width <=len && var->prcsn <= len && var->prcsn != 0)
		var->totale += len;
}
void			prnt_esa_support_b(t_format *var, int len)
{
	if ((var->width > len ) && var->flag != '-')
	{
		if (var-> width > var->prcsn)
		{
			var->totale += var->width;
				if (var->prcsn > len)
					{
						space_printer(var->width - var->prcsn, 0);
					}
				else
					space_printer((var->width  -  len), var->flag);
		}
	}
}
void			prnt_esa(t_format *var, int maiusc)
{
	unsigned	long	int	n;
	char					p[10000];
	int						len;
	
	ft_star_support(&(*var));
	if ((n = va_arg(var->arg_lst, unsigned long int)))
		ft_base_conv(n, p, maiusc, 0, 0);
	else 
	{
		p[0] = '0';
		p[1] = 0;
	}
	if (var->prcsn == 0)
		p[0] = 0;
	if (var->prcsn >= 1 && var->flag == '0')
		var->flag = 0;
	len = ft_strlen(p);
	prnt_esa_support_b(&(*var), len);
	prnt_esa_support(&(*var), len, p, n);
}

void			prnt_unint_support(t_format *var, int *len, char **s)
{
	if (var->prcsn == 0)
	{
		*s = 0;
		*len = 0;
	}
	if ((var->width > *len ) && var->flag != '-')
	{
		if (var-> width > var->prcsn)
		{
			var->totale += var->width;
				if (var->prcsn > *len)
					{
						space_printer(var->width - var->prcsn, var->flag);
					}
				else
					space_printer((var->width  -  *len), var->flag);
		}
	}
	if (var->prcsn > *len)
	{
		if (var->prcsn > var-> width)
			var->totale += var->prcsn;
		space_printer(var->prcsn - *len, '0');
	}
}
void 			prnt_unint(t_format *var)
{
	char *s;
	unsigned int n;
	int len;
	n = va_arg(var->arg_lst, int);
	if (var->prcsn >= 1 && var->flag == '0')
		var->flag = 0;
	len = ft_strlen(s = ft_uns_itoa(n));
	prnt_unint_support(&(*var), &len, &s); 
	if (var->prcsn != 0)
		strprint(s, -1);	
	if ((var->width > len || var->prcsn > len) && var->flag == '-')
	{
		if (var->width > var->prcsn)
		{
			var->totale += var->width;
			space_printer((var->width  - max_value(var->prcsn, len)), var->flag);
		}
	}
	if (var->width <=len && var->prcsn <= len && var->prcsn != 0)
		var->totale += len;
	free(s);
}

void			prnt_point_support(t_format *var, int *len, char *s)
{
	*len = ft_strlen(s);
	var->totale += *len;
	if ((var->width - *len ) > 0)
	{
		var->totale += var->width - *len;
		if (!var->flag)
		{
			space_printer((var->width) - *len, var->flag);
			if (var->prcsn != 0)
				strprint(s, var->prcsn);
			else
				strprint(s, -1);
		}
		else if (var->flag == '-')
		{
			strprint(s, var->prcsn);
			space_printer((var->width) - *len, var->flag);
		}
	}
	else 
		strprint(s, *len);	
}

void 			prnt_point(t_format *var)
{
	size_t hex;
	char s[10000];
	int len;
	int i;

	i = 0;
	ft_star_support(&(*var));
	hex = va_arg(var->arg_lst, size_t);
	if (!hex)
	{
		if (var->prcsn != 0)
		{
			s[i++] = '0';
			s[i++] = 'x';
			s[i++] = '0';
			s[i] = 0;
		}
		else
		{
			s[i++] = '0';
			s[i++] = 'x';
			s[i] = 0;
		}
	}
	else
		ft_base_conv(hex, s, 0, 1, 0);
	prnt_point_support(&(*var), &len, s);	
}
