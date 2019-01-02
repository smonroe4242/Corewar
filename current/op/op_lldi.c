/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 02:00:14 by jochang           #+#    #+#             */
/*   Updated: 2019/01/02 04:22:06 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_lldi(t_cyc *info, t_pc *pc)
{
	int32_t		loc;
	int32_t		tmp;
	uint8_t		acb;

	TEA;
	//ft_printf("%d--------------[LLDI]\n", pc->r[0]);
	acb = info->mem[0][MEM(pc->i + 1)];
	loc = 0;
	tmp = 0;
	if ((acb >> 6) == REG_CODE)
		loc += pc->r[info->mem[0][MEM(pc->i + 2)]];
	else if ((acb >> 6) == DIR_CODE || (acb >> 6) == IND_CODE)
		ft_memrcpy(&loc, &info->mem[0][MEM(pc->i + 2)], IND_SIZE);
	//ft_printf("%d\n", loc);
	if ((acb & 0x30) == (REG_CODE << 4))
		loc += pc->r[info->mem[0][(MEM(pc->i + 2 + ACB_ARG((acb & 0x30) >> 4)))]];
	else if (((acb & 0x30) == (DIR_CODE << 4)) || ((acb & 0x30) == (IND_CODE << 4)))
		ft_memrcpy(&tmp, &info->mem[0][MEM(pc->i + 2 + ACB_ARG((acb & 0x30) >> 4))], IND_SIZE);
	loc += tmp;
	tmp = info->mem[0][MEM(pc->i + acb_len(acb) - 1)];
	//ft_printf("%d as loc and for tmp %d\n", loc, tmp);
	if (REG(tmp))
		ft_memrcpy(&pc->r[tmp], &info->mem[0][MEM(pc->i + (int16_t)loc)], REG_SIZE);
	pc->i += acb_len(acb);
	pc->carry = (pc->r[tmp]) ? 0 : 1;
	TIME("op_lld\t");
}
