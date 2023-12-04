/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:49:09 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/04 19:01:11 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

static void	write_to_outfile(t_info info, int ***pipedes, pid_t **pid);
static void	write_loop(int fd, int ***pipedes, t_info info, pid_t **pid);

void	main_process(t_info info, pid_t **pid, char ***cmd, int ***pipedes)
{
	int	i;

	close_pipes_main(info, *pipedes);
	i = 0;
	while (i < info.nr_cmd)
	{
		if (waitpid((*pid)[i], NULL, 0) < 0)
			error_waiting(pid, cmd, pipedes, info.nr_cmd);
		i++;
	}
	free_cmd(&cmd, info.nr_cmd);
	write_to_outfile(info, pipedes, pid);
	i = 0;
	free(*pid);
	*pid = NULL;
	while (i < info.nr_cmd)
	{
		free((*pipedes)[i]);
		(*pipedes)[i] = NULL;
		i++;
	}
	free(*pipedes);
	*pipedes = NULL;
}

static void	write_to_outfile(t_info info, int ***pipedes, pid_t **pid)
{
	int		fd;

	if (info.mode == OVERWRITE)
		fd = open(info.outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(info.outfile, O_APPEND | O_WRONLY | O_CREAT, 0777);
	if (fd < 0)
	{
		perror("Error opening/creating outfile: ");
		quick_free_exit(pipedes, pid, info.nr_cmd);
	}
	write_loop(fd, pipedes, info, pid);
}

static void	write_loop(int fd, int ***pipedes, t_info info, pid_t **pid)
{
	char	buffer[50];
	int		bytes_read;

	while (1)
	{
		bytes_read = 0;
		bytes_read = read((*pipedes)[info.i - 1][0], buffer, 50);
		if (bytes_read < 0)
		{
			perror("Error reading: ");
			quick_free_exit(pipedes, pid, info.nr_cmd);
		}
		else if (bytes_read == 0)
			break ;
		else
			write(fd, buffer, bytes_read);
	}
	close((*pipedes)[info.i - 1][0]);
	close(fd);
}
