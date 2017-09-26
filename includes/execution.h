/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robechon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:49:02 by robechon          #+#    #+#             */
/*   Updated: 2017/06/16 14:55:37 by robechon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "ast.h"
# include "shell.h"
# include <fcntl.h>

# define PREAD		0
# define PWRITE		1

typedef struct	s_redirtab
{
	int	type;
	int	(*fct)(t_list **fd_list, t_redir *node, int words_fd, t_sh *shell);
}				t_redirtab;

int				simple_output(t_list **fd_list, t_redir *node,
		int words_fd, t_sh *shell);
int				append_output(t_list **fd_list, t_redir *node,
		int words_fd, t_sh *shell);
int				uas_output(t_list **fd_list, t_redir *node,
		int words_fd, t_sh *shell);
int				simple_input(t_list **fd_list, t_redir *node,
		int words_fd, t_sh *shell);
int				rdwr_input(t_list **fd_list, t_redir *node,
		int words_fd, t_sh *shell);
int				las_input(t_list **fd_list, t_redir *node,
		int words_fd, t_sh *shell);
int				heredoc_input(t_list **fd_list, t_redir *node,
		int words_fd, t_sh *shell);

int				main_execution(t_sh *shell, t_ast *tree);
int				init_pipe(t_sh *shell, t_ast *tree);
void			runpipe(t_sh *shell, t_ast *tree);
int				init_redir(t_list **fd_list, t_redir *redir, t_sh *shell);
int				execute_command(t_sh *shell, char **args);
void			browser_menu(t_sh *shell, t_ast *tree);
int				ast_browser(t_sh *sh, t_ast *tree);

void			free_redir(t_ast *tree);
void			stock_fd(t_list **begin, int fd, int mode);
char			**get_path(t_sh *shell);
int				duplicate(int oldfd, int newfd);
int				check_status(int status);
int				check_access(char *cmd);

int				is_localvar(t_sh *sh, char **args);
int				check_localvar(char *word);
int				fd_is_valid(char *node_fd, t_list **fd_list);

#endif
