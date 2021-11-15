/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <fle-blay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 12:01:59 by fle-blay          #+#    #+#             */
/*   Updated: 2021/11/15 11:34:05 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

unsigned int	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*copy;

	i = 0;
	copy = NULL;
	copy = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (! copy)
		return (NULL);
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strrawjoin(char const *s1, char const *s2, int s2size)
{
	char	*join;
	int		i;

	join = NULL;
	i = 0;
	if (! s1 && ! s2)
		return (NULL);
	join = (char *)malloc((ft_strlen(s1) + s2size + 1) * sizeof(char));
	if (! join)
		return (NULL);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2size)
	{
		join[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	join[ft_strlen(s1) + i] = '\0';
	return (join);
}

char	*ft_substr(char const *s, unsigned int start, unsigned int len)
{
	unsigned int	i;
	unsigned int	lensub;
	char			*subs;

	i = 0;
	if (! s)
		 return (NULL);
	subs = NULL;
	if (start > ft_strlen(s))
		lensub = 0;
	else if (ft_strlen(s) - start < len)
		lensub = ft_strlen(s) - start;
	else
		lensub = len;
	subs = (char *)malloc((lensub + 1) * sizeof(char));
	if (! subs)
		return (NULL);
	while (i < lensub)
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}
