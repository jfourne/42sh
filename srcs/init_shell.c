/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/20 10:01:52 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/21 11:18:15 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_shell.h"

static void	init_env(t_sh *sh)
{
	char	buf[4096];
	char	*tmp;

	ft_bzero(&buf, 4096);
	if (!ft_getenv("PWD", sh->env))
	{
		if (getcwd(buf, 4096))
			ft_setenv("PWD", buf, 1, &sh->env);
	}
	if (!ft_getenv("SHLVL", sh->env))
		ft_setenv("SHLVL", "1", 1, &sh->env);
	else
	{
		if ((tmp = ft_itoa(ft_atoi(ft_getenv("SHLVL", sh->env)) + 1)))
		{
			ft_setenv("SHLVL", tmp, 1, &sh->env);
			free(tmp);
		}
		else
			ft_fatalerror(E_ALLOC);
	}
}

static void	run_start_commands(const char *path, t_sh *sh)
{
	int		fd;
	int		ret;
	char	*str;
	t_tok	*tok;

	if ((fd = open(path, O_RDONLY)) == -1)
		return ;
	while ((ret = get_next_line(fd, &str)) > 0)
	{
		tok = lexer(sh, str);
		generate_ast(sh, tok);
		ft_tokdel(tok);
	}
	close(fd);
}

static void	init_files(t_sh *sh)
{
	char	buf[1024];
	char	*homedir;

	ft_bzero(&buf, 1024);
	if (!(homedir = getenv("HOME")))
		homedir = getpwuid(getuid())->pw_dir;
	if (ft_strlen(homedir) + ft_strlen("./42sh_history") >= 1024)
		return ;
	ft_strcpy(buf, homedir);
	ft_strcat(buf, "/.42sh_history");
	ft_strcpy(sh->hist_path, buf);
	sh->hist = read_history_file(NULL, sh);
	if (ft_strlen(homedir) + ft_strlen("/.42shrc") >= 1024)
		return ;
	ft_bzero(&buf, 1024);
	ft_strcpy(buf, homedir);
	ft_strcat(buf, "/.42shrc");
	run_start_commands(buf, sh);
}

int			init_shell(char **env, t_sh *sh)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	ft_bzero(sh, sizeof(sh));
	if (!(sh->env = ft_tabcpy(env)))
		return (EXIT_FAILURE);
	init_env(sh);
	init_files(sh);
	sh->is_interactive = (isatty(STDIN_FILENO) ? 1 : 0);
	sh->prompt = 1;
	return (EXIT_SUCCESS);
}
