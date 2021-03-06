/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 02:00:06 by jochang           #+#    #+#             */
/*   Updated: 2019/01/05 17:25:46 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_lld(t_cyc *info, t_pc *pc)
{
	uint8_t		reg;
	int16_t	loc;

	TEA;
	//ft_printf("%d-------------[LLD]\n", pc->r[0]);
	if (info->mem[0][MEM(pc->i + 1)].byte == 0x90)
	{
		//ft_printf("ACB:90\n");
		reg = info->mem[0][MEM(pc->i + 6)].byte;
		if (REG(reg))
			cw_memren(&pc->r[reg], &info->mem[0][MEM(pc->i + 2)], REG_SIZE);
		pc->i += 7;
		pc->carry = (pc->r[reg]) ? 0 : 1;
	}
	else if (info->mem[0][MEM(pc->i + 1)].byte == 0xd0)
	{
		//ft_printf("ACB:d0\n");
		reg = info->mem[0][MEM(pc->i + 4)].byte;
		cw_memren(&loc, &info->mem[0][MEM(pc->i + 2)], IND_SIZE);
		if (REG(reg))
			cw_memren(&pc->r[reg], &info->mem[0][MEM(pc->i + loc)], REG_SIZE);
		pc->i += 5;
		pc->carry = (pc->r[reg]) ? 0 : 1;
	}
	else
		pc->i++;
	TIME("op_lld\t");
}
