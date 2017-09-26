/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 11:09:00 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/13 13:47:49 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "lexerbis.h"
#include "ast.h"

int		handle_and(t_sh *sh, t_token *tok, t_tok **lst)
{
	(void)sh;
	end_token(tok, lst);
	tok->type = TOK_BG;
	if (*tok->line == '&')
	{
		tok->line++;
		tok->type = TOK_AND;
	}
	return (end_token(tok, lst));
}

int		handle_pipe(t_sh *sh, t_token *tok, t_tok **lst)
{
	(void)sh;
	end_token(tok, lst);
	tok->type = TOK_PIPE;
	if (*tok->line == '|')
	{
		tok->line++;
		tok->type = TOK_OR;
	}
	return (end_token(tok, lst));
}

int		handle_semico(t_sh *sh, t_token *tok, t_tok **lst)
{
	(void)sh;
	end_token(tok, lst);
	tok->type = TOK_SC;
	return (end_token(tok, lst));
}

int		handle_space(t_sh *sh, t_token *tok, t_tok **lst)
{
	(void)sh;
	return (end_token(tok, lst));
}

int		handle_hashtag(t_sh *sh, t_token *tok, t_tok **lst)
{
	handle_space(sh, tok, lst);
	return (42);
}
