/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 17:12:30 by jochang           #+#    #+#             */
/*   Updated: 2018/08/15 13:58:18 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

#define FDS 1024

static char	*ft_strjoinfr(char *s1, char const *s2)
{
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	if (!(new = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	if ((new = ft_strncat(new, s1, ft_strlen(s1) + ft_strlen(s2))))
		if ((new = ft_strncat(new, s2, ft_strlen(s1) + ft_strlen(s2))))
		{
			free(s1);
			return (new);
		}
	return (NULL);
}

int		get_next_line(const int fd, char **line)
{
	static char	*s[FDS];
	char		pipe[BUFF_SIZE + 1];
	char		*place;
	int			x;

	if (fd < 0 || fd >= FDS || !line || (!((!s[fd]) ? (s[fd] = ft_strnew(0))
								: (s[fd]))) || ((x = read(fd, pipe, 0)) == -1))
		return (-1);
	while ((x = read(fd, pipe, BUFF_SIZE)) > 0)
	{
		pipe[x] = '\0';
		s[fd] = ft_strjoinfr(s[fd], pipe);
	}
	if (!(s[fd][0] == '\0'))
	{
		if (!(place = ft_strchr(s[fd], '\n')))
			place = ft_strnew(0);
		else if (!(*place = '\0'))
			place = ft_strdup(place + 1);
		(*line = ft_strdup(s[fd])) ? ft_strdel(&s[fd]) : 1;
		(s[fd] = ft_strdup(place)) ? (free(place)) : 1;
		return (1);
	}
	ft_strclr(*line);
	return (x);
}
