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

void    p_flag_init(void)
{
    /*Initialize pipe to python instance and send header info*/
    
}

void    ft_hex_print(uint8_t x)
{
    char    s[3];
    char    *chars;

    chars = "0123456789abcdef";
    s[0] = chars[x >> 4];
    s[1] = chars[x & 15];
    s[2] = ' ';
    write(1, &s, 3); 
}

void    ft_dump_mem(t_cyc *info)
{
    int     i;

    ft_printf("Cycle%d\nLast%d\n", info->cycle, info->last);
    i = -1;
    ft_putstr("StartMem");
    while (++i < MEM_SIZE)
    {
        if (!(i % 64))
            ft_putchar('\n');
        ft_hex_print(info->mem[0][i]);
    }
    ft_putstr("\nEndMem\nStartRef");
    i = -1;
    while (++i < MEM_SIZE)
    {
        if (!(i % 64))
            ft_putchar('\n');
        ft_putchar(info->ref[0][i] + '0');
        ft_putchar(' ');
    }
    ft_putstr("\nEndRef\n");
}

void  		 display(t_cyc *info, t_head champ[MAX_PLAYERS], t_flg flag)
{
    (void)champ;
    if (flag.print == PRINT)
        ft_dump_mem(info);
    else if (flag.print == NCURSES)
        ncurse(info, g_head, champ);//ncurses function
}
