/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 14:01:14 by craffate          #+#    #+#             */
/*   Updated: 2017/06/06 15:48:17 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/*
** Does a first quick parsing to spot any potential error
** in which case the address of the token
** causing the parse error is returned
*/

t_tok		*tok_parsing(t_sh *sh, t_tok *tokens)
{
	if (!(tokens->type == TOK_ARG || isredir(tokens->type)))
	{
		sh->parsing_status = PARSE_ERROR;
		return (tokens);
	}
	while (tokens->type != TOK_END)
	{
		if (((tokens->type == TOK_PIPE || tokens->type == TOK_AND ||
		tokens->type == TOK_OR || tokens->type == TOK_SC) &&
		!(tokens->next->type == TOK_ARG || isredir(tokens->next->type))) ||
		(isredir(tokens->type) && tokens->next->type != TOK_ARG) ||
		(tokens->type == TOK_BG && tokens->next->type != TOK_BG))
		{
			if (tokens->type == TOK_SC && tokens->next->type == TOK_END)
				break ;
			sh->parsing_status = PARSE_ERROR;
			return (tokens->type == TOK_END ? tokens : tokens->next);
		}
		tokens = tokens->next;
	}
	return (NULL);
}
