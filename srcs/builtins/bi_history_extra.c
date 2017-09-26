/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_history_extra.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 14:35:51 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/07 14:36:45 by hdelaby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void		print_hist(t_dlist *hist, size_t offset)
{
	if (!hist)
		return ;
	while (hist)
	{
		ft_putnbr(offset);
		ft_putchar(' ');
		ft_putendl(hist->content);
		hist = hist->prev;
		offset++;
	}
}
