/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/20 10:03:00 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/20 10:08:54 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_SHELL_H
# define INIT_SHELL_H

# include "manip_env.h"
# include "shell.h"
# include "sh_error.h"
# include "ast.h"
# include "lexerbis.h"
# include "history_file.h"
# include <pwd.h>
# include <sys/types.h>

int		init_shell(char **env, t_sh *sh);

#endif
