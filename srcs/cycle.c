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

void	ft_memfree(uint8_t **m, size_t n)
{
	if (m && *m)
	{
		ft_memset(*m, 0, n);
		free(*m);
		*m = NULL;
	}
}

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

/*uint8_t		ACB_ARG(uint8_t tb)
{
	if (tb == 3)
		return (4);
	return (tb);
}*/

uint16_t	acb_len(uint8_t acb)
{
	//TEA
	uint16_t	len;

	len = 2;
	len += (((acb >> 6) == 3) ? 4 : (acb >> 6));
	len += ((((acb >> 4) & 3) == 3) ? 4 : ((acb >> 4) & 3));
	len += ((((acb >> 2) & 3) == 3) ? 4 : ((acb >> 2) & 3));
	//TIME("acb_len\t")
	return (len);
}

void	op_live(t_cyc *info, t_pc *pc)//imp
{
	TEA
	//ft_printf("%d-[ALIVE]\n", pc->r[0]);
	ft_memrcpy(&info->last, &info->mem[0][MEM(pc->i + 1)], REG_SIZE);
	if (-info->last - 1  < MAX_PLAYERS)
		info->pcount[-info->last - 1]++;
	pc->alive++;
	pc->i += 5;
	TIME("op_live\t")
}

void	op_ld(t_cyc *info, t_pc *pc)
{
	TEA
	uint8_t		reg;
	uint16_t	loc;

	//ft_printf("%d--[LD]\n", pc->r[0]);
	if (info->mem[0][MEM(pc->i + 1)] == 0x90)
	{
		//ft_printf("ACB:90\n");
		reg = info->mem[0][MEM(pc->i + 6)];
		ft_memrcpy(&pc->r[reg], &info->mem[0][MEM(pc->i + 2)], REG_SIZE);
		pc->i += 7;
	}
	else if (info->mem[0][MEM(pc->i + 1)] == 0xd0)
	{
		//ft_printf("ACB:d0\n");
		reg = info->mem[0][MEM(pc->i + 4)];
		ft_memrcpy(&loc, &info->mem[0][MEM(pc->i + 2)], IND_SIZE);
		ft_memrcpy(&pc->r[reg], &info->mem[0][MEM(pc->i + IDX(loc))], REG_SIZE);
		pc->i += 5;
	}
	else
		pc->i++;
	TIME("op_ld\t")
}

void	op_st(t_cyc *info, t_pc *pc)//imp
{
	TEA
	int16_t		loc;

	//ft_printf("%d---[ST]\n", pc->r[0]);
	if (info->mem[0][MEM(pc->i + 1)] == 0x50)
	{
		pc->r[info->mem[0][MEM(pc->i + 3)]] = pc->r[info->mem[0][MEM(pc->i + 2)]];
		pc->i += 4;
	}
	else if (info->mem[0][MEM(pc->i + 1)] == 0x70)
	{
		ft_memrcpy(&loc, &info->mem[0][MEM(pc->i + 3)], IND_SIZE);
		//ft_printf("ACB:70\tloc:%d\n", loc);
		ft_memrcpy(&info->mem[0][MEM(pc->i + IDX(loc))], &pc->r[info->mem[0][MEM(pc->i + 2)]], REG_SIZE);
		//ft_printf("|%.2x|", info->mem[0][MEM(pc->i + IDX(loc) + 1)]);
		ft_memset(&info->ref[0][MEM(pc->i + IDX(loc))], pc->r[0], REG_SIZE);
		//ft_printf("%.2x|\n", info->mem[0][MEM(pc->i + IDX(loc) + 1)]);
		pc->i += 5;
	}
	else
		pc->i++;
	TIME("op_sti\t")
}

void	op_add(t_cyc *info, t_pc *pc)
{
	TEA
	//ft_printf("%d-----[ADD]\n", pc->r[0]);
	if (info->mem[0][MEM(pc->i + 1)] == 0x54)
	{
		//ft_printf("arg1[%d] + arg2[%d]", pc->r[info->mem[0][MEM(pc->i + 2)]], pc->r[info->mem[0][MEM(pc->i + 3)]]);
		pc->r[info->mem[0][MEM(pc->i + 4)]] = pc->r[info->mem[0][MEM(pc->i + 2)]]
					+ pc->r[info->mem[0][MEM(pc->i + 3)]];
		//ft_printf(" = arg3[%d]\n", pc->r[info->mem[0][MEM(pc->i + 4)]]);
		pc->i += 5;
	}
	else
		pc->i++;
	TIME("op_add\t")
}

