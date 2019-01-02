/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 07:42:48 by smonroe           #+#    #+#             */
/*   Updated: 2018/04/21 08:50:02 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

float	ft_frand(void)
{
	char	num[10];
	int		n;
	int		i;
	int		r;
	float	f;

	i = 0;
	r = 0;
	f = 0.0f;
	n = open("/dev/random", O_RDONLY);
	read(n, num, 10);
	close(n);
	while (i < 10)
		r += (r * 10 + (num[i++] - '0')) & 0x7fffffff;
	f += (r / 2147483647.0f);
	return (f);
}
