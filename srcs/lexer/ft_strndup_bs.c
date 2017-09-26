/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup_bs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 10:10:08 by jfourne           #+#    #+#             */
/*   Updated: 2017/06/13 11:12:52 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char		*ft_strndup_bs(const char *s1, unsigned int i, unsigned int a,
							unsigned int n)
{
	int				bs;
	char			*dup;

	if (!s1 || s1 == NULL)
		return (NULL);
	if ((dup = (char *)malloc(sizeof(*dup) * (ft_strlen(s1) + 1))) == NULL)
		return (NULL);
	while (i < n)
	{
		bs = 0;
		if (s1[i] == '\\')
		{
			while (s1[i] && s1[i] == '\\')
			{
				int_reverse(&bs);
				if (bs == 0)
					dup[a++] = s1[i];
				i++;
			}
		}
		else
			dup[a++] = s1[i++];
	}
	dup[a] = '\0';
	return (dup);
}
