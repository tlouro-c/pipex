/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:43:58 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/02 12:39:02 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	not_enough_args(void)
{
	ft_putstr_fd("Error: Please provide at least 4 arguments\n", 2);
	exit (1);
}

void	quick_free_exit(int ***pipedes, pid_t **pid, int nr_pipes)
{
	int	i;

	i = 0;
	free(*pid);
	*pid = NULL;
	while (i < nr_pipes)
	{
		free((*pipedes)[i]);
		(*pipedes)[i] = NULL;
		i++;
	}
	free(*pipedes);
	*pipedes = NULL;
	exit(2);
}

char	***free_cmd(char ****cmd, int nr_cmd)
{
	int	i;

	i = 0;
	while (i < nr_cmd)
	{
		ft_free_str_arr2(&(*cmd)[i]);
		i++;
	}
	free(*cmd);
	*cmd = NULL;
	return (NULL);
}

void	error_waiting(int **pid, char ***cmd, int ***pipedes, int nr_pipes)
{
	free_cmd(&cmd, nr_pipes);
	ft_putstr_fd("Error waiting for child process", STDERR_FILENO);
	quick_free_exit(pipedes, pid, nr_pipes);
}

char	**ft_free_str_arr2(char ***array)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while ((*array)[i] != NULL)
	{
		size++;
		i++;
	}
	i = 0;
	while (i < size)
	{
		free((*array)[i]);
		(*array)[i] = NULL;
		i++;
	}
	free(*array);
	return (NULL);
}
