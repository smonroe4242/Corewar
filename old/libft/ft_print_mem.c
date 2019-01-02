/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <smonroe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 22:42:06 by smonroe           #+#    #+#             */
/*   Updated: 2018/09/05 22:44:55 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_print_mem(uint8_t *mem, int n)
{
	char	*chars;
	int		i;

	if (mem == NULL)
		return ;
	chars = "0123456789abcdef";
	i = -1;
	while (++i < n)
	{
		if(!(i % 16))
		{
			ft_putchar('\n');
			ft_printf("%.7x ", i);
		}
		ft_putchar(chars[mem[i] >> 4]);
		ft_putchar(chars[mem[i] & 0x0f]);
		ft_putchar(' ');

	}
	ft_putchar('\n');
}
