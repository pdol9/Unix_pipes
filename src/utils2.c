/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:43:05 by pdolinar          #+#    #+#             */
/*   Updated: 2022/05/03 16:35:18 by pdolinar         ###   ########.fr       */
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

/* 	return message if file descriptor (fd) or pid is invalid */
void	fd_error(pid_t pid)
{
	if (pid == -1)
	{
		perror("Failed to fork");
		exit(EXIT_FAILURE);
	}
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	exit(errno);
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

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	while (*s++ != '\0')
		counter++;
	return (counter);
}
