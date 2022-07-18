/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 17:24:44 by yboudoui          #+#    #+#             */
/*   Updated: 2022/07/18 17:07:16 by yboudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

const t_error	g_default = {NULL, NULL};

const t_error	g_failure = {"Unable to create an error for failure", NULL};

const t_error	g_w_input = {"Wrong input", NULL};

static	unsigned int	ft_strlen(const char *str)
{
	unsigned int	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}
bool	error_check(t_error err, bool print_log)
{
	if (print_log)
		write(STDOUT_FILENO, err.message, ft_strlen(err.message));
	return (err.message);
}

t_error	error_new(const char *message, void *data)
{
	t_error		out;

	if ((!!message) == (!!data))
		out = (t_error)g_failure;
	else
		out = (t_error){message, data};
	return (out);
}

t_error	error_try(void *data, void (*free)(void *), t_handler *handlers)
{
	t_error	err;
	if (!handlers->func)
		return ((t_error)g_default);
	err = handlers->func(data, handlers);
	if (free)
		free(data);
	return (err);
}

t_error	error_try_next(void *data, void (*free)(void *), t_handler *handlers)
{
	return (error_try(data, free, handlers + 1));
}
