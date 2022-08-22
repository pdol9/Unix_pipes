/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:43:05 by pdolinar          #+#    #+#             */
/*   Updated: 2022/05/03 20:46:29 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* after forking is done, close fd and run cmd */
static void	ft_closefile(int num, int filefd[], char **argv, char**envp)
{
	close(filefd[0]);
	unlink("tmp");
	close(filefd[1]);
	ft_new_process(num, argv, envp);
}

/* open/create a file and return a fd to write to a file */
static int	ft_writefd(int num, int argc, char **argv)
{
	int	fd;
	int	i;

	if (num == 4)
		i = O_APPEND;
	else
		i = O_TRUNC;
	fd = open(argv[argc - 1], O_CREAT | O_WRONLY | i, 0644);
	fd_pid_error(fd, 0);
	return (fd);
}

/* return fd when opening a file or creating a tmp file */
static int	ft_readfd(int num, int fd, char *line, char **argv)
{
	if (num == 4)
	{
		fd = open("tmp", O_CREAT | O_RDWR, 0644);
		fd_pid_error(fd, 0);
		while (1)
		{
			if (write(1, "heredoc> ", 9) == -1)
				exit(EXIT_FAILURE);
			line = get_next_line(0);
			if (ft_strncmp(argv[2], line, ft_strlen(argv[2])) == 0)
				break ;
			if (write(fd, line, ft_strlen(line)) == -1)
			{
				free(line);
				exit(EXIT_FAILURE);
			}
			free(line);
		}
	}
	else
	{
		fd = open(argv[1], O_RDONLY, 0644);
		fd_pid_error(fd, 0);
	}
	return (fd);
}

/* start process of forking */
static void	ft_fork(int argc, char **argv, char **envp)
{
	int	pipefd[2];
	int	pid;
	int	num;

	num = return_num(argv);
	while (num < argc)
	{
		pipe(pipefd);
		pipe_check(pipefd);
		pid = fork();
		fd_pid_error(0, pid);
		if (pid == 0)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			ft_new_process(num, argv, envp);
		}
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		waitpid(-1, NULL, WNOHANG);
		num++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		filefd[2];
	char	*line;
	int		num;
	int		fd;

	fd = 0;
	line = NULL;
	if (argc < 5)
	{
		write(2, "Use correct number of arguments !\n", 34);
		exit(EXIT_FAILURE);
	}
	num = return_num(argv);
	filefd[0] = ft_readfd(num, fd, line, argv);
	if (num == 4)
	{
		close(filefd[0]);
		filefd[0] = open("tmp", O_RDONLY, 0644);
	}
	filefd[1] = ft_writefd(num, argc, argv);
	dup2(filefd[0], STDIN_FILENO);
	ft_fork(argc, argv, envp);
	dup2(filefd[1], STDOUT_FILENO);
	ft_closefile(num, filefd, argv, envp);
	exit(EXIT_SUCCESS);
}
