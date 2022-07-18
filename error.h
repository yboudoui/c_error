/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 19:24:35 by yboudoui          #+#    #+#             */
/*   Updated: 2022/07/18 17:07:46 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdbool.h>
# include <unistd.h>

typedef struct s_error{
	const char	*message;
	void		*data;
}	t_error;

typedef union u_handler	t_handler;
typedef t_error			(*t_ft_handler)(void *, t_handler *);
union u_handler {
	t_ft_handler	func;
};

t_error	error_try(void *data, void (*free)(void *), t_handler *handlers);
t_error	error_try_next(void *data, void (*free)(void *), t_handler *handlers);
t_error	error_new(const char *message, void *data);
bool	error_check(t_error err, bool print_log);

extern const t_error	g_default;
extern const t_error	g_failure;
extern const t_error	g_w_input;
#endif
