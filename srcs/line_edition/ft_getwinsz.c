/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getwinsz.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 09:28:32 by hdelaby           #+#    #+#             */
/*   Updated: 2017/04/27 09:29:59 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include <sys/ioctl.h>
#include <stdlib.h>

/*
** Ioctl request to get window size. Result is stored in structure s_winsz.
** Returns EXIT_FAILURE on failure.
*/

int		ft_getwinsz(t_winsz *winsz)
{
	struct winsize	w;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) && ioctl(STDIN_FILENO, TIOCGWINSZ,
				&w))
		return (EXIT_FAILURE);
	winsz->col = w.ws_col;
	winsz->row = w.ws_row;
	return (EXIT_SUCCESS);
}
