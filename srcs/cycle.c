/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <smonroe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 20:19:50 by smonroe           #+#    #+#             */
/*   Updated: 2018/09/08 14:29:57 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

const t_fn g_op_fn[] = {NULL, &op_live, &op_ld, &op_st, &op_add,
							&op_sub, &op_and, &op_or, &op_xor, &op_zjmp,
							&op_ldi, &op_sti, &op_fork, &op_lld, &op_lldi,
							&op_lfork, &op_aff};

uint16_t	acb_lend(uint8_t acb)
{
	if (acb == 0x80 || acb == 0x70 || acb == 0x50)
		return (4);
	if (acb == 0xd0 || acb == 0x90 || acb == 54)
		return (5);
	if (acb == 0xd4 || acb == 0x74)
		return (6);
	if (acb == 0xf4)
		return (7);
	if (acb == 0x94 || acb == 0x64 || acb == 0x58)
		return (8);
	if (acb == 0xe4 || acb == 0xb4 || acb == 78)
		return (9);
	if (acb == 0x94 || acb == 0x68)
		return (11);
	else
		return (1);
}

uint16_t	acb_len(uint8_t acb)
{
	uint16_t	len;

	len = 0;
	len += (((acb >> 6) == 3) ? 4 : (acb >> 6));
	len += ((((acb >> 4) & 3) == 3) ? 4 : ((acb >> 4) & 3));
	len += ((((acb >> 2) & 3) == 3) ? 4 : ((acb >> 2) & 3));
	return (len + 2);
}

void	op_live(t_cyc *info, t_pc *pc)//imp
{
	ft_printf("--------------Im alive------------------");
	ft_memrcpy(&info->last, &info->mem[0][MEM(pc->i + 1)], REG_SIZE);
	if (-info->last - 1  < MAX_PLAYERS)
		info->pcount[-info->last - 1]++;
	pc->alive++;
	pc->i += 5;
}

void	op_ld(t_cyc *info, t_pc *pc)
{
	uint8_t		reg;
	uint16_t	loc;

	ft_printf("-----------------ld--%.2x---------------------", info->mem[0][MEM(pc->i + 1)]);
	if (info->mem[0][MEM(pc->i + 1)] == 0x90)
	{
		ft_printf("ACB:90\n");
		reg = info->mem[0][MEM(pc->i + 6)];
		ft_memrcpy(&pc->r[reg], &info->mem[0][MEM(pc->i + 2)], REG_SIZE);
		pc->i += 7;
	}
	else if (info->mem[0][MEM(pc->i + 1)] == 0xd0)
	{
		ft_printf("ACB:d0\n");
		reg = info->mem[0][MEM(pc->i + 4)];
		ft_memrcpy(&loc, &info->mem[0][MEM(pc->i + 2)], IND_SIZE);
		ft_memrcpy(&pc->r[reg], &info->mem[0][MEM(pc->i + IDX(loc))], REG_SIZE);
		pc->i += 5;
	}
	else
		pc->i++;
}

void	op_st(t_cyc *info, t_pc *pc)//imp
{
	uint16_t		loc;

	ft_printf("-----------------st---------------------");
	if (info->mem[0][MEM(pc->i + 1)] == 0x50)
	{
		pc->r[info->mem[0][MEM(pc->i + 3)]] = pc->r[info->mem[0][MEM(pc->i + 2)]];
		pc->i += 4;
	}
	else if (info->mem[0][MEM(pc->i + 1)] == 0x70)
	{
		ft_memrcpy(&loc, &info->mem[0][MEM(pc->i + 3)], IND_SIZE);
		ft_memrcpy(&info->mem[0][MEM(pc->i + IDX(loc))], &pc->r[info->mem[0][MEM(pc->i + 2)]], REG_SIZE);
		ft_memset(&info->ref[0][MEM(pc->i + IDX(loc))], pc->r[0], REG_SIZE);
		pc->i += 5;
	}
	else
		pc->i++;
}

void	op_add(t_cyc *info, t_pc *pc)
{
	if (info->mem[0][MEM(pc->i + 1)] == 0x54)
	{
		pc->r[info->mem[0][MEM(pc->i + 4)]] = pc->r[info->mem[0][MEM(pc->i + 2)]]
					+ pc->r[info->mem[0][MEM(pc->i + 3)]];
		pc->i += 5;
	}
	else
		pc->i++;
}

void	op_sub(t_cyc *info, t_pc *pc)
{
	if (info->mem[0][MEM(pc->i + 1)] == 0x54)
	{
		pc->r[info->mem[0][MEM(pc->i + 4)]] = pc->r[info->mem[0][MEM(pc->i + 2)]]
					- pc->r[info->mem[0][MEM(pc->i + 3)]];
		pc->i += 5;
	}
	else
		pc->i++;
}

void	op_and(t_cyc *info, t_pc *pc)//imp
{
	uint32_t	d1;
	uint32_t	d2;
	uint16_t	loc;

	d1 = 0;
	d2 = 0;
	if ((info->mem[0][MEM(pc->i + 1)] >> 6) == REG_CODE)
		ft_memrcpy(&d1, &pc->r[info->mem[0][MEM(pc->i + 2)]], REG_SIZE);
	else if ((info->mem[0][MEM(pc->i + 1)] >> 6) == IND_CODE)
	{
		ft_memrcpy(&loc, &info->mem[0][MEM(pc->i + 2)], IND_SIZE);
		ft_memrcpy(&d1, &info->mem[0][MEM(pc->i + IDX(loc))], REG_SIZE);
	}
	else if ((info->mem[0][MEM(pc->i + 1)] >> 6) == DIR_CODE)
		ft_memrcpy(&d1, &info->mem[0][MEM(pc->i + 2)], DIR_SIZE);
	if (((info->mem[0][MEM(pc->i + 1)] >> 4) & 0xff) == REG_CODE)
		ft_memrcpy(&d2, &pc->r[info->mem[0][MEM(pc->i + 2)]], REG_SIZE);
	else if (((info->mem[0][MEM(pc->i + 1)] >> 4) & 0xff) == IND_CODE)
	{
		ft_memrcpy(&loc, &info->mem[0][MEM(pc->i + 2)], IND_SIZE);
		ft_memrcpy(&d2, &info->mem[0][MEM(pc->i + IDX(loc))], REG_SIZE);
	}
	else if (((info->mem[0][MEM(pc->i + 1)] >> 4) & 0xff) == DIR_CODE)
		ft_memrcpy(&d2, &info->mem[0][MEM(pc->i + 2)], DIR_SIZE);
	loc = acb_len(info->mem[0][MEM(pc->i + 1)]);
	ft_printf("-----------and----loc:%d---------------", loc);
	pc->r[info->mem[0][MEM(pc->i + loc - 1)]] = d1 & d2;
	if (!(d1 & d2))
		pc->carry = 1;
	ft_printf("carry:%d---------\n", pc->carry);
	pc->i += loc;
}

void	op_or(t_cyc *info, t_pc *pc)
{
	(void)info;
	pc->carry = 1;
	//copy op_and when confirmed working
}

void	op_xor(t_cyc *info, t_pc *pc)
{
	(void)info;
	pc->carry = 1;
	//copy op_and when confirmed working
}

void	op_zjmp(t_cyc *info, t_pc *pc)//imp
{
	int16_t addr;

	if (pc->carry)
	{
		ft_memrcpy(&addr, &info->mem[0][MEM(pc->i + 1)], IND_SIZE);
		ft_printf("------------zjmp---carry:1------jump:%.4x");
		pc->i = MEM(pc->i + IDX(addr));
	}
	else
		pc->i += 3;
}

void	op_ldi(t_cyc *info, t_pc *pc)
{
	(void)info;
	(void)pc;
}

void	op_sti(t_cyc *info, t_pc *pc)
{
	(void)info;
	(void)pc;
}

void	op_fork(t_cyc *info, t_pc *pc)
{
	(void)info;
	(void)pc;
}

void	op_lld(t_cyc *info, t_pc *pc)
{
	(void)info;
	(void)pc;
}

void	op_lldi(t_cyc *info, t_pc *pc)
{
	(void)info;
	(void)pc;
}

void	op_lfork(t_cyc *info, t_pc *pc)
{
	(void)info;
	(void)pc;
	//same as fork but no idx_mod
}

void	op_aff(t_cyc *info, t_pc *pc)
{
	uint32_t	chr;

	if (info->mem[0][MEM(pc->i + 1)] == 0x40)
	{
		chr = pc->r[info->mem[0][MEM(pc->i + 2)]];
		chr = END32(chr);
		if (chr <= 0x7F)
			write(1, &chr, 1);
		else if (chr <= 0x7FF)
			write(1, &chr, 2);
		else if (chr <= 0xFFFF)
			write(1, &chr, 3);
		else if (chr <= 0x10FFFF)
			write(1, &chr, 4);
		pc->i += 3;
	}
	else
		pc->i++;
}

void	wait_mod(uint16_t *wait, uint8_t op)
{
	if (op == 16)
		*wait = 2;
	else if (op == 2 || op == 3)
		*wait = 5;
	else if (op >= 6 && op <= 8)
		*wait = 6;
	else if (op == 1 || op == 4 || op == 5 || op == 13)
		*wait = 10;
	else if (op == 9)
		*wait = 20;
	else if (op == 10 || op == 11)
		*wait = 25;
	else if (op == 14)
		*wait = 50;
	else if (op == 12)
		*wait = 800;
	else if (op == 15)
		*wait = 1000;
	else
		*wait = -1;
}

void	pc_scan_op(t_cyc *info, t_pc *pc)
{
	ft_printf("at mem[%d] (%.2x) for %d more cycles\n", pc->i, info->mem[0][pc->i], pc->wait);
	if (info->mem[0][pc->i] < 1 || info->mem[0][pc->i] > 16)
		pc->i++;
	else if (!pc->wait)
	{
		ft_printf("Doing function, pc->i = %d\n", pc->i);
		g_op_fn[info->mem[0][pc->i]](info, pc);
		wait_mod(&pc->wait, info->mem[0][pc->i]);
		ft_printf("pc->i updated to %d and given wait time of %d\n", pc->i, pc->wait);
	}
	else if (pc->wait > 0)
		pc->wait--;
	else
		wait_mod(&pc->wait, info->mem[0][pc->i]);
	if (pc->next)
		pc_scan_op(info, pc->next);
}
/*
** pc at op first time	| assign wait
** pc waiting at op		| decrement wait
** pc executes op		| !wait then set wait
*/
