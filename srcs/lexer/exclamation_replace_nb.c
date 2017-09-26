/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exclamation_replace_nb.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 15:55:58 by jfourne           #+#    #+#             */
/*   Updated: 2017/06/19 14:24:42 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char		*search_hist_nb_neg(int nb, t_sh *sh)
{
	t_dlist		*tmp;
	int			count;
	char		*replace;

	count = -1;
	tmp = ft_dlstgethead(sh->hist);
	while (tmp && count > nb)
	{
		tmp = tmp->next;
		count--;
	}
	if (tmp)
	{
		if ((replace = ft_strdup(tmp->content)) == NULL)
			ft_fatalerror(E_ALLOC);
		return (replace);
	}
	return (NULL);
}

char			*search_hist_nb(char *line, t_sh *sh)
{
	int			count;
	int			nb;
	t_dlist		*tmp;
	char		*replace;

	if ((nb = ft_atoi(line)) < 1)
		return (search_hist_nb_neg(nb, sh));
	count = 1;
	tmp = ft_dlstgettail(sh->hist);
	while (tmp && count < nb)
	{
		tmp = tmp->prev;
		count++;
	}
	if (tmp)
	{
		if ((replace = ft_strdup(tmp->content)) == NULL)
			ft_fatalerror(E_ALLOC);
		return (replace);
	}
	return (NULL);
}
