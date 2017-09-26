/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_motion.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 08:53:00 by hdelaby           #+#    #+#             */
/*   Updated: 2017/04/27 13:36:59 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURSOR_MOTION_H
# define CURSOR_MOTION_H

# include "line_edition.h"
# include <curses.h>
# include <term.h>

typedef struct	s_motiontab
{
	int		key;
	int		(*p)(t_line *line);
}				t_motiontab;

int				set_curpos(t_line *line);
int				cursor_to_end(t_line *line);
int				cursor_to_home(t_line *line);
int				cursor_to_left(t_line *line);
int				cursor_to_right(t_line *line);
int				goto_next_word(t_line *line);
int				goto_prev_word(t_line *line);
int				goto_next_line(t_line *line);
int				goto_prev_line(t_line *line);

#endif
