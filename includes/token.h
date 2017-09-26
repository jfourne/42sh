/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 10:47:19 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/07 16:03:14 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "shell.h"
# include "libft.h"
# include "ast.h"

# define MAX_TOKEN_LEN 512

typedef struct	s_token
{
	char	str[MAX_TOKEN_LEN];
	char	*line;
	char	*ptr;
	int		index;
	int		type;
}				t_token;

int				end_token(t_token *tok, t_tok **lst);
int				token_add_char(t_token *tok, char c);
t_tok			*toknew(char *word, int type);
void			tokpush(t_tok **head, t_tok *node);

#endif
