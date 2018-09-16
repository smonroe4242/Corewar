/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 04:23:32 by smonroe           #+#    #+#             */
/*   Updated: 2018/09/07 20:44:45 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_pc	*pc_new(uint32_t pnum, uint16_t loc, uint8_t op)
{
	t_pc	*new;

	if (!(new = ft_memalloc(sizeof(t_pc))))
		exit_msg(4, "pc_new");
	new->i = loc;
	ft_memset(&new->r, 0, sizeof(new->r));
	new->r[0] = -pnum;
	new->r[1] = pnum;
	new->carry = 0;
	new->alive = 0;
	wait_mod(&new->wait, op);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void   pc_app(t_pc **lst, t_pc *node)
{
    if (lst)
    {
        node->next = *lst;
        (*lst)->prev = node;
	}
    *lst = node;
}

void	pc_rem(t_pc **pc)
{
	//pc = NULL or *pc = NULL? Can't see behavioral difference but only one is right.
	if ((*pc)->next && (*pc)->prev)
	{
		//ft_printf("Removing Link : Next && Prev\n");
		//prove(*pc);
		(*pc)->next->prev = (*pc)->prev;
		(*pc)->prev->next = (*pc)->next;
		ft_bzero(*pc, sizeof(t_pc));
		free(*pc);
		pc = NULL;
	}
	else if ((*pc)->prev)
	{
		//ft_printf("Removing Link : Prev && !Next\n");
		//prove(*pc);
		(*pc)->prev->next = NULL;
		ft_bzero(*pc, sizeof(t_pc));
		free(*pc);
		pc = NULL;
	}
	else
		pc_rem_head(&g_head);
}

void	pc_rem_head(t_pc **pc)
{
	t_pc	*tmp;

	//ft_printf("Head removal in progress\n");
	tmp = NULL;
	if ((*pc)->next)
		tmp = (*pc)->next;
	ft_bzero(*pc, sizeof(*pc));
	free(*pc);
	*pc = tmp;
	if (*pc)
		(*pc)->prev = NULL;
	//ft_printf("Done\n");
}

void    pc_scan_rem(t_pc **pc)
{
    t_pc    *tmp;
	t_pc	*hold;
    tmp = *pc;
    while (tmp)
    {
		//ft_printf("bloop\t");
        if (!tmp->alive)
		{
			//ft_printf("blip\t\n");
			hold = tmp->next;
//			//ft_printf("%p : %d\n", &hold, hold->i);
            pc_rem(&tmp);
			tmp = hold;
//			//ft_printf("%p : %d\n", &tmp, tmp->i);
		}
		else
		{
			tmp->alive = 0;
        	tmp = tmp->next;
		}
    }
	//ft_printf("\n");
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
	int		i;

	i = -1;
	//ft_printf("%d, at mem[%d], with %d lives : next->%p, prev->%p\n", pc->r[0], pc->i, pc->alive, pc->next, pc->prev);
	while (++i < 17)
		//ft_printf("%d:%.8x ", i, pc->r[i]);
	ft_putchar('\n');
	if (pc->next)
		prove(pc->next);
	else
		;//ft_printf("List end\n\n");
}
