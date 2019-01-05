/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_rem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 18:09:26 by jochang           #+#    #+#             */
/*   Updated: 2019/01/05 02:10:17 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	pc_rem(t_pc **pc)
{
	//pc = NULL or *pc = NULL? Can't see behavioral difference but only one is right.
	if ((*pc)->next && (*pc)->prev)
	{
		//ft_printf("Removing Link : Next && Prev\n");
		//prove(*pc);
		(*pc)->next->prev = (*pc)->prev;
		(*pc)->prev->next = (*pc)->next;
		ft_bzero(*pc, sizeof(**pc));
		free(*pc);
		pc = NULL;
	}
	else if ((*pc)->prev)
	{
		//ft_printf("Removing Link : Prev && !Next\n");
		//prove(*pc);
		(*pc)->prev->next = NULL;
		ft_bzero(*pc, sizeof(**pc));
		free(*pc);
		pc = NULL;
	}
	else
		pc_rem_head(&g_head);
/*	if ((*rm)->next)
		(*rm)->next->prev = (*rm)->prev;
	if ((*rm)->prev)
		(*rm)->prev->next = (*rm)->next;
	ft_bzero(*rm, sizeof(*rm));
	free(*rm);
	*rm = NULL;*/
}