void	op_sub(t_cyc *info, t_pc *pc)
{
	TEA
	//ft_printf("%d-----[SUB]\n", pc->r[0]);
	if (info->mem[0][MEM(pc->i + 1)] == 0x54)
	{
		pc->r[info->mem[0][MEM(pc->i + 4)]] = pc->r[info->mem[0][MEM(pc->i + 3)]]
					- pc->r[info->mem[0][MEM(pc->i + 2)]];
		pc->i += 5;
	}
	else
		pc->i++;
	TIME("op_sub\t")
}

void	op_and(t_cyc *info, t_pc *pc)//imp
{
	TEA
	uint32_t	d1;
	uint32_t	d2;
	uint16_t	loc;
	uint8_t		acb;
	//ft_printf("%d------[AND]\n", pc->r[0]);
	d1 = 0;
	d2 = 0;
	acb = info->mem[0][MEM(pc->i + 1)];

	if ((acb >> 6) == REG_CODE)
		ft_memrcpy(&d1, &pc->r[info->mem[0][MEM(pc->i + 2)]], REG_SIZE);
	else if ((acb >> 6) == IND_CODE)
	{
		ft_memrcpy(&loc, &info->mem[0][MEM(pc->i + 2)], IND_SIZE);
		ft_memrcpy(&d1, &info->mem[0][MEM(pc->i + IDX(loc))], REG_SIZE);
	}
	else if ((acb >> 6) == DIR_CODE)
		ft_memrcpy(&d1, &info->mem[0][MEM(pc->i + 2)], DIR_SIZE);
	if (((acb >> 4) & 0xff) == REG_CODE)
		ft_memrcpy(&d2, &pc->r[info->mem[0][MEM(pc->i + ACB_ARG((acb & 0x20) >> 4))]], REG_SIZE);
	else if (((acb >> 4) & 0xff) == IND_CODE)
	{
		ft_memrcpy(&loc, &info->mem[0][MEM(pc->i + ACB_ARG((acb & 0x20) >> 4))], IND_SIZE);
		ft_memrcpy(&d2, &info->mem[0][MEM(pc->i + IDX(loc))], REG_SIZE);
	}
	else if (((acb >> 4) & 0xff) == DIR_CODE)
		ft_memrcpy(&d2, &info->mem[0][MEM(pc->i + ACB_ARG((acb & 0x20) >> 4))], DIR_SIZE);
	loc = acb_len(acb);
	pc->r[info->mem[0][MEM(pc->i + loc - 1)]] = d1 & d2;
	//if (!(d1 & d2))
	pc->carry = 1;
	pc->i += loc;
	TIME("op_and\t")
}

void	op_or(t_cyc *info, t_pc *pc)
{
	TEA
	//ft_printf("%d-------[OR]\n", pc->r[0]);
	(void)info;
	pc->carry = 1;
	//copy op_and when confirmed working
	TIME("op_or\t")
}

void	op_xor(t_cyc *info, t_pc *pc)
{
	TEA
	//ft_printf("%d--------[XOR]\n", pc->r[0]);
	(void)info;
	pc->carry = 1;
	//copy op_and when confirmed working
	TIME("op_xor\t")
}

void	op_zjmp(t_cyc *info, t_pc *pc)//imp
{
	TEA
	int16_t addr;

	//ft_printf("%d---------[ZJMP]\n", pc->r[0]);
	if (pc->carry)
	{
		ft_memrcpy(&addr, &info->mem[0][MEM(pc->i + 1)], IND_SIZE);
		pc->i = MEM(pc->i + IDX(addr));
		//ft_printf("Jumped to %d:%.2x\n", pc->i, info->mem[0][pc->i]);
	}
	else
	{
		//ft_printf("whoops lol~~~\n");
		pc->i += 3;
	}
	TIME("op_zjmp\t")
}

void	op_ldi(t_cyc *info, t_pc *pc)
{
	TEA
	int32_t		loc;
	int32_t		tmp;
	uint8_t		acb;
	//ft_printf("%d----------[LDI]\n", pc->r[0]);
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
	//ft_printf("%d\n", loc);
	ft_memrcpy(&pc->r[tmp], &info->mem[0][MEM(pc->i + IDX((int16_t)loc))], REG_SIZE);
	pc->i += acb_len(acb);
	TIME("op_ldi\t")
}

//[01 | 10 | 11][10 | 01][01]

void	op_sti(t_cyc *info, t_pc *pc)
{
	TEA
	int16_t		loc;
	int16_t		tmp;
	uint8_t		acb;
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
	TIME("op_sti\t")
}

