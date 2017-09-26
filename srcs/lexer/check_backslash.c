/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_backslash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 09:30:00 by jfourne           #+#    #+#             */
/*   Updated: 2017/06/13 10:49:23 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			check_backslash(t_grab_all *grab)
{
	if (grab->bs->sq == 0 && (*(grab->line))[grab->save->i] == '\\')
	{
		grab->save->a = grab->save->i;
		grab->save->b = 0;
		while ((*(grab->line))[grab->save->a] == '\\')
		{
			grab->save->a++;
			grab->save->b++;
		}
		if (grab->save->b % 2 == 1)
			grab->bs->inib = 1;
		if ((*(grab->replace) = ft_strndup_bs(*(grab->line) + grab->save->i,
						0, 0, grab->save->b)) == NULL)
			ft_fatalerror(E_ALLOC);
		grab->save->b = grab->save->a;
		grab->save->a = grab->save->i;
		grab->save->i += ft_strlen(*(grab->replace));
		replace_it(grab->line, grab->save, *(grab->replace));
	}
	return (EXIT_SUCCESS);
}
