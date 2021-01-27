/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_entry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 18:51:30 by obritany          #+#    #+#             */
/*   Updated: 2020/11/26 18:51:32 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*get_space(t_entry entry, char *str, int len, char type)
{
	char	*rslt;
	int		sign;
	int		size;

	sign = (str[0] == '-' ? 1 : 0);
	if (type == 'p' && sign)
		len--;
	if (type == 'w')
		size = entry.width - len;
	else
		size = entry.precision - len;
	if ((rslt = ft_calloc(size + 1, sizeof(char))) == 0)
		return (0);
	if (!(entry.flags & ZERO) && type == 'w')
		ft_memset(rslt, ' ', (size));
	else if (!(entry.flags & MINUS) || type == 'p')
	{
		ft_memset(rslt, '0', (size));
		if (sign)
		{
			rslt[0] = '-';
			str[0] = '0';
		}
	}
	return (rslt);
}

static char	*add_width(t_entry entry, char *str)
{
	char	*space;
	char	*temp;
	int		len;

	len = ft_strlen(str);
	if (entry.width <= len)
		return (str);
	space = get_space(entry, str, len, 'w');
	temp = str;
	if (entry.flags & MINUS)
		str = ft_strjoin(str, space);
	else
		str = ft_strjoin(space, str);
	free(temp);
	free(space);
	return (str);
}

static char	*add_precision(t_entry entry, char *str)
{
	char	*space;
	char	*temp;
	int		len;

	if (entry.precision == -1)
		return (str);
	len = ft_strlen(str);
	if (entry.type == 's')
		if (entry.precision < len)
			str[entry.precision] = '\0';
	if (entry.type != 's' && ft_strncmp(str, "0", 2) == 0 &&
		entry.precision == 0)
		str[0] = '\0';
	if (entry.type != 's')
	{
		if (entry.precision <= (len - (str[0] == '-' ? 1 : 0)))
			return (str);
		space = get_space(entry, str, len, 'p');
		temp = str;
		str = ft_strjoin(space, str);
		free(temp);
		free(space);
	}
	return (str);
}

static char	*get_str_value(t_entry entry)
{
	char *rslt;

	rslt = 0;
	if (entry.type == 'd' || entry.type == 'i')
		rslt = ft_itoa(entry.value);
	else if (entry.type == 'u')
		rslt = ft_utoa_base(entry.value, 10, 'i');
	else if (entry.type == 'x')
		rslt = ft_utoa_base(entry.value, 16, 'i');
	else if (entry.type == 'X')
		rslt = ft_strtoupper(ft_utoa_base(entry.value, 16, 'i'));
	else if (entry.type == 'c')
		rslt = ft_memset(ft_calloc(2, sizeof(char)),
			(entry.value == 0 ? '0' : entry.value), 1);
	else if (entry.type == 's')
	{
		if (entry.precision == 0)
			rslt = ft_strdup("");
		else
			rslt = ft_strdup(entry.value == 0 ? "(null)" : (char *)entry.value);
	}
	else if (entry.type == 'p')
		rslt = ft_utoa_base(entry.value, 16, 'l');
	return (rslt);
}

int			ft_print_entry(t_entry entry)
{
	char	*str;
	char	*temp;
	size_t	len;

	if ((str = get_str_value(entry)) == 0)
		return (0);
	if ((str = add_precision(entry, str)) == 0)
		return (0);
	if (entry.type == 'p')
	{
		temp = str;
		str = ft_strjoin("0x", str);
		free(temp);
		if (!str)
			return (0);
	}
	if ((str = add_width(entry, str)) == 0)
		return (0);
	len = ft_strlen(str);
	if (entry.type == 'c' && entry.value == 0)
		*ft_strchr(str, '0') = '\0';
	write(1, str, len);
	free(str);
	return (len);
}
