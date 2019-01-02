/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_nofile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 19:29:19 by jochang           #+#    #+#             */
/*   Updated: 2018/09/09 19:34:22 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/err.h"

void	err_nofile(char *prog, int n)
{
	RETURN_CHECK(n >= 2);
	if (ft_strequ(prog, "asm"))
	{
		ft_printf("Usage:\t./asm [file].s\n");
		ft_printf("Compiles champion .s file to .cor binary file.\n");
		ft_printf("No successive arguments are taken.\n");
	}
	else if (ft_strequ(prog, "cw"))
	{
		ft_printf("Usage: ./corewar [-p] [-n -d] [-w N] [champion].cor\n");
		ft_printf("\t-p: Python Visualizer\n\t-n: Ncurses Visualizer\n");
		ft_printf("\t-w [cycles per second]: Set Ncurses Visualizer speed\n");
		ft_printf("\t-d: Set Debug Mode for Ncurses Visualizer\n");
		ft_printf("\t\tPress key to advance 1 cycle, hold");
		ft_printf(" key to run continously\n");
		ft_printf("-p flag takes no additional arguments\n");
		ft_printf("-p and -n flags override each other such that first flag ");
		ft_printf("given will be ignored if both are present\n");
		ft_printf("-d and -w will only work if -n flag is present.\n\n");
		ft_printf("Corewar takes 1 - 4 .cor files and runs them in the ");
		ft_printf("Virtual Machine.\nWritten by jochang, jtashako, ");
		ft_printf("and smonroe.\n42 Silicon Valley, September 2018\n");
	}
	exit(1);
}
