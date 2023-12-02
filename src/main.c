/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 02:00:48 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/02 13:17:10 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_info	info;
	char	***cmd;
	int		**pipedes;

	if (argc < 5)
		not_enough_args();
	info = get_info(argc, argv);
	cmd = get_cmds(argc, argv, envp);
	alloc_mem(&info.pid, &pipedes, info);
	create_pipes(info, &pipedes, &info.pid);
	while (info.i < info.nr_cmd)
	{
		info.pid[info.i] = fork();
		if (info.pid[info.i] < 0)
			error_forking(&pipedes, &info.pid, cmd, info.nr_cmd);
		if (info.pid[info.i] == 0)
			child_process(cmd, pipedes, info, envp);
		info.i++;
	}
	main_process(info, &info.pid, cmd, &pipedes);
	return (0);
}
