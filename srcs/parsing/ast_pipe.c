/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 15:22:55 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/02 16:25:45 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/*
** Adds a pipe to the AST
*/

t_ast	*ast_pipe(t_sh *sh, t_tok **tokens)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*node;

	if (!sh->parsing_status &&
	(left = ast_arg(sh, tokens)) && (*tokens)->type == TOK_PIPE)
	{
		tok_pacman(tokens);
		if (!(right = ast_pipe(sh, tokens)))
		{
			sh->parsing_status = PARSE_ERROR;
			ft_astdel(left);
			return (NULL);
		}
		if (!(node = ast_node(TOK_PIPE, left, right)))
			free_nodes(&left, &right);
		return (node);
	}
	return (!sh->parsing_status ? left : NULL);
}
