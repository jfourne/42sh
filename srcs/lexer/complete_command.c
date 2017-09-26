/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 13:53:05 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/12 14:15:22 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "line_edition.h"
#include "ast.h"
#include "token.h"
#include "lexerbis.h"
#include "sh_error.h"

void		replace_newline(char *str)
{
	if (!str)
		return ;
	while (*str)
	{
		if (*str == '\n')
			*str = ' ';
		str++;
	}
}

int			append_history(t_sh *sh, t_token *tok)
{
	if (!sh->hist)
	{
		sh->hist = ft_dlstnew(tok->ptr, ft_strlen(tok->ptr) + 1);
		if (!sh->hist)
			ft_fatalerror(E_ALLOC);
	}
	else
	{
		sh->hist = ft_dlstgethead(sh->hist);
		free(sh->hist->content);
		sh->hist->content = NULL;
		sh->hist->content = ft_strdup(tok->ptr);
		if (!sh->hist->content)
			ft_fatalerror(E_ALLOC);
	}
	replace_newline(sh->hist->content);
	return (0);
}

static int	handle_input(char *prompt, char *input, t_token *tok)
{
	if (!input)
		ft_fatalerror(E_ALLOC);
	ft_putstr_fd(prompt, STDERR_FILENO);
	ft_putstr_fd("> ", STDERR_FILENO);
	free(tok->ptr);
	tok->ptr = input;
	return (0);
}

int			complete_command(t_sh *sh, t_token *tok, char *prompt)
{
	char	*input;
	size_t	len;

	len = ft_strlen(tok->ptr);
	if (ft_strcmp(prompt, "backslash"))
		input = ft_strjoin(tok->ptr, (tok->type == TOK_ARG ? "\n" : " "));
	else
		input = ft_strdup(tok->ptr);
	handle_input(prompt, input, tok);
	sh->prompt = 0;
	if (!(input = line_edition(sh)))
		return (1);
	if (!ft_strcmp(prompt, "backslash") && !ft_strcmp(input, "\\"))
	{
		free(input);
		return (42);
	}
	if (!(tok->line = ft_strfreejoin(tok->ptr, input)))
		ft_fatalerror(E_ALLOC);
	tok->ptr = tok->line;
	tok->line += len;
	return (0);
}
