/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_invarg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 21:37:15 by jochang           #+#    #+#             */
/*   Updated: 2018/09/12 21:38:21 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/err.h"

void	err_invarg(char *op, int l)
{
	ft_printf("\e[31m\e[1mError:\e[0m Bad argument \"\e[31m%s\e[0m\"", op);
	ft_printf(" found on line \e[32m%d\e[0m.\nFile failed to compile.\n", l);
	exit(1);
}
