#ifndef FT_PRINTF_LIB_H
# define FT_PRINTF_LIB_H

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


typedef struct s_format{
	char	flag;
	int		width;
    int     star_width;
	int		prcsn;
    int     star_prec;
	char	type;
	int		i_start;
	int		totale;
    va_list arg_lst;
}				t_format;

# ifndef MIN_INT
#  define MIN_INT -2147483648
# endif
# define EXA_MAX "0123456789ABCDEF"
# define EXA_MIN "0123456789abcdef"
# define DECA "0123456789"

void	ft_print_str(t_format *var);
int		is_a_flag(const char *s, int i, t_format *var);
int 	is_a_type(const char c);
int		ft_atoi(char *str);
char	*ft_itoa(int n);
void	prnt_int(t_format *var);
void 	prnt_unint(t_format *var);
void 	ft_putc(t_format *var);
void 	prnt_point(t_format *var);
int		ft_strlen(const char *str);
char    *ft_uns_itoa(unsigned int n);
void	prnt_esa(t_format *var, int maiusc);
int		ft_printf(const char *s, ...);
void	ft_pprint(t_format *var);
int		ft_counter(const char *s, int i, char buffer[100000],t_format *var, int precision);

#endif