/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 01:59:59 by jochang           #+#    #+#             */
/*   Updated: 2018/09/24 01:59:59 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_live(t_cyc *info, t_pc *pc)//imp
{
	TEA;
	//ft_printf("%d-[ALIVE]\n", pc->r[0]);
	ft_memrcpy(&info->last, &info->mem[0][MEM(pc->i + 1)], REG_SIZE);
	if (-info->last - 1  < MAX_PLAYERS && -info->last - 1 >= 0)
		info->pcount[-info->last - 1]++;
	pc->alive++;
	pc->i += 5;
	TIME("op_live\t");
}