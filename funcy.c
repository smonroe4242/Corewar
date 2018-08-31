/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smonroe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 20:27:41 by smonroe           #+#    #+#             */
/*   Updated: 2018/08/30 23:43:10 by smonroe          ###   ########.fr       */
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

	if (!org.l)
	{
		org.l = (t_label *)malloc(sizeof(t_label) * MAX_ARGS_NUMBER);
		ft_memset(org.l, 0, sizeof(t_label) * MAX_ARGS_NUMBER);
		i = -1;
		while (++i < MAX_ARGS_NUMBER)
		{
			org.l[i].name = NULL;
			org.l[i].loc = 0;
		}
	}
	o = 0;
	while (org.l[o].name)
		o++;
	i = 0;
	while (app.l[i].name)
	{
		org.l[o].name = ft_strdup(app.l[i].name);
		org.l[o].loc = app.l[i].loc;
		free(app.l[i].name);
		o++;
		i++;
	}
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
	return (l);
}

uint8_t		*labelify(t_byte f, t_label *l)
{
	int n;

	ft_printf("t_byte f labels:\n");
	n = -1;
	while (f.l[++n].name)
	{
		ft_printf("label %d: %s @ %d\n", n, f.l[n].name, f.l[n].loc);
		free(f.l[n].name);
	}
	ft_printf("Labels in list:\n");
	n = -1;
	while (l[++n].name)
	{
		ft_printf("func labels %d: %s as %d\n", n, l[n].name, l[n].loc);
		free(l[n].name);
	}
	return (f.code);
}
