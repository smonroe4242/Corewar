/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 02:01:09 by jochang           #+#    #+#             */
/*   Updated: 2018/09/24 02:01:09 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_xor(t_cyc *info, t_pc *pc)
{
	TEA;
	//ft_printf("%d--------[XOR]\n", pc->r[0]);
	(void)info;
	pc->carry = 1;
	//copy op_and when confirmed working
	TIME("op_xor\t");
}