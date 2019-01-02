/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 02:01:02 by jochang           #+#    #+#             */
/*   Updated: 2019/01/02 03:53:54 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_sub(t_cyc *info, t_pc *pc)
{
	uint8_t	arga;
	uint8_t	argb;
	uint8_t	argc;

	TEA;
	//ft_printf("%d-----[SUB]\n", pc->r[0]);
	argc = info->mem[0][MEM(pc->i + 4)];
	argb = info->mem[0][MEM(pc->i + 3)];
	arga = info->mem[0][MEM(pc->i + 2)];
	if (info->mem[0][MEM(pc->i + 1)] == 0x54 && REG(arga) &&
		REG(argb) && REG(argc))
	{
		pc->r[argc] = pc->r[arga] - pc->r[argb];
		pc->i += 5;
		pc->carry = (pc->r[argc]) ? 0 : 1;
	}
	else
		pc->i++;
	TIME("op_sub\t");
}
