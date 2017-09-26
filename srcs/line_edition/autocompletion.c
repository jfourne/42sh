/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 15:28:55 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/09 14:56:54 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "autocompletion.h"
#include "sh_error.h"
#include "input_keys.h"

int		treat_entries(t_line *line, t_list *lst, t_autocmp *autocmp)
{
	int		ret;

	if (!lst)
		return (EXIT_SUCCESS);
	else if (autocmp->nb_entries == 1)
	{
		insert_word(line, lst->content + autocmp->name_len);
		ft_strlcat(autocmp->fullpath, "/", MAX_LINE_LEN);
		ft_strlcat(autocmp->fullpath, lst->content, MAX_LINE_LEN);
		ret = !ft_isdir(autocmp->fullpath) ? insert_char(line, '/') :
			insert_char(line, ' ');
	}
	else
		ret = print_col(lst, line, autocmp);
	ft_lstdel(&lst, &ft_lstdelstr);
	return (ret);
}

int		get_matching_entries(DIR *dirp, t_autocmp *autocmp, t_list **lst)
{
	t_list			*node;
	struct dirent	*dir;
	char			*tmp;

	while ((dir = readdir(dirp)))
	{
		if (!ft_strncmp(dir->d_name, autocmp->name, autocmp->name_len))
		{
			tmp = ft_strdup(dir->d_name);
			if (!tmp)
				ft_fatalerror(E_ALLOC);
			node = ft_lstnew(tmp, ft_strlen(tmp) + 1);
			free(tmp);
			if (!node)
				ft_fatalerror(E_ALLOC);
			autocmp->nb_entries++;
			autocmp->maxlen = ft_strlen(dir->d_name) > autocmp->maxlen ?
				ft_strlen(dir->d_name) : autocmp->maxlen;
			ft_lstaddback(lst, node);
		}
	}
	return (closedir(dirp));
}

/*
** We assume only 2 different scenarios. Either we need to autocomplete a
** command or an argument. 2 cases hence 2 define: ARG & CMD.
*/

int		determine_type(t_line *line)
{
	size_t	i;
	int		count;

	count = 0;
	if ((i = line->cursor) == 0)
		return (CMD);
	while (i != 0 && line->cmd[i] != ';' && line->cmd[i] != '|' &&
			line->cmd[i] != '&')
		i--;
	i = i ? i + 1 : 0;
	while (i < line->cursor)
	{
		if (line->cmd[i] && line->cmd[i] != ' ')
		{
			count++;
			while (line->cmd[i] && line->cmd[i] != ' ')
				i++;
		}
		else
			i++;
	}
	if (!count)
		return (CMD);
	return (count == 1 && line->cmd[line->cursor - 1] != ' ' ? CMD : ARG);
}

int		determine_dir(t_autocmp *autocmp)
{
	char	*backspace;
	int		mode;

	if ((backspace = ft_strrchr(autocmp->fullpath, '/')))
	{
		mode = backspace == autocmp->fullpath ? 0 : 1;
		*backspace = mode ? '\0' : *backspace;
		if (ft_strlen(backspace + 1) >= MAX_LINE_LEN)
			return (EXIT_FAILURE);
		ft_strcpy(autocmp->name, backspace + 1);
		backspace++;
		if (!mode && *backspace)
			*backspace = '\0';
		if (ft_isdir(autocmp->fullpath))
			return (42);
	}
	else
	{
		if (ft_strlen(autocmp->fullpath) >= MAX_LINE_LEN)
			return (EXIT_FAILURE);
		ft_strcpy(autocmp->name, autocmp->fullpath);
		if (!getcwd(autocmp->fullpath, MAX_LINE_LEN))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		autocompletion(t_line *line, t_sh *sh)
{
	t_autocmp	autocmp;
	size_t		i;
	int			ret;

	ft_bzero(&autocmp, sizeof(autocmp));
	i = line->cursor;
	while (i && line->cmd[i - 1] != ' ' && line->cmd[i - 1] != '|' &&
			line->cmd[i - 1] != '&')
		i--;
	ft_strcpy(autocmp.fullpath, line->cmd + i);
	ret = determine_type(line) == CMD ?
		complete_cmd(line, &autocmp, sh) : complete_arg(line, &autocmp);
	return (ret);
}
