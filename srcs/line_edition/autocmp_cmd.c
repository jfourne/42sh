/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocmp_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 11:51:33 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/12 13:50:37 by robechon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocompletion.h"
#include "sh_error.h"
#include "input_keys.h"
#include "cursor_motion.h"

static int	feed_list(char *path, t_autocmp *autocmp, t_list **lst)
{
	DIR				*dirp;

	if (!(dirp = opendir(path)))
		return (EXIT_FAILURE);
	return (get_matching_entries(dirp, autocmp, lst));
}

int			complete_cmd(t_line *line, t_autocmp *autocmp, t_sh *sh)
{
	char	*path;
	char	**split_path;
	char	**ptr;
	t_list	*lst;

	lst = NULL;
	autocmp->name_len = ft_strlen(autocmp->fullpath);
	ft_strcpy(autocmp->name, autocmp->fullpath);
	if (autocmp->fullpath[0] == '/')
		return (complete_arg(line, autocmp));
	path = ft_getenv("PATH", sh->env);
	if (!path)
	{
		ft_putendl_fd("\n42sh: PATH is not set", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	split_path = ft_strsplit(path, ':');
	if (!split_path)
		ft_fatalerror(E_ALLOC);
	ptr = split_path;
	while (*split_path)
		feed_list(*split_path++, autocmp, &lst);
	ft_tabdel(ptr);
	return (treat_entries(line, lst, autocmp));
}
