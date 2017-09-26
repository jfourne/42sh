/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclamation_replace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 12:44:30 by jfourne           #+#    #+#             */
/*   Updated: 2017/06/13 14:09:49 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexerbis.h"

char			*search_hist_letter(char *line, t_replace *ex, t_sh *sh)
{
	t_dlist		*tmp;
	char		*replace;

	tmp = sh->hist;
	while (tmp)
	{
		if (ft_strncmp(line, tmp->content, ex->b - ex->a) == 0)
		{
			if ((replace = ft_strdup(tmp->content)) == NULL)
				ft_fatalerror(E_ALLOC);
			return (replace);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char			*search_last_cmd(t_sh *sh)
{
	t_dlist		*tmp;
	char		*replace;

	if (sh->hist)
	{
		tmp = sh->hist;
		if (tmp)
		{
			replace = ft_strdup(tmp->content);
			return (replace);
		}
	}
	return (NULL);
}

static char		*choose_exclamation(t_replace *ex, char *tmp, t_sh *sh)
{
	char		*replace;

	replace = NULL;
	ex->b = 0;
	if (tmp[ex->a] && tmp[ex->a] == '!')
	{
		replace = search_last_cmd(sh);
		ex->b = ex->a + 1;
	}
	else if (tmp[ex->a] && (ft_isdigit(tmp[ex->a]) || tmp[ex->a] == '-'))
	{
		ex->b = ex->a;
		while (tmp[ex->b] && (ft_isdigit(tmp[ex->b]) || tmp[ex->b] == '-'))
			ex->b++;
		replace = search_hist_nb(tmp + ex->a, sh);
	}
	else
		replace = choose_exclamation_next(ex, tmp, sh);
	replace = choose_exclamation_modifier(ex, tmp, sh, replace);
	ex->a--;
	return (replace);
}

int				exclamation_replace_check(char **line, t_replace *save,
											t_sh *sh)
{
	char		*replace;

	replace = choose_exclamation(save, *line, sh);
	if (replace == NULL)
		return (exclamation_error(*line, *save));
	save->i += ft_strlen(replace) - 1;
	replace_it(line, save, replace);
	return (EXIT_SUCCESS);
}

int				replace_exclamation(char **line, t_sh *sh)
{
	t_quot		bs;
	t_replace	save;

	ft_bzero(&bs, sizeof(t_quot));
	ft_bzero(&save, sizeof(t_replace));
	save.b = -2;
	while ((*line)[save.i])
	{
		exclamation_quote(*line, &bs, save.i);
		if ((*line)[save.i] && (*line)[save.i] == '!' && bs.sq == 0)
		{
			if (exclamation_backquote(&save, *line) == EXIT_SUCCESS)
			{
				if ((*line)[save.a] == '\0' || (*line)[save.a] == '"')
					return (-2);
				if (exclamation_replace_check(line, &save, sh) == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
		}
		save.i++;
	}
	if (save.b > -2)
		ft_putendl(*line);
	return (EXIT_SUCCESS);
}
