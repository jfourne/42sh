/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 16:02:48 by craffate          #+#    #+#             */
/*   Updated: 2017/06/13 14:00:10 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "shell.h"
# include "libft.h"

# define NODE_NEUTRAL 0
# define NODE_AND 1
# define NODE_OR 2

typedef enum		e_types
{
	TOK_ARG = 1,
	TOK_PIPE,
	TOK_SC,
	TOK_AND,
	TOK_OR,
	TOK_BG,
	TOK_INPUT,
	TOK_OUTPUT,
	TOK_HEREDOC,
	TOK_APPEND,
	TOK_UAS,
	TOK_LAS,
	TOK_RDWR,
	TOK_NOGLOB,
	TOK_END,
	TOK_BLANK
}					t_types;

typedef enum		e_redirs
{
	RD_INPUT = 1,
	RD_OUTPUT,
	RD_HEREDOC,
	RD_APPEND,
	RD_UAS,
	RD_LAS,
	RD_RDWR,
	RD_NOGLOB
}					t_redirs;

typedef struct		s_redir
{
	int				in_fd;
	int				out_fd;
	short			type;
	char			*redir;
	char			*word;
	struct s_redir	*next;
}					t_redir;

typedef struct		s_tok
{
	short			type;
	char			*lex;
	struct s_tok	*next;
}					t_tok;

typedef struct		s_tokenizer
{
	int				a;
	int				i;
	int				bs;
	t_tok			*tokens;
}					t_tokenizer;

typedef struct		s_ast
{
	short			type;
	char			**args;
	struct s_redir	*redir;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

/*
** AST functions
*/

int					arg_check(t_tok *tokens);
t_ast				*ast_arg_node(t_sh *sh, t_tok **tokens);
t_ast				*ast_node(const short type, t_ast *left, t_ast *right);
t_ast				*blank_node(void);
t_ast				*generate_ast(t_sh *sh, t_tok *tokens);
void				ast_push(t_ast **ast, t_ast *node, const short lr);

/*
** Utility functions
*/

char				**arr_push(char **arr, const char *s);
int					isredir(const short type);
size_t				arrlen(const char **arr);
t_tok				**tok_pacman(t_tok **tokens);
void				free_nodes(t_ast **left, t_ast **right);
void				free_tok(t_tok **tokens);
void				strpush(char **s, const char c);
void				ft_check_replace(t_tok **tokens, t_sh *sh);

/*
** Parsing functions
*/

t_tok				*tok_parsing(t_sh *sh, t_tok *tokens);

/*
** Error handling functions
*/

void				parse_error(t_tok *token);

t_ast				*ast_command(t_sh *sh, t_tok **tokens);
t_ast				*ast_pipe(t_sh *sh, t_tok **tokens);
t_ast				*ast_and_or(t_sh *sh, t_tok **tokens, int mode);
t_ast				*ast_arg(t_sh *sh, t_tok **tokens);

void				ft_astdel(t_ast *head);

#endif
