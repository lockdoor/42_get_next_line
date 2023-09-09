/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 09:11:35 by pnamnil           #+#    #+#             */
/*   Updated: 2023/09/09 09:12:00 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* 
** init memo->s with memo->bf
** find new line and set it to memo->nl
** set null of memo->s to memo->null
*/
void	ft_init_str(t_memo *memo)
{
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
}

/* 
** join memo->s with memo->bf
** find new line and set it to memo->nl
** set null of memo->s to memo->null
** set memo->s with new string joined and free old memo->s
*/
void	ft_join_str(t_memo *memo)
{
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
	while (++i < (int) memo->read_ret)
	{
		tab[i + s_len] = memo->bf[i];
		if (tab[i + s_len] == '\n' && memo->nl == NULL)
			memo->nl = &tab[i + s_len];
	}
	tab[i + s_len] = 0;
	free (memo->s);
	memo->nul = &tab[i + s_len];
	memo->s = tab;
}

/*
** read file to buffer (memo->bf)
** if memo->s == NULL, init string to memo->s
** else join memo->s with memo->bf
*/
void	ft_find_nl(t_memo *memo, int fd)
{
	while (!memo->nl)
	{
		memo->read_ret = read(fd, memo->bf, BUFFER_SIZE);
		if (memo->read_ret < 1)
			break ;
		(memo->bf)[memo->read_ret] = 0;
		if (!memo->s)
			ft_init_str (memo);
		else
			ft_join_str (memo);
	}
}

void	ft_keep_rest(t_memo *memo)
{
	char	*rest;
	char	*next_nl;
	int		i;

	next_nl = NULL;
	rest = (char *) malloc(memo->nul - memo->nl);
	i = -1;
	while (memo->nl[++i + 1])
	{
		rest[i] = memo->nl[i + 1];
		if (rest[i] == '\n' && next_nl == NULL)
			next_nl = &rest[i];
	}
	rest[i] = 0;
	memo->nul = &rest[i];
	free (memo->s);
	memo->s = rest;
	memo->nl = next_nl;
}

/*
** This fn is get string with new line from memo->s
** If have rest of memo->s use ft_keep_rest to make new memo->s
** If not have new line, this file is read to eof from ft_find_nl
** it return memo->s then set memo->s = NULL
*/
char	*ft_get_next_line(t_memo *memo)
{
	char	*result;
	int		i;

	if (memo->nl)
	{
		result = (char *) malloc (memo->nl - memo->s + 2);
		i = -1;
		while (++i < memo->nl - memo->s + 1)
			result[i] = memo->s[i];
		result[i] = 0;
		if (memo->s[i] != 0)
			ft_keep_rest(memo);
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
