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

static	void	prnt_unint_support(t_format *var, int *len, char **s)
{
	if (var->prcsn == 0)
	{
		*s = 0;
		*len = 0;
	}
	if ((var->width > *len) && var->flag != '-')
	{
		if (var->width > var->prcsn)
		{
			var->totale += var->width;
			if (var->prcsn > *len)
			{
				space_printer(var->width - var->prcsn, var->flag);
			}
			else
				space_printer((var->width - *len), var->flag);
		}
	}
	if (var->prcsn > *len)
	{
		if (var->prcsn > var->width)
			var->totale += var->prcsn;
		space_printer(var->prcsn - *len, '0');
	}
}

void			prnt_unint(t_format *var)
{
	char			*s;
	unsigned	int	n;
	int				len;

	n = va_arg(var->arg_lst, int);
	if (var->prcsn >= 1 && var->flag == '0')
		var->flag = 0;
	s = ft_uns_itoa(n);
	len = ft_strlen(s);
	prnt_unint_support(&(*var), &len, &s);
	if (var->prcsn != 0)
		strprint(s, -1);
	if ((var->width > len || var->prcsn > len) && var->flag == '-')
	{
		if (var->width > var->prcsn)
		{
			var->totale += var->width;
			space_printer((var->width - max_value
(var->prcsn, len)), var->flag);
		}
	}
	if (var->width <= len && var->prcsn <= len && var->prcsn != 0)
		var->totale += len;
	free(s);
}

static	void	prnt_point_support(t_format *var, int *len, char *s)
{
	*len = ft_strlen(s);
	var->totale += *len;
	if ((var->width - *len) > 0)
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

void			prnt_point(t_format *var, int i)
{
	size_t		hex;
	char		s[10000];
	int			len;

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
		ft_base_conv(hex, s, 0, 1);
	prnt_point_support(&(*var), &len, s);
}

void			ft_fll_support(const char *s, int *i,
	t_format *var, char *buffer)
{
	while (is_a_flag(s, *i, &(*var)))
	{
		if (var->flag != '-')
			var->flag = s[*i];
		*i += 1;
	}
	if (s[*i] == '*')
	{
		var->star_width = 1;
		*i += 1;
	}
	else if (!is_a_flag(s, *i, &(*var)) && (s[*i] >= '0' && s[*i] <= '9'))
		*i = ft_counter(s, *i, buffer, &(*var));
}
