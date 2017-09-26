/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 08:40:43 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/06 14:43:51 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexerbis.h"
#include "sh_error.h"

int			is_blank(char *str)
{
	if (!str)
		return (-1);
	while (*str)
	{
		if (*str != '\t' && *str != '\n' && *str != ' ')
			return (0);
		str++;
	}
	return (1);
}

int			add_history(t_sh *sh, char *line)
{
	t_dlist	*node;

	replace_newline(line);
	if (!sh->hist)
	{
		sh->hist = ft_dlstnew(line, ft_strlen(line) + 1);
		if (!sh->hist)
			ft_fatalerror(E_ALLOC);
	}
	else
	{
		node = ft_dlstnew(line, ft_strlen(line) + 1);
		if (!node)
			ft_fatalerror(E_ALLOC);
		ft_dlstadd(&sh->hist, node);
	}
	return (0);
}
