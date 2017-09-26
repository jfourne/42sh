/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:38:39 by hdelaby           #+#    #+#             */
/*   Updated: 2016/11/05 10:15:12 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*ret;

	ret = &(*s1);
	while (*s1)
		s1++;
	while (*s2 && n > 0)
	{
		*s1++ = *s2++;
		n--;
	}
	*s1 = '\0';
	return (ret);
}
