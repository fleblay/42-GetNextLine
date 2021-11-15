/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <fle-blay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:01:05 by fle-blay          #+#    #+#             */
/*   Updated: 2021/11/15 11:58:36 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

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

static char	*load_content(int fd, char **dest)
{
	char	buf[BUFFER_SIZE];
	char	*content;
	int		cntsize;

	ft_bzero(buf, BUFFER_SIZE);
	cntsize = read(fd, buf, BUFFER_SIZE);
	if (cntsize <= 0)
		return (NULL);
	content = ft_strrawjoin(*dest, buf, cntsize);
	if (! content)
		return (NULL);
	free(*dest);
	*dest = NULL;
	return (content);
}

char	*get_next_line(int fd)
{
	static char	*mainstr = NULL;
	char		*tmp = NULL;
	char		*togive = NULL;

	mainstr = (char *) malloc(sizeof(char));
	if (! mainstr)
		return (NULL);
	mainstr[0] = '\0';
	while (! ft_strchr(mainstr, '\n'))
		mainstr = load_content(fd, &mainstr);
	togive = ft_substr(mainstr, 0, ft_strchr(mainstr, '\n') - mainstr + 2);
	tmp = ft_strdup(mainstr);
	free(mainstr);
	mainstr = ft_substr(tmp, ft_strchr(tmp, '\n') - tmp + 1, ft_strlen(tmp));
	free(tmp);
	return (togive);
}

#include <fcntl.h>
#include <stdio.h>

int main (void)
{

	char *test;
	int	fd;

	fd = open("./test.txt", O_RDONLY);
	test = NULL;
	test = (char *)malloc(1 * sizeof(char));
	test[0] = '\0';

	test = get_next_line(fd);
	printf("test : %s\n", test);

	test = get_next_line(fd);
	printf("test : %s\n", test);

	free (test);
	test = NULL;
	
	return (0);
}
