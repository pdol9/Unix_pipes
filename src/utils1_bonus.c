/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:43:05 by pdolinar          #+#    #+#             */
/*   Updated: 2022/05/02 15:22:38 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* 	return number of constants, i.e. arguments,
	when reading from a file or here_doc
*/
int	return_num(char **argv)
{
	int	num;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		num = 4;
	else
		num = 3;
	return (num);
}

/* run bash command */
void	ft_new_process(int num, char **argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv[num - 1], ' ');
	path = parse_path(envp, cmd);
	if (path == NULL)
		error_path(cmd);
	if (execve(path, cmd, envp) == -1)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
	free_double_p(cmd);
	exit(errno);
}

/*	get the path of bash command and verify it */
char	*parse_path(char **envp, char **cmd)
{
	char	**local_paths;
	char	*final_path;
	char	*path;
	int		i;

	if (access(cmd[0], X_OK) == 0)
		return (cmd[0]);
	path = find_path(envp);
	local_paths = ft_split(path, ':');
	i = 0;
	while (local_paths[i] != NULL)
	{
		final_path = ft_custom_strjoin(local_paths[i++], "/", cmd[0]);
		if (access(final_path, X_OK) == 0)
			break ;
		free(final_path);
		final_path = NULL;
	}
	free_double_p(local_paths);
	return (final_path);
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
