/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 01:59:20 by jochang           #+#    #+#             */
/*   Updated: 2018/09/24 01:59:22 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_fork(t_cyc *info, t_pc *pc)
{
	int16_t	addr;
	t_pc	*new;

	TEA;
	ft_memrcpy(&addr, &info->mem[0][MEM(pc->i + 1)], IND_SIZE);
	new = pc_new(-(pc->r[0]), MEM(pc->i + IDX(addr)),
				info->mem[0][MEM(pc->i + IDX(addr))]);
	ft_memcpy(new->r, pc->r, sizeof(new->r));
	//ft_printf("sizeof(pc->r) == %d\n", sizeof(pc->r));
	//ft_printf("ADDR: %#.4x : %d; pc->i: %d\n", addr, addr, pc->i);
	new->carry = pc->carry;
	new->alive = pc->alive;
	pc_app(&g_head, new);
	//ft_printf("addr: %d + %d = %d:%d\n", addr, pc->i, addr + pc->i, new->i);
	pc->i += 3;
	TIME("op_fork\t");
}
