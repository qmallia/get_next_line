/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmallia <qmallia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 11:05:29 by qmallia           #+#    #+#             */
/*   Updated: 2026/11/10 21:21:40 by qmallia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*find_line(char *stock)
{
	size_t	i;
	char	*line;

	if (!stock[0])
		return (NULL);
	i = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	if (stock[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (stock[i] && stock[i] != '\n')
	{
		line[i] = stock[i];
		i++;
	}
	if (stock[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*create_new_stock(char *stock)
{
	size_t	i;
	size_t	j;
	char	*new_stock;

	i = 0;
	j = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
	{
		free(stock);
		return (NULL);
	}
	new_stock = malloc(ft_strlen(stock + i) + 1);
	if (!new_stock)
		return (NULL);
	i++;
	while (stock[i])
		new_stock[j++] = stock[i++];
	new_stock[j] = 0;
	free(stock);
	return (new_stock);
}

static char	*read_file(int fd, char *stock)
{
	int		bytes_red;
	char	*buffer;

	bytes_red = 1;
	if (ft_strchr(stock, '\n'))
		return (stock);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free_errors(stock, buffer));
	buffer[0] = 0;
	while (bytes_red && !ft_strchr(buffer, '\n'))
	{
		bytes_red = read(fd, buffer, BUFFER_SIZE);
		if (bytes_red == -1)
			return (free_errors(stock, buffer));
		buffer[bytes_red] = 0;
		stock = ft_strjoin(stock, buffer);
		if (!stock)
			break ;
	}
	free(buffer);
	return (stock);
}

char	*get_next_line(int fd)
{
	static char	*stock[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stock[fd] = read_file(fd, stock[fd]);
	if (!stock[fd])
		return (NULL);
	line = find_line(stock[fd]);
	if (!line)
	{
		free(stock[fd]);
		stock[fd] = NULL;
		return (NULL);
	}
	stock[fd] = create_new_stock(stock[fd]);
	return (line);
}
