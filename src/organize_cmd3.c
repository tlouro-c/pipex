/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_cmd3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:31:04 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/01 17:32:05 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

static int	get_cmd_len(char *s)
{
	int		i;
	int		size;

	size = 1;
	i = 0;
	while (s[i] != '\0' && ft_isspace(s[i]) && i < 15)
		i++;
	size = i;
	while (s[size] != '\0' && !ft_isspace(s[size]) && i < 15)
		size++;
	return (size - i);
}

char	*get_cmd(char *s)
{
	char	*cmd;
	int		i;
	int		j;
	int		size;

	size = get_cmd_len(s);
	j = 0;
	i = 0;
	while (s[i] != '\0' && ft_isspace(s[i]) && i < 15)
		i++;
	cmd = (char *)malloc(size + 3);
	if (cmd == NULL)
		return (NULL);
	cmd[j++] = '/';
	if (size == 0)
		cmd[j++] = ' ';
	else
		while (s[i] != '\0' && !ft_isspace(s[i]) && j < size + 1)
			cmd[j++] = s[i++];
	cmd[j] = '\0';
	return (cmd);
}
