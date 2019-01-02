/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 00:06:50 by jochang           #+#    #+#             */
/*   Updated: 2019/01/01 19:26:07 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

static t_cyc	init_t_cyc(uint8_t **mem, uint8_t **ref, t_pc *pc)
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

static void	init_proc(uint8_t **mem, uint8_t **ref, t_head champ[MAX_PLAYERS],
				t_flag flag)
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
	while (++i < n)
		pc_app(&pc,
		pc_new(champ[i].pnum, MEM_SIZE / n * i, mem[0][MEM_SIZE / n * i]));
	info = init_t_cyc(mem, ref, pc);
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

void	init_vm(t_head champ[MAX_PLAYERS], t_flag flag)
{
	uint8_t		*mem;
	uint8_t		*ref;
	int			i;
	int			n;

	RETURN_CHECK(!(mem = ft_memalloc(MEM_SIZE + REG_SIZE)));
	RETURN_CHECK(!(ref = ft_memalloc(MEM_SIZE + REG_SIZE)));
	n = 0;
	while (champ[n].pnum && n < MAX_PLAYERS)
	{
		ft_printf("Fighter #%d: %s (\"%s\"), at %d bytes long!\n",
		n + 1, champ[n].name, champ[n].comment, champ[n].size);
		n++;
	}
	if (!n) //when would this ever fail?
		err_nofile("cw", 1);
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
