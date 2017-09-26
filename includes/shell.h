/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 18:25:20 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/14 11:39:54 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"

# define PARSE_ERROR 42

typedef struct	s_sh
{
	char	**env;
	char	**local;
	t_dlist *hist;
	char	hist_path[1024];
	int		status;
	int		parsing_status;
	int		is_interactive;
	int		prompt;
}				t_sh;

#endif
