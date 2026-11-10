/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmallia <qmallia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 19:29:35 by qmallia           #+#    #+#             */
/*   Updated: 2026/11/10 21:16:58 by qmallia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*free_errors(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	*s2;

	if (!s)
		return (NULL);
	s2 = (char *)s;
	while (*s2 && *s2 != (unsigned char) c)
		s2++;
	if (!*s2 && c)
		return (NULL);
	return (s2);
}

char	*ft_strjoin(char *stock, char *buffer)
{
	int		i;
	int		j;
	size_t	total;
	char	*join;

	i = 0;
	j = -1;
	total = ft_strlen(stock) + ft_strlen(buffer);
	join = malloc(sizeof(char) * total + 1);
	if (!join)
	{
		free (stock);
		return (NULL);
	}
	while (stock && stock[i])
	{
		join[i] = stock[i];
		i++;
	}
	while (buffer[++j])
		join[i + j] = buffer[j];
	join[i + j] = 0;
	free(stock);
	return (join);
}
