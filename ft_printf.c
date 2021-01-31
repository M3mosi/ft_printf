/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgiovo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 18:28:57 by sgiovo            #+#    #+#             */
/*   Updated: 2021/01/30 18:28:59 by sgiovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_init(t_format *var)
{
	var->flag = 0;
	var->dot = 0;
	var->width = 0;
	var->prcsn = -1;
	var->type = 0;
	var->star_prec = 0;
	var->star_width = 0;
	var->i_start = 0;
}

int		ft_trckr(t_format *var)
{
	if (var->type == 'd')
		prnt_int(&*var);
	else if (var->type == 's')
		ft_print_str(&(*var));
	else if (var->type == 'c')
		ft_putc(&(*var));
	else if (var->type == 'i')
		prnt_int(&(*var));
	else if (var->type == 'p')
		prnt_point(&(*var), 0);
	else if (var->type == 'u')
		prnt_unint(&(*var));
	else if (var->type == 'x')
		prnt_esa(&(*var), 0);
	else if (var->type == 'X')
		prnt_esa(&(*var), 1);
	return (0);
}

int		ft_fll(const char *s, int i, t_format *var)
{
	char	buffer[100000];

	var->i_start = i;
	ft_fll_support(s, &i, &(*var), buffer);
	if (!is_a_flag(s, i, &(*var)) && s[i] == '.')
	{
		var->dot = '.';
		var->prcsn = 0;
		i = ft_counter(s, ++i, buffer, &(*var));
	}
	if (s[i] == '*')
	{
		var->star_prec = 1;
		i++;
	}
	if (!is_a_flag(s, i, &(*var)) && is_a_type(s[i]))
		var->type = s[i];
	if (s[i] == '%' && !(var->type))
		ft_pprint(&(*var));
	ft_trckr(var);
	if (s[i])
		return (i + 1);
	else
		return (i);
}

int		ft_scroll(const char *s, t_format *var, int i, int stampe)
{
	int len;

	len = ft_strlen(s);
	while (s[i])
	{
		ft_init(&*var);
		if (s[i] == '%' && (s[i + 1] && s[i + 1] != '%'))
		{
			i = ft_fll(s, i + 1, &(*var));
			continue ;
		}
		if (s[i] == '%' && !(s[i + 1]))
			return (stampe);
		if (s[i] == '%' && s[i + 1] == '%')
			i++;
		if (i < len)
		{
			write(1, &(s[i]), 1);
			stampe += 1;
		}
		i++;
	}
	return (stampe);
}

int		ft_printf(const char *s, ...)
{
	t_format	var;
	int			stampe;

	var.totale = 0;
	va_start(var.arg_lst, s);
	stampe = ft_scroll(s, &var, 0, 0);
	va_end(var.arg_lst);
	return (var.totale + stampe);
}
