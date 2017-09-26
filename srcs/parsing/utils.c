/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 10:46:53 by craffate          #+#    #+#             */
/*   Updated: 2017/05/30 11:27:40 by craffate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/*
** Pushes a character at the end of string, realloc if needed
*/

void	strpush(char **s, const char c)
{
	char	*str;
	size_t	si;

	str =
	((si = ft_strlen(*s)) % 32) ? *s :
	(char *)malloc(sizeof(char) * (si + 32 + 1));
	str[si] = c;
	str[si + 1] = 0;
	if (str == *s)
		return ;
	while (si--)
		str[si] = (*s)[si];
	free(*s);
	*s = str;
}

/*
** Frees a list of token
*/

void	free_tok(t_tok **tokens)
{
	t_tok	*tmp;

	tmp = *tokens;
	while (tmp->type != TOK_END)
	{
		*tokens = (*tokens)->next;
		free(tmp->lex);
		free(tmp);
		tmp = *tokens;
	}
	free(tmp->lex);
	free(tmp);
	tmp = NULL;
	*tokens = NULL;
}

/*
** hdelaby's array function
** Returns the actual size of a given array
*/

size_t	arrlen(const char **arr)
{
	size_t	si;

	si = 0;
	while (arr[si])
		++si;
	return (si);
}

/*
** hdelaby's array function
** Pushes a given string to an array, allocates the correct amount of memory
*/

char	**arr_push(char **arr, const char *s)
{
	size_t			si;
	char			**ret;
	unsigned int	i;

	i = 0;
	si = 2 + (arr ? arrlen((const char **)arr) : 0);
	if (!(ret = (char **)malloc(sizeof(char *) * si)))
		return (NULL);
	if (arr)
	{
		while (arr[i])
		{
			ret[i] = arr[i];
			++i;
		}
		arr ? free(arr) : 0;
	}
	ret[i++] = ft_strdup(s);
	ret[i] = NULL;
	return (ret);
}
