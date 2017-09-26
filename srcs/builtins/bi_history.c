/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 10:26:27 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/23 14:58:15 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

#define OPT_CLR 1
#define OPT_DEL 2

static int	hist_tail(char **args, t_sh *shell)
{
	size_t	offset;
	t_dlist	*lst;

	if (*args && ft_isnumber(*args))
		offset = ft_atoi(*args);
	else
		return (-1);
	lst = ft_dlstgettail(shell->hist);
	lst = ft_dlstgetn(lst, offset);
	if (!lst)
	{
		ft_putendl_fd("history: Not enough history entries.", 2);
		return (1);
	}
	print_hist(lst, offset);
	return (0);
}

static int	hist_delete(char **args, t_sh *shell)
{
	size_t	offset;
	t_dlist *lst;

	if (*args && ft_isnumber(*args))
		offset = ft_atoi(*args);
	else
	{
		ft_putendl_fd("usage: history -d offset\noffset must be a number", 2);
		return (1);
	}
	lst = ft_dlstgettail(shell->hist);
	lst = ft_dlstgetn(lst, offset);
	if (!lst)
	{
		ft_putendl_fd("history: Not enough history entries.", 2);
		return (1);
	}
	ft_dlstremovenode(&lst);
	shell->hist = ft_dlstgethead(lst);
	return (0);
}

static int	hist_clear(t_sh *shell)
{
	while (shell->hist)
		ft_dlstremovenode(&shell->hist);
	shell->hist = NULL;
	return (0);
}

static int	hist_get_option(char *args, int *opt_flag)
{
	args++;
	while (*args)
	{
		if (*args == 'c')
			*opt_flag |= OPT_CLR;
		else if (*args == 'd')
			*opt_flag |= OPT_DEL;
		else
		{
			ft_putstr_fd("history: illegal option -- ", 2);
			ft_putchar_fd(*args, 2);
			ft_putendl_fd("\nusage: history [-cd] [offset]", 2);
			return (1);
		}
		args++;
	}
	return (0);
}

int			bi_history(char **args, t_sh *shell)
{
	int		opt_flag;

	args++;
	if ((opt_flag = hist_tail(args, shell)) != -1)
		return (opt_flag);
	opt_flag = 0;
	while (*args && **args == '-')
		if (hist_get_option(*args++, &opt_flag))
			return (1);
	if (opt_flag & OPT_CLR)
		hist_clear(shell);
	else if (opt_flag & OPT_DEL)
	{
		if (hist_delete(args, shell))
			return (1);
	}
	else
		print_hist(ft_dlstgettail(shell->hist), 1);
	return (0);
}
