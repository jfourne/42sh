/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 10:48:32 by hdelaby           #+#    #+#             */
/*   Updated: 2017/05/12 10:55:47 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "line_edition.h"
# include "cursor_motion.h"

# define SPE_LINE_LEN 4242

int		old_hist_entry(t_line *line);
int		new_hist_entry(t_line *line);
int		clean_history(t_line *line);

#endif
