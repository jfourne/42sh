/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 15:26:39 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/02 15:20:50 by robechon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		bi_echo(char **args, t_sh *shell)
{
	(void)shell;
	args += 1;
	while (*args)
	{
		ft_putstr(*(args++));
		if (*args)
			ft_putchar(' ');
	}
	ft_putchar('\n');
	return (0);
}
