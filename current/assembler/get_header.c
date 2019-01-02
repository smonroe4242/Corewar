/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 00:36:51 by jochang           #+#    #+#             */
/*   Updated: 2018/09/10 00:36:52 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

//needs to be updated
t_header	get_header(int fd)
{
	t_header	h;
	char		*line;
	char		*dq;
	int			i;

	ft_memset(&h, 0, HEADER_SIZE);
	get_next_line(fd, &line);
	while (line[0] != '.')
		get_next_line(fd, &line);
	dq = ft_strchr(line, '"');
	i = 0;
	while (dq[++i] != '"')
		h.prog_name[i - 1] = dq[i];
	free(line);
	get_next_line(fd, &line);
	dq = ft_strchr(line, '"');
	i = 0;
	while (dq[++i] != '"')
		h.comment[i - 1] = dq[i];
	free(line);
	h.magic = COREWAR_EXEC_MAGIC;
	h.prog_size = 0;
	h.magic = END32(h.magic);
	h.prog_size = END32(h.prog_size);
	return (h);
}
