/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 10:53:20 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/07 16:14:58 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "lexerbis.h"
#include "ast.h"
#include "sh_error.h"

void		tokpush(t_tok **head, t_tok *node)
{
	if (!head)
		return ;
	while (*head)
		head = &(*head)->next;
	*head = node;
}

t_tok		*toknew(char *word, int type)
{
	t_tok	*node;

	if (!(node = (t_tok *)malloc(sizeof(t_tok))))
		return (NULL);
	if (word)
	{
		node->lex = ft_strdup(word);
		if (!node->lex)
		{
			free(node);
			return (NULL);
		}
	}
	else
		node->lex = NULL;
	node->type = type;
	node->next = NULL;
	return (node);
}

int			token_add_char(t_token *tok, char c)
{
	if (tok->index >= MAX_TOKEN_LEN - 1)
		return (1);
	tok->str[tok->index++] = c;
	return (0);
}

int			end_token(t_token *tok, t_tok **lst)
{
	t_tok	*node;

	if (tok->type)
	{
		node = toknew(tok->str, tok->type);
		if (!node)
			ft_fatalerror(E_ALLOC);
		tokpush(lst, node);
	}
	ft_bzero(tok->str, MAX_TOKEN_LEN);
	tok->index = 0;
	tok->type = 0;
	return (0);
}
