/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitwsp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 22:35:38 by jochang           #+#    #+#             */
/*   Updated: 2018/09/13 22:35:40 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

#define WSP(i) ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ')
#define PWSP ((*s >= 9 && *s <= 13) || *s == ' ')

static char	ft_word_count(char const *s)
{
	int words;
	int i;

	i = 0;
	words = 0;
	while (s[i] && WSP(i))
		i++;
	while (s[i])
	{
		if (!WSP(i))
			words++;
		while (!WSP(i) && s[i])
			i++;
		while (WSP(i) && s[i])
			i++;
	}
	return (words);
}

static char	**ft_make_2d(char const *s, char **bloc)
{
	int	i;
	int	w;
	int	l;

	if (!(bloc = (char **)malloc(sizeof(char *) * (ft_word_count(s) + 1))))
		return (NULL);
	w = 0;
	i = 0;
	while (s[i])
	{
		l = 0;
		while (WSP(i) && s[i])
			i++;
		while (!WSP(i) && s[i])
		{
			i++;
			l++;
		}
		if (l)
			if (!(bloc[w++] = ft_strnew(l + 1)) && s[i])
				return (NULL);
	}
	return (bloc);
}

char		**ft_strsplitwsp(char const *s)
{
	int		w;
	int		l;
	char	**bloc;

	if (!s)
		return (NULL);
	bloc = NULL;
	if (!(bloc = ft_make_2d(s, bloc)))
		return (NULL);
	w = 0;
	while (*s)
	{
		l = 0;
		while (PWSP && *s)
			s += 1;
		while (!PWSP && *s)
			bloc[w][l++] = *s++;
		if (l)
			bloc[w++][l] = '\0';
	}
	bloc[w] = 0;
	return (bloc);
}

/*
static int	word_count(char const *s)
{
	int		n;

	n = 0;
	while (*s)
	{
		if (!ft_isspace(*s))
			n++;
		while (!ft_isspace(*s) && *s)
			s++;
		while (ft_isspace(*s) && *s)
			s++;
	}
	return (n);
}

static int	word_len(char *s)
{
	int		i;

	i = 0;
	while (s[i] && !ft_isspace(s[i]))
		i++;
	return (i); 
}

char	**ft_strsplitwsp(char const *s)
{
	char    **arr;
	int		i;
	int		numwords;
	int		wlen;

	numwords = word_count((char*)s);
	NULL_CHECK(!(arr = (char**)ft_memalloc((numwords + 1) * sizeof(char*))));
	i = 0;
	while (numwords--)
	{
		while (*s && ft_isspace(*s))
			s++;
		wlen = word_len((char*)s);
		NULL_CHECK(!(arr[i] = ft_strsub(s, 0, wlen)));
		s += wlen;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
*/