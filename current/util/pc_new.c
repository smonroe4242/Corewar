/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 00:53:43 by jochang           #+#    #+#             */
/*   Updated: 2018/09/24 00:53:44 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

static uint32_t	g_arr[17] = {
	-1, 10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800, 10, 40, 1000, 2
};

static void	wait_mod(uint16_t *wait, uint8_t op)
{
	if (op < 0 || op > 16)
		op = 0;
	*wait = g_arr[op];
}

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
	wait_mod(&new->wait, op);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}