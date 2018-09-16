/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 20:42:37 by smonroe           #+#    #+#             */
/*   Updated: 2018/09/15 20:42:41 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void    ncurse(t_cyc *info, t_pc *pc, t_head ch[MAX_PLAYERS], t_flg flag)
{
    register uint8_t    x;
    register uint8_t    y;
    register uint16_t   i;
    register uint8_t    tmp;
    t_pc                *head;

    (void)pc;
    initscr();
    noecho();
//    nodelay(stdscr, true);
    curs_set(FALSE);
    start_color();
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_GREEN);
    init_pair(6, COLOR_WHITE, COLOR_BLUE);
    init_pair(7, COLOR_WHITE, COLOR_RED);
    init_pair(8, COLOR_WHITE, COLOR_CYAN);
    tmp = info->ref[0][0];
    attron(COLOR_PAIR(0));
    mvprintw(0, 0, "Cycle: %4d\tLast Live: %3d\n", info->cycle, info->last);
    i = -1;
    while (ch[++i].pnum && i < MAX_PLAYERS)
        mvprintw(1, i << 5, "Player%3d: %8d", ch[i].pnum, info->pcount[i]);
    i = -1;
    y = 2;
    attron(COLOR_PAIR(tmp));
    while (++i <  MEM_SIZE)
    {
        x = (i & 63) ? x + 3 : 0;
        y += (i & 63) ? 0 : 1;
        if (tmp != info->ref[0][i])
        {
            attroff(COLOR_PAIR(tmp));
            tmp = info->ref[0][i];
            attron(COLOR_PAIR(tmp));
        }
        mvprintw(y, x, "%.2x", info->mem[0][i]);
    }
    attroff(COLOR_PAIR(tmp));
    head = g_head;
    while (head)
    {
        attron(COLOR_PAIR(head->r[0] + 4));
        mvprintw((head->i / 64) + 3, (head->i % 64) * 3, "%.2x", info->mem[0][head->i]);
        attroff(COLOR_PAIR(head->r[0] + 4));
        head = head->next;
    }
    refresh();
    if (flag.delay)
        usleep(flag.delay); // Microsecond cycle interval
    if (flag.debug)
        getch();
}
