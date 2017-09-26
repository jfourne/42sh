/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 15:30:04 by jfourne           #+#    #+#             */
/*   Updated: 2017/06/19 14:09:47 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "lexerbis.h"

static void		init_grab(char **line, t_tok **tokens, t_sh *sh,
							t_grab_all *grab)
{
	grab->line = line;
	grab->tokens = tokens;
	grab->sh = sh;
}

static void		init_grab_next(t_quot *bs, t_replace *save, char **replace,
								t_grab_all *grab)
{
	grab->bs = bs;
	grab->save = save;
	grab->replace = replace;
}

int				ft_replace_recursive(char **line, t_tok **tokens, t_sh *sh,
										t_quot *bs)
{
	t_replace	save;
	char		*replace;
	t_grab_all	grab;

	replace = NULL;
	ft_bzero(&save, sizeof(t_replace));
	ft_bzero(&grab, sizeof(t_grab_all));
	init_grab(line, tokens, sh, &grab);
	init_grab_next(bs, &save, &replace, &grab);
	while ((*line)[save.i])
	{
		grab.bs->inib = 0;
		check_backslash(&grab);
		if (check_simple_quot(&grab) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else if (check_bquot(&grab, 0, NULL) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else if (check_others(line, &save, sh, bs) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (save.i == -1 || (*line)[save.i] != '\0')
			save.i++;
	}
	return (EXIT_SUCCESS);
}

void			ft_check_replace(t_tok **tokens, t_sh *sh)
{
	t_quot		bs;

	ft_bzero(&bs, sizeof(t_quot));
	if (!(*tokens)->lex)
		return ;
	ft_replace_recursive((&(*tokens)->lex), tokens, sh, &bs);
}
