/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 22:07:02 by smonroe           #+#    #+#             */
/*   Updated: 2018/08/27 16:21:48 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s, int n)
{
	char	*tmp;
	int		i;

	if (!(tmp = ft_strnew(n)))
		return (NULL);
	i = -1;
	while (++i < n)
		tmp[i] = s[i];
	return (tmp);
}
