/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacha <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:44:32 by jacha             #+#    #+#             */
/*   Updated: 2024/04/01 15:41:25 by jacha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

char	*join(char const *s1, char const *s2);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*read_fnc(int fd, char *s1);
char	*snap_shot(char *s1);
char	*result_cpy(char *src, int len);
int		find_newline(char *str);
char	*ft_strdup(const char *s);

#endif
