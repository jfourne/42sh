/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robechon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 16:32:40 by robechon          #+#    #+#             */
/*   Updated: 2017/06/16 14:55:03 by robechon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "shell.h"
#include "execution.h"
#include "sh_error.h"

int		simple_output(t_list **fd_list, t_redir *node, int words_fd,
		t_sh *shell)
{
	(void)shell;
	if ((words_fd = open(node->word,
			O_CREAT | O_WRONLY | O_TRUNC, 0644)) < 0)
		return (ft_puterr("42sh", "open failure", NULL, 1));
	stock_fd(fd_list, words_fd, 1);
	duplicate(words_fd, node->out_fd);
	return (EXIT_SUCCESS);
}

int		append_output(t_list **fd_list, t_redir *node, int words_fd,
		t_sh *shell)
{
	(void)shell;
	if ((words_fd = open(node->word, O_CREAT | O_APPEND | O_WRONLY, 0644))
			< 0)
		return (ft_puterr("42sh", "open failure", NULL, 1));
	stock_fd(fd_list, words_fd, 1);
	duplicate(words_fd, node->out_fd);
	return (EXIT_SUCCESS);
}

int		uas_output(t_list **fd_list, t_redir *node, int words_fd, t_sh *shell)
{
	int	fd;

	(void)fd_list;
	(void)words_fd;
	(void)shell;
	if (ft_strcmp(node->word, "-") == 0)
		return (close(node->out_fd));
	else if (ft_isnumber(node->word) == 1)
	{
		if (fd_is_valid(node->word, fd_list) == 0)
			duplicate(ft_atoi(node->word), node->out_fd);
		else
			return (ft_puterr("42sh", "Bad file descriptor", node->word, 1));
		return (EXIT_SUCCESS);
	}
	else
	{
		if ((fd = open(node->word, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
			return (ft_puterr("42sh", "ambiguous redirect", NULL, 1));
		else
			duplicate(fd, node->out_fd);
	}
	return (EXIT_SUCCESS);
}
