/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 10:46:48 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/13 11:49:06 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_FILE_H
# define HISTORY_FILE_H

# include "libft.h"
# include "sh_error.h"
# include "shell.h"
# include <fcntl.h>

t_dlist		*read_history_file(char *path, t_sh *sh);
void		write_history_file(char *path, t_sh *sh);

#endif
