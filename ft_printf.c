/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 18:51:43 by obritany          #+#    #+#             */
/*   Updated: 2020/11/26 18:51:49 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_entry	get_next_entry(const char **format, size_t *count)
{
	char	*temp;
	t_entry	entry;

	while (**format && **format != '%')
		*count += write(1, (*format)++, 1);
	if (**format == '\0')
		return (ft_new_entry());
	temp = (char*)*format;
	entry = ft_parse_entry(format);
	if (entry.type == '%')
	{
		entry.type = 'c';
		entry.value = '%';
	}
	if (entry.type == 0)
	{
		write(1, "%", 1);
		(*count)++;
		if (entry.type == 0)
			*format = ++temp;
		entry.type = -1;
	}
	return (entry);
}

static int		print_entries(const char *format, va_list arglist, size_t count)
{
	t_entry entry;

	while (*format)
	{
		entry = get_next_entry(&format, &count);
		if (entry.type == 0)
			break ;
		if (entry.type == -1)
			continue ;
		if (entry.width == -2)
			if ((entry.width = va_arg(arglist, int)) < 0)
				entry.flags = (entry.flags | MINUS) & ~ZERO;
		entry.width = (entry.width < 0) ? -entry.width : entry.width;
		if (entry.precision == -2)
			if ((entry.precision = va_arg(arglist, int)) < 0)
				entry.precision = -1;
		if (entry.precision != -1)
			entry.flags = entry.flags & ~ZERO;
		if (entry.value != '%' && (entry.type == 'p' || entry.type == 's'))
			entry.value = va_arg(arglist, long);
		else if (entry.value != '%')
			entry.value = va_arg(arglist, int);
		count += ft_print_entry(entry);
	}
	return (count);
}

int				ft_printf(const char *format, ...)
{
	size_t	count;
	va_list arglist;

	count = 0;
	va_start(arglist, format);
	count = print_entries(format, arglist, count);
	va_end(arglist);
	return (count);
}
