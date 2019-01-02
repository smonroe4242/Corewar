/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_rem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 18:09:26 by jochang           #+#    #+#             */
/*   Updated: 2019/01/01 20:27:27 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	pc_rem(t_pc **rm)
{
	if ((*rm)->next)
		(*rm)->next->prev = (*rm)->prev;
	if ((*rm)->prev)
		(*rm)->prev->next = (*rm)->next;
	ft_bzero(*rm, sizeof(*rm));
	free(*rm);
	*rm = NULL;
}
