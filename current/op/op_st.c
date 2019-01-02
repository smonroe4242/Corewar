/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 02:00:46 by jochang           #+#    #+#             */
/*   Updated: 2018/09/24 02:00:48 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_st(t_cyc *info, t_pc *pc)//imp
{
	int16_t		loc;

	TEA;
	//ft_printf("%d---[ST]\n", pc->r[0]);
	if (info->mem[0][MEM(pc->i + 1)] == 0x50)
	{
		pc->r[info->mem[0][MEM(pc->i + 3)]] = pc->r[info->mem[0][MEM(pc->i + 2)]];
		pc->i += 4;
	}
	else if (info->mem[0][MEM(pc->i + 1)] == 0x70)
	{
		//ft_printf("src: %hhd @ %d (%d)\n", info->mem[0][MEM(pc->i + 3)], MEM(pc->i + 3), pc->i + 3);
		ft_memrcpy(&loc, &info->mem[0][MEM(pc->i + 3)], IND_SIZE);
		//ft_printf("ACB:70\tloc:%d\tpc->i:%d\n", loc, pc->i);
		//ft_printf("val %d\n", info->mem[0][MEM(pc->i + IDX(loc))]);
		//ft_printf("________%x________%d________\n", loc, loc);
		ft_memrcpy(&info->mem[0][MEM(pc->i + IDX(loc))], &pc->r[info->mem[0][MEM(pc->i + 2)]], REG_SIZE);
		//ft_printf("|%.2x|", info->mem[0][MEM(pc->i + IDX(loc) + 1)]);
		ft_memset(&info->ref[0][MEM(pc->i + IDX(loc))], pc->r[0], REG_SIZE);
		//ft_printf("%.2x|\n", info->mem[0][MEM(pc->i + IDX(loc) + 1)]);
		pc->i += 5;
	}
	else
		pc->i++;
	TIME("op_sti\t");
}