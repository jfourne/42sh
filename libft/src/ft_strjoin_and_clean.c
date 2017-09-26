/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_and_clean.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 16:53:01 by jfourne           #+#    #+#             */
/*   Updated: 2017/05/15 12:08:54 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	clean_join(int clean, char *s1, char *s2)
{
	if (clean == 1)
		free(s1);
	else if (clean == 2)
		free(s2);
	else
	{
		free(s1);
		free(s2);
	}
}

char		*ft_strjoin_and_clean(char *s1, char *s2, int clean)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2 || ((str = (char *)malloc((ft_strlen(s1) +
							ft_strlen(s2) + 1) * sizeof(char))) == 0))
		return (NULL);
	while (s1[j])
	{
		str[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	clean_join(clean, s1, s2);
	return (str);
}
