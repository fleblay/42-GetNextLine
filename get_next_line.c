/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:38:53 by fle-blay          #+#    #+#             */
/*   Updated: 2021/11/24 17:30:39 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

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
	if (! content)
	{
		multi_freenull(dest, NULL, NULL, NULL);
		return (-2);
	}
	free(*dest);
	*dest = content;
	return (cntsize);
}

void	update_str(char **togive, char **mainstr)
{
	char	*tmp;

	*togive = ft_substr(*mainstr, 0, ft_strchr(*mainstr, '\n') - *mainstr + 1);
	if (! *togive)
	{
		free(*mainstr);
		*togive = NULL;
		return ;
	}
	tmp = ft_strdup(*mainstr);
	if (! tmp)
	{
		multi_freenull(mainstr, togive, NULL, NULL);
		return ;
	}
	free(*mainstr);
	*mainstr = ft_substr(tmp, ft_strchr(tmp, '\n') - tmp + 1, ft_strlen(tmp));
	if (! *mainstr)
	{
		multi_freenull(&tmp, mainstr, togive, NULL);
		return ;
	}
	if (! ft_strlen(*mainstr))
		multi_freenull(mainstr, NULL, NULL, NULL);
	free(tmp);
}

void	multi_freenull(char **s1, char **s2, char **s3, char **s4)
{
	if (s1 && *s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (s2 && *s2)
	{
		free(*s2);
		*s2 = NULL;
	}
	if (s3 && *s3)
	{
		free(*s3);
		*s3 = NULL;
	}
	if (s4 && *s4)
	{
		free(*s4);
		*s4 = NULL;
	}
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
			if (read == -2)
				return (NULL);
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
	while (1);
	return (0);
}
*/
