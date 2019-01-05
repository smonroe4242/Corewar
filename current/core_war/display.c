/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 22:10:21 by smonroe           #+#    #+#             */
/*   Updated: 2019/01/04 23:18:00 by smonroe          ###   ########.fr       */
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
	(void)pc;
	(void)ch;
	mvprintw(0, 0, "Cycle: %4d\tLast Live: %3d\n", info->cycle, info->last);
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
