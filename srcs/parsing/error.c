/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 12:17:09 by craffate          #+#    #+#             */
/*   Updated: 2017/06/12 14:18:06 by robechon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	parse_error(t_tok *token)
{
	ft_putstr_fd("42sh: syntax error near unexpected token `", 2);
	if (token->type != TOK_END)
	{
		if (token->type == TOK_AND)
			ft_putstr_fd("&&", 2);
		else if (token->type == TOK_OR)
			ft_putstr_fd("||", 2);
		else if (token->type == TOK_SC)
			ft_putstr_fd(";", 2);
		else if (token->type == TOK_PIPE)
			ft_putstr_fd("|", 2);
		else if (token->type == TOK_BG)
			ft_putstr_fd("&", 2);
		else
			ft_putstr_fd(token->lex, 2);
	}
	else
		ft_putstr_fd("newline", 2);
	ft_putendl_fd("'", 2);
}
