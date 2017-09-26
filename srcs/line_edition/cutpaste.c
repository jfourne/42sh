/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutpaste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 08:39:09 by hdelaby           #+#    #+#             */
/*   Updated: 2017/05/03 08:51:35 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include "input_keys.h"

int		cut_line(t_line *line)
{
	char	*clear_display;

	ft_strcpy(line->clipboard, line->cmd + line->cursor);
	ft_bzero(line->cmd + line->cursor, MAX_LINE_LEN - line->cursor - 1);
	line->length = line->cursor;
	if (!(clear_display = tgetstr("cd", NULL)))
		return (EXIT_FAILURE);
	tputs(clear_display, 0, &ft_putc);
	return (EXIT_SUCCESS);
}

int		paste_line(t_line *line)
{
	int		i;

	i = 0;
	while (line->clipboard[i])
		if (insert_char(line, line->clipboard[i++]))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
