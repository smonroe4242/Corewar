/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_invfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 19:31:37 by jochang           #+#    #+#             */
/*   Updated: 2018/09/09 19:34:40 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/err.h"

void	err_invfile(char *prog, char *file)
{
	if (ft_strequ(prog, "asm"))
		ft_printf("File not readable. Please enter valid .s champion file.\n");
	else if (ft_strequ(prog, "cw"))
		ft_printf("Read Error: %s not valid\n", file);
	exit(1);
}
