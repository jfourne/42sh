/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 15:05:45 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/09 15:06:19 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabadd(char **tab, char *str)
{
	size_t	tab_size;
	char	**ret;
	int		i;

	i = 0;
	tab_size = 2 + (tab ? ft_tablen(tab) : 0);
	ret = (char **)malloc(sizeof(char *) * tab_size);
	if (!ret)
		return (NULL);
	if (tab)
	{
		while (tab[i])
		{
			ret[i] = tab[i];
			i++;
		}
		free(tab);
	}
	ret[i++] = ft_strdup(str);
	ret[i] = NULL;
	return (ret);
}
