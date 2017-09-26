/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 15:36:48 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/22 15:37:45 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**ft_tabremove(char **tab, size_t index)
{
	char	**ret;
	size_t	len;

	len = ft_tablen(tab);
	ret = (char **)malloc(sizeof(char *) * len);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, tab, sizeof(char *) * index);
	ft_memcpy(ret + index, tab + index + 1, sizeof(char *) * (len - index - 1));
	ret[len - 1] = NULL;
	free(tab[index]);
	free(tab);
	return (ret);
}
