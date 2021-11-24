/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_opti.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <fle-blay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:01:05 by fle-blay          #+#    #+#             */
/*   Updated: 2021/11/24 11:43:02 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>

int	load_content(int fd, char **dest)
{
	char	buf[BUFFER_SIZE];
	char	*content;
	int		cntsize;

	content = NULL;
	cntsize = read(fd, buf, BUFFER_SIZE);
	if (cntsize <= 0)
		return (cntsize);
	content = ft_strrawjoin(*dest, buf, cntsize);
	free(*dest);
	*dest = content;
	return (cntsize);
}

int	update_str(char **togive, char **mainstr)
{
	char	*tmp;

	tmp = NULL;
	*togive = ft_substr(*mainstr, 0, ft_strchr(*mainstr, '\n') - *mainstr + 1);
	tmp = ft_strdup(*mainstr);
	free(*mainstr);
	*mainstr = ft_substr(tmp, ft_strchr(tmp, '\n') - tmp + 1, ft_strlen(tmp));
	if (! ft_strlen(*mainstr))
	{
		free(*mainstr);
		*mainstr = NULL;
	}
	free(tmp);
	return (1);
}

char	*safe_exit(char *str1, char *str2, char *str3, char *str4)
{
	if (str1)
	{
		free(str1);
	}
	if (str2)
	{
		free(str2);
	}
	if (str3)
	{
		free(str3);
	}
	if (str4)
	{
		free(str4);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*mainstr = NULL;
	char		*togive;
	int			read;
	int			cumulread;

	read = 0;
	cumulread = 0;
	if (load_content(fd, &mainstr) <= 0 && ! mainstr)
		return (NULL);
	while (! ft_strchr(mainstr + cumulread, '\n'))
	{
		read = load_content(fd, &mainstr);
		if (read <= 0)
		{
			togive = ft_strdup(mainstr);
			free(mainstr);
			mainstr = NULL;
			return (togive);
		}
		cumulread += read;
	}
	update_str(&togive, &mainstr);
	return (togive);
}

/*
#include <fcntl.h>
#include <stdio.h>

int	main(int ac, char *av[])
{
	char	*test;
	int		fd;

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
}*/
