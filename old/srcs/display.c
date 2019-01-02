/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 02:50:12 by smonroe           #+#    #+#             */
/*   Updated: 2019/01/01 22:24:56 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void    ft_dump_info(t_cyc *info, int fd)
{
    char    *out;

    out = "\nCycle ";
    out = ft_strappfr(out, ft_itoa(info->cycle));
    out = ft_strjoinfr(out, " Last ");
    out = ft_strmrg(out, ft_itoa(info->last));
    out = ft_strjoinfr(out, " Start\n");
    write(fd, out, ft_strlen(out));
    free(out);
}

void    ft_dump_mem(t_cyc *info, int fd)
{
    register int     i;
    register int     j;
    register char    buf[(MEM_SIZE << 2) + MEM_SIZE + 1];
    register char    *hex;
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

void    display(t_cyc *info, t_head champ[MAX_PLAYERS], t_flg flag)
{
    (void)champ;
    if (flag.print == 'p')
        ft_dump_mem(info, flag.fd);
    else if (flag.print == 'n')
        ncurse(info, g_head, champ, flag);//ncurses function
}
