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

void	op_live(t_cyc *info, t_pc *pc)//imp
{
	pc->i++;
	ft_memcpy(&info->last, &info->mem[0][MEM(pc->i)], REG_SIZE);
	info->last = END32((uint8_t)info->last);
	info->pcount[-info->last - 1]++;
	pc->alive++;
	pc->i += REG_SIZE;
	pc->i %= MEM_SIZE;
}

void	op_ld(t_cyc *info, t_pc *pc)
{
	(void)info;
	(void)pc;
	//load REG_SIZE bytes from pc + arg and place in reg
	//check if first arg is ind or dir
	//
}

void	op_st(t_cyc *info, t_pc *pc)//imp
{
	(void)info;
	(void)pc;	
	//store REG_SIZE bytes from reg and write at mem[i + arg]
}

void	op_add(t_cyc *info, t_pc *pc)
{
	pc->r[info->mem[0][MEM(pc->i + 4)]] = pc->r[info->mem[0][MEM(pc->i + 2)]]
				+ pc->r[info->mem[0][MEM(pc->i + 3)]];
	pc->i += 5;
}

void	op_sub(t_cyc *info, t_pc *pc)
{
	pc->r[info->mem[0][MEM(pc->i + 4)]] = pc->r[info->mem[0][MEM(pc->i + 2)]]
				- pc->r[info->mem[0][MEM(pc->i + 3)]];
	pc->i += 5;
}

void	op_and(t_cyc *info, t_pc *pc)//imp
{
	(void)info;
	(void)pc;
}

void	op_or(t_cyc *info, t_pc *pc)
{
	(void)info;
	(void)pc;
}

void	op_xor(t_cyc *info, t_pc *pc)
{
	(void)info;
	(void)pc;
}

void	op_zjmp(t_cyc *info, t_pc *pc)//imp
{
	int16_t addr;

	if (pc->carry)
	{
		pc->i++;
		ft_memcpy(&addr, &info->mem[0][MEM(pc->i)], 2);
		addr = END16(addr);
		pc->i += addr % IDX_MOD;
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
	(void)info;
	(void)pc;	
	//print single reg val to stdout
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
	//ft_printf("at %.2x for %d more cycles\n", info->mem[0][pc->i], pc->wait);
	pc->i %= MEM_SIZE;
	if (info->mem[0][pc->i] < 1 || info->mem[0][pc->i] > 16)
		pc->i++;
	else if (!pc->wait)
	{
		g_op_fn[info->mem[0][pc->i]](info, pc);
		wait_mod(&pc->wait, info->mem[0][pc->i]);
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
