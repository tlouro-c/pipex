/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_cmd2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:03:38 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/01 23:04:59 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

char	*ft_strjoin_free2(char const *s1, char *s2)
{
	char	*s3;
	int		j;
	int		i;

	s3 = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s3)
		return (s3);
	j = 0;
	i = 0;
	while (s1[i] != '\0')
		s3[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		s3[j++] = s2[i++];
	s3[j] = '\0';
	free(s2);
	return (s3);
}

void	free_and_exit_get_cmds(char ***cmds, char **paths, char *cmd, int nr)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("command not found\n", 2);
	ft_free_str_arr2(paths);
	free_cmd(cmds, nr);
	exit(EXIT_FAILURE);
}

int	env_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '=' && s1[i] == s2[i] && s1[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*env_key(char *key, char *envp[])
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (env_strcmp(key, envp[i]) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}
