/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 20:32:10 by jochang           #+#    #+#             */
/*   Updated: 2019/01/02 09:32:55 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "err.h"
# include "../libft/libft.h"
//# include "../ft_printf/inc/ft_printf.h"

# define HEADER_SIZE	PROG_NAME_LENGTH + COMMENT_LENGTH + 8

typedef struct		s_label
{
	char			*name;
	uint16_t		loc;
	uint16_t		addr;
}					t_label;

typedef struct		s_byte
{
	char			*label;
	uint8_t			*code;
	uint16_t		count;
	t_label			*l;
}					t_byte;

typedef struct		s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}					t_header;

typedef struct		s_op
{
	char			*name;
	int				argc;
	int				types[4];
	int				code;
	int				cycles;
	char			*desc;
	int				acb;
	int				flag2;
}					t_op;

extern const t_op	g_op_tab[17];

void				make_cor(char *fn);
t_header			get_header(int fd);
t_byte				get_bytecode(int fds);
t_byte				t_byte_init(void);
t_byte				t_byte_append(t_byte org, t_byte app);
void				t_byte_free(t_byte *x);
uint8_t				*label_fill(t_byte f, t_label *l);
t_label				*label_add(t_byte b, t_byte f, t_label *l);
t_byte				label_append(t_byte org, t_byte app);
t_byte				arg_no_acb(int i, char *arg, int lc, t_byte prm);
t_byte				arg_label(t_byte prm, char *arg, int n, int lc);
t_byte				arg_reg(t_byte prm, char *arg, int lc);
t_byte				arg_dir(t_byte prm, char *arg, int lc);
t_byte				arg_ind(t_byte prm, char *arg, int lc);

#endif
