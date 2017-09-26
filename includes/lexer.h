/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfourne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 13:48:12 by jfourne           #+#    #+#             */
/*   Updated: 2017/06/13 15:02:50 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <fcntl.h>
# include <dirent.h>
# include "libft.h"
# include "ast.h"
# include "shell.h"
# include "line_edition.h"
# include "execution.h"
# include "sh_error.h"

typedef	struct	s_quot
{
	int			sq;
	int			dq;
	int			bq;
	int			inib;
}				t_quot;

typedef struct	s_replace
{
	int			a;
	int			b;
	int			i;
}				t_replace;

typedef struct	s_grab_all
{
	t_replace	*save;
	char		**replace;
	t_quot		*bs;
	t_tok		**tokens;
	t_sh		*sh;
	char		**line;
}				t_grab_all;

int				ft_replace_recursive(char **line, t_tok **tokens, t_sh *sh,
									t_quot *bs);
char			*replace_backquote(char *bq_line, t_sh *sh);
void			replace_it(char **line, t_replace *tkz, char *replace);
int				check_others(char**line, t_replace *save, t_sh *sh,
									t_quot *bs);
int				check_simple_quot(t_grab_all *grab);
int				check_bquot(t_grab_all *grab, int ret, t_tok *tmp);
int				check_backslash(t_grab_all *grab);
char			*search_hist_nb(char *line, t_sh *sh);
int				check_quote_end(t_grab_all *grab, char c);
int				check_quote_end_backslash(t_grab_all *grab, int i, char c);
char			*quot(char **line, t_replace *save, char c, t_grab_all *grab);
void			int_reverse(int *reverse);
char			*ft_strndup_bs(const char *s1, unsigned int i, unsigned int a,
						unsigned int n);
int				exclamation_error(char *line, t_replace save);
void			exclamation_quote(char *line, t_quot *bs, int i);
char			*choose_exclamation_next(t_replace *ex, char *tmp, t_sh *sh);
char			*choose_exclamation_modifier(t_replace *ex, char *tmp,
						t_sh *sh, char *replace);
int				exclamation_backquote(t_replace *save, char *line);
int				exclamation_replace_check(char **line, t_replace *save,
						t_sh *sh);
char			*search_hist_letter(char *line, t_replace *ex, t_sh *sh);
char			*search_last_cmd(t_sh *sh);

t_tok			*tok_node(const char *lex, const short type);
void			tok_push(t_tok **tokens, t_tok *new_tok);
void			tok_print(t_tok *tokens);
void			save_and_restore(int copy_fd[2], int mode);

#endif
