/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatopchu <iatopchu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:12:01 by iatopchu          #+#    #+#             */
/*   Updated: 2024/06/11 22:35:30 by iatopchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "./libft.h"

char		*get_next_line(int fd);
char		*divide_line(char **leftover);
char		*read_line(int fd, char *buffer, char *leftover);
// int			ft_strlen(const char	*str);
// char		*ft_strchr(const char	*s, int c);
// int			ft_strncmp(const char *s1, const char *s2, size_t n);
// char		*ft_strdup(char const *src);
// char		*ft_strjoin(char const	*s1, char const	*s2);
// char		*ft_substr(char const *s, unsigned int start, size_t len);

#endif