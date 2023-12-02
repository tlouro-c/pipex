/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:10:23 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/02 14:05:52 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

t_info	get_info(int argc, char *argv[])
{
	t_info	info;

	info.pid = NULL;
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		info.limiter = argv[2];
		setup_here_doc(&info);
		info.infile = open(info.infile_name, O_RDONLY);
		info.mode = APPEND;
	}
	else
	{
		info.infile = open(argv[1], O_RDONLY);
		if (info.infile < 0)
		{
			perror(argv[1]);
			close(info.infile);
			exit(EXIT_FAILURE);
		}
		info.mode = OVERWRITE;
	}
	info.nr_cmd = argc - 3 - (ft_strcmp(argv[1], "here_doc") == 0);
	info.outfile = argv[argc - 1];
	info.i = 0;
	return (info);
}

void	create_pipes(t_info info, int ***pipedes, pid_t **pid)
{
	int	i;

	i = 0;
	while (i < info.nr_cmd)
	{
		if (pipe((*pipedes)[i]) < 0)
		{
			perror("Error creating pipes: ");
			close_all_pipes(*pipedes, i);
			quick_free_exit(pipedes, pid, info.nr_cmd);
		}
		i++;
	}
}

void	alloc_mem(pid_t **pid, int ***pipedes, t_info info)
{
	int	i;

	*pid = (pid_t *)malloc(info.nr_cmd * sizeof(pid_t));
	if (*pid == NULL)
		exit(2);
	*pipedes = (int **)malloc((info.nr_cmd) * sizeof(int *));
	if (*pipedes == NULL)
		free_int_ptr_exit(pid);
	i = 0;
	while (i < info.nr_cmd)
	{
		(*pipedes)[i] = (int *)malloc(2 * sizeof(int));
		if ((*pipedes)[i] == NULL)
		{
			ft_putstr_fd("Error allocating memory", 2);
			close_all_pipes(*pipedes, i);
			quick_free_exit(pipedes, pid, i);
		}
		i++;
	}
}

static int	ft_strcmpnew(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (s1[i] == '\n' && s2[i] == '\n')
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' )
	{
		if (s1[i + 1] == '\n')
			break ;
		i++;
	}
	return (s1[i] - s2[i]);
}

void	setup_here_doc(t_info *info)
{
	char	*next_line;
	int		fd;

	info -> infile_name = "/tmp/here_doc_tmp";
	fd = open(info -> infile_name, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	while (1)
	{
		ft_mini_printf("pipe heredoc>");
		next_line = ft_get_next_line(0);
		if (next_line == NULL || ft_strcmpnew(next_line, info -> limiter) == 0)
		{
			free(next_line);
			break ;
		}
		else
		{
			write(fd, next_line, ft_strlen(next_line));
			free(next_line);
		}
	}
	close(fd);
}
