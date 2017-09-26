/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 15:27:03 by hdelaby           #+#    #+#             */
/*   Updated: 2017/05/24 10:27:57 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "execution.h"

static int	execute_cmd(char **args, t_sh *shell, char **new_env)
{
	char	**ptr;
	int		ret;

	ptr = shell->env;
	shell->env = new_env;
	ret = execute_command(shell, args);
	shell->env = ptr;
	return (ret);
}

static void	env_ill_opt(char c)
{
	ft_putstr_fd("env: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd("\nusage: env [-i] [KEY=value ...] [utility [arg ...]]", 2);
}

static int	env_opt(char **args, int *i, int ret)
{
	int		j;

	while (args[*i] && args[*i][0] == '-')
	{
		j = 1;
		if (!ft_strcmp(args[*i], "--"))
		{
			*i += 1;
			return (ret);
		}
		while (args[*i][j] != '\0')
		{
			if (args[*i][j] == 'i')
				ret = 1;
			else
			{
				env_ill_opt(args[*i][j]);
				return (-1);
			}
			j++;
		}
		*i += 1;
	}
	return (ret);
}

int			bi_env(char **args, t_sh *shell)
{
	int		i;
	int		has_opt;
	char	**new_env;
	char	*tmp;

	i = 1;
	if ((has_opt = env_opt(args, &i, 0)) == -1)
		return (1);
	new_env = has_opt ? NULL : ft_tabcpy(shell->env);
	while (args[i] && (tmp = ft_strchr(args[i], '=')))
	{
		*tmp = '\0';
		tmp++;
		ft_setenv(args[i], tmp, 1, &new_env);
		i++;
	}
	has_opt = 0;
	if (args[i])
		has_opt = execute_cmd(args + i, shell, new_env);
	else
		ft_puttab(new_env);
	ft_tabdel(new_env);
	return (has_opt);
}
