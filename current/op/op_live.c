/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 01:59:59 by jochang           #+#    #+#             */
/*   Updated: 2019/01/05 01:00:06 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_live(t_cyc *info, t_pc *pc)//imp
{
	TEA;
	//ft_printf("%d-[ALIVE]\n", pc->r[0]);
	//set t_mem.active to 2 for live call instruction -smonroe DO THIS
	cw_memr(&info->last, &info->mem[0][MEM(pc->i + 1)], REG_SIZE);
	if (-info->last - 1  < MAX_PLAYERS && -info->last - 1 >= 0)
	{
		info->last_live[-info->last - 1] = info->cycle;
		info->pcount[-info->last - 1]++;
	}
	pc->alive++;
	pc->i += 5;
	TIME("op_live\t");
}
