/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_scan_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 19:46:50 by smonroe           #+#    #+#             */
/*   Updated: 2019/01/03 23:22:03 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	pc_scan_op(t_cyc *info, t_pc *pc)
{
	//ft_printf("at mem[%d] (%.2x) for %d more cycles\n", pc->i, info->mem[0][pc->i], pc->wait);
	t_pc		*tmp;
	uint32_t	front;
	uint32_t	back;

	tmp = pc;
	while (tmp)
	{
		if (info->mem[0][tmp->i] < 1 || info->mem[0][tmp->i] > 16)
			tmp->i++;
		else if (tmp->wait <= 0)
		{
			//ft_printf("Doing function, tmp->i = %d\n", tmp->i);
			front = (uint32_t)info->mem[0][0];
			back = (uint32_t)info->mem[0][MEM_SIZE];
			g_op_fn[info->mem[0][tmp->i]](info, tmp);
			//ft_printf("%.8x\n%.8x\n", (uint32_t)info->mem[0][MEM_SIZE], (uint32_t)info->mem[0][0]);
			if (front != (uint32_t)info->mem[0][0])
			{
				ft_memcpy(&info->mem[0][MEM_SIZE], &info->mem[0][0], REG_SIZE);
				ft_memcpy(&info->ref[0][MEM_SIZE], &info->ref[0][0], REG_SIZE);
			}
			if (back != (uint32_t)info->mem[0][MEM_SIZE])
			{
				ft_memcpy(&info->mem[0][0], &info->mem[0][MEM_SIZE], REG_SIZE);
				ft_memcpy(&info->ref[0][0], &info->ref[0][MEM_SIZE], REG_SIZE);
			}
			tmp->wait = WAIT_MOD(info->mem[0][tmp->i]);
		}
		tmp->wait--;
		if (tmp->wait < 0)
			if (info->mem[0][tmp->i] < 1 || info->mem[0][tmp->i] > 16)
				tmp->wait = WAIT_MOD(info->mem[0][tmp->i]);
		tmp = tmp->next;
	}
}

#undef ARR
#undef WAIT_MOD
