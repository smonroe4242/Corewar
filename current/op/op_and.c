/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 01:59:13 by jochang           #+#    #+#             */
/*   Updated: 2019/01/05 00:49:13 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

//needs work
void	op_and(t_cyc *info, t_pc *pc)//imp
{
	TEA;
	int32_t	d1;
	int32_t	d2;
	int16_t	loc;
	uint8_t		acb;
	//ft_printf("%d------[AND]\n", pc->r[0]);
	d1 = 0;
	d2 = 0;
	acb = info->mem[0][MEM(pc->i + 1)].byte;

	if ((acb >> 6) == REG_CODE)
		ft_memrcpy(&d1, &pc->r[info->mem[0][MEM(pc->i + 2)].byte], REG_SIZE);
	else if ((acb >> 6) == IND_CODE)
	{
		cw_memr(&loc, &info->mem[0][MEM(pc->i + 2)], IND_SIZE);
		cw_memr(&d1, &info->mem[0][MEM(pc->i + IDX(loc))], REG_SIZE);
	}
	else if ((acb >> 6) == DIR_CODE)
		cw_memr(&d1, &info->mem[0][MEM(pc->i + 2)], DIR_SIZE);
	if ((acb >> 4) == REG_CODE)
		ft_memrcpy(&d2, &pc->r[info->mem[0][MEM(pc->i + ACB_ARG((acb & 0x20) >> 4))].byte], REG_SIZE);
	else if ((acb >> 4) == IND_CODE)
	{
		cw_memr(&loc, &info->mem[0][MEM(pc->i + ACB_ARG((acb & 0x20) >> 4))], IND_SIZE);
		cw_memr(&d2, &info->mem[0][MEM(pc->i + IDX(loc))], REG_SIZE);
	}
	else if (((acb >> 4) & 0x3) == DIR_CODE)
		cw_memr(&d2, &info->mem[0][MEM(pc->i + ACB_ARG((acb & 0x20) >> 4))], DIR_SIZE);
	loc = acb_len(acb);
	if (REG(info->mem[0][MEM(pc->i + loc - 1)].byte))
		pc->r[info->mem[0][MEM(pc->i + loc - 1)].byte] = d1 & d2;
	pc->carry = (d1 & d2) ? 0 : 1;
	pc->i += loc;
	TIME("op_and\t");
}
