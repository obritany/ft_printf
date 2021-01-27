/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_entry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obritany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 18:51:03 by obritany          #+#    #+#             */
/*   Updated: 2020/11/26 18:51:10 by obritany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_entry	ft_new_entry(void)
{
	t_entry rslt;

	rslt.flags = 0b00000000;
	rslt.width = 0;
	rslt.precision = -1;
	rslt.length = 0;
	rslt.type = '\0';
	rslt.value = 0;
	return (rslt);
}
