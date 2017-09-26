/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_browser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robechon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 14:25:20 by robechon          #+#    #+#             */
/*   Updated: 2017/05/31 10:52:00 by robechon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "shell.h"
#include "execution.h"

/*
** Simple function for command launching!
*/

int			ast_browser(t_sh *shell, t_ast *tree)
{
	if (tree == NULL)
		return (EXIT_FAILURE);
	if (tree->type == TOK_PIPE)
		shell->status = init_pipe(shell, tree);
	if (tree->type == TOK_ARG)
		shell->status = main_execution(shell, tree);
	return (EXIT_SUCCESS);
}
