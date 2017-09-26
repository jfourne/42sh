/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 16:27:43 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/22 16:36:04 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	cd_get_option(char *arg, int *has_opt)
{
	if (!ft_strcmp(arg, "-"))
		return (1);
	arg += 1;
	while (*arg)
	{
		if (*arg == 'P')
			*has_opt = 1;
		else if (*arg == 'L')
			*has_opt = 0;
		else
			return (1);
		arg += 1;
	}
	return (0);
}
