/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 12:51:56 by jochang           #+#    #+#             */
/*   Updated: 2018/08/12 12:55:34 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strndup(const char *src, size_t len)
{
	char	*str;

	NULL_CHECK(!(str = (char*)malloc(len + 1)));
	str = ft_strncpy(str, src, len);
	str[len] = '\0';
	return (str);
}
