/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:24:26 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/02 02:46:31 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

static void	first_child(t_info info);
static void	child(t_info info, int *pipedes[]);

void	child_process(char ***cmd, int **pipedes, t_info info, char *envp[])
{
	close_pipes_child(info, pipedes);
	if (info.i == 0)
		first_child(info);
	else
		child(info, pipedes);
	dup2(pipedes[info.i][1], STDOUT_FILENO);
	close(pipedes[info.i][1]);
	execve(cmd[info.i][0], cmd[info.i], envp);
	perror("Error");
	error_child(&pipedes, &info.pid, cmd, info.nr_cmd);
	exit(EXIT_FAILURE);
}

static void	child(t_info info, int *pipedes[])
{
	if (info.i == 1 && info.mode == APPEND)
		unlink(info.infile_name);
	dup2(pipedes[info.i - 1][0], STDIN_FILENO);
	close(pipedes[info.i - 1][0]);
}

static void	first_child(t_info info)
{
	dup2(info.infile, STDIN_FILENO);
	close(info.infile);
	if (info.mode == APPEND)
		unlink(info.infile_name);
}
