/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstgetn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 14:41:33 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/09 11:04:58 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstgetn(t_dlist *lst, size_t n)
{
	size_t	i;

	if (n == 0)
		return (NULL);
	i = 1;
	lst = ft_dlstgethead(lst);
	if (n > ft_dlstsize(lst))
		return (NULL);
	lst = ft_dlstgettail(lst);
	while (lst && i < n)
	{
		lst = lst->prev;
		i++;
	}
	return (lst);
}
