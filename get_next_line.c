/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <fle-blay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:01:05 by fle-blay          #+#    #+#             */
/*   Updated: 2021/11/17 11:14:38 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>

void	ft_bzero(void *s, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		((char *) s)[i] = '\0';
		i++;
	}
}

/*static char	*load_content(int fd, char **dest)
{
	char	buf[BUFFER_SIZE];
	char	*content;
	int		cntsize;

	ft_bzero(buf, BUFFER_SIZE);
	cntsize = read(fd, buf, BUFFER_SIZE);
	if (cntsize <= 0)
	{
		free(*dest);
		return (NULL);
	}
	content = ft_strrawjoin(*dest, buf, cntsize);
	if (! content)
	{	
		free(*dest);
		return (NULL);
	}
	free(*dest);
	*dest = NULL;
	return (content);
}*/

static char	*load_content(int fd, char **dest)
{
	char	buf[BUFFER_SIZE];
	char	*content;
	int		cntsize;

	ft_bzero(buf, BUFFER_SIZE);
	cntsize = read(fd, buf, BUFFER_SIZE);
	if (cntsize <= 0)
	{
		free(*dest);
		return (NULL);
	}
	content = ft_strrawjoin(*dest, buf, cntsize);
	if (! content)
	{	
		free(*dest);
		return (NULL);
	}
	free(*dest);
	*dest = NULL;
	return (content);
}

char	*get_next_line(int fd)
{
	static char	*mainstr = NULL;
	char		*tmp = NULL;
	char		*togive = NULL;

	if (! mainstr)
		mainstr = ft_strdup("\0");
	if (! mainstr)
		return (NULL);
	printf("mainstr : '%s'\n", mainstr);
	while (mainstr && ! ft_strchr(mainstr, '\n'))
	{
		mainstr = load_content(fd, &mainstr);
		printf(" main str pdt chargement : '%s'\n", mainstr);
	}
	if (! mainstr)
		return (NULL);
	printf("strchr(mainstr, \\n) - mainstr : %ld\n", ft_strchr(mainstr, '\n') - mainstr);
	togive = ft_substr(mainstr, 0, ft_strchr(mainstr, '\n') - mainstr + 1);
	if (! togive)
		return (NULL);
	printf("to give : '%s'\n", togive);
	tmp = ft_strdup(mainstr);
	printf(" tmp = mainstr : '%s'\n", tmp);
	free(mainstr);
	mainstr = ft_substr(tmp, ft_strchr(tmp, '\n') - tmp + 1, ft_strlen(tmp));
	printf(" main str restant : '%s'\n", mainstr);
	free(tmp);
	return (togive);
}

#include <fcntl.h>
#include <stdio.h>

int main (void)
{

	char *test;
	int	fd;

	fd = open("./test3.txt", O_RDONLY);
	test = NULL;

	while ((test = get_next_line(fd)) != NULL)
	{
		printf("test : %s", test);
		free (test);
		test = NULL;
	}

	return (0);
}
