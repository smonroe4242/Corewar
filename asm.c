/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 03:37:03 by smonroe           #+#    #+#             */
/*   Updated: 2018/08/26 23:59:05 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	asm_error(int n, char *s)
{
	if (n == 0)
	{
		ft_printf("Usage:\t./asm [file].s\nCompiles champion .s file to .cor");
		ft_printf(" binary file.\nNo successive arguments are taken.\n");
	}
	else if (n == 1)
		ft_printf("File not readable. Please enter valid .s champion file.\n");
	else if	(n == 2)
		ft_printf("\e[31m\e[1mError:\e[0m Bad op \"\e[31m%s\e[0m\" found.\n", s);
	exit(0);
}

uint32_t	endian_swap(uint32_t n)
{
	return (((n & 0xff000000) >> 24) | ((n & 0xff0000) >> 8)
			| ((n & 0xff00) << 8) | ((n & 0xff) << 24));
}

t_header	get_header(int fd)
{
	t_header	head;
	char		*line;
	char		*dq;
	int			i;

	ft_memset(&head, 0, HEADER_SIZE);
	get_next_line(fd, &line);
	dq = ft_strchr(line, '"');
	i = 0;
	while (dq[++i] != '"')
		head.prog_name[i - 1] = dq[i];
	get_next_line(fd, &line);
	dq = ft_strchr(line, '"');
	i = 0;
	while (dq[++i] != '"')
		head.comment[i - 1] = dq[i];
	head.magic = COREWAR_EXEC_MAGIC;
	head.prog_size = 42;
	head.magic = endian_swap(head.magic);
	head.prog_size = endian_swap(head.prog_size);
	return (head);
}

int		main(int ac, char **av)
{
	t_header	s;
	int			fds;
	int			fdc;
	char		*cor;

	if (ac != 2)
		asm_error(0, NULL);
	fds = open(av[1], O_RDONLY);
	cor = NULL;
	if (fds == -1 || (read(fds, cor, 0)) == -1)
		asm_error(1, NULL);
	cor = ft_strnew(ft_strlen(av[1]) + 2);
	cor = ft_strcat(cor, av[1]);
	ft_memmove(&cor[ft_strlen(cor) - 1], "cor", 3);
	fdc = open(cor, O_CREAT | O_RDWR | O_TRUNC, 0777);
	s = get_header(fds);
//	bytecode(fdc, fds);
	write(fdc, &s, HEADER_SIZE);
	close(fds);
	close(fdc);
	free(cor);
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
