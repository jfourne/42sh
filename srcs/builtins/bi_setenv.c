/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 15:27:58 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/08 14:39:01 by robechon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		bi_setenv(char **args, t_sh *shell)
{
	size_t	tab_size;

	tab_size = ft_tablen(args);
	if (args[1] == NULL)
		ft_puttab(shell->env);
	else if (tab_size < 2 || tab_size > 4)
	{
		ft_putendl_fd("Usage:\nsetenv [key] [value [overwrite]]", 2);
		return (-1);
	}
	else if (tab_size == 2)
		ft_setenv(args[1], "", 1, &shell->env);
	else if (tab_size == 3)
		ft_setenv(args[1], args[2], 1, &shell->env);
	else
		ft_setenv(args[1], args[2], ft_atoi(args[3]), &shell->env);
	return (0);
}
