/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 02:50:12 by smonroe           #+#    #+#             */
/*   Updated: 2018/09/09 02:50:14 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void    color_dt(uint8_t n)
{
    if (n == 1)
        write(1, "\e[34m", 5);
    else if (n == 2)
        write(1, "\e[32m", 5);
    else if (n == 3)
        write(1, "\e[31m", 5);
    else if (n == 4)
        write(1, "\e[36m", 5);
    else
        write(1, "\e[0m", 4);
}

void    ft_dump_mem(t_cyc *info)
{
    char    *chars;
    int     i;
    uint8_t tmp;

    chars = "0123456789abcdef";
    system("clear");
    ft_printf("Cycle: %.5d\t\tLast Live Call: %d\n", info->cycle, info->last);
    write(1, "\e[0m", 4);
    i = -1;
    tmp = 0;
    while (++i < MEM_SIZE)
    {
        if (info->ref[0][i] != tmp)
            color_dt(info->ref[0][i]);
        tmp = info->ref[0][i];
        if(!(i % 64))
            ft_putchar('\n');
        ft_putchar(chars[info->mem[0][i] >> 4]);
        ft_putchar(chars[info->mem[0][i] & 0x0f]);
        ft_putchar(' ');
    }
    write(1, "\e[0m\n", 5);
}
void  		 display(t_cyc *info, t_head champ[MAX_PLAYERS], t_flg flag)
{
    (void)champ;
    if (flag.print == PRINT)
        ft_dump_mem(info);
    else if (flag.print == MLX)
        ;//mlx function
    else if (flag.print == NCURSES)
        ;//ncurses function
}
