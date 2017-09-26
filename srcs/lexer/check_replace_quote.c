/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_replace_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 17:04:12 by jfourne           #+#    #+#             */
/*   Updated: 2017/06/13 15:52:18 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexerbis.h"

char			*quot(char **line, t_replace *save, char c, t_grab_all *grab)
{
	char		*replace;

	save->i += 1;
	save->a = save->i;
	save->b = save->i;
	while ((*line)[save->b])
	{
		if ((*line)[save->b] == c &&
			check_quote_end_backslash(grab, save->b - 1, c) == EXIT_SUCCESS)
			break ;
		save->b++;
	}
	if ((*line)[save->b] == '\0')
		return (NULL);
	if ((replace = ft_strndup(*line + save->a, save->b - save->a)) == NULL)
		ft_fatalerror(E_ALLOC);
	save->a--;
	save->b++;
	return (replace);
}

static int		dquote_free(t_grab_all *grab)
{
	if (*(grab->replace) == NULL)
	{
		free(*(grab->line));
		*(grab->line) = NULL;
	}
	return (EXIT_FAILURE);
}

static int		check_double_quot(t_grab_all *grab)
{
	if (grab->bs->sq == 0 &&
			(*(grab->line))[grab->save->i] &&
			(*(grab->line))[grab->save->i] == '"' && grab->bs->inib == 0 &&
			check_quote_end(grab, '"') == EXIT_SUCCESS)
	{
		grab->bs->dq = 1;
		if (!(*(grab->replace) = quot(grab->line, grab->save, '"', grab)))
			return (EXIT_FAILURE);
		if (ft_replace_recursive(grab->replace,
					grab->tokens, grab->sh, grab->bs) == EXIT_FAILURE)
			return (dquote_free(grab));
		grab->save->i += ft_strlen(*(grab->replace)) - 2;
		replace_it(grab->line, grab->save, *(grab->replace));
		grab->bs->dq = 0;
	}
	return (EXIT_SUCCESS);
}

int				check_simple_quot(t_grab_all *grab)
{
	if (grab->bs->dq == 0 &&
			(*(grab->line))[grab->save->i] &&
			(*(grab->line))[grab->save->i] == '\'' && grab->bs->inib == 0 &&
			check_quote_end(grab, '\'') == EXIT_SUCCESS)
	{
		grab->bs->sq = 1;
		if (!(*(grab->replace) = quot(grab->line, grab->save, '\'', grab)))
			return (EXIT_FAILURE);
		if (ft_replace_recursive(grab->replace,
					grab->tokens, grab->sh, grab->bs) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		grab->save->i += ft_strlen(*(grab->replace)) - 2;
		replace_it(grab->line, grab->save, *(grab->replace));
		grab->bs->sq = 0;
	}
	else if (check_double_quot(grab) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
