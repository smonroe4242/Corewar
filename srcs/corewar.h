/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <smonroe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 03:53:45 by smonroe           #+#    #+#             */
/*   Updated: 2018/09/08 14:29:57 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "op.h"
# define MLX 'm'
# define PRINT 'p'
# define NCURSES 'n'
# include <stdio.h>

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
	uint32_t		pcount[MAX_PLAYERS];
	uint8_t			**mem;
	uint8_t			**ref;
	t_pc			*pc;
}					t_cyc;

typedef struct		s_flg
{
	uint8_t			print;
}					t_flg;

typedef void	(*t_fn)(t_cyc *, t_pc *);

void				prove(t_pc *pc);
void				ft_memrcpy(void *dst, void *src, size_t n);

char				*g_optarg;
int					g_optind;
int					g_optopt;
t_flg				ft_setopt(int ac, char **av);
int					ft_getopt(int ac, char **av, char *flg);

uint8_t				acb_arg(uint8_t tb);

void				op_live(t_cyc *info, t_pc *pc);
void				op_ld(t_cyc *info, t_pc *pc);
void				op_st(t_cyc *info, t_pc *pc);
void				op_add(t_cyc *info, t_pc *pc);
void				op_sub(t_cyc *info, t_pc *pc);
void				op_and(t_cyc *info, t_pc *pc);
void				op_or(t_cyc *info, t_pc *pc);
void				op_xor(t_cyc *info, t_pc *pc);
void				op_zjmp(t_cyc *info, t_pc *pc);
void				op_ldi(t_cyc *info, t_pc *pc);
void				op_sti(t_cyc *info, t_pc *pc);
void				op_fork(t_cyc *info, t_pc *pc);
void				op_lld(t_cyc *info, t_pc *pc);
void				op_lldi(t_cyc *info, t_pc *pc);
void				op_lfork(t_cyc *info, t_pc *pc);
void				op_aff(t_cyc *info, t_pc *pc);

void				wait_mod(uint16_t *wait, uint8_t op);
void				pc_scan_op(t_cyc *info, t_pc *pc);

t_pc				*pc_new(uint32_t pnum, uint16_t loc, uint8_t op);
void				pc_app(t_pc *org, t_pc *new);
void				pc_rem(t_pc *old);
t_pc				*pc_rem_head(t_pc *pc);
void				pc_scan_rem(t_pc *pc);
void				pc_free(t_pc *pc);

void				ft_dump_mem(t_cyc *info);
t_head				file_stuff(char *cor);
void				exit_msg(int n, char *s);
void				display(t_cyc *info, t_head champ[MAX_PLAYERS], t_flg flag);
void				ft_memfree(uint8_t **m, size_t n);
t_cyc				t_cyc_init(uint8_t **mem, uint8_t **ref, t_pc *pc);
int					init_env(t_cyc info, t_head champ[MAX_PLAYERS], t_flg flag);
void				init_proc(uint8_t **mem, uint8_t **ref, t_head champ[MAX_PLAYERS], t_flg flag);
void				init_vm(t_head champ[MAX_PLAYERS], t_flg flag);

#endif
