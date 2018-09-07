/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <smonroe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 03:53:45 by smonroe           #+#    #+#             */
/*   Updated: 2018/09/07 00:05:14 by smonroe          ###   ########.fr       */
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
	uint16_t		i;
	int				r[REG_NUMBER + 1];
	uint8_t			carry;
	uint16_t		alive;
	uint16_t		wait;
	struct s_pc		*next;
	struct s_pc		*prev;
}					t_pc;

typedef struct		s_cyc
{
	int				cycle;
	int				last;
	uint8_t			kill;
	uint8_t			**mem;
	uint8_t			**ref;
	t_pc			*pc;
}					t_cyc;

void				prove(t_pc *pc);

t_pc				*pc_new(uint32_t pnum, uint16_t loc);
void				pc_scan_op(t_cyc *info);
void				pc_app(t_pc *org, t_pc *new);
void				pc_rem(t_pc *old);
t_pc				*pc_rem_head(t_pc *pc);
void				pc_scan_rem(t_pc *pc);
void				pc_free(t_pc *pc);

void				ft_dump_mem(uint8_t *mem, uint8_t *ref);
t_head				file_stuff(char *cor);
int					turn(uint8_t **mem, uint8_t **ref, t_pc *pc);
void				init_proc(uint8_t **mem, uint8_t **ref, t_head champ[MAX_PLAYERS], int n);
void				init_env(uint8_t **mem, uint8_t **ref, t_head champ[MAX_PLAYERS], t_pc *pc);
void				init_vm(t_head champ[MAX_PLAYERS], int chs);

#endif
