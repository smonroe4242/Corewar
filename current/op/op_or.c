/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 02:00:21 by jochang           #+#    #+#             */
/*   Updated: 2018/09/24 02:00:21 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/corewar.h"

void	op_or(t_cyc *info, t_pc *pc)
{
	TEA;
	//ft_printf("%d-------[OR]\n", pc->r[0]);
	(void)info;
	pc->carry = 1;
	//copy op_and when confirmed working
	TIME("op_or\t");
}