/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 10:48:12 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/12 10:35:36 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "input_keys.h"

/*
** This lot of functions handles the history functionaly of our line edition.
**
** Only trick we use is that we set content_size of our entry to SPE_LINE_LEN
** to indicate that it is the first command incomplete before accessing the
** history.
*/

static int	feed_line(t_line *line, char *entry)
{
	char	*clear_display;

	ft_putchar('z');
	if (cursor_to_home(line) || !(clear_display = tgetstr("cd", NULL)))
		return (EXIT_FAILURE);
	tputs(clear_display, 0, &ft_putc);
	ft_bzero(line->cmd, MAX_LINE_LEN);
	line->length = 0;
	line->cursor = 0;
	while (*entry)
		if (insert_char(line, *entry++))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			new_hist_entry(t_line *line)
{
	if (!line->hist || (line->hist && !line->hist_depth) || !line->hist->prev)
		return (EXIT_SUCCESS);
	line->hist_depth--;
	line->hist = line->hist->prev;
	if (feed_line(line, line->hist->content))
		return (EXIT_FAILURE);
	if (!line->hist_depth)
		ft_dlstremovenode(&line->hist);
	return (EXIT_SUCCESS);
}

int			old_hist_entry(t_line *line)
{
	t_dlist *new_node;

	if (!line->hist || (line->hist && line->hist_depth == line->hist_len))
		return (EXIT_SUCCESS);
	if (!line->hist_depth)
	{
		new_node = ft_dlstnew(line->cmd, ft_strlen(line->cmd) + 1);
		if (!new_node)
			return (EXIT_FAILURE);
		new_node->content_size = SPE_LINE_LEN;
		ft_dlstadd(&line->hist, new_node);
	}
	line->hist = line->hist->next;
	line->hist_depth++;
	if (feed_line(line, line->hist->content))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			clean_history(t_line *line)
{
	line->hist = ft_dlstgethead(line->hist);
	if (line->hist && line->hist->content_size == SPE_LINE_LEN)
		ft_dlstremovenode(&line->hist);
	return (EXIT_SUCCESS);
}
