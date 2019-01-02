/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 20:35:53 by jochang           #+#    #+#             */
/*   Updated: 2018/09/09 20:40:20 by jochang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H
# define ERR_H

# include "../libft/inc/libft.h"
# include "../ft_printf/inc/ft_printf.h"

void	err_nofile(char *prog, int n);
void	err_invfile(char *prog, char *file);
void	err_invop(char *op, int l);
void	err_invarg(char *op, int l);
void	err_invflag(char c);
void	err_malloc(char *fun);
void	err_invheader(char *file);

#endif
