/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 12:18:32 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/14 09:37:57 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexerbis.h"
#include "ast.h"
#include "sh_error.h"
#include "line_edition.h"

static int	treat_content(t_tok *tok, char *ret, char *eof, t_sh *sh)
{
	if (!ft_strcmp(ret, eof))
		return (1);
	if (tok->lex)
		if (!(tok->lex = ft_strjoin_and_clean(tok->lex, "\n", 1)))
			ft_fatalerror(E_ALLOC);
	tok->lex = tok->lex ? ft_strjoin_and_clean(tok->lex, ret, 1)
		: ft_strdup(ret);
	if (!tok->lex)
		ft_fatalerror(E_ALLOC);
	if (sh->is_interactive)
		ft_putstr_fd("heredoc> ", 2);
	return (0);
}

static int	get_hdoc(t_tok *tok, t_sh *sh)
{
	char	*eof;
	char	*ret;
	int		i;

	if (tok->type != TOK_ARG)
		return (1);
	if (!(eof = ft_strdup(tok->lex)))
		ft_fatalerror(E_ALLOC);
	ft_strdel(&tok->lex);
	sh->prompt = 0;
	if (sh->is_interactive)
		ft_putstr_fd("heredoc> ", 2);
	while ((ret = line_edition(sh)))
	{
		i = treat_content(tok, ret, eof, sh);
		free(ret);
		if (i)
			break ;
	}
	if (!ret)
		ft_strdel(&tok->lex);
	ft_strdel(&eof);
	return (ret ? 0 : 1);
}

int			handle_hdoc(t_tok *tok, t_sh *sh)
{
	while (tok)
	{
		if (tok->type == TOK_HEREDOC)
		{
			tok = tok->next;
			if (get_hdoc(tok, sh))
				return (1);
		}
		tok = tok->next;
	}
	return (0);
}
