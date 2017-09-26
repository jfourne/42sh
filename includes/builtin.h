/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 16:04:00 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/07 16:36:09 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "manip_env.h"
# include "libft.h"
# include "sh_error.h"
# include "shell.h"

typedef struct	s_builtin
{
	char	*cmd;
	int		(*fct)(char **, t_sh *);
}				t_builtin;

int				bi_setenv(char **args, t_sh *shell);
int				bi_unsetenv(char **args, t_sh *shell);
int				bi_cd(char **args, t_sh *shell);
int				cd_get_option(char *arg, int *has_opt);
int				bi_exit(char **args, t_sh *shell);
int				bi_echo(char **args, t_sh *shell);
int				bi_env(char **args, t_sh *shell);
int				bi_history(char **args, t_sh *shell);
int				bi_export(char **args, t_sh *shell);
int				bi_unset(char **args, t_sh *shell);
void			print_hist(t_dlist *hist, size_t offset);

#endif
