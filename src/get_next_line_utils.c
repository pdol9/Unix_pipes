/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 01:42:40 by pdolinar          #+#    #+#             */
/*   Updated: 2022/04/26 22:15:04 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* set all elements of a string to 0 (i.e. '\0') */

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*i;

	i = (unsigned char *)s;
	while (n > 0)
	{
		*i = '\0';
		i++;
		n--;
	}
}

/* fetch the length of a string */

size_t	ft_strlen(const char *str)
{
	size_t	counter;

	if (!str)
		return (0);
	counter = 0;
	while (str[counter] != '\0')
		counter++;
	return (counter);
}

/*  function similar to original calloc from stdlib.h which allocates
	the	memory with given size (number of bytes * size of char)	on heap,
	set it to '\0' and returns a pointer to that memory location.
*/

char	*ft_calloc(size_t count, size_t size)
{
	void	*s;

	s = malloc(count * size);
	if (!s)
		return (NULL);
	ft_bzero(s, count * size);
	return (s);
}

/*  concatenate two strings to a new memory location, free 1. string
	and return a pointer to a new concatenated string.
*/

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1)
		return (ft_custom_strdup(s2, ft_strlen(s2)));
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	if (s1)
		free(s1);
	return (str);
}

/* copy a string to a new memory location and return a pointer to it */

char	*ft_custom_strdup(const char *s, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	str = malloc(sizeof(char) * (len + 1));
	if (!(str))
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[len] = '\0';
	return (str);
}
