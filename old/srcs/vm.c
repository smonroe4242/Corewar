/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 00:22:39 by smonroe           #+#    #+#             */
/*   Updated: 2019/01/05 04:35:51 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_op(void)
{
	g_op_fn[0] = NULL;
	g_op_fn[1] = &op_live;
	g_op_fn[2] = &op_ld;
	g_op_fn[3] = &op_st;
	g_op_fn[4] = &op_add;
	g_op_fn[5] = &op_sub;
	g_op_fn[6] = &op_and;
	g_op_fn[7] = &op_or;
	g_op_fn[8] = &op_xor;
	g_op_fn[9] = &op_zjmp;
	g_op_fn[10] = &op_ldi;
	g_op_fn[11] = &op_sti;
	g_op_fn[12] = &op_fork;
	g_op_fn[13] = &op_lld;
	g_op_fn[14] = &op_lldi;
	g_op_fn[15] = &op_lfork;
	g_op_fn[16] = &op_aff;
}

t_cyc	t_cyc_init(uint8_t **mem, uint8_t **ref, t_pc *pc)
{
	t_cyc	info;

	info.cycle = 0;
	info.last = 0;
	ft_bzero(info.pcount, sizeof(info.pcount));
	info.mem = mem;
	info.ref = ref;
	info.pc = pc;
	return (info);
}

int		live_sum(uint32_t p[MAX_PLAYERS])
{
	uint32_t	total;
	uint32_t		i;

	total = 0;
	i = -1;
	while (++i < MAX_PLAYERS)
		total += p[i];
	return (total);
}

int		init_env(t_cyc info, t_head champ[MAX_PLAYERS], t_flg flag)
{
	int32_t	die;
	int32_t	step;
	uint32_t	total;
	uint32_t	kill;
	
	die = CYCLE_TO_DIE;
	kill = 0;
	init_op();
	g_head = info.pc;
	ft_memcpy(&info.mem[0][MEM_SIZE], &info.mem[0][0], REG_SIZE);
	ft_memcpy(&info.ref[0][MEM_SIZE], &info.ref[0][0], REG_SIZE);
	while (die > 0)
	{
		step = 0;
		if (!g_head)
			break ;
		while (step++ < die)
		{
			pc_scan_op(&info, g_head);
			if (flag.print)
				display(&info, champ, flag);
			//ft_printf("\e[35m%d\e[0m\n", info.cycle);
			info.cycle++;
		}
		total = live_sum(info.pcount);
		ft_memset(&info.pcount, 0, sizeof(info.pcount));
		pc_scan_rem(&(g_head));
		if (!g_head)
			break ;
		if (total >= NBR_LIVE)
		{
			kill = 0;
			die -= CYCLE_DELTA;
		}
		else
			kill++;
		if (kill == MAX_CHECKS)
		{
			kill = 0;
			die -= CYCLE_DELTA;
		}
	}
	if (g_head)
		pc_free(g_head);
	if (flag.print == 'n')
		endwin();
	return (info.last);
}

void	init_proc(uint8_t **mem, uint8_t **ref, t_head champ[MAX_PLAYERS], t_flg flag)
{
	t_cyc	info;
	t_pc	*pc;
	int		i;
	int		winner;
	int		n;

	n = 0;
	while (champ[n].pnum && n < MAX_PLAYERS)
		n++;
	pc = pc_new(champ[0].pnum, 0, mem[0][0]);
	i = 0;
	if (n > 1)
		while (++i < n)
			pc_app(&pc, pc_new(champ[i].pnum, MEM_SIZE / n * i, mem[0][MEM_SIZE / n * i]));
	info = t_cyc_init(mem, ref, pc);
	if (!(winner = init_env(info, champ, flag)))
		ft_printf("There has been a tie!\n", champ[0].pnum, champ[0].name);
	else
	{
		i = 0;
		while (champ[i].pnum != winner && i < MAX_PLAYERS)
			i++;
		ft_printf("Player %d (%s) won\n", champ[i].pnum, champ[i].name);
	}
}

void	init_vm(t_head champ[MAX_PLAYERS], t_flg flag)
{
	uint8_t		*mem;
	uint8_t		*ref;
	int			i;
	int			n;

	mem = ft_memalloc(MEM_SIZE + REG_SIZE);
	ref	= ft_memalloc(MEM_SIZE + REG_SIZE);
	n = 0;
	while (champ[n].pnum && n < MAX_PLAYERS)
	{
		ft_printf("Fighter #%d: %s (\"%s\"), at %d bytes long!\n", n
		+ 1, champ[n].name, champ[n].comment, champ[n].size);
		n++;
	}
	if (!n)
		exit_msg(n, NULL);
	i = -1;
	while (++i < n)
	{
		ft_memcpy(&mem[MEM_SIZE / n * i], champ[i].code, champ[i].size);
		ft_memset(&ref[MEM_SIZE / n * i], -champ[i].pnum, champ[i].size);
	}
	init_proc(&mem, &ref, champ, flag);
	ft_memfree(&mem, MEM_SIZE);
	ft_memfree(&ref, MEM_SIZE);
}
