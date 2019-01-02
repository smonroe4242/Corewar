/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_scan_rem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 18:48:09 by jochang           #+#    #+#             */
/*   Updated: 2018/09/09 18:56:14 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	pc_scan_rem(t_pc *pc)
{
	t_pc	tmp;

	tmp = pc;
	while (tmp)
	{
		if (!tmp->alive && tmp->prev)
			pc_rem(tmp);
		tmp = tmp->next;
	}
	if (!pc->alive)
		pc = pc_rem_head(pc);
}
