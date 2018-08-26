/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 22:07:02 by smonroe           #+#    #+#             */
/*   Updated: 2018/08/25 22:28:02 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s, int i)
{
	char	*tmp;

	if (!s)
		return (NULL);
	if (!(tmp = ft_strnew(i)))
		return (NULL);
	ft_memcpy(tmp, s, ft_strlen(s));
	return (tmp);
}
