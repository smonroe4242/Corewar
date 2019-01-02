/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_byte_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 00:46:11 by jochang           #+#    #+#             */
/*   Updated: 2018/09/10 00:46:12 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/asm.h"

t_byte		t_byte_init(void)
{
	t_byte	tmp;
	int		i;

	i = 0;
	tmp.code = (uint8_t *)malloc(0); //change this later
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
	return (org);
}

void		t_byte_free(t_byte *x)
{
	int		i;

	i = -1;
	if (x->l)
	{
		while (x->l[++i].name)
			free(x->l[i].name);
		free(x->l);
	}
	if (x->code)
		free(x->code);
	if (x->label)
		free(x->label);
}