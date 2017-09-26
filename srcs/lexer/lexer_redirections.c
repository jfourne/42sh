/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 13:21:09 by hdelaby           #+#    #+#             */
/*   Updated: 2017/05/31 13:36:03 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lexerbis.h"
#include "token.h"

int		handle_inredir(t_sh *sh, t_token *tok, t_tok **lst)
{
	char	c;

	(void)sh;
	if (tok->type == TOK_ARG && !ft_isnumber(tok->str))
		end_token(tok, lst);
	tok->str[tok->index++] = '<';
	tok->type = TOK_INPUT;
	c = *tok->line;
	if (c == '>')
	{
		tok->str[tok->index++] = *tok->line++;
		tok->type = TOK_RDWR;
	}
	else if (c == '&')
	{
		tok->str[tok->index++] = *tok->line++;
		tok->type = TOK_LAS;
	}
	else if (c == '<')
	{
		tok->str[tok->index++] = *tok->line++;
		tok->type = TOK_HEREDOC;
	}
	return (end_token(tok, lst));
}

int		handle_outredir(t_sh *sh, t_token *tok, t_tok **lst)
{
	char	c;

	(void)sh;
	if (tok->type == TOK_ARG && !ft_isnumber(tok->str))
		end_token(tok, lst);
	tok->str[tok->index++] = '>';
	tok->type = TOK_OUTPUT;
	c = *tok->line;
	if (c == '>')
	{
		tok->str[tok->index++] = *tok->line++;
		tok->type = TOK_APPEND;
	}
	else if (c == '&')
	{
		tok->str[tok->index++] = *tok->line++;
		tok->type = TOK_UAS;
	}
	return (end_token(tok, lst));
}
