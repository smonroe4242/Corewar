/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 20:30:41 by jochang           #+#    #+#             */
/*   Updated: 2018/09/09 20:30:41 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

static void	new_cor(char *fn, t_header s, t_byte file)
{
	char	*cor;
	int		fd;

	cor = ft_strnew(ft_strlen(fn) + 2);
	cor = ft_strccpy(cor, fn, '.');
	cor = ft_strcat(cor, ".cor");
	fd = open(cor, O_CREAT | O_RDWR | O_TRUNC, 0777);
	free(cor);
	write(fd, &s, HEADER_SIZE);
	write(fd, file.code, file.count);
	close(fd);
}

void	make_cor(char *fn)
{
	int			fds;
	t_header	s;
	t_byte		file;

	fds = open(fn, O_RDONLY);
	if (fds == -1 || (read(fds, &fds, 0)) == -1)
		err_invfile("asm", NULL);
	s = get_header(fds);
	file = get_bytecode(fds);
	s.prog_size = END32(file.count);
	close(fds);
	new_cor(fn, s, file);
	t_byte_free(&file);
}
