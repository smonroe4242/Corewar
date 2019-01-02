/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 02:00:55 by jochang           #+#    #+#             */
/*   Updated: 2018/09/24 02:00:56 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_sti(t_cyc *info, t_pc *pc)
{
	int16_t		loc;
	int16_t		tmp;
	uint8_t		acb;

	TEA;
	//ft_printf("%d-----------[STI]\n", pc->r[0]);
	acb = info->mem[0][MEM(pc->i + 1)];
	loc = 0;
	tmp = 0;
	if ((acb >> 4) == 5)
		loc += pc->r[info->mem[0][MEM(pc->i + 3)]];
	else if ((acb >> 4) == 7 || (acb >> 4) == 6)
		ft_memrcpy(&loc, &info->mem[0][MEM(pc->i + 3)], IND_SIZE);
	//ft_printf("%d\n", loc);
	if ((acb & 0x0f) == 4)
	{
		//ft_printf("\n[register %d hold %d]\n", info->mem[0][(MEM(pc->i + 3 + ACB_ARG((acb & 0x30) >> 4)))], pc->r[info->mem[0][(MEM(pc->i + 3 + ACB_ARG((acb & 0x30) >> 4)))]]);
		//ft_printf("loc is %d before", loc);
		loc += pc->r[info->mem[0][(MEM(pc->i + 3 + ACB_ARG((acb & 0x30) >> 4)))]];
		//ft_printf(" and %d after\n", loc);
	}
	else if ((acb & 0x0f) == 8)
		ft_memrcpy(&tmp, &info->mem[0][MEM(pc->i + 3 + ACB_ARG((acb & 0x30) >> 4))], IND_SIZE);
	//ft_printf("loc: %d tmp: %d | ", loc, tmp);
	loc += tmp;
	//ft_printf("%d - %d idx\n", loc, IDX(loc));
	ft_memrcpy(&info->mem[0][MEM(pc->i + IDX((int16_t)loc))],
	&pc->r[info->mem[0][MEM(pc->i + 2)]], REG_SIZE);
	ft_memset(&info->ref[0][MEM(pc->i + IDX((int16_t)loc))], pc->r[0], REG_SIZE);
	pc->i += acb_len(acb);
	TIME("op_sti\t");
}
