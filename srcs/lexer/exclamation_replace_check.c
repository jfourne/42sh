/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclamation_replace_check.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 11:46:24 by jfourne           #+#    #+#             */
/*   Updated: 2017/06/13 14:37:10 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int				exclamation_error(char *line, t_replace save)
{
	if (save.b == 0)
		save.b = save.a + 2;
	ft_putstr_fd("42sh: ", 2);
	write(2, line + save.i, save.b - save.a);
	ft_putendl_fd(": event not found", 2);
	return (EXIT_FAILURE);
}

void			exclamation_quote(char *line, t_quot *bs, int i)
{
	if ((line)[i] == '"')
		int_reverse(&bs->dq);
	if ((line)[i] == '\'' && bs->dq == 0)
		int_reverse(&bs->sq);
}

int				exclamation_backquote(t_replace *save, char *line)
{
	save->a = save->i + 1;
	save->b = save->i - 1;
	while (save->b > -1 && line[save->b] == '\\')
		save->b--;
	if ((save->i - 1) == save->b)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
