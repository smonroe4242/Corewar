/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 08:28:49 by smonroe           #+#    #+#             */
/*   Updated: 2018/09/09 08:30:40 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

int		main(void)
{
	int	x;
	char y;

	x = 65;
	y = 'A';
	write(1, &x, 4);
	write(1, "\n", 1);
	write(1, &y, 1);
	write(1, "\n", 1);
	return (0);
}
