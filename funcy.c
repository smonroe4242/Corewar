/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 20:27:41 by smonroe           #+#    #+#             */
/*   Updated: 2018/08/31 22:43:07 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

t_byte		init_t_byte(void)
{
	t_byte	tmp;
	int		i;

	i = 0;
	tmp.code = (uint8_t *)malloc(0);
	tmp.count = 0;
	tmp.l = (t_label *)malloc(sizeof(t_label) * MAX_ARGS_NUMBER);
	i = -1;
	while (++i < MAX_ARGS_NUMBER)
	{
		tmp.l[i].name = NULL;
		tmp.l[i].loc = 0;
		tmp.l[i].addr = 0;
	}
	tmp.label = NULL;
	return (tmp);
}

t_byte		t_byte_append(t_byte org, t_byte app)
{
	org.code = (uint8_t *)realloc(org.code, org.count + app.count);
	ft_memcpy(&org.code[org.count], app.code, app.count);
	org.count += app.count;
	free(app.code);
	return (org);
}

t_byte		label_append(t_byte org, t_byte app)
{
	int	o;
	int	i;

	o = 0;
	while (org.l[o].name)
		o++;
	i = 0;
	while (app.l[i].name)
	{
		org.l[o].name = ft_strdup(app.l[i].name);
		org.l[o].loc = app.l[i].loc + org.count - app.count;
		org.l[o].addr = org.count - app.count;
		free(app.l[i].name);
		o++;
		i++;
	}
	org.l = (t_label *)realloc(org.l, sizeof(t_label) * ++o);
	org.l[--o].name = NULL;
	org.l[o].loc = 0;
	org.l[o].addr = 0;
	return (org);
}

t_label		*add_lab(t_byte b, t_byte f, t_label *l)
{
	int	n;

	if (!l)
	{
		l = (t_label *)malloc(sizeof(t_label));
		ft_memset(l, 0, sizeof(t_label));
		l[0].name = NULL;
	}
	n = 0;
	while (l[n].name)
		n++;
	l = (t_label *)realloc(l, sizeof(t_label) * (n + 2));
	l[n].name = ft_strdup(b.label);
	free(b.label);
	l[n++].loc = f.count - b.count;
	l[n].name = NULL;
	l[n].loc = 0;
	l[n].addr = 0;
	return (l);
}

uint8_t		*labelify(t_byte f, t_label *l)
{
	int		n;
	int		i;
	uint16_t diff;

	n = -1;
	while (f.l[++n].name)
	{
		ft_printf("|%s|", f.l[n].name);
		i = -1;
		while (l[++i].name)
			if (!ft_strcmp(l[i].name, f.l[n].name))
				break ;
		diff = l[i].loc - f.l[n].addr;
		ft_printf("|%s|", l[i].name);
		ft_printf("%.4x/%d = %d - %d\n", diff, diff, l[i].loc, f.l[n].addr);
		diff = END16(diff);
		ft_memcpy(&f.code[f.l[n].loc], &diff, 2);
		free(f.l[n].name);
	}
	n = -1;
	while (l[++n].name)
		free(l[n].name);
	return (f.code);
}
