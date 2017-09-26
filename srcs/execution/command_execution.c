/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robechon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 13:53:57 by robechon          #+#    #+#             */
/*   Updated: 2017/06/09 14:12:08 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "execution.h"
#include "manip_env.h"
#include "shell.h"
#include "sh_error.h"

static void	join_and_exec(t_sh *shell, char **args, int i)
{
	int		ret;
	char	*cmd;
	char	**path_tab;

	ret = 1;
	if (ft_strchr(args[0], '/'))
		execve(args[0], args, shell->env);
	else
	{
		path_tab = get_path(shell);
		while (path_tab && path_tab[i])
		{
			if ((cmd = ft_strjoin(path_tab[i], "/")) == NULL)
				ft_fatalerror(E_ALLOC);
			if ((cmd = ft_strjoin_and_clean(cmd, args[0], 1)) == NULL)
				ft_fatalerror(E_ALLOC);
			if (execve(cmd, args, shell->env) == -1)
				ret = check_access(cmd);
			i++;
		}
	}
	if (ret == 1)
		ft_puterr("42sh", E_NOCMD, args[0], 1);
	exit(127);
}

int			execute_command(t_sh *shell, char **args)
{
	pid_t	pid;
	int		ret;

	ret = 0;
	if (!args)
		return (shell->status);
	if ((pid = fork()) == -1)
		ft_fatalerror(E_FORK);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		join_and_exec(shell, args, 0);
	}
	wait(&ret);
	return (check_status(ret));
}

static int	execute_builtin(t_sh *shell, char **args)
{
	int					i;
	static	t_builtin	builtin_tab[9] = {
		{"cd", &bi_cd},
		{"echo", &bi_echo},
		{"exit", &bi_exit},
		{"env", &bi_env},
		{"setenv", &bi_setenv},
		{"unsetenv", &bi_unsetenv},
		{"history", &bi_history},
		{"export", &bi_export},
		{"unset", &bi_unset},
	};

	i = 0;
	if (ft_strchr(args[0], '='))
		return (is_localvar(shell, args));
	while (i < 9)
		if (!ft_strcmp(args[0], builtin_tab[i++].cmd))
			return (builtin_tab[i - 1].fct(args, shell));
	return (-2);
}

static void	save_and_restore(int copy_fd[3], int mode)
{
	if (mode)
	{
		if ((copy_fd[0] = dup(STDIN_FILENO)) == -1)
			ft_fatalerror(E_DUP2);
		if ((copy_fd[1] = dup(STDOUT_FILENO)) == -1)
			ft_fatalerror(E_DUP2);
		if ((copy_fd[2] = dup(STDERR_FILENO)) == -1)
			ft_fatalerror(E_DUP2);
	}
	else
	{
		dup2(copy_fd[0], STDIN_FILENO);
		dup2(copy_fd[1], STDOUT_FILENO);
		dup2(copy_fd[2], STDERR_FILENO);
		close(copy_fd[0]);
		close(copy_fd[1]);
		close(copy_fd[2]);
	}
}

int			main_execution(t_sh *shell, t_ast *tree)
{
	int		ret;
	t_list	*fd_list;
	int		copy_fd[3];

	fd_list = NULL;
	save_and_restore(copy_fd, 1);
	ret = init_redir(&fd_list, tree->redir, shell);
	if (!tree->args || ret)
	{
		stock_fd(&fd_list, 0, 0);
		save_and_restore(copy_fd, 0);
		if (!tree->args && ret == 0)
			return (0);
		return (-1);
	}
	if ((ret = execute_builtin(shell, tree->args)) == -2)
		ret = execute_command(shell, tree->args);
	stock_fd(&fd_list, 0, 0);
	if (ret >= 128)
		ft_putchar('\n');
	save_and_restore(copy_fd, 0);
	return (ret);
}
