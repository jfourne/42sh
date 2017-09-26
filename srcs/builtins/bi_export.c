/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:05:06 by jfourne           #+#    #+#             */
/*   Updated: 2017/06/12 13:31:02 by robechon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "manip_env.h"
#include "execution.h"
#include "sh_error.h"

static int	first_check(char *curr_arg, char *equal)
{
	int		i;

	i = 0;
	while (curr_arg[i] && &(curr_arg[i]) != equal)
	{
		if (ft_isalpha(curr_arg[0]) != 1 || (curr_arg[i] != '_' &&
					ft_isalnum(curr_arg[i]) != 1))
			return (ft_puterr("export", "not a valid identifier", curr_arg, 1));
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	ft_dtab_print(char **tab)
{
	int		i;

	i = 0;
	while (tab && tab[i])
	{
		ft_putendl(tab[i]);
		i++;
	}
}

static int	export_no_value(char *arg, char **env)
{
	int		i;
	char	*equal;

	i = 0;
	while (env && env[i])
	{
		equal = ft_strchr(env[i], '=');
		if (ft_strncmp(arg, env[i], equal - env[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	export_value(char *equal, char *curr_arg, t_sh *shell)
{
	if (equal)
	{
		*equal = '\0';
		equal++;
		unset_no_value(curr_arg, &shell->env);
		ft_setenv(curr_arg, equal, 1, &shell->env);
	}
	else
	{
		if ((equal = ft_getenv(curr_arg, shell->local)) != NULL)
			ft_setenv(curr_arg, equal, 1, &shell->env);
		else if (!export_no_value(curr_arg, shell->env))
			shell->env = ft_tabadd(shell->env, curr_arg);
	}
}

int			bi_export(char **args, t_sh *shell)
{
	char	*equal;
	char	*curr_arg;

	args++;
	if (!(*args) || (*args && !(ft_strcmp(*args, "-p")) && !*(++args)))
		ft_dtab_print(shell->env);
	while (*args)
	{
		curr_arg = *args;
		equal = ft_strchr(curr_arg, '=');
		if (first_check(curr_arg, equal) == EXIT_SUCCESS)
			export_value(equal, curr_arg, shell);
		args++;
	}
	return (EXIT_SUCCESS);
}
