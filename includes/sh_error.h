/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 13:10:07 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/09 08:46:34 by robechon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_ERROR_H
# define SH_ERROR_H

# include "libft.h"

# define E_NOENT "no such file or directory"
# define E_ACCES "permission denied"
# define E_NOCMD "command not found"
# define E_EINVAL "invalid argument"

# define E_FORK "unable to fork"
# define E_PIPE "unable to create pipe"
# define E_DUP2 "can't duplicate fd"
# define E_ALLOC "could not allocate memory"

int		ft_puterr(char *program, char *errmsg, char *arg, int error_code);
void	ft_fatalerror(char *errmsg);

#endif
