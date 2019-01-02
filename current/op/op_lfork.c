/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 01:59:52 by jochang           #+#    #+#             */
/*   Updated: 2018/09/24 01:59:52 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_lfork(t_cyc *info, t_pc *pc)
{
	int16_t	addr;
	t_pc	*new;

	TEA;
	//ft_printf("%d---------------[LFORK]\n", pc->r[0]);
	ft_memrcpy(&addr, &info->mem[0][MEM(pc->i + 1)], IND_SIZE);
	new = pc_new(-pc->r[0], MEM(pc->i + addr), info->mem[0][MEM(pc->i + addr)]);
	ft_memcpy(&new->r, &pc->r, sizeof(new->r));
	new->carry = pc->carry;
	new->alive = pc->alive;
	pc_app(&g_head, new);
	pc->i += 3;
	pc->carry = 1;
	TIME("op_lfork\t");
}
