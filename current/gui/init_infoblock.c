/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_infoblock.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 03:28:52 by jochang           #+#    #+#             */
/*   Updated: 2019/01/05 03:28:54 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

static t_ncrs	init_upper(t_ncrs ncrs, t_cyc cyc, t_flag flag)
{
	int		temp_num;

	temp_num = 42;
	PRINT_INFO_N("Cycles/second limit : %d", flag.w);
	ncrs.init_y += 2;
	PRINT_INFO("              Cycle : 0");
	ncrs.init_y += 2;
	PRINT_INFO_N("          Processes : %d", cyc.num_champs);
	ncrs.init_y += 2;
	return (ncrs);
}

static t_ncrs	init_players(t_ncrs ncrs, t_cyc cyc, t_head *head)
{
	int		i;

	i = -1;
	while (++i < cyc.num_champs)
	{
		PRINT_INFO_N("Player %d :", -(i + 1));
		wattron(ncrs.infowin, COLOR_PAIR(i + 1));
		mvwprintw(ncrs.infowin, ncrs.init_y, ncrs.init_x + 12, head[i].name);
		wattroff(ncrs.infowin, COLOR_PAIR(i + 1));
		ncrs.init_y++;
		PRINT_INFO("  Last live               : 0");
		ncrs.init_y++;
		PRINT_INFO("  Lives in current period : 0");
		ncrs.init_y += 2;
	}
	return (ncrs);
}

static t_ncrs	init_breakdown(t_ncrs ncrs)
{
	PRINT_INFO("Live breakdown for current period :");
	ncrs.init_y++;
	wattron(ncrs.infowin, GRAY_TEXT);
	PRINT_INFO(INIT_BRACKETS);
	INIT_LINE;
	wattroff(ncrs.infowin, GRAY_TEXT);
	ncrs.init_y += 2;
	PRINT_INFO("Live breakdown for last period :");
	ncrs.init_y++;
	wattron(ncrs.infowin, GRAY_TEXT);
	PRINT_INFO(INIT_BRACKETS);
	INIT_LINE;
	wattroff(ncrs.infowin, GRAY_TEXT);
	ncrs.init_y += 2;
	return (ncrs);
}

static t_ncrs	init_lower(t_ncrs ncrs)
{
	int		temp_num;

	temp_num = 42;
	PRINT_INFO_N("CYCLE_TO_DIE : %d", temp_num); //passed in
	ncrs.init_y += 2;
	PRINT_INFO_N(" CYCLE_DELTA : %d", CYCLE_DELTA);
	ncrs.init_y += 2;
	PRINT_INFO_N("    NBR_LIVE : %d", NBR_LIVE);
	ncrs.init_y += 2;
	PRINT_INFO_N("  MAX_CHECKS : %d", MAX_CHECKS);
	return (ncrs);
}

//just needs cycle to die: everything else is hard coded and will be changed in update functions
void		init_infoblock(t_ncrs ncrs, t_cyc cyc, t_head *head, t_flag flag)
{
	int		temp_num;

	temp_num = 42;
	ncrs.init_x = WINDOWS_OFFSET_LEFT;
	ncrs.init_y = 2;
	wattron(ncrs.infowin, A_BOLD);
	PRINT_INFO("** PAUSED **");
	ncrs.init_y += 2;
	ncrs = init_upper(ncrs, cyc, flag);
	ncrs = init_players(ncrs, cyc, head);
	ncrs = init_breakdown(ncrs);
	ncrs = init_lower(ncrs);
	wrefresh(ncrs.infowin);
}
