/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <smonroe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 03:53:45 by smonroe           #+#    #+#             */
/*   Updated: 2018/09/05 17:36:05 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "op.h"

typedef struct		s_head
{
	int				pnum;
	char			name[PROG_NAME_LENGTH];
	char			comment[COMMENT_LENGTH];
	int				size;
	uint8_t			code[CHAMP_MAX_SIZE];
}					t_head;

typedef struct		s_pc
{
	uint8_t			*p;
	int				r[REG_NUMBER + 1];
	uint8_t			carry;
	struct t_pc		*next;
}					t_pc;

t_head				file_stuff(char *cor);

#endif
