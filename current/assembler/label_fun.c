/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_fun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 18:48:29 by jochang           #+#    #+#             */
/*   Updated: 2018/09/10 18:48:31 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

uint8_t		*label_fill(t_byte f, t_label *l)
{
	int		n;
	int		i;
	uint16_t diff;

	n = -1;
	while (f.l[++n].name)
	{
		i = -1;
		while (l[++i].name)
			if (!ft_strcmp(l[i].name, f.l[n].name))
				break ;
		diff = l[i].loc - f.l[n].addr;
		diff = END16(diff);
		ft_memcpy(&f.code[f.l[n].loc], &diff, 2);
	}
	n = -1;
	if (l)
	{
		while (l[++n].name)
			free(l[n].name);
		free(l);
	}
	return (f.code);
}

t_label		*label_add(t_byte b, t_byte f, t_label *l)
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
	l[n++].loc = f.count - b.count;
	l[n].name = NULL;
	l[n].loc = 0;
	l[n].addr = 0;
	return (l);
}

//append label to tbyte struct
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
		o++;
		i++;
	}
	org.l = (t_label *)realloc(org.l, sizeof(t_label) * ++o);
	org.l[--o].name = NULL;
	org.l[o].loc = 0;
	org.l[o].addr = 0;
	return (org);
}