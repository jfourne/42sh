/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocmp_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 10:39:42 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/08 14:30:01 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocompletion.h"
#include "input_keys.h"
#include "cursor_motion.h"

int			complete_arg(t_line *line, t_autocmp *autocmp)
{
	DIR		*dirp;
	t_list	*lst;
	int		ret;

	lst = NULL;
	if ((ret = determine_dir(autocmp)) == 42)
		return (EXIT_SUCCESS);
	else if (ret)
		return (EXIT_FAILURE);
	if (!(dirp = opendir(autocmp->fullpath)))
		return (EXIT_FAILURE);
	autocmp->name_len = ft_strlen(autocmp->name);
	if (get_matching_entries(dirp, autocmp, &lst))
		return (EXIT_FAILURE);
	return (treat_entries(line, lst, autocmp));
}
