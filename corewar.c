/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <smonroe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 03:51:26 by smonroe           #+#    #+#             */
/*   Updated: 2018/09/05 05:44:21 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "corewar.h"

void	file_stuff(char *cor)
{
	t_head	file;
	int		fd;
	int		ret;
	char	buf[COMMENT_LENGTH];

	if ((fd = open(cor, O_RDONLY)) == 1 || (read(fd,buf,0)))
		exit_msg(1, cor);
	ft_memcpy(&ret, buf, 4);
	if (END32(ret) != COREWAR_EXEC_MAGIC)
		exit_msg(1, cor);
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
	return (file);
}

int		main(int ac, char **av)
{
	if (argc == 1)
		exit_msg(0, NULL);
	file_stuff(argv[1]);
	return (0);
}
