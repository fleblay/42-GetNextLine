/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <fle-blay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:01:05 by fle-blay          #+#    #+#             */
/*   Updated: 2021/11/17 16:26:11 by fle-blay         ###   ########.fr       */
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

static int	load_content(int fd, char **dest)
{
	char	buf[BUFFER_SIZE];
	char	*content;
	int		cntsize;

	ft_bzero(buf, BUFFER_SIZE);
	cntsize = read(fd, buf, BUFFER_SIZE);
	if (cntsize <= 0)
		return (cntsize);
	content = ft_strrawjoin(*dest, buf, cntsize);
	if (! content)
	{	
		free(*dest);
		return (-1);
	}
	free(*dest);
	*dest = content;
	return (cntsize);
}

//char	*get_next_line(int fd)
//{
//	static char	*mainstr = NULL;
//	char		*tmp = NULL;
//	char		*togive = NULL;
//
//	//if (! mainstr)
//	//	mainstr = ft_strdup("\0");
//	//if (! mainstr)
//	//	return (NULL);
//	printf("mainstr avant loop: '%s'\n", mainstr);
//	if (load_content(fd, &mainstr) <= 0 && ! mainstr)
//		return (NULL);
//	while (/*mainstr && */! ft_strchr(mainstr, '\n'))
//	{
//		//load_content(fd, &mainstr);
//		if (load_content(fd, &mainstr) <= 0)
//		{
//			printf("breaking loading loop\n");
//			togive = ft_strdup(mainstr);
//			if (! togive)
//				return (NULL);
//			free(mainstr);
//			mainstr = NULL;
//			return (togive);
//		}
//		printf(" main str pdt chargement : '%s'\n", mainstr);
//	}
//	//if (! mainstr)
//	//	return (NULL);
//	printf("mainstr apres loop : '%s'\n", mainstr);
//	printf("strchr(mainstr, \\n) - mainstr : %ld\n", ft_strchr(mainstr, '\n') - mainstr);
//	togive = ft_substr(mainstr, 0, ft_strchr(mainstr, '\n') - mainstr + 1);
//	if (! togive)
//		return (NULL);
//	printf("to give : '%s'\n", togive);
//	tmp = ft_strdup(mainstr);
//	if (! tmp)
//		return (NULL);
//	printf(" tmp = mainstr : '%s'\n", tmp);
//	free(mainstr);
//	mainstr = ft_substr(tmp, ft_strchr(tmp, '\n') - tmp + 1, ft_strlen(tmp));
//	if (! mainstr)
//		return (NULL);
//	printf(" main str restant : '%s'\n", mainstr);
//	if (! ft_strlen(mainstr))
//	{
//		free(mainstr);
//		mainstr = NULL;
//	}
//	free(tmp);
//	return (togive);
//}

char	*get_next_line(int fd)
{
	static char	*mainstr = NULL;
	char		*tmp;
	char		*togive;

	if (load_content(fd, &mainstr) <= 0 && ! mainstr)
		return (NULL);
	while (! ft_strchr(mainstr, '\n'))
	{
		if (load_content(fd, &mainstr) <= 0)
		{
			togive = ft_strdup(mainstr);
			if (! togive)
				return (NULL);
			free(mainstr);
			mainstr = NULL;
			return (togive);
		}
	}
	//fonction updatestr pour *togive && *mainstr
	//free togive puis togive && tmp puis togive, tmp && main si alloc fail
	togive = ft_substr(mainstr, 0, ft_strchr(mainstr, '\n') - mainstr + 1);
	if (! togive)
		return (NULL);
	tmp = ft_strdup(mainstr);
	if (! tmp)
		return (NULL);
	free(mainstr);
	mainstr = ft_substr(tmp, ft_strchr(tmp, '\n') - tmp + 1, ft_strlen(tmp));
	if (! mainstr)
		return (NULL);
	if (! ft_strlen(mainstr))
	{
		free(mainstr);
		mainstr = NULL;
	}
	free(tmp);
	return (togive);
}

#include <fcntl.h>
#include <stdio.h>

int main (int ac, char *av[])
{

	char *test;
	int	fd;

	test = NULL;
	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
		fd = 0;

	while ((test = get_next_line(fd)) != NULL)
	{
		printf("\x1b[31mtest : '%s'\x1b[0m", test);
		free (test);
		test = NULL;
	}

	return (0);
}
