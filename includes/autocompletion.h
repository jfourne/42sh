/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 15:24:17 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/09 14:57:52 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCOMPLETION_H
# define AUTOCOMPLETION_H

# include "line_edition.h"
# include "shell.h"
# include <dirent.h>

# define CMD 1
# define ARG 2

# define LEN_LIMIT 256

typedef struct	s_autocmp
{
	char	fullpath[MAX_LINE_LEN];
	char	name[LEN_LIMIT];
	size_t	name_len;
	size_t	nb_entries;
	size_t	maxlen;
	size_t	nb_col;
	size_t	nb_row;
}				t_autocmp;

int				autocompletion(t_line *line, t_sh *sh);
int				complete_arg(t_line *line, t_autocmp *autocmp);
int				complete_cmd(t_line *line, t_autocmp *autocmp, t_sh *sh);
int				determine_dir(t_autocmp *autocmp);
int				print_col(t_list *lst, t_line *line, t_autocmp *autocmp);
int				get_matching_entries(DIR *dirp, t_autocmp *autocmp,
		t_list **lst);
int				treat_entries(t_line *line, t_list *list, t_autocmp *autocmp);

#endif
