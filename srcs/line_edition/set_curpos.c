/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_curpos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 11:26:15 by hdelaby           #+#    #+#             */
/*   Updated: 2017/05/16 11:46:02 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cursor_motion.h"

/*
** These two functions allow proper cursor movement based on window's width
** and height. We force the scroll as well in case we have no room to display
** next line.
** Behaviour is quite simple to understand otherwise.
*/

static int	solve_scroll(t_line *line)
{
	size_t	xpos;
	size_t	ypos;
	char	*scroll;

	if (!line->winsz.col)
		return (EXIT_FAILURE);
	xpos = line->start.col + line->length % line->winsz.col;
	ypos = line->start.row + line->length / line->winsz.col;
	if (xpos > line->winsz.col)
		ypos++;
	if (ypos > line->winsz.row)
	{
		ypos--;
		line->start.row--;
		if (!(scroll = tgetstr("sf", NULL)))
			return (EXIT_FAILURE);
		tputs(scroll, 0, &ft_putc);
	}
	return (EXIT_SUCCESS);
}

int			set_curpos(t_line *line)
{
	size_t	xpos;
	size_t	ypos;
	char	*move;

	if (!line->winsz.col || solve_scroll(line))
		return (EXIT_FAILURE);
	xpos = line->start.col + line->cursor % line->winsz.col;
	ypos = line->start.row + line->cursor / line->winsz.col;
	if (xpos > line->winsz.col)
	{
		xpos %= line->winsz.col;
		ypos++;
	}
	if (!(move = tgetstr("cm", NULL))
			|| !(move = tgoto(move, xpos - 1, ypos - 1)))
		return (EXIT_FAILURE);
	tputs(move, 0, &ft_putc);
	return (EXIT_SUCCESS);
}
