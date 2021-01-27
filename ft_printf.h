/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 18:51:55 by obritany          #+#    #+#             */
/*   Updated: 2020/11/26 18:52:13 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "libft/libft.h"

# define EMPTY	0b00000000
# define MINUS	0b00000001
# define ZERO	0b00000010

typedef struct	s_entry
{
	char	flags;
	int		width;
	int		precision;
	int		length;
	char	type;
	long	value;
}				t_entry;

int				ft_printf (const char *format, ...);
int				ft_print_entry(t_entry entry);
t_entry			ft_new_entry();
t_entry			ft_parse_entry (const char **format);

#endif
