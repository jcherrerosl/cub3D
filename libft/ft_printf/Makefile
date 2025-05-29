# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juanherr <juanherr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/29 23:13:11 by juanherr          #+#    #+#              #
#    Updated: 2025/05/27 15:47:58 by juanherr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -fPIC

NAME = libftprintf.a

SRCS = ft_printf.c ft_printchar.c ft_put_hex_low.c ft_put_hex_upp.c ft_printnbr.c \
	   ft_putptr.c ft_putstr.c ft_put_unsigned.c ft_put_perc.c len_num.c

OBJS = $(SRCS:.c=.o)

RM = rm -f

AR = ar rcs

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re
