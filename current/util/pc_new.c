/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 00:53:43 by jochang           #+#    #+#             */
/*   Updated: 2019/01/03 23:20:47 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

t_pc	*pc_new(uint32_t pnum, uint16_t loc, uint8_t op)
{
	t_pc	*new;

	if (!(new = ft_memalloc(sizeof(t_pc))))
		err_malloc("pc_new");
	new->i = loc;
	ft_memset(&new->r, 0, sizeof(new->r));
	new->r[0] = -pnum;
	new->r[1] = pnum;
	new->carry = 0;
	new->alive = 0;
	new->wait = WAIT_MOD(op);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
