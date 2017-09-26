/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:00:37 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/14 09:27:15 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		bi_unsetenv(char **args, t_sh *shell)
{
	if (args[1] == NULL)
	{
		ft_putendl_fd("unsetenv: Too few arguments.", STDERR_FILENO);
		return (1);
	}
	args = args + 1;
	while (*args)
		ft_unsetenv(*(args++), &shell->env);
	return (0);
}
