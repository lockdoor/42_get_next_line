/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:22:10 by pnamnil           #+#    #+#             */
/*   Updated: 2023/09/06 12:22:10 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_strdup_find_nl(char *s, char **nl)
{
	size_t	i;
	char	*tab;

	i = 0;
	while (s[i])
		i++ ;
	tab = (char *) malloc (i + 1);
	if (!tab)
		return (NULL);
	while (*s)
	{
		*tab = *s;
		if (*tab == '\n' && *nl == NULL)
			*nl = tab;
		tab++ ;
		s++ ;
	}
	*tab = 0;
	return (tab - i);
}

static char	*ft_strjoin_find_nl(char *s1, char *s2, char **nl)
{
	char	*tab;
	size_t	i;

	i = 0;
	tab = s1;
	while (*tab++)
		i++ ;
	tab = s2;
	while (*tab++)
		i++ ;
	tab = (char *) malloc (i + 1);
	if (!tab)
		return (NULL);
	while (*s1)
		*tab++ = *s1++;
	while (*s2)
	{
		*tab = *s2;
		if (*tab == '\n' && *nl == NULL)
			*nl = tab;
		tab++ ;
		s2++ ;
	}
	*tab = 0;
	return (tab - i);
}

static char	*ft_get_next_line(char	**str, char *nl)
{
	char	*result;
	char	*tmp;

	if (nl)
	{
		result = ft_substr (*str, 0, nl - *str + 1);
		if (*(nl + 1) != 0)
		{
			tmp = ft_strdup_find_nl (nl + 1, &nl);
			free (*str);
			*str = tmp;
		}
		else
		{
			free (*str);
			*str = NULL;
		}
	}
	else
	{
		result = ft_strdup_find_nl(*str, &nl);
		free (*str);
		*str = NULL;
	}
	return (result);
}

static char	*ft_find_nl(char **s, char *bf, int fd, int *read_ret)
{
	char	*nl;
	char	*tmp;

	nl = ft_strchr(*s, '\n');
	while (!nl)
	{
		*read_ret = read(fd, bf, BUFFER_SIZE);
		if (*read_ret < 1)
			break ;
		bf[*read_ret] = 0;
		if (*s == NULL)
			*s = ft_strdup_find_nl(bf, &nl);
		else
		{
			tmp = ft_strjoin_find_nl(*s, bf, &nl);
			free (*s);
			*s = tmp;
		}
	}
	return (nl);
}

char	*get_next_line(int fd)
{
	char		*bf;
	static char	*s[10];
	char		*nl;
	int			read_ret;

	if (fd < 0)
		return (NULL);
	bf = (char *) malloc (BUFFER_SIZE + 1);
	if (!bf)
		return (NULL);
	read_ret = 0;
	nl = ft_find_nl(&s[fd], bf, fd, &read_ret);
	if (read_ret == -1)
	{
		if (s[fd])
			free (s[fd]);
		s[fd] = NULL;
	}
	free (bf);
	if (!s[fd])
		return (NULL);
	return (ft_get_next_line(&s[fd], nl));
}
