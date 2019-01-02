/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 01:59:07 by jochang           #+#    #+#             */
/*   Updated: 2018/09/24 01:59:08 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_aff(t_cyc *info, t_pc *pc)
{
	uint32_t	chr;

	TEA;
	if (info->mem[0][MEM(pc->i + 1)] == 0x40)
	{
		chr = pc->r[info->mem[0][MEM(pc->i + 2)]];
		if (chr <= 0x7F)
			write(1, &chr, 1);
		else
			ft_putwchar(chr);
		pc->i += 3;
	}
	else
		pc->i++;
	TIME("op_aff\t");
}
