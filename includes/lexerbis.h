/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerbis.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 10:58:16 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/13 13:49:17 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXERBIS_H
# define LEXERBIS_H

# include "shell.h"
# include "token.h"
# include "ast.h"

typedef struct	s_lextab
{
	char	key;
	int		(*fct)(t_sh *sh, t_token *tok, t_tok **lst);
}				t_lextab;

t_tok			*lexer(t_sh *sh, char *line);

int				complete_command(t_sh *sh, t_token *tok, char *prompt);
int				add_history(t_sh *sh, char *line);
int				is_blank(char *str);
void			replace_newline(char *str);
void			ft_tokdel(t_tok *head);
int				replace_exclamation(char **line, t_sh *sh);
void			inutile(t_sh *sh, t_tok *tok);
int				handle_hdoc(t_tok *tok, t_sh *sh);

int				handle_semico(t_sh *sh, t_token *tok, t_tok **lst);
int				handle_space(t_sh *sh, t_token *tok, t_tok **lst);
int				handle_pipe(t_sh *sh, t_token *tok, t_tok **lst);
int				handle_and(t_sh *sh, t_token *tok, t_tok **lst);
int				handle_inredir(t_sh *sh, t_token *tok, t_tok **lst);
int				handle_outredir(t_sh *sh, t_token *tok, t_tok **lst);
int				handle_dquote(t_sh *sh, t_token *tok, t_tok **lst);
int				handle_squote(t_sh *sh, t_token *tok, t_tok **lst);
int				handle_backslash(t_sh *sh, t_token *tok, t_tok **lst);
int				handle_backquote(t_sh *sh, t_token *tok, t_tok **lst);
int				handle_hashtag(t_sh *sh, t_token *tok, t_tok **lst);

#endif
