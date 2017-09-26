/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_motion_extra.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 13:20:33 by hdelaby           #+#    #+#             */
/*   Updated: 2017/04/27 13:41:38 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cursor_motion.h"

/*
** Set of functions to navigate between words or lines. Same behaviour than
** the normal set of cursor_motion.c
*/

int		goto_next_word(t_line *line)
{
	while (line->cmd[line->cursor] != ' ' && line->cursor != line->length)
		if (cursor_to_right(line))
			return (EXIT_FAILURE);
	while (line->cmd[line->cursor] == ' ' && line->cursor != line->length)
		if (cursor_to_right(line))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		goto_prev_word(t_line *line)
{
	if (line->cursor && line->cmd[line->cursor - 1] == ' ')
		if (cursor_to_left(line))
			return (EXIT_FAILURE);
	while (line->cmd[line->cursor] == ' ' && line->cursor)
		if (cursor_to_left(line))
			return (EXIT_FAILURE);
	while (line->cmd[line->cursor] != ' ' && line->cursor)
		if (cursor_to_left(line))
			return (EXIT_FAILURE);
	if (line->cursor)
		if (cursor_to_right(line))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		goto_next_line(t_line *line)
{
	line->cursor = line->cursor + line->winsz.col > line->length ?
		line->length : line->cursor + line->winsz.col;
	return (set_curpos(line));
}

int		goto_prev_line(t_line *line)
{
	line->cursor = line->cursor < line->winsz.col ? 0 : line->cursor -
		line->winsz.col;
	return (set_curpos(line));
}
