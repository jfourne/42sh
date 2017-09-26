/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 13:07:51 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/13 13:08:34 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void		ft_tokdel(t_tok *head)
{
	if (!head)
		return ;
	ft_tokdel(head->next);
	if (head->lex)
		free(head->lex);
	free(head);
}
