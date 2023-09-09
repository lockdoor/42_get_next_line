/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 08:32:57 by pnamnil           #+#    #+#             */
/*   Updated: 2023/09/09 08:32:57 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*This code pass Tripouille test case in 120000 micro sec*/
char	*get_next_line(int fd)
{
	static t_memo	memo;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	memo.bf = (char *) malloc (BUFFER_SIZE + 1);
	if (!memo.bf)
		return (NULL);
	if (!memo.nl)
		ft_find_nl(&memo, fd);
	free (memo.bf);
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
