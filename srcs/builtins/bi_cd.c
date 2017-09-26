/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 15:26:23 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/12 13:28:23 by robechon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*cd_get_arg(char *arg, char ***env)
{
	char	*path;

	if (!arg && !ft_getenv("HOME", *env))
	{
		ft_putendl_fd("cd: HOME is not set", 2);
		return (NULL);
	}
	else if (!arg)
		path = ft_getenv("HOME", *env);
	else if (!ft_strcmp(arg, "-"))
	{
		path = ft_getenv("OLDPWD", *env);
		if (!path)
			ft_putendl_fd("cd: OLDPWD is not set", 2);
	}
	else
		path = arg;
	return (path);
}

static char	*cd_get_fullpath(char *dir, char ***env)
{
	char	*fullpath;
	char	*tmp;
	char	buf[4096];

	ft_bzero(&buf, 4096);
	tmp = NULL;
	if (dir && dir[0] != '/')
	{
		if (!(ft_getenv("PWD", *env)))
			tmp = getcwd(buf, 4096);
		else
			tmp = ft_getenv("PWD", *env);
		if (!tmp)
			return (NULL);
		if (!(fullpath = ft_build_path(tmp, dir)))
			ft_fatalerror(E_ALLOC);
	}
	else if (dir)
		fullpath = ft_strdup(dir);
	else
		fullpath = ft_strdup("");
	return (fullpath);
}

int			cd_chg_env(char *path, char ***env, int has_opt)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 0);
	if (has_opt && !chdir(path))
	{
		ft_setenv("OLDPWD", buf, 1, env);
		free(buf);
		buf = NULL;
		buf = getcwd(buf, 0);
		ft_setenv("PWD", buf, 1, env);
	}
	else if (!chdir(path))
	{
		if (ft_getenv("PWD", *env))
			ft_setenv("OLDPWD", ft_getenv("PWD", *env), 1, env);
		ft_setenv("PWD", path, 1, env);
	}
	else
	{
		free(buf);
		return (1);
	}
	free(buf);
	return (0);
}

int			cd_path_errors(char **fullpath, char *dir, int has_opt, char *arg)
{
	if (!access(has_opt ? dir : *fullpath, F_OK))
		ft_puterr("cd", E_ACCES, arg, 1);
	else
		ft_puterr("cd", E_NOENT, arg, 1);
	ft_strdel(fullpath);
	return (1);
}

int			bi_cd(char **args, t_sh *shell)
{
	char	*fullpath;
	char	*dir;
	int		has_opt;

	has_opt = 0;
	args += 1;
	while (*args && *args[0] == '-')
		if (cd_get_option(*(args++), &has_opt))
		{
			args--;
			break ;
		}
	if (!(dir = cd_get_arg(*args, &shell->env))
			|| !(fullpath = cd_get_fullpath(dir, &shell->env)))
		return (1);
	ft_canon_path(&fullpath);
	if (cd_chg_env(has_opt ? dir : fullpath, &shell->env, has_opt))
		return (cd_path_errors(&fullpath, dir, has_opt, *args));
	if (*args && !ft_strcmp(*args, "-"))
		ft_putendl(ft_getenv("PWD", shell->env));
	free(fullpath);
	return (0);
}
