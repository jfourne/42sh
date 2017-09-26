/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robechon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 11:45:10 by robechon          #+#    #+#             */
/*   Updated: 2017/06/12 13:58:52 by robechon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "shell.h"
#include "execution.h"
#include "sh_error.h"

int		output_redir(t_list **fd_list, t_redir *node, t_sh *shell)
{
	int					words_fd;
	int					i;
	static t_redirtab	output_tab[3] = {
		{TOK_OUTPUT, &simple_output},
		{TOK_APPEND, &append_output},
		{TOK_UAS, &uas_output},
	};

	i = 0;
	words_fd = 0;
	if (!ft_isdigit(node->redir[0]))
		node->out_fd = 1;
	else
		node->out_fd = ft_atoi(node->redir);
	while (i < 3)
	{
		if (node->type == output_tab[i++].type)
			return (output_tab[i - 1].fct(fd_list, node, words_fd, shell));
	}
	return (EXIT_FAILURE);
}

int		input_redir(t_list **fd_list, t_redir *node, t_sh *shell)
{
	int					words_fd;
	int					i;
	static t_redirtab	input_tab[4] = {
		{TOK_INPUT, &simple_input},
		{TOK_RDWR, &rdwr_input},
		{TOK_LAS, &las_input},
		{TOK_HEREDOC, &heredoc_input},
	};

	i = 0;
	words_fd = 0;
	if (!ft_isdigit(node->redir[0]))
		node->in_fd = 0;
	else
		node->in_fd = ft_atoi(node->redir);
	if (node->next != NULL &&
			(node->next->type == TOK_INPUT ||
			node->next->type == TOK_HEREDOC || node->next->type == TOK_LAS))
		return (0);
	while (i < 4)
	{
		if (node->type == input_tab[i++].type)
			return (input_tab[i - 1].fct(fd_list, node, words_fd, shell));
	}
	return (EXIT_FAILURE);
}

/*
** Permet de gerer les redirections chainees.
*/

int		init_redir(t_list **fd_list, t_redir *redir, t_sh *shell)
{
	while (redir != NULL)
	{
		while (redir != NULL &&
				(redir->type == TOK_INPUT || redir->type == TOK_HEREDOC ||
				redir->type == TOK_RDWR || redir->type == TOK_LAS))
		{
			if (input_redir(fd_list, redir, shell) == 1)
				return (EXIT_FAILURE);
			redir = redir->next;
		}
		while (redir != NULL &&
				(redir->type == TOK_OUTPUT || redir->type == TOK_APPEND ||
				redir->type == TOK_UAS))
		{
			if (output_redir(fd_list, redir, shell) == 1)
				return (EXIT_FAILURE);
			redir = redir->next;
		}
	}
	return (EXIT_SUCCESS);
}
