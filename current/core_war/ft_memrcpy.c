/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 02:15:06 by jochang           #+#    #+#             */
/*   Updated: 2018/09/24 02:15:07 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	ft_memrcpy(void *dst, void *src, size_t n)
{
	uint8_t		*p;
	uint8_t		*w;

	p = src + n - 1;
	w = dst;
	while (n--)
		*(w++) = *(p--);
}