void	op_fork(t_cyc *info, t_pc *pc)
{
	TEA
	//ft_printf("%d------------[FORK]\n", pc->r[0]);
//	clock_t t;
	int16_t	addr;
	t_pc	*new;

	ft_memrcpy(&addr, &info->mem[0][MEM(pc->i + 1)], IND_SIZE);
	//ft_printf("ADDR: %#.4x : %d; pc->i: %d\n", addr, addr, pc->i);
	new = pc_new(-pc->r[0], MEM(pc->i + IDX(addr)), info->mem[0][MEM(pc->i + IDX(addr))]);
	ft_memcpy(&new->r[0], &pc->r[0], sizeof(new->r));
	//ft_printf("%d : %.2x\n", MEM(pc->i + IDX(addr)), info->mem[0][MEM(pc->i + IDX(addr))]);
	new->carry = pc->carry;
	new->alive = pc->alive;
//	t = clock();
	pc_app(&pc, new);
//	printf("-----pc_app in fork: %lu\n", clock() - t);
	//ft_printf("addr: %d + %d = %d:%d\n", addr, pc->i, addr + pc->i, new->i);
	pc->i += 3;
	TIME("op_fork\t")
}

void	op_lld(t_cyc *info, t_pc *pc)
{
	TEA
	uint8_t		reg;
	uint16_t	loc;

	//ft_printf("%d-------------[LLD]\n", pc->r[0]);
	if (info->mem[0][MEM(pc->i + 1)] == 0x90)
	{
		//ft_printf("ACB:90\n");
		reg = info->mem[0][MEM(pc->i + 6)];
		ft_memrcpy(&pc->r[reg], &info->mem[0][MEM(pc->i + 2)], REG_SIZE);
		pc->i += 7;
	}
	else if (info->mem[0][MEM(pc->i + 1)] == 0xd0)
	{
		//ft_printf("ACB:d0\n");
		reg = info->mem[0][MEM(pc->i + 4)];
		ft_memrcpy(&loc, &info->mem[0][MEM(pc->i + 2)], IND_SIZE);
		ft_memrcpy(&pc->r[reg], &info->mem[0][MEM(pc->i + loc)], REG_SIZE);
		pc->i += 5;
	}
	else
		pc->i++;
	TIME("op_lld\t")
}

void	op_lldi(t_cyc *info, t_pc *pc)
{
	TEA
	int32_t		loc;
	int32_t		tmp;
	uint8_t		acb;
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
	//ft_printf("%d\n", loc);
	ft_memrcpy(&pc->r[tmp], &info->mem[0][MEM(pc->i + (int16_t)loc)], REG_SIZE);
	pc->i += acb_len(acb);
	TIME("op_lld\t")
}

void	op_lfork(t_cyc *info, t_pc *pc)
{
	TEA
	//ft_printf("%d---------------[LFORK]\n", pc->r[0]);
	int16_t	addr;
	t_pc	*new;

	ft_memrcpy(&addr, &info->mem[0][MEM(pc->i + 1)], IND_SIZE);
	new = pc_new(-pc->r[0], MEM(pc->i + addr), info->mem[0][MEM(pc->i + addr)]);
	ft_memcpy(&new->r, &pc->r, sizeof(new->r));
	new->carry = pc->carry;
	pc_app(&pc, new);
	pc->i += 3;
	TIME("op_lfork\t")
}

void	op_aff(t_cyc *info, t_pc *pc)
{
	TEA
	uint32_t	chr;

	//ft_printf("%d----------------[AFF]", pc->r[0]);
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
	//ft_printf("\n");
	TIME("op_aff\t")
}

void	wait_mod(uint16_t *wait, uint8_t op)
{
//	TEA
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
//	TIME("wait_mod")
}
//
void	pc_scan_op(t_cyc *info, t_pc *pc)
{
//	//ft_printf("at mem[%d] (%.2x) for %d more cycles\n", pc->i, info->mem[0][pc->i], pc->wait);
	//ft_printf("");
	if (info->mem[0][pc->i] < 1 || info->mem[0][pc->i] > 16)
		pc->i++;
	else if (!pc->wait)
	{
//		//ft_printf("Doing function, pc->i = %d\n", pc->i);
		g_op_fn[info->mem[0][pc->i]](info, pc);
		wait_mod(&pc->wait, info->mem[0][pc->i]);
//		pc->wait--;
//		//ft_printf("pc->i updated to %d and given wait time of %d\n", pc->i, pc->wait);
	}
	else if (pc->wait > 0)
		pc->wait--;
	else
	{
		wait_mod(&pc->wait, info->mem[0][pc->i]);
//		pc->wait--;
	}
	if (pc->next)
		pc_scan_op(info, pc->next);
}
/*
** pc at op first time	| assign wait
** pc waiting at op		| decrement wait
** pc executes op		| !wait then set wait
*/
