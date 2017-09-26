/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_startpos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 09:47:59 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/09 14:57:31 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "line_edition.h"
#include "fcntl.h"

/*
** Use of the escape code to get the position right after the prompt so that
** we can determine the offset needed for each letter.
*/

int		get_startpos(t_line *line)
{
	char	answer[20];
	int		i;

	ft_putstr_fd("\e[6n", STDIN_FILENO);
	ft_bzero(answer, 20);
	tcflush(STDIN_FILENO, TCIFLUSH);
	i = read(STDIN_FILENO, answer, 20);
	if (i <= 0)
		return (EXIT_FAILURE);
	answer[i] = '\0';
	i = 2;
	line->start.row = ft_atoi(answer + i);
	while (ft_isdigit(answer[i]))
		i++;
	line->start.col = ft_atoi(answer + i + 1);
	return (EXIT_SUCCESS);
}
