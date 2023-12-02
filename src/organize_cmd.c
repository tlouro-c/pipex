/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:07:01 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/02 13:09:36 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

char	*get_option(char *s)
{
	char	*option;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (s[i] != '-' && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		return (NULL);
	k = i;
	j = 0;
	while (!ft_isspace(s[i++]))
		j++;
	option = (char *)malloc(j + 1);
	if (option == NULL)
		return (NULL);
	j = 0;
	while (!ft_isspace(s[k]))
		option[j++] = s[k++];
	option[j] = '\0';
	return (option);
}

static void	fill(char **arr, char *cmd, char *option)
{
	free(arr[0]);
	free(arr[1]);
	arr[0] = cmd;
	arr[1] = option;
}

char	***get_cmds_loop(int argc, char *argv[], char **paths, char ***cmds)
{
	char			*path;
	static int		k;
	int				i;
	int				j;
	int				status;

	i = 1 + (ft_strcmp(argv[1], "here_doc") == 0);
	while (++i < argc - 1)
	{
		j = -1;
		while (paths[++j] != NULL)
		{
			path = ft_strjoin_free2(paths[j], get_cmd(argv[i]));
			status = access(path, X_OK);
			if (status == 0)
			{
				fill(cmds[k++], ft_strdup(path), get_option(argv[i]));
				break ;
			}
			free(path);
		}
		if (status != 0)
			free_and_exit_get_cmds(&cmds, &paths, argv[i], i);
	}
	return (cmds);
}

char	***get_cmds(int argc, char *argv[], char *envp[])
{
	char	**paths;
	char	***cmds;
	int		i;

	paths = ft_split(env_key("PATH=", envp) + 5, ':');
	if (paths == NULL)
		return (NULL);
	cmds = (char ***)malloc((argc - 3 - (ft_strcmp(argv[1], "here_doc") == 0))
			* sizeof(char **));
	if (cmds == NULL)
		return ((char ***)ft_free_str_arr2(&paths));
	i = 0;
	while (i < argc - 3 - (ft_strcmp(argv[1], "here_doc") == 0))
	{
		cmds[i] = (char **)malloc(3 * sizeof(char *));
		if (cmds[i] == NULL)
		{
			ft_free_str_arr2(&paths);
			return (free_cmd(&cmds, i - 1));
		}
		cmds[i++][2] = NULL;
	}
	get_cmds_loop(argc, argv, paths, cmds);
	ft_free_str_arr2(&paths);
	return (cmds);
}
