/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_scan_rem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 18:48:09 by jochang           #+#    #+#             */
/*   Updated: 2019/01/05 02:17:33 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	pc_scan_rem(t_pc **pc)
{
	t_pc	*tmp;

	tmp = *pc;
	while (tmp->next)
	{
		tmp = tmp->next;
		if (!tmp->prev->alive)
			pc_rem(&tmp->prev);
	}
	if (!(*pc)->alive)
		pc_rem_head(pc);
}
