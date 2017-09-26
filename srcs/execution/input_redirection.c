/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robechon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 16:51:20 by robechon          #+#    #+#             */
/*   Updated: 2017/06/19 13:58:51 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "shell.h"
#include "sh_error.h"
#include "execution.h"

int		simple_input(t_list **fd_list, t_redir *node, int words_fd,
		t_sh *shell)
{
	(void)shell;
	if ((words_fd = open(node->word, O_RDONLY)) < 0)
		return (ft_puterr("42sh", E_NOENT, node->word, 1));
	stock_fd(fd_list, words_fd, 1);
	duplicate(words_fd, node->in_fd);
	return (EXIT_SUCCESS);
}

int		rdwr_input(t_list **fd_list, t_redir *node, int words_fd,
		t_sh *shell)
{
	(void)shell;
	if ((words_fd = open(node->word, O_CREAT | O_RDWR | O_SYNC)) < 0)
		return (ft_puterr("42sh", E_NOENT, node->word, 1));
	stock_fd(fd_list, words_fd, 1);
	duplicate(words_fd, node->in_fd);
	return (EXIT_SUCCESS);
}

int		las_input(t_list **fd_list, t_redir *node, int words_fd,
		t_sh *shell)
{
	(void)fd_list;
	(void)words_fd;
	if (ft_strcmp(node->word, "-") == 0)
	{
		close(node->out_fd);
		return (EXIT_SUCCESS);
	}
	else if (ft_isnumber(node->word) == 1)
	{
		if (fd_is_valid(node->word, fd_list) == 0)
			duplicate(ft_atoi(node->word), node->in_fd);
		else
			return (ft_puterr("42sh", "Bad file descriptor", node->word, 1));
		return (EXIT_SUCCESS);
	}
	else
	{
		shell->status = 1;
		return (ft_puterr("42sh", "ambiguous redirect", NULL, 1));
	}
	return (EXIT_FAILURE);
}

int		heredoc_input(t_list **fd_list, t_redir *node, int words_fd,
		t_sh *shell)
{
	int		save_output;
	int		pipefd[2];

	(void)fd_list;
	(void)words_fd;
	(void)shell;
	if (pipe(pipefd) == -1)
		return (ft_puterr("42sh", "pipe error", NULL, 1));
	if ((save_output = dup(STDOUT_FILENO)) == -1)
		ft_fatalerror(E_DUP2);
	duplicate(pipefd[PWRITE], STDOUT_FILENO);
	ft_putstr(node->word);
	if (node->word)
		ft_putchar('\n');
	duplicate(save_output, STDOUT_FILENO);
	close(save_output);
	close(pipefd[PWRITE]);
	duplicate(pipefd[PREAD], STDIN_FILENO);
	return (EXIT_SUCCESS);
}
