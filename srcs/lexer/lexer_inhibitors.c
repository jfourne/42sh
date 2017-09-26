/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_inhibitors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 14:15:59 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/13 12:58:46 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "lexerbis.h"
#include "ast.h"

int		handle_backquote(t_sh *sh, t_token *tok, t_tok **lst)
{
	(void)sh;
	(void)lst;
	tok->type = TOK_ARG;
	token_add_char(tok, '`');
	while (42)
	{
		if (*tok->line == '`')
			break ;
		if (*tok->line)
			token_add_char(tok, *tok->line++);
		else
		{
			if (complete_command(sh, tok, "backquote"))
				return (1);
		}
	}
	token_add_char(tok, *tok->line++);
	return (0);
}

int		handle_backslash(t_sh *sh, t_token *tok, t_tok **lst)
{
	int		ret;

	ret = 0;
	(void)sh;
	(void)lst;
	tok->type = TOK_ARG;
	token_add_char(tok, '\\');
	if (is_blank(tok->line))
	{
		while ((ret = complete_command(sh, tok, "backslash")))
		{
			if (ret == 1)
				return (1);
		}
	}
	token_add_char(tok, *tok->line++);
	return (0);
}

int		handle_dquote(t_sh *sh, t_token *tok, t_tok **lst)
{
	(void)sh;
	(void)lst;
	tok->type = TOK_ARG;
	token_add_char(tok, '\"');
	while (42)
	{
		if (*tok->line == '\"')
			break ;
		if (*tok->line == '\\')
			token_add_char(tok, *tok->line++);
		if (*tok->line)
			token_add_char(tok, *tok->line++);
		else
		{
			if (complete_command(sh, tok, "dquote"))
				return (1);
		}
	}
	token_add_char(tok, *tok->line++);
	return (0);
}

int		handle_squote(t_sh *sh, t_token *tok, t_tok **lst)
{
	(void)sh;
	(void)lst;
	tok->type = TOK_ARG;
	token_add_char(tok, '\'');
	while (42)
	{
		if (*tok->line == '\'')
			break ;
		if (*tok->line)
			token_add_char(tok, *tok->line++);
		else
		{
			if (complete_command(sh, tok, "squote"))
				return (1);
		}
	}
	token_add_char(tok, *tok->line++);
	return (0);
}
