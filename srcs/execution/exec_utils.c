/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robechon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:07:43 by robechon          #+#    #+#             */
/*   Updated: 2017/06/06 11:27:00 by robechon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "shell.h"
#include "manip_env.h"
#include "execution.h"
#include "sh_error.h"

int			duplicate(int oldfd, int newfd)
{
	int		ret;

	if ((ret = dup2(oldfd, newfd)) == -1)
		ft_fatalerror(E_DUP2);
	return (ret);
}

int			check_status(int status)
{
	int		ret;

	ret = 0;
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ret = WTERMSIG(status) + 128;
	return (ret);
}

char		**get_path(t_sh *shell)
{
	char	*value;
	char	**tab;

	tab = NULL;
	value = ft_getenv("PATH", shell->env);
	if (!value)
		return (NULL);
	tab = ft_strsplit(value, ':');
	if (!tab)
		ft_fatalerror(E_ALLOC);
	return (tab);
}

int			check_access(char *cmd)
{
	if (!access(cmd, F_OK) && access(cmd, X_OK))
	{
		(ft_puterr("42sh", E_ACCES, cmd, 1));
		return (2);
	}
	return (1);
}

void		stock_fd(t_list **begin, int fd, int mode)
{
	char	*content;
	t_list	*tmp;

	tmp = NULL;
	content = NULL;
	if (mode)
	{
		if ((content = ft_itoa(fd)) == NULL)
			ft_fatalerror(E_ALLOC);
		ft_lstaddback(begin, ft_lstnew(content, ft_strlen(content)));
		free(content);
	}
	else
	{
		while (*begin != NULL)
		{
			close(ft_atoi((*begin)->content));
			tmp = *begin;
			free((*begin)->content);
			*begin = (*begin)->next;
			free(tmp);
		}
	}
}
