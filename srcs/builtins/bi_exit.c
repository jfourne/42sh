/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 10:31:50 by hdelaby           #+#    #+#             */
/*   Updated: 2017/05/23 11:52:52 by robechon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "history_file.h"

static int	is_number(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*(str++)))
			return (0);
	}
	return (1);
}

int			bi_exit(char **args, t_sh *shell)
{
	int		ret;

	(void)shell;
	if (args[1])
	{
		if (args[2])
			return (ft_puterr("exit", "Too many arguments", NULL, 1));
		write_history_file(NULL, shell);
		if (!is_number(args[1]))
			exit(ft_puterr("exit", "Numeric argument required", NULL, 255));
		exit(ft_atoi(args[1]));
	}
	else
		ret = shell->status;
	write_history_file(NULL, shell);
	exit(ret);
}
