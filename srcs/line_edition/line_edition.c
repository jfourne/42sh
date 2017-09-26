/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 10:31:05 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/23 14:56:37 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edition.h"
#include "input_keys.h"
#include "cursor_motion.h"
#include "history.h"
#include "autocompletion.h"

void			display_prompt(t_sh *sh, int to_free)
{
	char		*pwd;
	char		*to_disp;

	if ((pwd = ft_getenv("PWD", sh->env)))
		to_free = 0;
	else if ((pwd = getcwd(NULL, 0)))
		to_free = 1;
	else
		pwd = "";
	if (!sh->status)
		ft_putstr_fd("\e[1m\e[32m\u25CF ", STDERR_FILENO);
	else
		ft_putstr_fd("\e[1m\e[31m\u25CF ", STDERR_FILENO);
	to_disp = ft_strrchr(pwd, '/');
	ft_putstr_fd("\e[34m", STDERR_FILENO);
	if (!to_disp)
		ft_putstr_fd(pwd, STDERR_FILENO);
	else if (to_disp == pwd)
		ft_putstr_fd(to_disp, STDERR_FILENO);
	else
		ft_putstr_fd(to_disp + 1, STDERR_FILENO);
	if (to_free)
		free(pwd);
	ft_putstr_fd(" \e[0m", STDERR_FILENO);
}

/*
** Here we have to handle 2 different scenarios. Either STDIN is a tty and
** thus we must read and write the keys pressed by the user, or STDIN is not a
** tty and we must only read and not write.
*/

static int		auxiliary(t_sh *sh, t_line *line, int *ret)
{
	if (raw_term_mode() || get_startpos(line))
		return (-1);
	line->hist = sh->hist;
	line->hist_len = ft_dlstsize(line->hist);
	*ret = interactive_loop(line, *ret, sh);
	if (default_term_mode())
		return (-1);
	return (0);
}

char			*line_edition(t_sh *sh)
{
	t_line		line;
	int			ret;

	ret = 21;
	ft_bzero(&line, sizeof(line));
	line.is_interactive = sh->is_interactive;
	line.prompt = 1;
	if (sh->is_interactive)
	{
		while (ret > EXIT_FAILURE)
		{
			if (sh->prompt)
				display_prompt(sh, 0);
			if (auxiliary(sh, &line, &ret))
				return (NULL);
			if (ret != 42)
				clean_history(&line);
		}
	}
	else
	{
		if (non_interactive_loop(&line) == -42)
			return (NULL);
	}
	return (ret != EXIT_FAILURE ? ft_strdup(line.cmd) : NULL);
}
