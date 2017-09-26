/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_and_or.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 15:22:15 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/07 14:59:04 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"

static t_ast	*node_error(t_sh *sh, t_ast *left)
{
	sh->parsing_status = PARSE_ERROR;
	ft_astdel(left);
	return (NULL);
}

/*
** Adds an AND or OR gate to the AST
*/

t_ast			*ast_and_or(t_sh *sh, t_tok **tokens, int mode)
{
	t_ast	*left;
	t_ast	*right;
	short	type;

	right = NULL;
	if (!sh->parsing_status && (left = ast_pipe(sh, tokens)) &&
	((*tokens)->type == TOK_OR || (*tokens)->type == TOK_AND))
	{
		type = (*tokens)->type;
		tok_pacman(tokens);
		if (mode == NODE_NEUTRAL || (mode == NODE_AND && !sh->status) ||
		(mode == NODE_OR && sh->status))
			ast_browser(sh, left);
		if (type == TOK_AND)
			right = ast_and_or(sh, tokens, NODE_AND);
		else if (type == TOK_OR)
			right = ast_and_or(sh, tokens, NODE_OR);
		if (!right)
			node_error(sh, left);
		if ((type == TOK_AND && !sh->status) || (type == TOK_OR && sh->status))
			ast_browser(sh, right);
		free_nodes(&left, &right);
		return (blank_node());
	}
	return (!sh->parsing_status ? left : NULL);
}
