/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 11:40:07 by hdelaby           #+#    #+#             */
/*   Updated: 2017/03/21 11:41:37 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabcpy(char **array)
{
	char	**ret;
	int		i;

	i = 0;
	ret = (char **)malloc(sizeof(char *) * (ft_tablen(array) + 1));
	if (!ret)
		return (NULL);
	while (array[i])
	{
		ret[i] = ft_strdup(array[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
