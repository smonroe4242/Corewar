/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <smonroe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 03:51:26 by smonroe           #+#    #+#             */
/*   Updated: 2018/09/05 17:59:51 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
	ft_printf("%#x\n", ret);
	if (ret != COREWAR_EXEC_MAGIC)
		exit_msg(2, cor);
	ret = read(fd, buf, PROG_NAME_LENGTH);
	ft_memcpy(file.name, buf, PROG_NAME_LENGTH);
	ret = read(fd, buf, 4);
	ft_memcpy(&file.size, buf, 4);
	file.size = END32(file.size);
	ret = read(fd, buf, COMMENT_LENGTH);
	ft_memcpy(file.comment, buf, COMMENT_LENGTH);
	if ((ret = read(fd, buf, file.size)) != file.size)
		exit_msg(2, cor);
	ft_memcpy(file.code, buf, file.size);
	if ((ret = read(fd, buf, 1)))
		exit_msg(2, cor);
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
		file[i - 1] = file_stuff(av[1]);
	i = -1;
	while (file[++i].pnum)
		ft_printf("File: %s\nPlayer Number: %d\n Name: %s\nComment: %s\nSize: %d\n", av[i + 1], file[i].pnum, file[i].name, file[i].comment, file[i].size);
	return (0);
}
