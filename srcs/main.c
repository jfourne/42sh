/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 17:00:49 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/20 10:09:43 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "line_edition.h"
#include "ast.h"
#include "lexer.h"
#include "execution.h"
#include "manip_env.h"
#include "lexerbis.h"
#include "token.h"
#include "sh_error.h"
#include "history_file.h"
#include "init_shell.h"

static int	shell_loop(t_sh *sh)
{
	char	*str;
	t_tok	*tok;

	while ((str = line_edition(sh)))
	{
		tok = lexer(sh, str);
		generate_ast(sh, tok);
		ft_tokdel(tok);
		sh->prompt = 1;
	}
	return (sh->status);
}

int			main(int ac, char **av, char **env)
{
	t_sh	sh;

	(void)ac;
	(void)av;
	if (init_shell(env, &sh))
		return (EXIT_FAILURE);
	shell_loop(&sh);
	write_history_file(NULL, &sh);
	return (sh.status);
}
