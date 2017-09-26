/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robechon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 11:29:01 by robechon          #+#    #+#             */
/*   Updated: 2017/06/16 15:08:56 by robechon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "shell.h"
#include "manip_env.h"
#include "sh_error.h"
#include "execution.h"

void	free_redir(t_ast *tree)
{
	t_redir *tmp;

	while (tree->redir != NULL)
	{
		if (tree->redir->word)
			free(tree->redir->word);
		if (tree->redir->redir)
			free(tree->redir->redir);
		tmp = tree->redir;
		tree->redir = tree->redir->next;
		free(tmp);
	}
}

int		check_localvar(char *word)
{
	int	i;

	i = 0;
	if (!ft_isalpha(word[0]))
		return (1);
	i++;
	while (word[i])
	{
		if (!ft_isalnum(word[i]) && word[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int		is_localvar(t_sh *shell, char **args)
{
	char	*value;
	char	*save;

	save = NULL;
	value = NULL;
	(void)shell;
	if (!args[1] && (value = ft_strchr(args[0], '=')) != NULL)
	{
		save = value;
		value[0] = '\0';
		value++;
		if (check_localvar(args[0]))
		{
			save[0] = '=';
			return (ft_puterr("42sh", E_NOCMD, args[0], 1));
		}
		ft_setenv(args[0], value, 1, &shell->local);
		return (0);
	}
	return (1);
}

int		fd_is_valid(char *node_fd, t_list **fd_list)
{
	t_list	*tmp;
	int		var;

	var = ft_atoi(node_fd);
	tmp = *fd_list;
	if (var == STDIN_FILENO || var == STDOUT_FILENO || var == STDERR_FILENO)
		return (0);
	while (tmp)
	{
		if (ft_strcmp(node_fd, tmp->content))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
