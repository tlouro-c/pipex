/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:39:10 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/04 19:35:13 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	error_forking(int ***pipedes, pid_t **pid, char ***cmd, int nr_pipes)
{
	free_cmd(&cmd, nr_pipes);
	ft_putstr_fd("Error forking", 2);
	quick_free_exit(pipedes, pid, nr_pipes);
}

void	error_child(int ***pipedes, pid_t **pid, char ***cmd, int nr_pipes)
{
	free_cmd(&cmd, nr_pipes);
	quick_free_exit(pipedes, pid, nr_pipes);
}

void	free_int_ptr_exit(int **ptr)
{
	free(*ptr);
	ptr = NULL;
	exit(2);
}

void	env_missing()
{
	ft_putstr_fd("Error: Needed enviroment variables not found\n", 2);
	exit (1);
}
