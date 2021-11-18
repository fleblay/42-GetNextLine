/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <fle-blay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:03:35 by fle-blay          #+#    #+#             */
/*   Updated: 2021/11/18 11:32:40 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>

unsigned int	ft_strlen(const char *s);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s);
char			*ft_strrawjoin(char const *s1, char const *s2, int s2size);
char			*ft_substr(char const *s, unsigned int start, unsigned int len);
void			ft_bzero(void *s, unsigned int n);
int				load_content(int fd, char **dest);
int				update_str(char **togive, char **mainstr);
char			*get_next_line(int fd);

#endif
