/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 11:20:54 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/12 13:54:32 by robechon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term_mode.h"
#include "sh_error.h"

/*
** Ensures that the given argument for TERM is valid. If no argument is given,
** we assume a 'xterm' term. Otherwise, we try to retrieve information about the
** type from the termcap database.
*/

static void	init_term_data(void)
{
	char	*termtype;
	int		success;

	if (!(termtype = getenv("TERM")))
		termtype = "xterm";
	success = tgetent(NULL, termtype);
	if (success < 0)
		ft_fatalerror("\n42sh: could not retrieve the termcap database.");
	if (success == 0)
		ft_fatalerror("\n42sh: the given terminal type does not exist.");
}

int			default_term_mode(void)
{
	struct termios	tattr;

	if (tcgetattr(STDIN_FILENO, &tattr))
		return (EXIT_FAILURE);
	tattr.c_lflag |= (ECHO | ICANON | ISIG);
	return (tcsetattr(STDIN_FILENO, TCSADRAIN, &tattr));
}

int			raw_term_mode(void)
{
	struct termios	tattr;

	if (tcgetattr(STDIN_FILENO, &tattr))
		return (EXIT_FAILURE);
	tattr.c_lflag &= ~(ICANON | ECHO | ISIG);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &tattr))
		return (EXIT_FAILURE);
	init_term_data();
	return (EXIT_SUCCESS);
}
