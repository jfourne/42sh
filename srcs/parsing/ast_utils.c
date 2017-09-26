/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:23:47 by craffate          #+#    #+#             */
/*   Updated: 2017/06/07 16:07:46 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "sh_error.h"

/*
** Checks if a token is a redirection
** Returns 0 if it isn't
*/

int		isredir(const short type)
{
	return (type == TOK_INPUT || type == TOK_OUTPUT ||
		type == TOK_HEREDOC || type == TOK_APPEND ||
		type == TOK_UAS || type == TOK_LAS ||
		type == TOK_RDWR || type == TOK_NOGLOB ? 1 : 0);
}

/*
** ᗧ token->token->token->token...
*/

t_tok	**tok_pacman(t_tok **tokens)
{
	t_tok	*tmp;

	tmp = *tokens;
	if ((*tokens)->next)
		*tokens = (*tokens)->next;
	return (tokens);
}

/*
** Generates a node for the AST as long as you feed it the correct arguments
** If there's no redirection, redir should be NULL
*/

t_ast	*ast_node(const short type, t_ast *left, t_ast *right)
{
	t_ast	*node;

	if (!(node = (t_ast *)malloc(sizeof(t_ast))))
		ft_fatalerror(E_ALLOC);
	node->args = NULL;
	node->redir = NULL;
	node->type = type;
	node->left = left;
	node->right = right;
	return (node);
}

t_ast	*blank_node(void)
{
	t_ast	*node;

	if (!(node = (t_ast *)malloc(sizeof(t_ast))))
		ft_fatalerror(E_ALLOC);
	ft_bzero(node, sizeof(t_ast));
	node->type = TOK_BLANK;
	return (node);
}

/*
** Checks if the next token is a simple command/argument
** Returns 1 if the next token is a simple command, 0 if it isn't
** and -1 if the next token is NULL
*/

int		arg_check(t_tok *tokens)
{
	if (!tokens->next)
		return (-1);
	return (tokens->next->type == TOK_ARG ? 1 : 0);
}
