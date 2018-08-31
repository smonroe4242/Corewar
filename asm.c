/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 03:37:03 by smonroe           #+#    #+#             */
/*   Updated: 2018/08/30 23:56:04 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	asm_error(int n)
{
	if (n == 0)
	{
		ft_printf("Usage:\t./asm [file].s\nCompiles champion .s file to .cor");
		ft_printf(" binary file.\nNo successive arguments are taken.\n");
	}
	else if (n == 1)
		ft_printf("File not readable. Please enter valid .s champion file.\n");
	exit(0);
}

void	comp_error(int n, char *s, int l)
{
	if (n == 0)
	{
		ft_printf("\e[31m\e[1mError:\e[0m Bad op \"\e[31m%s\e[0m\"", s);
		ft_printf(" found on line \e[32m%d\e[0m.\nFile failed to compile.\n", l);
	}
	else if (n == 1)
	{
		ft_printf("\e[31m\e[1mError:\e[0m Bad argument \"\e[31m%s\e[0m\"", s);
		ft_printf(" found on line \e[32m%d\e[0m.\nFile failed to compile.\n", l);
	}
	exit(0);
}

void		free_line(char **coms, char **args)
{
	int i;

	if (coms)
	{
		i = -1;
		while (coms[++i])
			free(coms[i]);
		free(coms);
	}
	if (args)
	{
		i = -1;
		while (args[++i])
			free(args[i]);
		free(args);
	}
}

t_header	get_header(int fd)
{
	t_header	h;
	char		*line;
	char		*dq;
	int			i;

	ft_memset(&h, 0, HEADER_SIZE);
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

int		main(int ac, char **av)
{
	t_header	s;
	int			fds;
	int			fdc;
	char		*cor;
	t_byte		file;

	if (ac != 2)
		asm_error(0);
	fds = open(av[1], O_RDONLY);
	cor = NULL;
	if (fds == -1 || (read(fds, cor, 0)) == -1)
		asm_error(1);
	s = get_header(fds);
	file = bytecode(fds);
	s.prog_size = END32(file.count);
	close(fds);
	cor = ft_strnew(ft_strlen(av[1]) + 2);
	cor = ft_strcat(cor, av[1]);
	ft_memmove(&cor[ft_strlen(cor) - 1], "cor", 3);
	fdc = open(cor, O_CREAT | O_RDWR | O_TRUNC, 0777);
	free(cor);
	write(fdc, &s, HEADER_SIZE);
	write(fdc, file.code, file.count);
	close(fdc);
	free(file.code);
	while(1);
	return (0);
}

/*
0x0000 first 4 bytes magic number immediately followed by name.
0x008a 2 byte length of champion, then comment
0x0890 champion start

file[0] = magic
file[4] = name|00000
file[136] = size
file[140] = comment|0000
file[2192] = champ|EOF
*/
