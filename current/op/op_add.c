/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 01:58:58 by jochang           #+#    #+#             */
/*   Updated: 2018/09/24 01:58:59 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_add(t_cyc *info, t_pc *pc)
{
	uint8_t	arga;
	uint8_t	argb;
	uint8_t	argc;

	TEA;
	arga = info->mem[0][MEM(pc->i + 2)];
	argb = info->mem[0][MEM(pc->i + 3)];
	argc = info->mem[0][MEM(pc->i + 4)];
	if (info->mem[0][MEM(pc->i + 1)] == 0x54 &&
		REG(arga) && REG(argb) && REG(argc))
	{
		pc->r[argc] = pc->r[argb] + pc->r[arga];
		pc->i += 5;
		pc->carry = 1;
	}
	else
		pc->i++;
	TIME("op_add\t");
}