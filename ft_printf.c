#include "ft_printf_lib.h"

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
        prnt_unint(&(*var));/*
    else if (var->type == 'x')
        prnt_esa(&(*var));
    else if (var->type == 'X')
        prnt_esamausic(&(*var)); */ 
	return (0);
}

int     ft_fll(const char *s,int i, t_format *var)
{
    char    buffer[100000];
    int     j;
    
    var->i_start = i;
    if (is_a_flag(s, i, &(*var)))
	{
		var->flag = s[i];
		i++;
	}
    if (!is_a_flag(s, i, &(*var)) && s[i] >= '0' && s[i] <= '1')
    {
        if (s[i] == '*')
        var->star_width = 1;
        else
        {
            j = 0;
            buffer[0] = 0;
            while(s[i] <= '9' && s[i] >= '0')
                buffer[j++] = s[i++];
            buffer[j] = 0;
            if(buffer[0])
                var->width = ft_atoi(buffer); 
        }   
    }
    if (!is_a_flag(s, i, &(*var)) && is_a_type(s[i]))
        var->type = s[i];
    ft_trckr(var);
    return (i + 1);
}

int     ft_scroll(const char *s, t_format *var)
{
    char *str;
    int len;
    int i;
    int stampe;

    i=0;
    stampe = 0;
    len = ft_strlen(s);
    ft_init(&*var);
    while (s[i])
    {
        if (s[i] == '%' && s[i + 1] != '%')
           i = ft_fll(s,i+1, &(*var));
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

int     main()
{
	unsigned int s = 4294967294;
    int inter = 398734;
    int ninter = -391734345;
    int n;
    int m;
    char *p = "bella frah";
    

    m = ft_printf("MIA:      %s\n", p);
    n = printf("ORIGINAL: %s\n", p);
    printf("mia:      %d\nprintf:   %d\n",m,n);
}