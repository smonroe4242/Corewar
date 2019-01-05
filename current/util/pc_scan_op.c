/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_scan_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 19:46:50 by smonroe           #+#    #+#             */
/*   Updated: 2019/01/05 04:43:41 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	pc_scan_op(t_cyc *info, t_pc *pc)
{
	//ft_printf("at mem[%d] (%.2x) for %d more cycles\n", pc->i, info->mem[0][pc->i], pc->wait);
	t_pc		*tmp;
	t_mem	front[REG_SIZE];
	t_mem	back[REG_SIZE];

	tmp = pc;
	while (tmp)
	{
		if (info->mem[0][tmp->i].byte < 1 || info->mem[0][tmp->i].byte > 16)
			tmp->i++;
		else if (tmp->wait <= 0)
		{
			//ft_printf("Doing function, tmp->i = %d\n", tmp->i);
			cw_memcp(front, &info->mem[0][0], REG_SIZE);
			cw_memcp(back, &info->mem[0][MEM_SIZE], REG_SIZE);
			g_op_fn[info->mem[0][tmp->i].byte](info, tmp);
			//ft_printf("%.8x\n%.8x\n", (uint32_t)info->mem[0][MEM_SIZE], (uint32_t)info->mem[0][0]);
			if (ft_memcmp(front, &info->mem[0][0], sizeof(front)))
				cw_memcp(&info->mem[0][MEM_SIZE], &info->mem[0][0], REG_SIZE);
			if (ft_memcmp(back, &info->mem[0][MEM_SIZE], sizeof(back)))
				cw_memcp(&info->mem[0][0], &info->mem[0][MEM_SIZE], REG_SIZE);
			tmp->wait = WAIT_MOD(info->mem[0][tmp->i].byte);
		}
		tmp->wait--;
		if (tmp->wait < 0)
			if (info->mem[0][tmp->i].byte < 1 || info->mem[0][tmp->i].byte > 16)
				tmp->wait = WAIT_MOD(info->mem[0][tmp->i].byte);
		info->mem[0][tmp->i].active = 1;
		tmp = tmp->next;
	}
}

#undef ARR
#undef WAIT_MOD
