#ifndef ERROR_H
# define ERROR_H

# include <stdlib.h>
# include <errno.h>

void	throw_params_count(void);
void	throw_params_value(void);
void	throw_mutex_init(t_mgc mgc);
void	throw_alloc_failed(t_mgc mgc);
void	try_alloc(t_mgc mgc, void *ptr);

#endif