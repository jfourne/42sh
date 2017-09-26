/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 10:57:28 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/13 13:49:29 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "lexerbis.h"
#include "ast.h"
#include "sh_error.h"

static int	final_token(t_token *tok, t_tok **lst)
{
	tok->type = TOK_END;
	return (end_token(tok, lst));
}

static int	handle_others(t_sh *sh, char c, t_token *tok, t_tok **lst)
{
	(void)sh;
	(void)lst;
	tok->type = TOK_ARG;
	token_add_char(tok, c);
	return (0);
}

static int	match_table(t_sh *sh, char c, t_token *tok, t_tok **lst)
{
	int				i;
	static t_lextab	ltab[11] = {
		{' ', &handle_space},
		{';', &handle_semico},
		{'|', &handle_pipe},
		{'&', &handle_and},
		{'<', &handle_inredir},
		{'>', &handle_outredir},
		{'\"', &handle_dquote},
		{'\'', &handle_squote},
		{'\\', &handle_backslash},
		{'`', &handle_backquote},
		{'#', &handle_hashtag}
	};

	i = 0;
	while (i < 11)
	{
		if (c == ltab[i++].key)
			return (ltab[i - 1].fct(sh, tok, lst));
	}
	return (handle_others(sh, c, tok, lst));
}

static int	pre_check(char *line, t_token *tok, t_sh *sh)
{
	if (is_blank(line))
	{
		free(line);
		return (1);
	}
	if (replace_exclamation(&line, sh) == EXIT_FAILURE)
	{
		free(line);
		return (1);
	}
	replace_newline(line);
	ft_bzero(tok, sizeof(t_token));
	tok->line = line;
	tok->ptr = line;
	return (0);
}

t_tok		*lexer(t_sh *sh, char *line)
{
	t_token	tok;
	t_tok	*lst;
	int		ret;

	ret = 0;
	lst = NULL;
	if (pre_check(line, &tok, sh))
		return (NULL);
	while (*tok.line && !ret)
		ret = match_table(sh, *tok.line++, &tok, &lst);
	end_token(&tok, &lst);
	final_token(&tok, &lst);
	if ((ret && ret != 42) || handle_hdoc(lst, sh))
	{
		ft_tokdel(lst);
		lst = NULL;
	}
	if (sh->is_interactive)
		add_history(sh, tok.ptr);
	free(tok.ptr);
	return (lst);
}
