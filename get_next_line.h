/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slistle <slistle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 16:02:01 by slistle           #+#    #+#             */
/*   Updated: 2023/06/18 22:35:24 by slistle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

char	*get_next_line(int fd);
char	*new_buf(char *buf);
char	*put_to_result(char *buf);
char	*read_to_buf(int fd, char *buf);
char	*ft_strjoin(char *s1, char *s2);
int		check_the_line(char *buf);
int		ft_strlen_after_new_line(char *buf);
size_t	ft_strlen_before_newline(char *s);
size_t	ft_strlen(char *s);

#endif