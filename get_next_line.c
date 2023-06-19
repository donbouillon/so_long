/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slistle <slistle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:43:41 by slistle           #+#    #+#             */
/*   Updated: 2023/06/18 22:28:45 by slistle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

/*
	this function reads from our file and joins strings till it finds a newline
*/

char	*read_to_buf(int fd, char *result)
{
	int		check_read;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1 * sizeof(char));
	buf[0] = 0;
	if (!buf)
		return (NULL);
	check_read = 1;
	while (check_the_line(result) == 0 && check_read != 0)
	{
		if (check_read == 0)
			return (free (result), free(buf), NULL);
		check_read = read(fd, buf, BUFFER_SIZE);
		if (check_read == -1)
			return (free(buf), NULL);
		buf[check_read] = '\0';
		result = ft_strjoin(result, buf);
	}
	if (check_read == 0 && result != NULL && result[0] == '\0')
		return (free (result), free(buf), NULL);
	free(buf);
	return (result);
}

/*
	this function puts the joined string to the result string omitting the newline 
	and everything afterwards
*/

char	*put_to_result(char *buf)
{
	char	*result;
	int		i;

	result = malloc(ft_strlen_before_newline(buf) + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (buf[i] != '\n' && buf[i] != '\0')
	{
		result[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
	{
		result[i] = '\n';
		i++;
	}
	if (buf == NULL)
		return (free(result), NULL);
	result[i] = '\0';
	return (result);
}

/*
	this function creates new buf, which includes only characters 
	only after the newline
*/

char	*new_buf(char *buf)
{
	char	*new_buf;
	int		i;
	int		j;

	if (buf == NULL)
		return (0);
	new_buf = malloc(ft_strlen_after_new_line(buf) + 1);
	if (!new_buf)
		return (NULL);
	i = 0;
	j = ft_strlen_before_newline(buf);
	while (buf[j] != '\0')
	{
		new_buf[i] = buf[j];
		i++;
		j++;
	}
	new_buf[i] = '\0';
	free(buf);
	return (new_buf);
}

char	*get_next_line(int fd)
{
	static char		*buf;
	char			*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = read_to_buf(fd, buf);
	if (!buf)
		return (NULL);
	result = put_to_result(buf);
	buf = new_buf(buf);
	return (result);
}
