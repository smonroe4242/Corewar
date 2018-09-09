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

extern const t_fn g_op_fn[] = {NULL, &op_live, &op_ld, &op_st, &op_add,
							&op_sub, &op_and, &op_or, &op_xor, &op_zjmp,
							&op_ldi, &op_sti, &op_fork, &op_lld, &op_lldi,
							&op_lfork, &op_aff}

void	op_live(t_cyc *info, t_pc *pc)
{
	pc->i++;
	ft_memcpy(info->last, info->mem[pc->i], REG_SIZE);
	info->last = END32((uint8_t)info->last);
	info->pcount[-info->last - 1]++;
	pc->alive++;
	pc->i += REG_SIZE;
	pc->i %= MEM_SIZE;
}

void	op_ld(t_cyc *info, t_pc *pc)
{
	//load REG_SIZE bytes from pc + arg and place in reg
}

void	op_st(t_cyc *info, t_pc *pc)
{
	//store REG_SIZE bytes from reg and write at mem[i + arg]
}

void	op_add(t_cyc *info, t_pc *pc)
{
	
}

void	op_sub(t_cyc *info, t_pc *pc)
{
	
}

void	op_and(t_cyc *info, t_pc *pc)
{
	
}

void	op_or(t_cyc *info, t_pc *pc)
{
	
}

void	op_xor(t_cyc *info, t_pc *pc)
{
	
}

void	op_zjmp(t_cyc *info, t_pc *pc)
{
	int16_t addr;

	if (pc->carry)
	{
		pc->i++;
		ft_memrcpy(&addr, info->mem[pc->i], 2);
		pc->i += addr % IDX_MOD;
	}
	else
		pc->i += 3;
}

void	op_ldi(t_cyc *info, t_pc *pc)
{
	
}

void	op_sti(t_cyc *info, t_pc *pc)
{
	
}

void	op_fork(t_cyc *info, t_pc *pc)
{
	
}

void	op_lld(t_cyc *info, t_pc *pc)
{
	
}

void	op_lldi(t_cyc *info, t_pc *pc)
{
	
}

void	op_lfork(t_cyc *info, t_pc *pc)
{
	//same as fork but no idx_mod
}

void	op_aff(t_cyc *info, t_pc *pc)
{
	//print single reg val to stdout
}

void	wait_mod(t_pc *pc, uint8_t op)
{
	if (op == 16)
		pc->wait = 2;
	else if (op == 2 || op == 3)
		pc->wait = 5;
	else if (op >= 6 && op <= 8)
		pc->wait = 6;
	else if (op == 1 || op == 4 || op == 5 || op == 13)
		pc->wait = 10;
	else if (op == 9)
		pc->wait = 20;
	else if (op == 10 || op == 11)
		pc->wait = 25;
	else if (op == 14)
		pc->wait = 50;
	else if (op == 12)
		pc->wait = 800;
	else if (op == 15)
		pc->wait = 1000;
	else
		pc->wait = -1;
}

void	pc_scan_op(t_cyc *info, t_pc *pc)
{
	if (*info->mem[pc->i] < 1 || *info->mem[pc->i] > 16)
		pc->i++;
	else if (!pc->wait)
	{
		g_op_fn[*info->mem[pc->i]];
		wait_mod(pc, *info->mem[pc->i]);
	}
	else if (pc->wait > 0)
		pc->wait--;
	else
		wait_mod(pc, *info->mem[pc->i]);
	if (pc->next)
		pc_scan_op(info, pc->next);
}
/*
** pc at op first time	| assign wait
** pc waiting at op		| decrement wait
** pc executes op		| !wait then set wait
*/
