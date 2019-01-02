/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 01:59:44 by jochang           #+#    #+#             */
/*   Updated: 2018/09/24 01:59:44 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_ldi(t_cyc *info, t_pc *pc)
{
	int32_t		loc;
	int32_t		tmp;
	uint8_t		acb;

	TEA;
	//ft_printf("%d----------[LDI]\n", pc->r[0]);
	acb = info->mem[0][MEM(pc->i + 1)];
	loc = 0;
	tmp = 0;
	if ((acb >> 6) == REG_CODE)
		loc += pc->r[info->mem[0][MEM(pc->i + 2)]];
	else if ((acb >> 6) == DIR_CODE || (acb >> 6) == IND_CODE)
		ft_memrcpy(&loc, &info->mem[0][MEM(pc->i + 2)], IND_SIZE);
	//ft_printf("|%d| + ", loc);
	if ((acb & 0x30) == (REG_CODE << 4))
	{
		//ft_printf("pc->r[%02x]\n", info->mem[0][(MEM(pc->i + 3 + ACB_ARG((acb & 0x30) >> 4)))]);
		tmp = pc->r[info->mem[0][(MEM(pc->i + 3 + ACB_ARG((acb & 0x30) >> 4)))]];
	}
	else if (((acb & 0x30) == (DIR_CODE << 4)) || ((acb & 0x30) == (IND_CODE << 4)))
		ft_memrcpy(&tmp, &info->mem[0][MEM(pc->i + 3 + ACB_ARG((acb & 0x30) >> 4))], IND_SIZE);
	loc += tmp;
	//ft_printf("|%d| = |%d|\n", tmp, loc);
	tmp = info->mem[0][MEM(pc->i + acb_len(acb) - 1)];
	//ft_printf("reg[%d]\n", tmp);
	if (REG(tmp))
		ft_memrcpy(&pc->r[tmp], &info->mem[0][MEM(pc->i + IDX((int16_t)loc))], REG_SIZE);
	//ft_printf("Result: %08x\n", pc->r[tmp]);
	//ft_printf("IDX((int16_t)loc) == %d and loc == %d", IDX((int16_t)loc), loc);
	pc->i += acb_len(acb);
	pc->carry = 1;
	TIME("op_ldi\t");
}
