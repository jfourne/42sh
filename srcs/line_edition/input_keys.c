/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 12:04:31 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/05 10:55:14 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_keys.h"
#include "cursor_motion.h"
#include "line_edition.h"

int		insert_word(t_line *line, char *word)
{
	while (*word)
		if (insert_char(line, *word++))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		insert_char(t_line *line, int key)
{
	if (line->length + 1 >= MAX_LINE_LEN)
		return (EXIT_SUCCESS);
	ft_memmove(line->cmd + line->cursor + 1, line->cmd + line->cursor,
			MAX_LINE_LEN - line->cursor - 1);
	line->cmd[line->cursor] = key;
	line->length++;
	line->cursor++;
	if (line->is_interactive)
	{
		ft_putstr_fd(line->cmd + line->cursor - 1, STDIN_FILENO);
		return (set_curpos(line));
	}
	return (EXIT_SUCCESS);
}

int		delete_char(t_line *line, int key)
{
	char	*erase_line;

	if (key == 127 && !line->cursor)
		return (EXIT_SUCCESS);
	if (key == 127)
		cursor_to_left(line);
	if (line->cursor == line->length)
		return (EXIT_SUCCESS);
	ft_memmove(line->cmd + line->cursor, line->cmd + line->cursor + 1,
			MAX_LINE_LEN - line->cursor - 1);
	line->length--;
	if (!(erase_line = tgetstr("cd", NULL)))
		return (EXIT_FAILURE);
	tputs(erase_line, 0, &ft_putc);
	ft_putstr_fd(line->cmd + line->cursor, STDIN_FILENO);
	return (set_curpos(line));
}

int		ctrld_key(t_line *line)
{
	if (!line->prompt)
		return (0);
	if (!line->length)
	{
		ft_strcpy(line->cmd, "exit");
		ft_putendl(line->cmd);
		return (42);
	}
	else
		return (delete_char(line, KEY_DC));
}
