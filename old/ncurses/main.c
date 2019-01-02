/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 20:05:57 by smonroe           #+#    #+#             */
/*   Updated: 2018/09/06 23:54:52 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include "../libft/libft.h"
#include <fcntl.h>
#define X 0
#define Y 0

int	main(void)
{
	int 	ch;
	int		row;
	int		col;
	int		fd;
	char	*line;

	col = 0;
	row = 0;
	initscr();
	noecho();
	fd = open("enter", O_RDONLY);
	getmaxyx(stdscr, row, col);
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	ch = -18;
	while (get_next_line(fd, &line))
	{
		mvprintw(row / 2 + ch++, (col - ft_strlen(line)) / 2, "%s", line);
		free(line);
	}
	refresh();
	ch = getch();
	attroff(COLOR_PAIR(0));
	close(fd);
	endwin();
	return (0);
}


















