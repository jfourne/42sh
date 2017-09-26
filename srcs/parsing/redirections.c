/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 13:26:53 by craffate          #+#    #+#             */
/*   Updated: 2017/06/19 14:08:28 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "sh_error.h"
#include "execution.h"

static void		redir_push(t_redir **list, t_redir *node)
{
	if (!list || !node)
		return ;
	while (*list)
		list = &(*list)->next;
	*list = node;
}

/*
** Assigns values to a node and returns it
*/

static t_redir	*node_redir_assign(t_sh *sh, t_tok **tokens)
{
	t_redir	*ret;

	(void)sh;
	if (!(ret = (t_redir *)malloc(sizeof(t_redir))))
		ft_fatalerror(E_ALLOC);
	ret->in_fd = STDIN_FILENO;
	ret->out_fd = STDOUT_FILENO;
	ret->type = (*tokens)->type;
	ret->redir = ft_strdup((*tokens)->lex);
	if (!ret->redir)
		ft_fatalerror(E_ALLOC);
	tok_pacman(tokens);
	ft_check_replace(tokens, sh);
	ret->word = (*tokens)->lex ? ft_strdup((*tokens)->lex) : NULL;
	ret->next = NULL;
	return (ret);
}

/*
** Returns a redirection node
*/

static t_redir	*node_redir(t_sh *sh, t_tok **tokens)
{
	t_redir		*ret;

	if ((*tokens)->next && (*tokens)->next->type == TOK_ARG)
		ret = node_redir_assign(sh, tokens);
	else
	{
		tok_pacman(tokens);
		sh->parsing_status = PARSE_ERROR;
		return (NULL);
	}
	return (ret);
}

static int		feed_node(t_sh *sh, t_tok **tokens, t_ast *node)
{
	t_redir	*redir;

	if ((*tokens)->type == TOK_ARG)
	{
		ft_check_replace(tokens, sh);
		if (!(*tokens)->lex)
			return (0);
		if (!(node->args = arr_push(node->args, (*tokens)->lex)))
			ft_fatalerror(E_ALLOC);
	}
	else
	{
		if (!(redir = node_redir(sh, tokens)))
		{
			ft_astdel(node);
			node = NULL;
			return (1);
		}
		redir_push(&node->redir, redir);
	}
	return (0);
}

t_ast			*ast_arg(t_sh *sh, t_tok **tokens)
{
	t_ast	*node;
	char	**arr;

	arr = NULL;
	if (!sh->parsing_status)
	{
		node = ast_node(TOK_ARG, NULL, NULL);
		if (!node)
			ft_fatalerror(E_ALLOC);
		while ((*tokens) && ((*tokens)->type == TOK_ARG ||
			isredir((*tokens)->type)))
		{
			if (feed_node(sh, tokens, node))
				return (NULL);
			tok_pacman(tokens);
		}
		return (node);
	}
	return (NULL);
}
