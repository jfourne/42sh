/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_canon_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 10:30:49 by hdelaby           #+#    #+#             */
/*   Updated: 2017/01/26 16:19:56 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*lst_to_path(t_list *lst)
{
	char	path[1024];

	ft_bzero(path, 1024);
	while (lst)
	{
		ft_strcat(path, lst->content);
		if (ft_strcmp(lst->content, "/") && lst->next)
			ft_strcat(path, "/");
		lst = lst->next;
	}
	return (ft_strdup(path));
}

static void	remove_last_dir(t_list **head)
{
	while ((*head)->next)
		head = &(*head)->next;
	if (ft_strcmp((*head)->content, "/"))
	{
		free((*head)->content);
		free(*head);
		*head = NULL;
	}
}

int			ft_canon_path(char **path)
{
	char	**tokens;
	t_list	*ptr;
	t_list	*lst;
	t_list	*cut_path;

	lst = NULL;
	tokens = ft_strsplit(*path, '/');
	cut_path = ft_lstnew("/", 2);
	cut_path->next = ft_tab_to_lst(tokens);
	ptr = cut_path;
	ft_tabdel(tokens);
	while (cut_path)
	{
		if (!ft_strcmp(cut_path->content, ".."))
			remove_last_dir(&lst);
		else if (ft_strcmp(cut_path->content, "."))
			ft_lstaddback(&lst, ft_lstnew(cut_path->content,
						ft_strlen(cut_path->content) + 1));
		cut_path = cut_path->next;
	}
	ft_strdel(path);
	*path = lst_to_path(lst);
	ft_lstdel(&lst, &ft_lstdelstr);
	ft_lstdel(&ptr, &ft_lstdelstr);
	return (0);
}
