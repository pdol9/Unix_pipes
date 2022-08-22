/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdolinar <pdolinar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 18:43:15 by pdolinar          #+#    #+#             */
/*   Updated: 2022/05/03 16:43:00 by pdolinar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned char		*s1;
	unsigned char		*s2;
	size_t				i;

	i = 0;
	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] == s2[i] && (s1[i] || s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (*needle == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && (i != len))
	{
		j = 0;
		while (haystack[i + j] == needle[j])
		{
			if (needle[j + 1] == '\0' && ((i + j) < len))
				return ((char *)haystack + i);
			else
				j++;
		}
		i++;
	}
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	char	*dst1;
	char	*src1;
	size_t	i;

	dst1 = (char *)dest;
	src1 = (char *)src;
	if (!src && !dest)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dst1[i] = src1[i];
		i++;
	}
	return (dst1);
}

void	*ft_memset(void *str, int c, size_t n)
{
	size_t	i;
	char	*s;

	i = 0;
	s = (char *)str;
	while (i < n)
	{
		s[i] = c;
		i++;
	}
	return (s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	size_t	i;
	char	*new;

	size = ft_strlen(s);
	if (len > size)
		len = size;
	if (start > size)
		len = (0);
	if (s == 0)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!(new))
		return (NULL);
	new = ft_memset(new, '0', len);
	i = 0;
	s = s + start;
	while (i < len && s[i] != '\0')
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
