/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgiovo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 18:29:03 by sgiovo            #+#    #+#             */
/*   Updated: 2021/01/30 18:29:05 by sgiovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

typedef	struct s_format{
	char	flag;
	char	dot;
	int		width;
	int		star_width;
	int		prcsn;
	int		star_prec;
	char	type;
	int		i_start;
	int		totale;
	va_list arg_lst;
}				t_format;

# ifndef MIN_INT
#  define MIN_INT -2147483648
#  define INT_MAX 2147483647
# endif
# define EXA_MAX "0123456789ABCDEF"
# define EXA_MIN "0123456789abcdef"
# define DECA "0123456789"

void	ft_print_str(t_format *var);
int		is_a_flag(const char *s, int i, t_format *var);
int		is_a_type(const char c);
int		ft_atoi(char *str);
char	*ft_itoa(int n);
void	prnt_int(t_format *var);
void	prnt_unint(t_format *var);
void	ft_putc(t_format *var);
void	prnt_point(t_format *var, int i);
int		ft_strlen(const char *str);
char	*ft_uns_itoa(unsigned int n);
void	prnt_esa(t_format *var, int maiusc);
int		ft_printf(const char *s, ...);
void	ft_pprint(t_format *var);
void	ft_fll_support(const char *s, int *i, t_format *var, char *buffer);
int		ft_counter(const char *s, int i, char buffer[100000], t_format *var);
void	space_printer(int n, char zero);
void	strprint(char *c, int len);
int		max_value(int a, int b);
void	ft_star_support(t_format *var);
void	ft_base_conv(unsigned long int orig,
char	*addr, int maiusc, int radice);
int		n_len(int n);
char	*ft_strdup(char *src);
#endif
