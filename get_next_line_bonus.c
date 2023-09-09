/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 09:08:05 by pnamnil           #+#    #+#             */
/*   Updated: 2023/09/09 09:23:37 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <sys/select.h>

/*This code pass Tripouille test case in 120000 micro sec*/
char	*get_next_line(int fd)
{
	static t_memo	memo[FD_SETSIZE + 1];

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	memo[fd].bf = (char *) malloc (BUFFER_SIZE + 1);
	if (!memo[fd].bf)
		return (NULL);
	if (!memo[fd].nl)
		ft_find_nl(&memo[fd], fd);
	free (memo[fd].bf);
	if (memo[fd].read_ret == -1)
	{
		if (memo[fd].s)
			free (memo[fd].s);
		memo[fd].s = NULL;
	}
	if (!memo[fd].s)
		return (NULL);
	return (ft_get_next_line(&memo[fd]));
}
