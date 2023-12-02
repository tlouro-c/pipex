/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 02:00:48 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/02 02:26:43 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>

enum e_mode
{
	OVERWRITE,
	APPEND
};

typedef struct s_info
{
	pid_t		*pid;
	int			infile;
	char		*infile_name;
	char		*outfile;
	int			nr_cmd;
	enum e_mode	mode;
	int			i;
	char		*limiter;
}	t_info;

void	main_process(t_info info, pid_t **pid, char ***cmd, int ***pipedes);
void	child_process(char ***cmd, int **pipedes, t_info info, char *envp[]);

void	free_int_ptr_exit(int **ptr);
char	***free_cmd(char ***cmd, int nr_cmd);
void	quick_free_exit(int ***pipedes, pid_t **pid, int nr_pipes);
void	error_waiting(int **pid, char ***cmd, int ***pipedes, int nr_pipes);
void	not_enough_args(void);
char	**ft_free_str_arr2(char **array);
void	error_child(int ***pipedes, pid_t **pid, char ***cmd, int nr_pipes);

void	close_all_pipes(int **pipedes, int nr_pipes);
void	close_pipes_main(t_info info, int **pipedes);
void	close_pipes_child(t_info info, int **pipedes);

void	create_pipes(t_info info, int ***pipedes, pid_t **pid);
void	alloc_mem(pid_t **pid, int ***pipedes, t_info info);
t_info	get_info(int argc, char *argv[]);

char	*get_cmd(char *s);
char	***get_cmds(int argc, char *argv[], char *envp[]);
char	*ft_strjoin_free2(char const *s1, char *s2);
void	free_and_exit_get_cmds(char ***cmds, char **paths, char *cmd, int nr);
char	*env_key(char *key, char *envp[]);
void	error_forking(int ***pipedes, pid_t **pid, char ***cmd, int nr_pipes);
int		env_strcmp(char *s1, char *s2);
void	setup_here_doc(t_info *info);

#endif /* PIPEX_H */
