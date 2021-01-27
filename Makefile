# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obritany <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/05 17:09:06 by obritany          #+#    #+#              #
#    Updated: 2020/11/26 21:27:43 by obritany         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a
SRCS		= ft_printf.c ft_new_entry.c ft_parse_entry.c ft_print_entry.c
OBJS		= $(SRCS:.c=.o)
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

LIBFT_DIR	= libft/
LIBFT		= libft.a

all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
			ar rcs $(NAME) $(OBJS)
			
$(LIBFT):
			$(MAKE) -C $(LIBFT_DIR)
			cp $(LIBFT_DIR)$(LIBFT) $(NAME)

clean:
			$(RM) $(OBJS)
			$(MAKE) -C $(LIBFT_DIR) clean

fclean:		clean
			$(RM) $(NAME)
			$(RM) $(LIBFT_DIR)$(LIBFT)

re:			fclean all

.PHONY:   all clean fclean re
