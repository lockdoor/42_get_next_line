/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:23:05 by pnamnil           #+#    #+#             */
/*   Updated: 2023/09/06 12:23:05 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*t;
	unsigned char	cmp;

	if (s == NULL)
		return (NULL);
	t = (unsigned char *) s;
	cmp = (unsigned char) c;
	while (*t)
	{
		if (*t == cmp)
			return ((char *) t);
		t++ ;
	}
	if (cmp == 0)
		return ((char *) t);
	return (NULL);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*tab;
	size_t	i;
	size_t	j;
	size_t	s_len;

	s_len = 0;
	while (s[s_len])
		s_len++ ;
	if (len > s_len)
		len = s_len;
	tab = (char *) malloc (len + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (s[i] && i < start)
		i++ ;
	j = 0;
	while (s[i] && j < len)
		tab[j++] = s[i++];
	tab[j] = 0;
	return (tab);
}
