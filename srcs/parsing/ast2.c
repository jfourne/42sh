/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craffate <craffate@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:40:45 by craffate          #+#    #+#             */
/*   Updated: 2017/06/08 11:39:52 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "sh_error.h"

void	free_nodes(t_ast **left, t_ast **right)
{
	if (left)
	{
		ft_astdel(*left);
		*left = NULL;
	}
	if (right)
	{
		ft_astdel(*right);
		*right = NULL;
	}
}
