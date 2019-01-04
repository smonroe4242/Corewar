/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/23 21:00:29 by jochang           #+#    #+#             */
/*   Updated: 2019/01/04 01:50:27 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <curses.h>
# include <time.h>
# include "op.h"
# include "err.h"
# include "../libft/libft.h"
//# include "../ft_printf/inc/ft_printf.h"

/*
** Macros
*/

# define MEM(x) (((x) < 0) ? (MEM_SIZE + ((x) % MEM_SIZE)) : ((x) % MEM_SIZE))

# define ACB_ARG(x) (((x) == 3) ? 4 : (x))
# define REG(r) ((r) > 0 && (r) <= REG_NUMBER)
# define TEA //g_time = clock()
# define TIME(s) //ft_printf("%s: %8lu\n", (s), clock() - g_time)

# define IDX(x) ((x) % IDX_MOD)

// for pc_scan_op && pc_new
#define ARR -1, 10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800, 10, 50, 1000, 2
#define WAIT_MOD(x) (uint16_t[]){ARR}[(x)]

/*
** Structs
*/

typedef struct	s_mem
{
	uint8_t		byte; // content
	int			pnum; // pnum last modified
	uint8_t		timer; // decrement each cycle after mem modification
}				t_mem;

/*
** Mem struct for array
*/

typedef struct		s_flag
{
	uint8_t			p;
	uint8_t			n;
	uint8_t			d;
	uint32_t		w;
	int				fd;
}					t_flag;

typedef struct		s_head
{
	int				pnum;
	int				live;
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

/*
** Dispatch Array
*/

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

typedef void		(*t_fn)(t_cyc *, t_pc *);
extern const t_fn	g_op_fn[];

/*
** Globals
*/

clock_t				g_time;
t_pc				*g_head;

t_flag				ft_setopt(int ac, char **av);
t_head				parse_file(char *cor);
void				init_vm(t_head champ[MAX_PLAYERS], t_flag flag);
int					init_env(t_cyc info, t_head champ[MAX_PLAYERS], t_flag flag);

uint16_t			acb_len(uint8_t acb);
void				ft_memfree(uint8_t **m, size_t n);
void				ft_memrcpy(void *dst, void *src, size_t n);

void				display(t_cyc *info, t_head champ[MAX_PLAYERS], t_flag flag);

/*
** Util
*/

void				pc_app(t_pc **lst, t_pc *node);
void				pc_free(t_pc *pc);
t_pc				*pc_new(uint32_t pnum, uint16_t loc, uint8_t op);
void				pc_rem_head(t_pc **pc);
void				pc_rem(t_pc **rm);
void				pc_scan_rem(t_pc **pc);
void				pc_scan_op(t_cyc *info, t_pc *pc);

#endif
