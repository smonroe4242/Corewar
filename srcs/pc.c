/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 04:23:32 by smonroe           #+#    #+#             */
/*   Updated: 2018/09/07 00:03:58 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_pc	*pc_new(uint32_t pnum, uint16_t loc)
{
	t_pc	*new;

	new = ft_memalloc(sizeof(t_pc));
	new->i = loc;
	ft_memset(&new->r, 0, sizeof(new->r));
	new->r[0] = -pnum;
	new->r[1] = pnum;
	new->carry = 0;
	new->alive = 0;
	new->wait = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	pc_scan_op(t_cyc *info)
{
	ft_dump_mem(*info->mem, *info->ref);
}

void	pc_app(t_pc *org, t_pc *new)
{
	if (org->next)
		pc_app(org->next, new);
	else
	{
		org->next = new;
		new->prev = org;
	}
}

void	pc_rem(t_pc *old)
{
	if (old->next)
		old->next->prev = old->prev;
	if (old->prev)
		old->prev->next = old->next;
	ft_bzero(old, sizeof(t_pc));
	free(old);
}

t_pc	*pc_rem_head(t_pc *pc)
{
	t_pc	*tmp;

	tmp = pc->next;
	ft_bzero(pc, sizeof(t_pc));
	free(pc);
	return (tmp);
}
	
void	pc_scan_rem(t_pc *pc)
{
	if (pc->next)
		pc_scan_rem(pc->next);
	if (!pc->alive && pc->prev)
		pc_rem(pc);
}

void	pc_free(t_pc *pc)
{
	if (pc->next)
		pc_free(pc->next);
	ft_bzero(pc, sizeof(t_pc));
	free(pc);
}

void	prove(t_pc *pc)
{
	ft_printf("%d, at mem[%d], with %d lives\n", pc->r[0], pc->i, pc->alive);
	if (pc->next)
		prove(pc->next);
	else
		ft_printf("List end\n");
}
