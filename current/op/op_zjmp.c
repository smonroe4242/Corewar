/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 02:01:15 by jochang           #+#    #+#             */
/*   Updated: 2018/09/24 02:01:16 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_zjmp(t_cyc *info, t_pc *pc)//imp
{
	int16_t addr;

	TEA;
	//ft_printf("%d---------[ZJMP]\n", pc->r[0]);
	if (pc->carry)
	{
		ft_memrcpy(&addr, &info->mem[0][MEM(pc->i + 1)], IND_SIZE);
		pc->i = MEM(pc->i + IDX(addr));
		//ft_printf("Jumped to %d:%.2x\n", pc->i, info->mem[0][pc->i]);
	}
	else
	{
		//ft_printf("whoops lol~~~\n");
		pc->i += 3;
	}
	TIME("op_zjmp\t");
}
