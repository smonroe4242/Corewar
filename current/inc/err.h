/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jochang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 20:35:53 by jochang           #+#    #+#             */
/*   Updated: 2019/01/02 09:39:52 by smonroe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H
# define ERR_H

# include "../libft/libft.h"
# define RETURN_CHECK(x) if (x) return
//# include "../ft_printf/inc/ft_printf.h"

void	err_nofile(char *prog, int n);
void	err_invfile(char *prog, char *file);
void	err_invop(char *op, int l);
void	err_invarg(char *op, int l);
void	err_invflag(char c);
void	err_malloc(char *fun);
void	err_invheader(char *file);

#endif
