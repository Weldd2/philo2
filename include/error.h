/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:39:37 by antoinemura       #+#    #+#             */
/*   Updated: 2025/03/05 15:39:38 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdlib.h>
# include <errno.h>

void	throw_params_count(void);
void	throw_params_value(void);
void	throw_mutex_init(t_mgc mgc);
void	try_alloc(t_mgc mgc, void *ptr);
void	throw_thread_create(t_mgc mgc);

#endif