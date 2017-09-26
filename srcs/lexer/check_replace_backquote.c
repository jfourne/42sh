/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_replace_backquote.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 10:30:13 by jfourne           #+#    #+#             */
/*   Updated: 2017/06/20 11:43:57 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexerbis.h"

static void		bquot_move_tokens(t_grab_all *grab, t_tok *tmp)
{
	t_tok		*move;
	t_tok		*last;

	grab->save->i += ft_strlen(*(grab->replace)) - 2;
	replace_it(grab->line, grab->save, *(grab->replace));
	if (grab->bs->dq != 0)
		return ;
	move = (*(grab->tokens))->next;
	last = tmp;
	while (tmp && tmp->next && tmp->next->type != TOK_END)
		tmp = tmp->next;
	free(tmp->next->lex);
	free(tmp->next);
	tmp->next = move;
	(*(grab->tokens))->next = last->next;
	free(last->lex);
	free(last);
	grab->sh->is_interactive = 1;
}

static void		reset_line(t_grab_all *grab)
{
	free(*(grab->line));
	*(grab->line) = NULL;
	grab->save->i -= 2;
}

static int		found_bquot(t_grab_all *grab)
{
	if (!(*(grab->replace) = quot(grab->line, grab->save, '`', grab)))
		return (EXIT_FAILURE);
	if ((*(grab->replace) = replace_backquote(*(grab->replace), grab->sh))
			== NULL)
	{
		if (grab->save->a == 0 && (*(grab->line))[grab->save->b] == '\0' &&
				grab->save->i == 1)
			reset_line(grab);
		else
		{
			*(grab->replace) = ft_strdup("");
			replace_it(grab->line, grab->save, *(grab->replace));
			grab->save->i -= 2;
			return (2);
		}
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int				check_bquot(t_grab_all *grab, int ret, t_tok *tmp)
{
	if (grab->bs->sq == 0 && grab->bs->inib == 0 &&
		(*(grab->line))[grab->save->i] && (*(grab->line))[grab->save->i] == '`'
		&& check_quote_end(grab, '`') == EXIT_SUCCESS)
	{
		grab->bs->bq = 1;
		if ((ret = found_bquot(grab)) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (ret == 2)
			return (EXIT_SUCCESS);
		if (grab->bs->dq == 0)
		{
			grab->sh->is_interactive = 0;
			if ((tmp = lexer(grab->sh, *(grab->replace))) == NULL)
			{
				grab->sh->is_interactive = 1;
				return (EXIT_FAILURE);
			}
			if ((*(grab->replace) = ft_strdup(tmp->lex)) == NULL)
				return (EXIT_FAILURE);
		}
		bquot_move_tokens(grab, tmp);
		grab->bs->bq = 0;
	}
	return (EXIT_SUCCESS);
}
