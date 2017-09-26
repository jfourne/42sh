/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 10:28:13 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/07 16:03:50 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITION_H
# define LINE_EDITION_H

# include "shell.h"
# include "term_mode.h"
# include "keys.h"
# include "manip_env.h"

# define MAX_LINE_LEN 4096

typedef struct	s_winsz
{
	size_t	row;
	size_t	col;
}				t_winsz;

typedef struct	s_line
{
	char	cmd[MAX_LINE_LEN];
	char	clipboard[MAX_LINE_LEN];
	t_dlist	*hist;
	size_t	cursor;
	size_t	length;
	size_t	hist_depth;
	size_t	hist_len;
	t_winsz	winsz;
	t_winsz	start;
	char	is_interactive;
	char	prompt;
}				t_line;

char			*line_edition(t_sh *sh);
int				get_startpos(t_line *line);

int				ft_putc(int c);
int				interactive_loop(t_line *line, int mode, t_sh *sh);
int				non_interactive_loop(t_line *line);
int				ft_getwinsz(t_winsz *winsz);

int				cut_line(t_line *line);
int				paste_line(t_line *line);

#endif
