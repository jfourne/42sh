/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_backquote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 12:20:40 by jfourne           #+#    #+#             */
/*   Updated: 2017/06/20 09:29:41 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexerbis.h"

static char		*read_and_close(int *pipefd, t_tok *bq_tok)
{
	char		buf[1024];
	char		*buf_dup;
	int			ret;

	buf_dup = NULL;
	ret = read(pipefd[PREAD], buf, 1023);
	if (ret >= 0)
		buf[ret] = '\0';
	if (ret == 1 && buf[0] == '\n')
	{
		ft_tokdel(bq_tok);
		close(pipefd[PREAD]);
		return (buf_dup);
	}
	if (ret > 0)
		buf_dup = ft_strdup(buf);
	ft_tokdel(bq_tok);
	close(pipefd[PREAD]);
	return (buf_dup);
}

char			*replace_backquote(char *bq_line, t_sh *sh)
{
	pid_t		pid;
	t_tok		*bq_tok;
	int			pipefd[2];

	sh->is_interactive = 0;
	bq_tok = lexer(sh, bq_line);
	sh->is_interactive = 1;
	if (pipe(pipefd) == -1)
		ft_fatalerror(E_PIPE);
	if (!(pid = fork()))
	{
		close(pipefd[PREAD]);
		duplicate(pipefd[PWRITE], STDOUT_FILENO);
		generate_ast(sh, bq_tok);
		exit(0);
	}
	else if (pid < 0)
		ft_fatalerror(E_FORK);
	close(pipefd[PWRITE]);
	wait(NULL);
	return (read_and_close(pipefd, bq_tok));
}
