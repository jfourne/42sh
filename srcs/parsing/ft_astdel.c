/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_astdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 13:19:12 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/01 11:31:57 by robechon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "execution.h"

void	ft_astdel(t_ast *head)
{
	if (!head)
		return ;
	free_redir(head);
	ft_astdel(head->left);
	ft_astdel(head->right);
	if (head->args)
		ft_tabdel(head->args);
	free(head);
}
