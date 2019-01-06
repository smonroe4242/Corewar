/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 02:00:55 by jochang           #+#    #+#             */
/*   Updated: 2019/01/05 17:24:32 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_sti(t_cyc *info, t_pc *pc)
{
	int16_t		loc;
	int16_t		tmp;
	uint8_t		acb;

	TEA;
	acb = info->mem[0][MEM(pc->i + 1)].byte;
	loc = 0;
	tmp = 0;
	if ((acb >> 4) == 5)
		loc += pc->r[info->mem[0][MEM(pc->i + 3)].byte];
	else if ((acb >> 4) == 7 || (acb >> 4) == 6)
		cw_memren(&loc, &info->mem[0][MEM(pc->i + 3)], IND_SIZE);
	if ((acb & 0x0f) == 4)
		loc += pc->r[info->mem[0][(MEM(pc->i + 3 + ACB_ARG((acb & 0x30) >> 4)))].byte];
	else if ((acb & 0x0f) == 8)
		cw_memren(&tmp, &info->mem[0][MEM(pc->i + 3 + ACB_ARG((acb & 0x30) >> 4))], IND_SIZE);
	loc += tmp;
	cw_memwen(&info->mem[0][MEM(pc->i + IDX((int16_t)loc))], &pc->r[info->mem[0][MEM(pc->i + 2)].byte], REG_SIZE, pc->r[0]);
	pc->i += acb_len(acb);
	TIME("op_sti\t");
}
