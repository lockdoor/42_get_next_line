/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 08:32:36 by pnamnil           #+#    #+#             */
/*   Updated: 2023/09/09 08:32:36 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_memo
{
	char	*s;
	char	*bf;
	char	*nl;
	char	*nul;
	int		read_ret;
	int		malloc_error;
	int		read_end;
}	t_memo;

char	*get_next_line(int fd);

// utils
int		ft_init_str(t_memo *memo);
int		ft_join_str(t_memo *memo);
void	ft_find_nl(t_memo *memo, int fd);
void	ft_keep_rest(t_memo *memo);
char	*ft_get_next_line(t_memo *memo);

#endif
