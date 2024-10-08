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

#include "get_next_line_bonus.h"

void	*special_free(char *buffer,  t_list **head, t_list **lst)
{
	t_list	*tmp;
	t_list	*prev;
	int		fd;

	if (buffer)
		free(buffer);
	while (!(*head) && (*lst))
	{
		free((*lst) -> stash);
		tmp = (*lst);
		(*lst) = (*lst) -> next;
		free(tmp);
	}
	if ((*head) && (*lst))
	{
		fd = ((*head) -> fd);
		(*head) = (*lst);
		prev = (*lst);
		while ((*head) && ((*head) -> fd) != fd)
		{
			prev = (*head);
			(*head) = ((*head) -> next);
		}
		if (prev)
			(prev -> next) = ((*head) -> next);
		if ((*head) == (*lst))
			(*lst) = (*lst) -> next;
		free(((*head) -> stash));
		free((*head));
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
		free((*stash));
		(*stash) = NULL;
	}
	else if ((*stash)[0] != 0)
		line = dup_stash_till_nl(stash);
	return (line);
}

char	*read_line(int fd, char *line, char *buffer, char **stash)
{
	char	*new_stash;
	int		read_return;

	while(1)
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
			break;
	}
	return (dup_stash_till_nl(stash));
}

t_list	*new_lst_elem(int fd, t_list *next)
{
	t_list	*lst;

	lst = (t_list *)malloc(sizeof(t_list) * 1);
	if (!lst)
		return (NULL);
	lst -> fd = fd;
	lst -> stash = malloc(sizeof(char) * 1);
	if (!(lst -> stash))
		return (NULL);
	(lst -> stash)[0] = 0;
	lst -> next = next;
	return (lst);
}

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;
	t_list			*head;
	char			*buffer;
	char			*line;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (!lst)
	{
		lst = new_lst_elem(fd, NULL);
		if (!lst)
			return (special_free(buffer, NULL, NULL));
	}
	head = lst;
	while (head && head -> fd != fd)
		head = head -> next;
	if (!head)
	{
		head = new_lst_elem(fd, lst);
		if (!head)
			return (special_free(buffer, NULL, &lst));
		lst = head;
	}
	line = read_line(fd, NULL, buffer, &(head -> stash));
	if (!line)
		return (special_free(buffer, &head, &lst));
	if (!(head -> stash))
		special_free(NULL, &head, &lst);
	free(buffer);
	return (line);
}