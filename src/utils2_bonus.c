/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:43:05 by pdolinar          #+#    #+#             */
/*   Updated: 2022/05/02 15:15:45 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* return error message for invalid bash command*/
void	error_path(char **cmd)
{
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": command not found\n", 20);
	free_double_p(cmd);
	exit(127);
}

/* 	return message if pid or file descriptor is invalid */
void	fd_pid_error(int fd, pid_t pid)
{
	if (pid == -1)
	{
		perror("Failed to fork");
		exit(EXIT_FAILURE);
	}
	if (fd < 0)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		exit(errno);
	}
}

/* return message if pipefd is invalid */
void	pipe_check(int pipefd[])
{
	if (pipe(pipefd) == -1)
	{
		write(2, "Failed to pipe\n", 16);
		exit(EXIT_FAILURE);
	}
}

char	*ft_custom_strjoin(char const *s1, char const *s2, char const *s3)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	str = malloc(sizeof(char) * len + 1);
	if (!(str))
		return (NULL);
	ft_memcpy(str, s1, ft_strlen(s1));
	ft_memcpy(str + ft_strlen(s1), s2, ft_strlen(s2));
	ft_memcpy(str + ft_strlen(s1) + ft_strlen(s2), s3, ft_strlen(s3));
	str[len] = '\0';
	return (str);
}
