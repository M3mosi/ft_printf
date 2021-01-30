# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgiovo <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/30 18:29:42 by sgiovo            #+#    #+#              #
#    Updated: 2021/01/30 18:29:45 by sgiovo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra

LIBRI	= ft_printf.h

SRCS	=  ft_printf.c ft_uns_itoa.c ft_printf_utils.c 

OBJS	= ${SRCS:.c=.o}

RM		= rm -f

.c.o:
		${CC} ${CFLAGS} -I ${LIBRI} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
		ar rcs ${NAME} ${OBJS}

all:	${NAME}

clean:
		${RM} ${OBJS} *.gch

fclean:	clean
		${RM} ${NAME}

