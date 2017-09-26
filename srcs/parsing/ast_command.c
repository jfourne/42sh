/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 15:23:10 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/01 09:09:36 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"

/*
** Adds a simple command to the AST
*/

t_ast	*ast_command(t_sh *sh, t_tok **tokens)
{
	t_ast	*left;
	t_ast	*right;

	if (!sh->parsing_status &&
	(left = ast_and_or(sh, tokens, 0)) && (*tokens)->type == TOK_SC)
	{
		tok_pacman(tokens);
		ast_browser(sh, left);
		if (!(right = ast_command(sh, tokens)))
		{
			ft_astdel(left);
			if (!((*tokens)->type == TOK_END) &&
					(sh->parsing_status = PARSE_ERROR))
				return (NULL);
			return (blank_node());
		}
		ast_browser(sh, right);
		ft_astdel(left);
		ft_astdel(right);
		return (blank_node());
	}
	return ((sh->parsing_status != PARSE_ERROR) ? left : NULL);
}
