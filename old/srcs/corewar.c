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

void	usage(void)
{
	ft_printf("\n\nUsage: ./corewar [-p] [-n -w N -d] [champion].cor\n\t-p: P");
	ft_printf("ython Visualizer\n\t-n: Ncurses Visualizer\n\t-w [cycles per s");
	ft_printf("econd]: Set speed of Ncurses visualizer\n\t-d: Set Debug Mode ");
	ft_printf("for Ncurses Visualizer\n\t\tPress key to advance 1 cycle, hold");
	ft_printf(" key to run continously\n-p flag takes no additional arguments");
	ft_printf("\n-p and -n flags override each other such that first flag giv");
	ft_printf("en will be ignored if both are present\n-d and -w will only wo");
	ft_printf("rk if -n flag is present.\n\nCorewar takes 1 - 4 .cor files an");
	ft_printf("d runs them in the Virtual Machine.\nWritten by jochang, jtash");
	ft_printf("ako, and smonroe.\n42 Silicon Valley, September 2018\n\n\n\n\n");
	exit(0);
}

void	exit_msg(int n, char *s)
{
	if (n == 1)
		ft_printf("Error in file read in for champion file %s\n", s);
	else if (n == 2)
		ft_printf("Header got f u c k e d in %s man\n", s);
	else if (n == 3)
		ft_printf("Error in grabbing flags. Only -pnwd are available.\n");
	else if (n == 4)
		ft_printf("Malloc has failed inside %s\n", s);
	exit(0);
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
	flag.debug = 0;
	while ((opt = ft_getopt(ac, av, "pnw:d")) != -1)
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
			else if (opt == 'd')
				flag.debug = 1;
		}
	}
	flag.fd = (flag.print == 'p') ? open(OUT, O_CREAT | O_TRUNC | O_WRONLY) : 1;
	if (flag.fd == -1)
		exit(1);
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
		usage();
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
//	pause();
	return (0);
}
