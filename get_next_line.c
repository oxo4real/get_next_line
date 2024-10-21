/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:48:37 by marvin            #+#    #+#             */
/*   Updated: 2024/10/03 15:48:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*special_free(char *buffer, char **stash)
{
	if (buffer)
		free(buffer);
	if (stash && (*stash))
	{
		free((*stash));
		(*stash) = NULL;
	}
	return (NULL);
}

char	*dup_stash_till_nl(char **stash)
{
	int		i;
	int		j;
	char	*rendu;
	char	*tmp;

	i = 0;
	while ((*stash)[i] != '\n' && (*stash)[i])
		i++;
	rendu = malloc(sizeof(char) * (i + 1 + 1));
	if (!rendu)
		return (NULL);
	j = i + 1;
	rendu[j] = 0;
	while (--j > -1)
		rendu[j] = (*stash)[j];
	tmp = ft_strdup(&(*stash)[i + 1]);
	if (!tmp)
	{
		free(rendu);
		return (NULL);
	}
	free((*stash));
	(*stash) = tmp;
	return (rendu);
}

char	*handle_eof(char **stash, char *line)
{
	if ((*stash)[0] == 0)
		return (NULL);
	if (find_chr((*stash), '\n') < 0 && (*stash)[0] != 0)
	{
		line = ft_strdup((*stash));
		special_free(NULL, stash);
	}
	else if ((*stash)[0] != 0)
		line = dup_stash_till_nl(stash);
	return (line);
}

char	*read_line(int fd, char *line, char *buffer, char **stash)
{
	char	*new_stash;
	int		read_return;

	while (1)
	{
		read_return = read(fd, buffer, BUFFER_SIZE);
		if (read_return < 0)
			return (NULL);
		if (read_return == 0)
			return (handle_eof(stash, line));
		buffer[read_return] = 0;
		new_stash = custom_strjoin((*stash), buffer);
		if (!new_stash)
			return (NULL);
		(*stash) = new_stash;
		if (find_chr((*stash), '\n') >= 0)
			break ;
	}
	return (dup_stash_till_nl(stash));
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*buffer;
	char		*line;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (!stash)
	{
		stash = malloc(sizeof(char) * 1);
		if (!stash)
			return (special_free(buffer, NULL));
		stash[0] = 0;
	}
	line = read_line(fd, NULL, buffer, &stash);
	if (!line)
		return (special_free(buffer, &stash));
	free(buffer);
	return (line);
}
