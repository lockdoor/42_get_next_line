/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:21:49 by pnamnil           #+#    #+#             */
/*   Updated: 2023/09/06 12:21:49 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static void	ft_init_str(t_memo *memo)
{
	// printf ("init_str called!\n");
	size_t	i;

	i = -1;
	memo->s = (char *) malloc (sizeof (char) * memo->read_ret + 1);
	while (memo->bf[++i] != 0)
	{
		memo->s[i] = memo->bf[i];
		if (memo->s[i] == '\n' && memo->nl == NULL)
			memo->nl = &memo->s[i];
	}
	memo->s[i] = 0;
	memo->nul = &memo->s[i];
	// printf ("memo->s: %s\n", memo->s);
	// printf ("last charecter in frist line: %c\n", *(memo->nl - 1));
	// printf ("charecter before end: %c", *(memo->nul - 1));
}

static void ft_join_str(t_memo *memo)
{
	// printf ("join_str called!\n");
	char	*tab;
	size_t	s_len;
	size_t	new_len;
	int		i;

	s_len = memo->nul - memo->s;
	new_len = s_len + memo->read_ret;
	tab = (char *) malloc (new_len + 1);
	i = -1;
	while (++i < (int) s_len)
		tab[i] = memo->s[i];
	i = -1;
	// printf ("memo->bf: %s\n", memo->bf);
	while (++i < (int) memo->read_ret)
	{
		// find nl here
		tab[i + s_len] = memo->bf[i];
		if (tab[i + s_len] == '\n' && memo->nl == NULL)
			memo->nl = &tab[i + s_len];
	}
	tab[i + s_len] = 0;
	free (memo->s);
	memo->nul = &tab[i + s_len];
	memo->s = tab;
	// printf ("memo->s: %s\n", memo->s);
	// printf ("tab: %s\n", tab);
	// printf ("s_len: %zu\n", s_len);
}

static void	ft_find_nl(t_memo *memo, int fd)
{
	// printf ("find_nl called!\n");
	// memo->nl = ft_strchr(memo->s, '\n');
	while (!memo->nl)
	{
		memo->read_ret = read(fd, memo->bf, BUFFER_SIZE);
		if (memo->read_ret < 1)
			break;
		(memo->bf)[memo->read_ret] = 0;
		if (!memo->s)
		{
			// memo->nul = &(memo->bf)[memo->read_ret];
			ft_init_str (memo);
			// printf ("memo->s: %s\n", memo->s);
		}
		else
		{
			ft_join_str (memo);
		}
		// printf ("memo->read_ret: %d\tmemo->nl: %p\n", memo->read_ret, memo->nl);
		// printf ("memo->bf: %s\n", memo->bf);
	}
}

static char *ft_get_next_line(t_memo *memo)
{
	char	*result;
	int		i;

	result = NULL;
	if (memo->nl)
	{
		result = (char *) malloc (memo->nl - memo->s + 1);

		// make substr
		i = -1;
		while (++i < memo->nl - memo->s + 1)
			result[i] = memo->s[i];
		result[i] = 0;

		// keep rest then find and save next new line
		if (memo->s[i] != 0)
		{
			char	*tab;
			char	*next_nl;
			next_nl = NULL;

			tab = (char *) malloc(memo->nul - memo->nl);
			i = -1;
			while (memo->nl[++i + 1])
			{
				tab[i] = memo->nl[i + 1];
				if (tab[i] == '\n' && next_nl == NULL)
					next_nl = &tab[i];
			}
			tab[i] = 0;
			memo->nul = &tab[i];
			free (memo->s);
			memo->s = tab;
			memo->nl = next_nl;
		}
		else
		{
			memo->nl = NULL;
			free(memo->s);
			memo->s = NULL;
		}
	}

	else
	{
		result = memo->s;
		memo->s = NULL;		
	}

	return (result);
}

char	*get_next_line(int fd)
{
	// printf ("get_next_line called!\n");
	static t_memo	memo;

	if (fd < 0)
		return (NULL);
	memo.bf = (char *) malloc (BUFFER_SIZE + 1);
	if (!memo.bf)
		return (NULL);	
	if (!memo.nl)
		ft_find_nl(&memo, fd);
	free (memo.bf);
	memo.bf = NULL;
	if (memo.read_ret == -1)
	{
		if (memo.s)
			free (memo.s);
		memo.s = NULL;
	}
	if (!memo.s)
		return (NULL);
	return (ft_get_next_line(&memo));
}
