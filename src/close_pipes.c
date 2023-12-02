/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:53:07 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/02 01:57:55 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	close_pipes_child(t_info info, int **pipedes)
{
	int	i;

	i = 0;
	while (i < info.nr_cmd)
	{
		if (info.i == 0)
			close(pipedes[i][0]);
		else if (i != info.i - 1)
			close(pipedes[i][0]);
		if (i != info.i)
			close(pipedes[i][1]);
		i++;
	}
}

void	close_pipes_main(t_info info, int **pipedes)
{
	int	i;

	i = 0;
	while (i < info.nr_cmd)
	{
		close(pipedes[i][1]);
		if (i != info.i - 1)
			close(pipedes[i][0]);
		i++;
	}
}

void	close_all_pipes(int **pipedes, int nr_pipes)
{
	int	i;

	i = 0;
	while (i < nr_pipes)
	{
		close(pipedes[i][0]);
		close(pipedes[i][1]);
	}
}
