/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 15:34:34 by hdelaby           #+#    #+#             */
/*   Updated: 2017/06/08 15:06:39 by jfourne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANIP_ENV_H
# define MANIP_ENV_H

# include "libft.h"

char	*ft_getenv(const char *name, char **env);
int		ft_setenv(const char *name, const char *value,
		int overwrite, char ***env);
int		ft_unsetenv(const char *name, char ***env);
void	unset_no_value(const char *name, char ***env);

#endif
