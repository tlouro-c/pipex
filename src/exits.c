/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:43:58 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/04 19:12:07 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	not_enough_args(int argc, char *argv[], char *envp[])
{
	if (argc < 2)
		ft_putstr_fd("Error: Please provide at least 4 arguments\n", 2);
	else if (ft_strcmp("here_doc", argv[1]) != 0)
		ft_putstr_fd("Error: You must provide at least 4 arguments:\
 ./pipex file1 cmd1 cmd2 file2\n", 2);
	else if (envp == NULL)
		ft_putstr_fd("Error: Error finding needed enviroment variables\n", 2);
	else
		ft_putstr_fd("Error: You must provide at least 5 arguments when you're\
 using here_doc: ./pipex here_doc LIMITER cmd cmd1 file\n", 2);
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
	int	j;

	i = 0;
	while (i < nr_cmd)
	{
		j = 0;
		while (j < 4)
		{
			free((*cmd)[i][j]);
			j++;
		}
		free((*cmd)[i]);
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
