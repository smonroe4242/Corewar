/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 03:37:03 by smonroe           #+#    #+#             */
/*   Updated: 2018/08/26 05:16:59 by smonroe          ###   ########.fr       */
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

char	*line_to_hex(char *s)
{
	
	return ((char *)0xea83f300);
}

int		main(int ac, char **av)
{
	int		fds;
	int		fdc;
	char	*cor;
	char	*line;

	if (ac != 2)
		asm_error(0);
	fds = open(av[1], O_RDONLY);
	if (fds == -1 || (read(fds, line, 0)) == -1)
		asm_error(1);
	cor = ft_strnew(ft_strlen(av[1]) + 2);
	cor = ft_strcat(cor, av[1]);
	ft_memmove(&cor[ft_strlen(cor) - 1], "cor", 3);
	ft_printf("\nFile name: %s -> %s\n", av[1], cor);
	fdc = open(cor, O_CREAT | O_APPEND | O_RDWR | O_TRUNC, 0777);
	while (get_next_line(fds, &line))
	{
		ft_printf("%s\n", line_to_hex(line));
		ft_putendl_fd(line, fdc);
		free(line);
	}
	ft_printf("Succesfully wrote to %s from %s\n", cor, av[1]);
	close(fds);
	close(fdc);
	free(cor);
	return (0);
}
