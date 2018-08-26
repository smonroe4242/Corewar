/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 03:37:03 by smonroe           #+#    #+#             */
/*   Updated: 2018/08/26 16:04:36 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft/libft.h"
#include <fcntl.h>

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

uint32_t	endian_swap(uint32_t n)
{
	return (((n & 0xff000000) >> 24) | ((n & 0xff0000) >> 8)
			| ((n & 0xff00) << 8) | ((n & 0xff) << 24));
}

header_t	get_header(int fd)
{
	header_t	head;
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
	ft_printf("magic = %#x\nprog_name = %s\nprog_size = %u\ncomment = %s\n",
				head.magic, head.prog_name, head.prog_size, head.comment);
	head.magic = endian_swap(head.magic);
	head.prog_size = endian_swap(head.prog_size);
	return (head);
}

int		main(int ac, char **av)
{
	header_t	s;
	int			fds;
	int			fdc;
	char		*cor;
	int			i;

	if (ac != 2)
		asm_error(0);
	fds = open(av[1], O_RDONLY);
	if (fds == -1 || (read(fds, cor, 0)) == -1)
		asm_error(1);
	cor = ft_strnew(ft_strlen(av[1]) + 2);
	cor = ft_strcat(cor, av[1]);
	ft_memmove(&cor[ft_strlen(cor) - 1], "cor", 3);
	ft_printf("\nFile name: %s -> %s\n", av[1], cor);
	fdc = open(cor, O_CREAT | O_APPEND | O_RDWR | O_TRUNC, 0777);
	s = get_header(fds);
	ft_printf("\n%p\n%p\n%p\n%p\n", &s.magic, &s.prog_name, &s.prog_size, &s.comment);
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
