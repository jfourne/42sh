/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edition_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robechon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 14:05:42 by robechon          #+#    #+#             */
/*   Updated: 2017/06/13 09:43:20 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include "input_keys.h"
#include "cursor_motion.h"
#include "history.h"
#include "autocompletion.h"

static int	match_keys(t_line *line, int key)
{
	int					i;
	static t_motiontab	mtab[12] = {
		{KEY_RIGHT, &cursor_to_right},
		{KEY_LEFT, &cursor_to_left},
		{KEY_HOME, &cursor_to_home},
		{KEY_END, &cursor_to_end},
		{KEY_SRIGHT, &goto_next_word},
		{KEY_SLEFT, &goto_prev_word},
		{KEY_SPREVIOUS, &goto_prev_line},
		{KEY_SNEXT, &goto_next_line},
		{KEY_UP, &old_hist_entry},
		{KEY_DOWN, &new_hist_entry},
		{KEY_DL, &cut_line},
		{KEY_IL, &paste_line}
	};

	i = 0;
	while (i < 12)
		if (key == mtab[i++].key)
			return (mtab[i - 1].p(line));
	return (EXIT_SUCCESS);
}

int			non_interactive_loop(t_line *line)
{
	int		key;

	while ((key = read_input()))
	{
		if (key > 31 && key < 127)
			insert_char(line, key);
		if (key == 10)
			break ;
	}
	return (!key ? -42 : EXIT_SUCCESS);
}

static void	reset_line(t_line *line, int mode)
{
	if (mode == 42)
	{
		ft_putstr_fd(line->cmd, STDIN_FILENO);
		set_curpos(line);
	}
	else if (mode == 21)
	{
		ft_bzero(&line->cmd, MAX_LINE_LEN);
		line->cursor = 0;
		line->length = 0;
		line->hist_depth = 0;
		line->hist = ft_dlstgethead(line->hist);
	}
}

static int	special_keys(t_line *line, int key, t_sh *sh)
{
	if (key == 10)
	{
		cursor_to_end(line);
		ft_putchar('\n');
		return (EXIT_SUCCESS);
	}
	if (key == 4)
	{
		if (ctrld_key(line) == 42)
			return (EXIT_SUCCESS);
	}
	if (key == 9)
	{
		if (autocompletion(line, sh))
			return (42);
	}
	if (key == 3)
	{
		ft_putchar_fd('\n', STDIN_FILENO);
		sh->status = 1;
		return (21);
	}
	return (-42);
}

int			interactive_loop(t_line *line, int mode, t_sh *sh)
{
	int		key;
	int		ret;

	reset_line(line, mode);
	if (mode == 21 && !line->prompt)
		return (EXIT_FAILURE);
	line->prompt = sh->prompt;
	while ((key = read_input()))
	{
		ft_getwinsz(&line->winsz);
		if (key > 31 && key < 127)
			insert_char(line, key);
		if (key == KEY_DC || key == 127)
			delete_char(line, key);
		if ((ret = special_keys(line, key, sh)) != -42)
			return (ret);
		match_keys(line, key);
	}
	return (!key ? EXIT_FAILURE : EXIT_SUCCESS);
}
