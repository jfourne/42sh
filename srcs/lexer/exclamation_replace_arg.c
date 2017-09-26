/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclamation_replace_arg.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 12:23:07 by jfourne           #+#    #+#             */
/*   Updated: 2017/06/19 13:48:33 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexerbis.h"

char			*search_last_arg(t_sh *sh, char *replace, t_tok *save)
{
	t_tok		*tmp;
	t_tok		*tokens;

	if (replace == NULL)
	{
		if ((replace = search_last_cmd(sh)) == NULL)
			return (NULL);
	}
	tokens = lexer(sh, replace);
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TOK_ARG)
			save = tmp;
		tmp = tmp->next;
	}
	if (save == NULL)
	{
		ft_tokdel(tokens);
		return (NULL);
	}
	replace = ft_strdup(save->lex);
	ft_tokdel(tokens);
	return (replace);
}

char			*search_first_arg(t_sh *sh, char *replace)
{
	t_tok		*tmp;
	t_tok		*tokens;

	if (replace == NULL)
	{
		if ((replace = search_last_cmd(sh)) == NULL)
			return (NULL);
	}
	tokens = lexer(sh, replace);
	tmp = tokens;
	while (tmp && tmp->type != TOK_ARG)
		tmp = tmp->next;
	if (tmp == NULL)
	{
		ft_tokdel(tokens);
		return (NULL);
	}
	replace = ft_strdup(tmp->lex);
	ft_tokdel(tokens);
	return (replace);
}

char			*choose_exclamation_modifier(t_replace *ex, char *tmp,
						t_sh *sh, char *replace)
{
	if ((tmp[ex->a] && tmp[ex->a] == '$') ||
			((ex->b != 0) && tmp[ex->b] == '$'))
	{
		sh->is_interactive = 0;
		replace = search_last_arg(sh, replace, NULL);
		(ex->b == 0) ? (ex->b = ex->a + 1) : (ex->b += 1);
		sh->is_interactive = 1;
	}
	else if ((tmp[ex->a] && tmp[ex->a] == '^') ||
				((ex->b != 0) && tmp[ex->b] == '^'))
	{
		sh->is_interactive = 0;
		replace = search_first_arg(sh, replace);
		(ex->b == 0) ? (ex->b = ex->a + 1) : (ex->b += 1);
		sh->is_interactive = 1;
	}
	return (replace);
}

char			*choose_exclamation_next(t_replace *ex, char *tmp, t_sh *sh)
{
	char		*replace;

	replace = NULL;
	if (tmp[ex->a] && (ft_isalnum(tmp[ex->a]) || tmp[ex->a] == '/'))
	{
		ex->b = ex->a;
		while (tmp[ex->b] && (ft_isalnum(tmp[ex->b]) || tmp[ex->b] == '/'))
			ex->b++;
		replace = search_hist_letter(tmp + ex->a, ex, sh);
	}
	return (replace);
}
