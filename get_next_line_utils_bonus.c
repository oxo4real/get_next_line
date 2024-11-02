/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:18:08 by marvin            #+#    #+#             */
/*   Updated: 2024/10/04 20:18:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;

	dup = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] != 0)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

// the only difference is that it frees s1 if everything was syccessful
char	*custom_strjoin(char *s1, char *s2)
{
	int			size;
	size_t		i;
	size_t		j;
	char		*rendu;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	rendu = (char *) malloc(size);
	if (!rendu)
		return (NULL);
	i = 0;
	j = 0;
	while (j < ft_strlen(s1))
	{
		rendu[i] = s1[j++];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s2))
	{
		rendu[i] = s2[j++];
		i++;
	}
	rendu[i] = 0;
	free(s1);
	return (rendu);
}

int	find_chr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
