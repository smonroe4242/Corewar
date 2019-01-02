/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 22:10:21 by smonroe           #+#    #+#             */
/*   Updated: 2019/01/01 22:29:15 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"
/*
void	ft_dump_info(t_cyc *info, int fd)
{
	char	*out;

	out = "\nCycle ";
	out = ft_strappfr(out, ft_itoa(info->cycle));
	out = ft_strjoinfr(out, " Last ");
	out = ft_strmrg(out, ft_itoa(info->last));
	out = ft_strjoinfr(out, " Start\n");
	write(fd, out, ft_strlen(out));
	free(out);
}

void	ft_dump_mem(t_cyc *info, int fd)
{
	register int	 i;
	register int	 j;
	register char	 buf[(MEM_SIZE << 2) + MEM_SIZE + 1];
	register char	 *hex;
	register uint8_t byte;

	j = 0;
	i = 0;
	hex = "0123456789abcdef";
	while (j < MEM_SIZE)
	{
		byte = info->mem[0][j++];
		buf[i++] = hex[byte >> 4];
		buf[i++] = hex[byte & 15];
		buf[i++] = (j % 64) ? ' ' : '\n';
	}
	j = 0;
	while (j < MEM_SIZE)
	{
		buf[i++] = (j % 64) ? ' ' : '\n';
		buf[i++] = info->ref[0][j++] + '0';
	}
	ft_dump_info(info, fd);
	write(fd, buf, i);
}
*/

void	ncurse(t_cyc *info, t_pc *pc, t_head ch[MAX_PLAYERS], t_flag flag)
{
	register uint8_t	x;
	register uint8_t	y;
	register uint16_t	i;
	register uint8_t	tmp;
	t_pc				*head;

	(void)pc;
	initscr();
	noecho();
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
		if (((head->i / 64) + 3) < 63)
			mvprintw((head->i / 64) + 3, (head->i % 64) * 3, "%.2x", info->mem[0][head->i]);
		attroff(COLOR_PAIR(head->r[0] + 4));
		head = head->next;
	}
	refresh();
	if (flag.w)
		usleep(flag.w); // Microsecond cycle interval
	if (flag.d)
		getch();
}

void	display(t_cyc *info, t_head champ[MAX_PLAYERS], t_flag flag)
{
	if (flag.p)
		;//ft_dump_mem(info, flag.fd);
	if (flag.n)
		ncurse(info, g_head, champ, flag);//ncurses function
}
