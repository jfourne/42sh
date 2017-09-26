/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_keys.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 12:12:38 by hdelaby           #+#    #+#             */
/*   Updated: 2017/05/10 11:24:26 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_KEYS_H
# define INPUT_KEYS_H

# include "term_mode.h"
# include "line_edition.h"

int		insert_word(t_line *line, char *word);
int		insert_char(t_line *line, int key);
int		delete_char(t_line *line, int key);
int		ctrld_key(t_line *line);

#endif
