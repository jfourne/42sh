/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_replace_others.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 16:51:06 by jfourne           #+#    #+#             */
/*   Updated: 2017/06/13 10:42:03 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char		*dollar_replace(t_replace *save, char *line, t_sh *sh)
{
	char		*var;
	char		*find_in_env;
	char		*replace;

	save->b = save->a + 1;
	if (line[save->b] && line[save->b] == '?')
	{
		save->b++;
		return (ft_itoa(sh->status));
	}
	while (line[save->b] && (ft_isalnum(line[save->b]) || line[save->b] == '_'))
		save->b++;
	if ((var = ft_strndup(line + save->a + 1, save->b - save->a - 1)) == NULL)
		return (NULL);
	if ((find_in_env = ft_getenv(var, sh->env)) == NULL
			&& (find_in_env = ft_getenv(var, sh->local)) == NULL)
	{
		free(var);
		return (NULL);
	}
	if (var)
		free(var);
	if ((replace = ft_strdup(find_in_env)) == NULL)
		ft_fatalerror(E_ALLOC);
	return (replace);
}

static int		not_found_dollar(char **line, t_replace *save)
{
	char		*replace;

	if (save->a == 0 && (*line)[save->b] == '\0')
	{
		free(*line);
		*line = NULL;
	}
	else
	{
		replace = ft_strdup("");
		replace_it(line, save, replace);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

static int		check_dollar(char **line, t_replace *save, t_sh *sh)
{
	int			count;
	char		*replace;

	save->a = save->i;
	replace = NULL;
	count = 0;
	if ((*line)[save->a + 1] && (*line)[save->a + 1] != '\'')
	{
		save->b = save->i - 1;
		replace = dollar_replace(save, *line, sh);
		if (replace == NULL)
			return (not_found_dollar(line, save));
		save->i += ft_strlen(replace) - 1;
		replace_it(line, save, replace);
	}
	return (EXIT_SUCCESS);
}

static int		check_tilt(char **line, t_replace *save, t_sh *sh)
{
	char		*replace;

	replace = NULL;
	if ((*line)[save->i + 1] == '\0' || (*line)[save->i + 1] == '/')
	{
		save->a = save->i - 1;
		if ((replace = ft_getenv("HOME", sh->env)) == NULL)
			return (EXIT_FAILURE);
		if ((replace = ft_strdup(replace)) == NULL)
			ft_fatalerror(E_ALLOC);
		if (replace != NULL)
		{
			save->a = save->i;
			save->b = save->i + 1;
			save->i += ft_strlen(replace) - 1;
			replace_it(line, save, replace);
		}
	}
	return (EXIT_SUCCESS);
}

int				check_others(char **line, t_replace *save, t_sh *sh,
		t_quot *bs)
{
	if (bs->sq == 0 && bs->inib == 0 &&
			(*line)[save->i] && (*line)[save->i] == '$')
	{
		if (check_dollar(line, save, sh) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (bs->sq == 0 && bs->dq == 0 && bs->inib == 0 &&
			(*line)[save->i] &&
			(*line)[save->i] == '~')
	{
		if (check_tilt(line, save, sh) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (*line == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
