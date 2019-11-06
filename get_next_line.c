/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 17:10:11 by akhastaf          #+#    #+#             */
/*   Updated: 2019/11/05 21:05:06 by akhastaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_checkerror(int fd, char **buff)
{
	if (!(BUFFER_SIZE >= 1) || (read(fd, *buff, 0) < 0))
		return (NULL);
	return (*buff);
}

int		ft_readline(int fd, char **str)
{
	char	*tmp;
	char	*buff;
	int		n;

	if ((!(buff = malloc(BUFFER_SIZE + 1))) || (!ft_checkerror(fd, &buff)))
	{
		free(buff);
		return (-1);
	}
	while ((n = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[n] = '\0';
		tmp = *str;
		*str = ft_strjoin(*str, buff);
		free(tmp);
		if (ft_strchr(*str, '\n'))
			break ;
	}
	free(buff);
	return (n);
}

int		get_next_line(int fd, char **line)
{
	static char	*str[ULIMIT];
	char		*tmp;
	char		*s;
	int			n;

	if ((n = ft_readline(fd, &str[fd]) < 0 || !line))
		return (-1);
	if ((s = ft_strchr(str[fd], '\n')))
	{
		*line = ft_strndup(str[fd], s - str[fd]);
		tmp = str[fd];
		str[fd] = ft_strdup(s + 1);
		free(tmp);
		return (1);
	}
	if (!n && str[fd])
	{
		*line = ft_strdup(str[fd]);
		free(str[fd]);
		str[fd] = NULL;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}
