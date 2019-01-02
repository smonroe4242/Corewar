/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 10:08:04 by smonroe           #+#    #+#             */
/*   Updated: 2019/01/02 10:08:25 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putwchar(uint32_t c)
{
	uint8_t	str[4];

	if (c < (1 << 11))
	{
		str[0] = (unsigned char)((c >> 6) | 0xC0);
		str[1] = (unsigned char)((c & 0x3F) | 0x80);
		write(1, &str, 2);
	}
	else if (c < (1 << 16))
	{
		str[0] = (unsigned char)(((c >> 12)) | 0xE0);
		str[1] = (unsigned char)(((c >> 6) & 0x3F) | 0x80);
		str[2] = (unsigned char)((c & 0x3F) | 0x80);
		write(1, &str, 3);
	}
	else if (c < (1 << 21))
	{
		str[0] = (unsigned char)(((c >> 18)) | 0xF0);
		str[1] = (unsigned char)(((c >> 12) & 0x3F) | 0x80);
		str[2] = (unsigned char)(((c >> 6) & 0x3F) | 0x80);
		str[3] = (unsigned char)((c & 0x3F) | 0x80);
		write(1, &str, 4);
	}
}
