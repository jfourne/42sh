/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robechon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:22:56 by robechon          #+#    #+#             */
/*   Updated: 2017/05/30 14:11:05 by robechon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "shell.h"
#include "manip_env.h"
#include "execution.h"
#include "sh_error.h"

static void	left_cmd(int *pipefd, t_sh *shell, t_ast *tree)
{
	close(pipefd[PREAD]);
	duplicate(pipefd[PWRITE], STDOUT_FILENO);
	main_execution(shell, tree->left);
	exit(141);
}

static void	right_cmd(int *pipefd, t_sh *shell, t_ast *tree)
{
	close(pipefd[PWRITE]);
	duplicate(pipefd[PREAD], STDIN_FILENO);
	if (tree->right->type == TOK_PIPE)
		runpipe(shell, tree->right);
	else
		exit(main_execution(shell, tree->right));
}

static void	set_exitcode(int ret1, int ret2)
{
	ret1 = check_status(ret1);
	ret2 = check_status(ret2);
	if (ret1 == 141)
		exit(ret2);
	else if (ret2 == 141)
		exit(ret1);
	exit(1);
}

void		runpipe(t_sh *shell, t_ast *tree)
{
	pid_t	left_pid;
	pid_t	right_pid;
	int		pipefd[2];
	int		ret1;
	int		ret2;

	ret1 = 0;
	ret2 = 0;
	if (pipe(pipefd) == -1)
		ft_fatalerror(E_PIPE);
	if ((left_pid = fork()) == 0)
		left_cmd(pipefd, shell, tree);
	else if (left_pid < 0)
		ft_fatalerror(E_FORK);
	if ((right_pid = fork()) == 0)
		right_cmd(pipefd, shell, tree);
	else if (right_pid < 0)
		ft_fatalerror(E_FORK);
	close(pipefd[PREAD]);
	close(pipefd[PWRITE]);
	wait(&ret1);
	wait(&ret2);
	set_exitcode(ret1, ret2);
}

int			init_pipe(t_sh *shell, t_ast *tree)
{
	pid_t	pid;
	int		ret;

	ret = 0;
	if ((pid = fork()) == -1)
		ft_fatalerror(E_FORK);
	else if (pid == 0)
		runpipe(shell, tree);
	wait(&ret);
	return (check_status(ret));
}
