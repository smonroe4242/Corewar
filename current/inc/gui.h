/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 03:22:13 by jochang           #+#    #+#             */
/*   Updated: 2019/01/05 16:33:15 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

//Test Includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Final Includes
#include <curses.h>
#include "corewar.h"
//NEW
# define MEMWIN_HEIGHT 68
# define MEMWIN_WIDTH 197
# define INFOWIN_WIDTH 58
# define COLOR_GRAY 242
# define BORDER_COLOR COLOR_PAIR(20)
# define GRAY_TEXT COLOR_PAIR(21)
# define WINDOWS_OFFSET_LEFT 3
# define PRINT_INFO(a) mvwprintw(ncrs.infowin, ncrs.init_y, ncrs.init_x, a)
# define PRINT_INFO_N(a, b) mvwprintw(ncrs.infowin, ncrs.init_y, ncrs.init_x, a, b)
# define INIT_BRACKETS "[                                                  ]"
# define INIT_DASHES "--------------------------------------------------"
# define INIT_PRINT_LINE mvwprintw(ncrs.infowin, ncrs.init_y, ncrs.init_x + 1, INIT_DASHES);
# define INIT_BOLD wattron(ncrs.infowin, A_BOLD);
# define INIT_NOBOLD wattroff(ncrs.infowin, A_BOLD);
# define INIT_LINE INIT_NOBOLD INIT_PRINT_LINE INIT_BOLD

typedef struct	s_ncrs
{
	WINDOW		*memwin;
	WINDOW		*infowin;
	uint8_t		paused;
	uint8_t		init_x;
	uint8_t		init_y;
}				t_ncrs;
/*
typedef struct s_cyc	t_cyc;
typedef struct s_head	t_head;
typedef struct s_flag	t_flag;
*/
t_ncrs			init_gui(t_cyc *cyc, t_head *head, t_flag flag);
void			update_memblock(t_ncrs ncrs, t_cyc *cyc);
void			init_infoblock(t_ncrs ncrs, t_cyc *cyc, t_head *head, t_flag flag);

#endif
