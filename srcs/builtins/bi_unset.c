/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:27:25 by jfourne           #+#    #+#             */
/*   Updated: 2017/06/08 14:55:41 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "manip_env.h"

void		unset_no_value(const char *name, char ***env)
{
	int		i;
	char	**entry;

	i = 0;
	entry = NULL;
	while (env && *env && (*env)[i])
	{
		if (ft_strcmp(name, (*env)[i]) == 0)
			entry = &((*env)[i]);
		i++;
	}
	if (entry)
		*env = ft_tabremove(*env, (size_t)(entry - *env));
}

int			bi_unset(char **args, t_sh *shell)
{
	if (args[1] == NULL)
		return (-1);
	args++;
	while (*args)
	{
		unset_no_value(*args, &shell->env);
		ft_unsetenv(*args, &shell->env);
		ft_unsetenv(*args, &shell->local);
		args++;
	}
	return (0);
}
