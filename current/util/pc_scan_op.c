/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_scan_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 19:46:50 by smonroe           #+#    #+#             */
/*   Updated: 2019/01/01 22:29:45 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"
#define ARR -1, 10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800, 10, 50, 1000, 2
#define WAIT_MOD(x) (uint16_t[]){ARR}[(x)]

void	pc_scan_op(t_cyc *info, t_pc *pc)
{
	//ft_printf("at mem[%d] (%.2x) for %d more cycles\n", pc->i, info->mem[0][pc->i], pc->wait);
	t_pc	*tmp;

	tmp = pc;
	while (tmp)
	{
		if (info->mem[0][tmp->i] < 1 || info->mem[0][tmp->i] > 16)
			tmp->i++;
		else if (!tmp->wait)
		{
			//ft_printf("Doing function, tmp->i = %d\n", tmp->i);
			g_op_fn[info->mem[0][tmp->i]](info, tmp);
			if ((uint32_t)info->mem[0][MEM_SIZE] != (uint32_t)info->mem[0][0])
			{
				//ft_printf("%.8x\n%.8x\n", (uint32_t)info->mem[0][MEM_SIZE], (uint32_t)info->mem[0][0]);
				ft_memcpy(&info->mem[0][0], &info->mem[0][MEM_SIZE], REG_SIZE);
				ft_memcpy(&info->ref[0][0], &info->ref[0][MEM_SIZE], REG_SIZE);
			}
			tmp->wait = WAIT_MOD(info->mem[0][tmp->i]) - 1; /// check one-off error ---
//			^ replaces : // wait_mod(&tmp->wait, info->mem[0][tmp->i]);
			//ft_printf("tmp->i updated to %d and given wait time of %d\n", tmp->i, tmp->wait);
		}
//		else if (tmp->wait > 0)
//			tmp->wait--;
		tmp->wait--;
		if (tmp->wait < 0)
			if (info->mem[0][tmp->i] < 1 || info->mem[0][tmp->i] > 16)
				tmp->wait = WAIT_MOD(info->mem[0][tmp->i]);
		tmp = tmp->next;
	}
}

#undef ARR
#undef WAIT_MOD
