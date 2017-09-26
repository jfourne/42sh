/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_mode.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 11:31:01 by hdelaby           #+#    #+#             */
/*   Updated: 2017/04/26 12:12:02 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_MODE_H
# define TERM_MODE_H

# include <termios.h>
# include <stdlib.h>
# include <unistd.h>
# include <term.h>

int		default_term_mode(void);
int		raw_term_mode(void);
void	ft_fatal(char *msg);

#endif
