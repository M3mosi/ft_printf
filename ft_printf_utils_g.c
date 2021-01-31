#include "ft_printf.h"

static	void	int_supp_a(t_format *var, int len, int n)
{
	if ((var->width > len || var->prcsn > len) && var->flag == '-')
	{
		if (var->width > var->prcsn)
			var->totale += var->width;
		if (n < 0)
		{
			if (var->prcsn - len > 0)
				space_printer(var->width - var->prcsn - 1, var->flag);
			else
				space_printer((var->width - len), var->flag);
		}
		else
			space_printer((var->width - max_value(var->prcsn, len)
), var->flag);
	}
	if (var->width <= len && var->prcsn <= len && var->prcsn != 0)
		var->totale += len;
}

static	void	int_supp_b(int *minus, t_format *var, int *len, int n)
{
	if ((var->width > *len) && var->flag != '-')
		if (var->width > var->prcsn)
		{
			var->totale += var->width;
			if (n < 0 && var->flag == '0')
			{
				write(1, "-", 1);
				*minus -= 1;
				if (var->prcsn - *len > 0)
					space_printer(var->width - var->prcsn, var->flag);
				else
					space_printer((var->width - *len), var->flag);
			}
			else
			{
				if (var->prcsn > *len)
					space_printer(var->width - var->prcsn - *minus, var->flag);
				else
					space_printer((var->width - *len), var->flag);
			}
		}
}

static	void	int_supp_c(int *minus, t_format *var, int len, int n)
{
	if (var->prcsn > len)
	{
		if (var->prcsn > var->width)
			var->totale += var->prcsn + *minus;
		if (n >= 0)
			space_printer(var->prcsn - len, '0');
		else
		{
			write(1, "-", 1);
			space_printer(var->prcsn - len + *minus, '0');
			*minus -= 1;
		}
	}
}

static	int		int_supp_d(int *min, t_format *var, char **s, int *n)
{
	int len;

	len = 0;
	if (var->prcsn >= 1 && var->flag == '0')
		var->flag = 0;
	if (var->prcsn == 0)
		*s = 0;
	if (*n >= 0)
	{
		*s = ft_itoa(*n);
		len = ft_strlen(*s);
	}
	else
	{
		*s = ft_itoa(*n * -1);
		len = ft_strlen(*s) + 1;
		*min += 1;
	}
	if (var->prcsn == 0)
	{
		*s = 0;
		len = 0;
	}
	return (len);
}

void			prnt_int(t_format *var)
{
	char	*s;
	int		n;
	int		len;
	int		minus;

	minus = 0;
	ft_star_support(&(*var));
	n = va_arg(var->arg_lst, int);
	len = int_supp_d(&minus, &(*var), &s, &n);
	int_supp_b(&minus, &(*var), &len, n);
	int_supp_c(&minus, &(*var), len, n);
	if (minus)
		write(1, "-", minus--);
	if (var->prcsn != 0)
		strprint(s, -1);
	int_supp_a(&(*var), len, n);
	free(s);
}
