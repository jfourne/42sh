/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclamation_replace_it.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 12:56:27 by jfourne           #+#    #+#             */
/*   Updated: 2017/06/12 14:39:03 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void		replace_it(char **line, t_replace *ex, char *replace)
{
	char	*finale;

	if ((finale = ft_strndup(*line, ex->a)) == NULL)
		ft_fatalerror(E_ALLOC);
	if ((finale = ft_strjoin_and_clean(finale, replace, 3)) == NULL)
		ft_fatalerror(E_ALLOC);
	if ((finale = ft_strjoin_and_clean(finale, *line + ex->b, 1)) == NULL)
		ft_fatalerror(E_ALLOC);
	if (line && *line)
		free(*line);
	*line = finale;
}
