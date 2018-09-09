/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 00:22:39 by smonroe           #+#    #+#             */
/*   Updated: 2018/09/08 00:53:09 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_cyc	t_cyc_init(uint8_t **mem, uint8_t **ref, t_pc *pc)
{
	t_cyc	info;

	info.cycle = 0;
	info.last = 0;
	ft_bzero(info.pcount, sizeof(info.pcount));
	info.kill = 0;
	info.mem = mem;
	info.ref = ref;
	info.pc = pc;
	return (info);
}

int		init_env(t_cyc info, t_head champ[MAX_PLAYERS], t_flg flag)
{
	int		die;
	int		step;

	die = CYCLE_TO_DIE;
	while (die > 0)
	{
		step = 0;
		if (!info.pc)
			break ;
		while (step++ < die)
		{
			//ft_printf("%d, %d, %d\n", die, step, info.cycle);
			pc_scan_op(&info, info.pc);
			display(&info, champ, flag);
			info.cycle++;
		}
		pc_scan_rem(info.pc);
		if (!info.pc->alive)
			info.pc = pc_rem_head(info.pc);
		if (info.kill)
			die -= CYCLE_DELTA;
	}
	if (info.pc)
		pc_free(info.pc);
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
	//ft_printf("Printing mem in init_proc();\n");
	//ft_print_mem(mem[0], MEM_SIZE);
	ft_printf("\tWe have %d champions in the arena.\n", n);
	ft_printf("\tcreating link for champion 1 now\n");
	pc = pc_new(champ[0].pnum, 0, mem[0][0]);
	i = 0;
	if (n > 1)
		while (++i < n)
		{
			ft_printf("\tappending link for champion %d now\n", i);
			ft_printf("\t\t%d : ", champ[i].pnum);
			ft_printf("mem[%d] = ", MEM_SIZE / n * i);
			ft_printf("%d---\n", mem[0][MEM_SIZE / n * i]);
			pc_app(pc, pc_new(champ[i].pnum, MEM_SIZE / n * i, mem[0][MEM_SIZE / n * i]));
		}
	ft_printf("\tchampions ready!\n");
	info = t_cyc_init(mem, ref, pc);
	if (!(winner = init_env(info, champ, flag)))
		ft_printf("There has been a tie!\n", champ[0].pnum, champ[0].name);
	else
	{
		i = 0;
		while (champ[i].pnum != winner)
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

	mem = ft_memalloc(MEM_SIZE);
	ref	= ft_memalloc(MEM_SIZE);
	n = 0;
	while (champ[n].pnum && n < MAX_PLAYERS)
		n++;
	ft_printf("\t%d Champions have entered the Arena!\n", n);
	if (!n)
		exit_msg(n, NULL);
	i = -1;
	while (++i < n)
	{
		ft_memcpy(&mem[MEM_SIZE / n * i], champ[i].code, champ[i].size);
		ft_memset(&ref[MEM_SIZE / n * i], -champ[i].pnum, champ[i].size);
	}
	//ft_print_mem(mem, MEM_SIZE);
	init_proc(&mem, &ref, champ, flag);
	ft_memset(mem, 0, MEM_SIZE);
	free(mem);
	ft_memset(ref, 0, MEM_SIZE);
	free(ref);
}
