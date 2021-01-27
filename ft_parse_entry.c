/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_entry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 18:51:18 by obritany          #+#    #+#             */
/*   Updated: 2020/11/26 18:51:21 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_get_precision(const char **format)
{
	int rslt;

	rslt = -1;
	if (**format == '.')
	{
		(*format)++;
		if (**format == '*')
		{
			(*format)++;
			return (-2);
		}
		rslt = 0;
		while (**format >= '0' && **format <= '9')
		{
			rslt = (rslt * 10) + (**format - '0');
			(*format)++;
		}
	}
	return (rslt);
}

static int	ft_get_width(const char **format)
{
	int rslt;

	if (**format == '*')
	{
		(*format)++;
		return (-2);
	}
	rslt = 0;
	while (**format >= '0' && **format <= '9')
	{
		rslt = (rslt * 10) + (**format - '0');
		(*format)++;
	}
	return (rslt);
}

static char	ft_get_flags(const char **format)
{
	char rslt;

	rslt = EMPTY;
	while (**format == '-' || **format == '0')
	{
		if (**format == '-')
			rslt = rslt | MINUS;
		if (**format == '0')
			rslt = rslt | ZERO;
		(*format)++;
	}
	if (rslt & MINUS)
		rslt = rslt & ~ZERO;
	return (rslt);
}

t_entry		ft_parse_entry(const char **format)
{
	t_entry rslt;

	(*format)++;
	rslt = ft_new_entry();
	rslt.flags = ft_get_flags(format);
	rslt.width = ft_get_width(format);
	rslt.precision = ft_get_precision(format);
	rslt.type = **format;
	if (!ft_strchr("cspdiuxX%", rslt.type))
		rslt.type = 0;
	(*format)++;
	return (rslt);
}
