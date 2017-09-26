/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 11:19:28 by hdelaby           #+#    #+#             */
/*   Updated: 2017/05/23 12:23:36 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# define MAX_KEY_LEN 5

# define KEY_CODE_UP "\x1b\x5b\x41\0\0"
# define KEY_CODE_DO "\x1b\x5b\x42\0\0"
# define KEY_CODE_RI "\x1b\x5b\x43\0\0"
# define KEY_CODE_LE "\x1b\x5b\x44\0\0"

# define KEY_CODE_DEL "\x1b\x5b\x33\x7e\0"

# define KEY_CODE_HOME "\x1b\x5b\x48\0\0"
# define KEY_CODE_END "\x1b\x5b\x46\0\0"

# define KEY_CODE_SUP "\x1b\x1b\x5b\x41\0"
# define KEY_CODE_SDO "\x1b\x1b\x5b\x42\0"
# define KEY_CODE_SRI "\x1b\x1b\x5b\x43\0"
# define KEY_CODE_SLE "\x1b\x1b\x5b\x44\0"

# define KEY_CODE_AUP "\x1b\x1b\x5b\x35\x7e"
# define KEY_CODE_ADO "\x1b\x1b\x5b\x36\x7e"

struct	s_keymatch
{
	char	*key_code;
	int		key_ret;
};

int		read_input(void);

#endif
