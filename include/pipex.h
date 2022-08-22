/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 02:12:33 by pdolinar          #+#    #+#             */
/*   Updated: 2022/05/03 16:46:37 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 300
# endif

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>

/* pipex functions */
char	*parse_path(char **envp, char **cmd);
char	*find_path(char **envp);
void	run_cmd(char *path, char **cmd, char **envp);
void	free_double_p(char **local_paths);
char	**set_cmd(char **argv, pid_t pid);
void	error_path(char **cmd);
void	fd_error(pid_t pid);

/* libft functions */
size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *str, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t size);
char	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s);
char	**ft_split(const char *s, char c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);

/* custom functions */
char	*ft_custom_strjoin(char const *s1, char const *s2, char const *s3);
char	*ft_custom_strdup(const char *s, size_t len);
char	*ft_gnl_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);

/* bonus functions */
void	ft_new_process(int num, char **argv, char **envp);
void	pipe_check(int pipefd[]);
void	fd_pid_error(int fd, pid_t pid);
int		return_num(char **argv);

#endif
