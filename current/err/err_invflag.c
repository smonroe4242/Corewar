/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_invflag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 22:04:06 by jochang           #+#    #+#             */
/*   Updated: 2018/09/23 22:04:08 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/err.h"

void	err_invflag(char c)
{
	if (c == '?')
	{
		ft_printf("Error: Invalid Flag.\n");
		err_nofile("cw", 1);
	}
}
