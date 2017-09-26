/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 09:27:03 by hdelaby           #+#    #+#             */
/*   Updated: 2017/05/03 13:24:30 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cursor_motion.h"

/*
** This set of fonctions ensures the good behaviour of cursor motion. That
** includes L/R arrows and home/end keys.
*/

int		cursor_to_end(t_line *line)
{
	line->cursor = line->length;
	return (set_curpos(line));
}

int		cursor_to_home(t_line *line)
{
	line->cursor = 0;
	return (set_curpos(line));
}

int		cursor_to_left(t_line *line)
{
	if (!line->cursor)
		return (EXIT_SUCCESS);
	line->cursor--;
	return (set_curpos(line));
}

int		cursor_to_right(t_line *line)
{
	if (line->cursor == line->length)
		return (EXIT_SUCCESS);
	line->cursor++;
	return (set_curpos(line));
}
