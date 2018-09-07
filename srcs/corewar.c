/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <smonroe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 03:51:26 by smonroe           #+#    #+#             */
/*   Updated: 2018/09/06 19:53:56 by smonroe          ###   ########.fr       */
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

void    ft_dump_mem(uint8_t *mem, uint8_t *ref)
{
    char    *chars;
    int     i;
    uint8_t tmp;

    chars = "0123456789abcdef";
    system("sleep 0.2; clear");
    write(1, "\e[0m", 4);
    i = -1;
    tmp = 0;
    while (++i < MEM_SIZE)
    {
        if (ref[i] != tmp)
            color_dt(ref[i]);
        tmp = ref[i];
        if(!(i % 64))
            ft_putchar('\n');
        ft_putchar(chars[mem[i] >> 4]);
        ft_putchar(chars[mem[i] & 0x0f]);
        ft_putchar(' ');
    }
    write(1, "\e[0m\n", 5);
}

void	exit_msg(int n, char *s)
{
	if (!n)
		ft_printf("Usage: its the goddamn corewar executable\n");
	else if (n == 1)
		ft_printf("%s is bust dude better luck next time\n", s);
	else if (n == 2)
		ft_printf("Header got f u c k e d in %s man\n", s);
	exit(0);
}

uint32_t		endian_swap32(uint32_t x)
{
	return ((x >> 24) | (x << 24) | ((x >> 8 ) & 0xff00) | ((x << 8) & 0xff0000));
}

t_head	file_stuff(char *cor)
{
	t_head	file;
	int		fd;
	int		ret;
	char	buf[COMMENT_LENGTH];
	static int	pn;

	if ((fd = open(cor, O_RDONLY)) == 1 || (read(fd, buf, 0)))
		exit_msg(1, cor);
	ret = read(fd, buf, 4);
	ft_memcpy(&ret, &buf, 4);
	ret = endian_swap32(ret);
	if (ret != COREWAR_EXEC_MAGIC)
		exit_msg(2, cor);
	ret = read(fd, buf, PROG_NAME_LENGTH);
	ft_memcpy(file.name, buf, PROG_NAME_LENGTH);
	ret = read(fd, buf, 8);
	ft_memcpy(&file.size, &buf[4], 4);
	file.size = endian_swap32(file.size);
	ret = read(fd, buf, COMMENT_LENGTH - 4);
	ft_memcpy(file.comment, buf, COMMENT_LENGTH - 4);
	ret = read(fd, buf, file.size);
	ft_memcpy(file.code, buf, file.size);
	file.pnum = --pn;
	return (file);
}

int		main(int ac, char **av)
{
	t_head	file[MAX_PLAYERS];
	int		i;

	if (ac == 1)
		exit_msg(0, NULL);
	ft_bzero(&file, sizeof(t_head) * MAX_PLAYERS);
	i = 0;
	while (++i < ac)	
		file[i - 1] = file_stuff(av[i]);
	i = 0;
	while (i < MAX_PLAYERS && file[i].name[0])
		i++;
	init_vm(file, i);
//	pause();
	return (0);
}
