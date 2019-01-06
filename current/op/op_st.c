/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 02:00:46 by jochang           #+#    #+#             */
/*   Updated: 2019/01/05 17:20:55 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_st(t_cyc *info, t_pc *pc)//imp
{
	int16_t		loc;

	TEA;
	//ft_printf("%d---[ST]\n", pc->r[0]);
	if (info->mem[0][MEM(pc->i + 1)].byte == 0x50)
	{
		pc->r[info->mem[0][MEM(pc->i + 3)].byte] = pc->r[info->mem[0][MEM(pc->i + 2)].byte];
		pc->i += 4;
	}
	else if (info->mem[0][MEM(pc->i + 1)].byte == 0x70)
	{
		cw_memren(&loc, &info->mem[0][MEM(pc->i + 3)], IND_SIZE);
		cw_memwen(&info->mem[0][MEM(pc->i + IDX(loc))], &pc->r[info->mem[0][MEM(pc->i + 2)].byte], REG_SIZE, pc->r[0]);
		pc->i += 5;
	}
	else
		pc->i++;
	TIME("op_sti\t");
}
