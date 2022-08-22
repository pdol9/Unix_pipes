/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:43:05 by pdolinar          #+#    #+#             */
/*   Updated: 2022/04/29 23:54:36 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

/*	Child process opens a file(gets assigned a new file descriptor),
	redirects its fd to a pipe, fetches the path of a bash command and
	starts a new process and writes the output to a pipe.
*/
static void	child_process(int pipefd[], char **argv, char **envp, pid_t pid)
{
	char	**cmd2;
	char	*path;
	int		read_file;

	read_file = open(argv[1], O_RDONLY, 0644);
	if (read_file < 0)
		fd_error(pid);
	if (dup2(read_file, STDIN_FILENO) < 0)
		fd_error(pid);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		fd_error(pid);
	close(read_file);
	close(pipefd[0]);
	close(pipefd[1]);
	cmd2 = set_cmd(argv, pid);
	path = parse_path(envp, cmd2);
	if (path == NULL)
		error_path(cmd2);
	run_cmd(path, cmd2, envp);
}

/*	Parent process reads output of a pipe, finds the path 
	to binaries, starts a new process and writes result of it
	to a new file.
*/
static void	parent_process(int pipefd[], char **argv, char **envp, pid_t pid)
{
	char	**cmd1;
	char	*path;
	int		write_file;

	waitpid(-1, NULL, WNOHANG);
	write_file = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (write_file < 0)
		fd_error(pid);
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		fd_error(pid);
	if (dup2(write_file, STDOUT_FILENO) < 0)
		fd_error(pid);
	close(pipefd[1]);
	close(pipefd[0]);
	close(write_file);
	cmd1 = set_cmd(argv, pid);
	path = parse_path(envp, cmd1);
	if (path == NULL)
		error_path(cmd1);
	run_cmd(path, cmd1, envp);
}

/* fork the process */
static void	ft_fork(int pipefd[], char **argv, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		fd_error(pid);
	if (pid == 0)
		child_process(pipefd, argv, envp, pid);
	parent_process(pipefd, argv, envp, pid);
	exit(errno);
}

int	main(int argc, char **argv, char **envp)
{
	int	pipefd[2];

	if (argc != 5)
	{
		write(2, "Use correct number of arguments !\n", 34);
		exit(EXIT_FAILURE);
	}
	if (pipe(pipefd) == -1)
	{
		write(2, "Failed to pipe\n", 16);
		exit(EXIT_FAILURE);
	}
	ft_fork(pipefd, argv, envp);
	exit(EXIT_FAILURE);
}
