/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 14:42:28 by craffate          #+#    #+#             */
/*   Updated: 2017/06/16 15:24:52 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"
#include "lexer.h"
#include "sh_error.h"

/*
** Generates and returns an AST from the given token list
*/

t_ast	*generate_ast(t_sh *sh, t_tok *tokens)
{
	t_ast	*ast;
	t_tok	*tok;

	ast = NULL;
	sh->parsing_status = 0;
	if (!tokens || tokens->type == TOK_END)
		return (NULL);
	tok = tok_parsing(sh, tokens);
	if (!sh->parsing_status)
	{
		ast = ast_command(sh, &tokens);
		ast_browser(sh, ast);
		ft_astdel(ast);
	}
	else
		parse_error(tok);
	return (NULL);
}
