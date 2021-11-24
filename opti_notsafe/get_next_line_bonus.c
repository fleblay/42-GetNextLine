/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:33:20 by fle-blay          #+#    #+#             */
/*   Updated: 2021/11/24 11:37:41 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
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

char	*get_next_line(int fd)
{
	static char	*mainstr[FD_MAX_NUMBER] = {NULL};
	char		*togive;
	int			read;
	int			cumulread;

	read = 0;
	cumulread = 0;
	if (load_content(fd, &mainstr[fd]) <= 0 && ! mainstr[fd])
		return (NULL);
	while (! ft_strchr(mainstr[fd] + cumulread, '\n'))
	{
		read = load_content(fd, &mainstr[fd]);
		if (read <= 0)
		{
			togive = ft_strdup(mainstr[fd]);
			free(mainstr[fd]);
			mainstr[fd] = NULL;
			return (togive);
		}
		cumulread += read;
	}
	update_str(&togive, &mainstr[fd]);
	return (togive);
}

/*#include <fcntl.h>
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
