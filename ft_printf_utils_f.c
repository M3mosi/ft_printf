#include "ft_printf.h"

void			ft_print_str_support(t_format *var, char *s, int len)
{
	if (var->prcsn != -1 && var->prcsn < len)
		len = var->prcsn;
	if (var->width > len)
	{
		var->totale += var->width;
		if (var->flag != '-')
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

void			ft_print_str(t_format *var)
{
	char	*s;
	int		len;

	ft_star_support(&(*var));
	if (!(s = va_arg(var->arg_lst, char *)))
		s = ft_strdup("(null)");
	len = ft_strlen(s);
	ft_print_str_support(&(*var), s, len);
}

void			prnt_esa_support(t_format *var, int len, char *p, int n)
{
	if (var->prcsn > len)
	{
		if (var->prcsn > var->width)
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
	if ((var->width > len || var->prcsn > len) && var->flag == '-')
	{
		if (var->width > var->prcsn)
		{
			var->totale += var->width;
			space_printer((var->width - max_value(var->prcsn, len)
), var->flag);
		}
	}
	if (var->width <= len && var->prcsn <= len && var->prcsn != 0)
		var->totale += len;
}

void			prnt_esa_support_b(t_format *var, int len)
{
	if ((var->width > len) && var->flag != '-')
	{
		if (var->width > var->prcsn)
		{
			var->totale += var->width;
			if (var->prcsn > len)
			{
				space_printer(var->width - var->prcsn, 0);
			}
			else
				space_printer((var->width - len), var->flag);
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
		ft_base_conv(n, p, maiusc, 0);
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
