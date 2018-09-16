/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <smonroe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 03:51:26 by smonroe           #+#    #+#             */
/*   Updated: 2018/09/07 00:07:51 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_memrcpy(void *dst, void *src, size_t n)
{
	uint8_t		*p;
	uint8_t		*w;

	p = src + n - 1;
	w = dst;
	while (n--)
		*(w++) = *(p--);
}

void	exit_msg(int n, char *s)
{
	if (!n)
	{
		ft_printf("Usage: ./corewar [-p] [-m] [-n] FILE.cor\n-p to enable ");
		ft_printf("printing to stdout\n-m to enable graphic window mode\n-");
		ft_printf("n to enable ncurses mode\n\nThe -p -m and -n flags over");
		ft_printf("ride each other. if multiple have been given, the last ");
		ft_printf("one will be the output mode.\n");
	}
	else if (n == 1)
		ft_printf("Error in file read in for champion file %s\n", s);
	else if (n == 2)
		ft_printf("Header got f u c k e d in %s man\n", s);
	else if (n == 3)
		ft_printf("Error in grabbing flags. Only p, n, and m are available.\n");
	else if (n == 4)
		ft_printf("Failed to malloc in %s\n");
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
	ft_memrcpy(&ret, buf, 4);
	if (ret != COREWAR_EXEC_MAGIC)
		exit_msg(2, cor);
	ret = read(fd, buf, PROG_NAME_LENGTH);
	ft_memcpy(file.name, buf, PROG_NAME_LENGTH);
	ret = read(fd, buf, 8);
	ft_memrcpy(&file.size, &buf[4], 4);
	ret = read(fd, buf, COMMENT_LENGTH - 4);
	ft_memcpy(file.comment, buf, COMMENT_LENGTH - 4);
	ret = read(fd, buf, file.size);
	ft_memcpy(file.code, buf, file.size);
	file.pnum = --pn;
	return (file);
}

t_flg	ft_setopt(int ac, char **av)
{
	t_flg	flag;
	int8_t	opt;

	g_optind = 1;
	flag.print = 0;
	flag.delay = 0;
	while ((opt = ft_getopt(ac, av, "pnw:")) != -1)
	{
		ft_printf("opt:%c, optarg:%s, optind:%d, %s\n", opt, g_optarg, g_optind, av[g_optind]);
		if (opt == '?')
			exit_msg(3, NULL);
		else
		{
			if (opt == 'p' || opt == 'n')
				flag.print = opt;
			else if (opt == 'w')
				flag.delay = ft_atoi(g_optarg);
		}
	}
	flag.delay = (flag.delay != 0) ? 1000000/flag.delay : 0;
	return (flag);
}

int		ft_getopt(int ac, char **av, char *flg)
{
	static int	nextchar;
	int			i;

	g_optind += (&g_optarg == &av[g_optind] ? 1 : 0);
	g_optarg = NULL;
	if (g_optind >= ac || av[g_optind][0] != '-')
		return (-1);
	i = -1;
	nextchar++;
	while (++i < (int)ft_strlen(flg))
	{
		if (av[g_optind][nextchar] == flg[i])
		{
			g_optarg = (flg[i + 1] == ':' ? &av[++g_optind][0] : NULL);
			if (!(av[g_optind][nextchar + 1]))
			{
				g_optind++;
				nextchar = 0;
			}
			return (flg[i]);
		}
	}
	g_optopt = av[g_optind][nextchar];
	return ('?');
}

int		main(int ac, char **av)
{
	t_head	file[MAX_PLAYERS];
	t_flg	flag;
	int		i;

	if (ac == 1)
		exit_msg(0, NULL);
	ft_bzero(&file, sizeof(t_head) * MAX_PLAYERS);
	flag = ft_setopt(ac, av);
	ft_printf("g_optind = %d and ac = %d\n", g_optind, ac);
	if (g_optind >= ac)
		exit_msg(0, NULL);
	ft_printf("Going through files now\n");
	i = 0;
	while (g_optind < ac && i < MAX_PLAYERS)
		file[i++] = file_stuff(av[g_optind++]);
	ft_printf("Success! Initializing vm now.\n");
	init_vm(file, flag);
	return (0);
}
