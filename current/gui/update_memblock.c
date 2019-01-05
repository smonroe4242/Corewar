/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_memblock.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 03:28:10 by jochang           #+#    #+#             */
/*   Updated: 2019/01/05 04:37:17 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void		select_color(t_ncrs ncrs, t_mem mem)
{
	if (mem.pnum)
	{
		mem.pnum = -mem.pnum;
		if (mem.active)
		{
			if (mem.active == 1)
				wattron(ncrs.memwin, A_STANDOUT);
			if (mem.active == 2)
			{
				mem.pnum += 4;
				wattron(ncrs.memwin, A_BOLD);
				wattron(ncrs.memwin, A_STANDOUT);
			}
		}
		else if (mem.timer)
			wattron(ncrs.memwin, A_BOLD);
		wattron(ncrs.memwin, COLOR_PAIR(mem.pnum));
	}
	else
		wattron(ncrs.memwin, A_BOLD);
}

void		deselect_color(t_ncrs ncrs)
{
	wattrset(ncrs.memwin, GRAY_TEXT);
}

void		update_memblock(t_ncrs ncrs, t_cyc cyc)
{
	int		i;
	int		x;
	int		y;

	i = -1;
	y = 1;
	//default color on
	wattron(ncrs.memwin, GRAY_TEXT);
	while (++i < MEM_SIZE)
	{
		x = (i & 63) ? x + 3 : WINDOWS_OFFSET_LEFT;
		y += (i & 63) ? 0 : 1;
		//initialize color set based on pnum, timer, and existing process cursor
		select_color(ncrs, cyc.mem[0][i]);
		mvwprintw(ncrs.memwin, y, x, "%.2x", cyc.mem[0][i].byte);
		//uninitialize color if it was set
		deselect_color(ncrs);
		//decrement timer if it is > 0, maybe bit shift + mask?
	}
	//default color off
	wattroff(ncrs.memwin, GRAY_TEXT);
	wrefresh(ncrs.memwin);
}
