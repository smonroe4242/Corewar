/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 03:26:48 by jochang           #+#    #+#             */
/*   Updated: 2019/01/05 13:19:16 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

static void		init_colors(t_ncrs ncrs)
{
	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	//1-4 are for basic player colors
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	//4-8 are for white text on color back
	init_pair(5, COLOR_GREEN, COLOR_WHITE);
	init_pair(6, COLOR_BLUE, COLOR_WHITE);
	init_pair(7, COLOR_RED, COLOR_WHITE);
	init_pair(8, COLOR_CYAN, COLOR_WHITE);
	init_pair(20, COLOR_GRAY, COLOR_GRAY);
	init_pair(21, COLOR_GRAY, COLOR_BLACK);
	wattron(ncrs.memwin, A_BOLD);
	wattron(ncrs.infowin, A_BOLD);
}

static void		init_windows(t_ncrs ncrs)
{
	wattron(ncrs.memwin, BORDER_COLOR);
	wattron(ncrs.infowin, BORDER_COLOR);
	wborder(ncrs.memwin, '*', '*', '*', '*', '*', '*', '*', '*');
	wborder(ncrs.infowin, '*', '*', '*', '*', '*', '*', '*', '*');
	wattroff(ncrs.memwin, BORDER_COLOR);
	wattroff(ncrs.infowin, BORDER_COLOR);
}

t_ncrs			init_gui(t_cyc cyc, t_head *head, t_flag flag)
{
	t_ncrs	ncrs;

	initscr();
	noecho();
	curs_set(0);
	use_default_colors();
	ncrs.memwin = newwin(MEMWIN_HEIGHT, MEMWIN_WIDTH, 0, 0);
	ncrs.infowin = newwin(MEMWIN_HEIGHT, INFOWIN_WIDTH, 0, MEMWIN_WIDTH - 1);
	ncrs.paused = 1;
	init_colors(ncrs);
	init_windows(ncrs);
	update_memblock(ncrs, cyc);
	init_infoblock(ncrs, cyc, head, flag);
	return (ncrs);
}
