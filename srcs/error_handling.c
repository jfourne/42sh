/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:32:21 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/12 13:03:40 by robechon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh_error.h"

void	ft_fatalerror(char *errmsg)
{
	ft_putstr_fd("42sh: ", STDERR_FILENO);
	ft_putendl_fd(errmsg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int		ft_puterr(char *program, char *errmsg, char *arg, int error_code)
{
	ft_putstr_fd(program, 2);
	if (arg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
	}
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(errmsg, 2);
	return (error_code);
}
