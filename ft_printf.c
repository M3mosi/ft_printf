#include "ft_printf.h"

void    ft_init(t_format *var)
{
	var->flag = 0;
	var->width = 0;
	var->prcsn = -1;
	var->type = 0;
    var->star_prec = 0;
    var->star_width = 0;
	var->i_start = 0;
}

int     ft_trckr(t_format *var)
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
        prnt_point(&(*var));
    else if (var->type == 'u')
        prnt_unint(&(*var));
    else if (var->type == 'x')
        prnt_esa(&(*var), 0);
    else if (var->type == 'X')
        prnt_esa(&(*var), 1); 
	return (0);
}

int     ft_fll(const char *s, int i, t_format *var)
{
    char    buffer[100000];
    
    var->i_start = i;
    if (is_a_flag(s, i, &(*var)) && var->flag != '-')
		var->flag = s[i++];
    if (s[i] == '*')
        var->star_width = 1;
    else if (!is_a_flag(s, i, &(*var)) && (s[i] >= '0' && s[i] <= '9'))
        i = ft_counter(s, i, buffer, &(*var), var->prcsn);
    if(!is_a_flag(s, i, &(*var) ) && s[i] == '.')
        i = ft_counter(s, ++i, buffer, &(*var), (var->prcsn = 0));
    if (!is_a_flag(s, i, &(*var)) && is_a_type(s[i]))
        var->type = s[i];
    if(s[i] == '%' && !(var->type))
        ft_pprint(&(*var));
    ft_trckr(var);
    return (i + 1);
}

int     ft_scroll(const char *s, t_format *var)
{
    int len;
    int i;
    int stampe;

    i=0;
    stampe = 0;
    len = ft_strlen(s);
    while (s[i])
    {
        ft_init(&*var);
        if (s[i] == '%' && s[i + 1] != '%')
        {
           i = ft_fll(s,i+1, &(*var));
           continue;
        }
        if (s[i] == '%' && s[i + 1] == '%')
            i++;
        if (i < len)
        {
            write(1,&(s[i]),1);
            stampe += 1;
        }
        i++;
    }
    return(stampe);
}

int     ft_printf(const char *s, ...) 
{
    t_format var;
    int stampe;

    var.totale = 0;
    va_start(var.arg_lst, s);
    stampe = ft_scroll(s, &var);
    va_end(var.arg_lst);
    return(var.totale + stampe);
}

 /* int     main()
{
	unsigned int s = 4294967294;
    int inter = 398734;
    int ninter = -391734345;
    unsigned char h = 0x64;
    char c = 'r'; 
    int h2 = 0xFAFA;
    int n;
    int m;
    char *p = "bella frah";

    printf("\n---------------\n");
    m = ft_printf("MINE    :%7.5s", "bombastic");
    printf("\n---------------\n");
    n = printf("Original:%7.5s", "bombastic");
    printf("\n---------------\n");printf("\n---------------\n");
    printf("\nmia     :      %d\nprintf  :   %d\n", m, n);
 }  */
 