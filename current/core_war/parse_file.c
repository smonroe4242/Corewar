/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 22:23:39 by jochang           #+#    #+#             */
/*   Updated: 2019/01/02 05:09:37 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

t_head	parse_file(char *cor)
{
	t_head		file;
	int			fd;
	int			ret;
	char		buf[COMMENT_LENGTH];
	static int	pn;

	if ((fd = open(cor, O_RDONLY)) == 1 || (read(fd, buf, 0)))
		err_invfile("cw", cor);
	ret = read(fd, buf, 4);
	ft_memrcpy(&ret, buf, 4);
	if (ret != COREWAR_EXEC_MAGIC)
		err_invheader(cor);
	ret = read(fd, buf, PROG_NAME_LENGTH);
	ft_memcpy(file.name, buf, PROG_NAME_LENGTH);
	ret = read(fd, buf, 8);
	ft_memrcpy(&file.size, &buf[4], 4);
	ret = read(fd, buf, COMMENT_LENGTH - 4);
	ft_memcpy(file.comment, buf, COMMENT_LENGTH - 4);
	ret = read(fd, buf, file.size);
	ft_memcpy(file.code, buf, file.size);
	file.pnum = --pn; // why is it --pn?
// emulating player numbers original corewar vm. static starts at 0, -1, -2, -3, -4. -smonroe
	return (file);
// I think COMMENT_LENGTH needs to be fixed in .h and read size logic should get cleaned up. Check var widths in fille format.
}
