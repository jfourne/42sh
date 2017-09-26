/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 13:47:53 by jfourne           #+#    #+#             */
/*   Updated: 2017/06/13 15:46:33 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int			check_quote_end_backslash(t_grab_all *grab, int i, char c)
{
	int		count;

	count = 0;
	if (grab->bs->dq == 1 && c == '\'')
		return (EXIT_SUCCESS);
	while (i > -1 && (*(grab->line))[i] == '\\')
	{
		i--;
		count++;
	}
	if ((count % 2) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int			check_quote_end(t_grab_all *grab, char c)
{
	int		i;

	i = grab->save->i;
	while ((*(grab->line))[i])
	{
		i++;
		if ((*(grab->line))[i] == c)
		{
			if (check_quote_end_backslash(grab, i - 1, c) == EXIT_SUCCESS)
				return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}
