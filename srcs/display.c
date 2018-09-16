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

}

void    ft_dump_mem(t_cyc *info)
{
    int     i;
    char    s[2];
    char    *chars;
    t_pc    *ptr;

    chars = "0123456789abcdef";
    ft_printf("Cycle%d\nLast%d\n", info->cycle, info->last);
    i = -1;
    ft_putstr("StartMem");
    while (++i < MEM_SIZE)
    {
        if (!(i % 64))
            ft_putchar('\n');
        s[0] = chars[x >> 4];
        s[1] = chars[x & 15];
        write(1, &s, 2);
    }
    ft_putstr("\nEndMem\nStartRef");
    i = -1;
    while (++i < MEM_SIZE)
    {
        if (!(i % 64))
            ft_putchar('\n');
        ft_putchar(info->ref[0][i] + '0');
    }
    ft_putstr("\nEndRef\nStartPc\n");
    ptr = g_head;
    i = 0;
    while (ptr)
    {
        ft_printf("%d:%d\n", ptr->r[0], ptr->i);
        ptr = ptr->next;
        i++;
    }
    ft_printf("Count:%d\n", i);
    ft_putstr("EndPc\n");
}

void  		 display(t_cyc *info, t_head champ[MAX_PLAYERS], t_flg flag)
{
    (void)champ;
    if (flag.print == 'p')
        ft_dump_mem(info);
    else if (flag.print == 'n')
        ncurse(info, g_head, champ, flag.delay);//ncurses function
}
