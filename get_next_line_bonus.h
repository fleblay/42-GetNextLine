/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-blay <fle-blay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:54:25 by fle-blay          #+#    #+#             */
/*   Updated: 2021/11/24 16:38:05 by fle-blay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# define FD_MAX_NUMBER 1024

unsigned int	ft_strlen(const char *s);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s);
char			*ft_strrawjoin(char const *s1, char const *s2, int s2size);
char			*ft_substr(char const *s, unsigned int start, unsigned int len);
void			ft_bzero(void *s, unsigned int n);
int				load_content(int fd, char **dest);
void			update_str(char **togive, char **mainstr);
void			multi_freenull(char **s1, char **s2, char **s3, char **s4);
char			*get_next_line(int fd);

#endif
