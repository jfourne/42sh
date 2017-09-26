/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_col.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 15:06:09 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/09 14:53:22 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocompletion.h"
#include "cursor_motion.h"
#include "input_keys.h"
#include "sh_error.h"

static void		lst_print_index(t_list *lst, size_t index, t_autocmp *autocmp)
{
	size_t	i;

	i = 0;
	if (index >= autocmp->nb_entries)
		return ;
	while (i < index)
	{
		lst = lst->next;
		i++;
	}
	ft_putstr_fd(lst->content, STDIN_FILENO);
}

static size_t	common_char(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (*s1 && *s2 && *s1 == *s2)
	{
		i++;
		s1++;
		s2++;
	}
	return (i);
}

static void		prep_print(t_line *line, t_autocmp *autocmp, t_list *lst,
		size_t common_len)
{
	char	*first;

	if (!lst)
		return ;
	autocmp->maxlen += 2;
	autocmp->nb_col = line->winsz.col / autocmp->maxlen;
	autocmp->nb_row = autocmp->nb_entries / autocmp->nb_col;
	autocmp->nb_row++;
	first = lst->content;
	while (lst)
	{
		common_len = common_char(first, lst->content);
		lst = lst->next;
	}
	if ((common_len -= autocmp->name_len) > 0)
	{
		if (!(first = ft_strndup(first + autocmp->name_len, common_len)))
			ft_fatalerror(E_ALLOC);
		line->is_interactive = 0;
		insert_word(line, first);
		line->is_interactive = 1;
		free(first);
	}
	ft_putchar_fd('\n', STDIN_FILENO);
}

int				print_col(t_list *lst, t_line *line, t_autocmp *autocmp)
{
	size_t	i;
	size_t	j;
	size_t	offset;
	char	*move;

	prep_print(line, autocmp, lst, 0);
	i = 0;
	while (i < autocmp->nb_row)
	{
		j = 0;
		offset = 0;
		while (j < autocmp->nb_col)
		{
			if (!(move = tgetstr("ch", NULL)) ||
					!(move = tgoto(move, 0, j * autocmp->maxlen)))
				return (EXIT_FAILURE);
			tputs(move, 0, &ft_putc);
			lst_print_index(lst, offset + i, autocmp);
			offset += autocmp->nb_row;
			j++;
		}
		ft_putchar('\n');
		i++;
	}
	return (42);
}
