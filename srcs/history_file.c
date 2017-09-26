/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 10:46:30 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/20 10:01:14 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history_file.h"

#define MODE_APPEND	1
#define MODE_WRITE	2

t_dlist	*read_history_file(char *path, t_sh *sh)
{
	int		fd;
	char	*line;
	t_dlist	*lst;
	t_dlist	*node;
	int		ret;

	lst = NULL;
	if ((fd = open((!path ? sh->hist_path : path), O_RDONLY)) == -1)
		return (NULL);
	while ((ret = get_next_line(fd, &line)))
	{
		if (ret == -1)
			return (lst);
		node = ft_dlstnew(line, ft_strlen(line) + 1);
		node->content_size = 10042;
		if (!node)
			ft_fatalerror(E_ALLOC);
		ft_dlstaddback(&lst, node);
		free(line);
	}
	return (lst);
}

void	write_history_file(char *path, t_sh *sh)
{
	int		fd;
	t_dlist	*hist;

	hist = ft_dlstgethead(sh->hist);
	if ((fd = open((!path ? sh->hist_path : path),
					O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
		return ;
	while (hist)
	{
		if (hist->content_size != 10042)
			ft_putendl_fd(hist->content, fd);
		hist = hist->next;
	}
}
