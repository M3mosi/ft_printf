#include "ft_printf.h"

void	space_printer(int n, char zero)
{
	int		i;

	i = 0;
	if (zero != '0')
		while (i++ < n)
			write(1, " ", 1);
	else
		while (i++ < n)
			write(1, "0", 1);
}

void	ft_pprint(t_format *var)
{
	if ((var->width - 1) > 0)
	{
		var->totale += var->width;
		if (var->flag != '-')
		{
			space_printer((var->width) - 1, var->flag);
			write(1, "%", 1);
		}
		else if (var->flag)
		{
			write(1, "%", 1);
			space_printer((var->width) - 1, var->flag);
		}
	}
	else
	{
		var->totale += 1;
		write(1, "%", 1);
	}
}

void	strprint(char *c, int len)
{
	int	i;

	i = 0;
	if (len == -1)
		len = ft_strlen(c);
	while (c[i] && i < len)
		write(1, &c[i++], 1);
}

void	ft_putc(t_format *var)
{
	char c;

	ft_star_support(&(*var));
	c = va_arg(var->arg_lst, int);
	if ((var->width - 1) > 0)
	{
		var->totale += var->width;
		if (!var->flag)
		{
			space_printer((var->width) - 1, var->flag);
			write(1, &c, 1);
		}
		else if (var->flag == '-')
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

int		max_value(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}
