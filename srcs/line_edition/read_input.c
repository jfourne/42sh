/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 13:15:16 by hdelaby           #+#    #+#             */
/*   Updated: 2017/05/16 11:42:46 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <curses.h>
#include "libft.h"
#include "keys.h"

#include <stdio.h>

/*
** Reads MAX_KEY_LEN at a time. Matches the string with a list of known
** key sequences. Then returns the value of the key_pressed contained in
** curses.h.
*/

static int	match_key(char *key_str, int i)
{
	static struct s_keymatch	key_couple[13] = {
		{KEY_CODE_UP, KEY_UP},
		{KEY_CODE_DO, KEY_DOWN},
		{KEY_CODE_RI, KEY_RIGHT},
		{KEY_CODE_LE, KEY_LEFT},
		{KEY_CODE_DEL, KEY_DC},
		{KEY_CODE_HOME, KEY_HOME},
		{KEY_CODE_END, KEY_END},
		{KEY_CODE_SRI, KEY_SRIGHT},
		{KEY_CODE_SLE, KEY_SLEFT},
		{KEY_CODE_SUP, KEY_SPREVIOUS},
		{KEY_CODE_SDO, KEY_SNEXT},
		{KEY_CODE_AUP, KEY_DL},
		{KEY_CODE_ADO, KEY_IL}
	};

	i = 0;
	while (i < 13)
		if (!ft_memcmp(key_couple[i++].key_code, key_str, MAX_KEY_LEN))
			return (key_couple[i - 1].key_ret);
	return (key_str[0]);
}

/*
** Small particularity of this function lies in the fact that we first read 1
** character. If this value equals '\x1b'(escape) we read 4 other chars.
** This behaviour makes copied text works.
*/

int			read_input(void)
{
	char	*key_str;
	int		key_pressed;
	int		ret;

	key_str = ft_strnew(MAX_KEY_LEN);
	if (!key_str)
		return (0);
	ret = read(STDIN_FILENO, key_str, 1);
	if (ret == 0 || ret == -1)
	{
		free(key_str);
		return (0);
	}
	if (*key_str == '\x1b')
		read(STDIN_FILENO, key_str + 1, MAX_KEY_LEN - 1);
	key_pressed = match_key(key_str, 0);
	free(key_str);
	return (key_pressed);
}
