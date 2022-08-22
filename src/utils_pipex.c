/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:43:05 by pdolinar          #+#    #+#             */
/*   Updated: 2022/05/03 16:35:50 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* start a new process which replaces the child/parent process */
void	run_cmd(char *path, char **cmd, char **envp)
{
	if (execve(path, cmd, envp) == -1)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
	free_double_p(cmd);
	exit(errno);
}

/* find PATH line in evnp variable */
char	*find_path(char **envp)
{
	char	*env_path;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		env_path = ft_strnstr(envp[i++], "PATH=", 5);
		if (env_path != NULL)
			break ;
	}
	return (env_path);
}

/* process the user's input (commands) into seperate strings */
char	**set_cmd(char **argv, pid_t pid)
{
	char	**split_cmd;
	int		i;

	if (pid == 0)
		i = 2;
	else
		i = 3;
	split_cmd = ft_split(argv[i], ' ');
	return (split_cmd);
}

/* free allocated memory - double pointer */
void	free_double_p(char **local_paths)
{
	int	i;

	i = 0;
	while (local_paths[i] != NULL)
		free(local_paths[i++]);
	free(local_paths[i]);
	free(local_paths);
}
