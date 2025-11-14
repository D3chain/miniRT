/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getd_next_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:21:09 by cgajean           #+#    #+#             */
/*   Updated: 2025/06/21 00:01:40 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_extract_data(int fd)
{
	char	*stash;
	int		bytes_read;

	stash = ft_calloc(BUFFER_SIZE + 1, sizeof(t_byte));
	if (stash == NULL)
		return (0);
	bytes_read = read(fd, stash, BUFFER_SIZE);
	if (bytes_read > 0)
	{
		stash[bytes_read] = '\0';
		return (stash);
	}
	else if (bytes_read == 0)
		return (free(stash), NULL);
	else
		return (stash[0] = -1, stash);
}

void	line_builder(char **stsh, char **p, char **nl)
{
	char		*temp;
	size_t		len;

	len = ft_strlen(*nl);
	temp = ft_realloc((void **) nl, len + 1, len + (*p - *stsh) + 1);
	if (!temp)
		return ((void)(free(*nl), *nl = NULL));
	*nl = ft_strnjoin(temp, *stsh, *p - *stsh);
	free(temp);
}

void	gnl_mainloop(int fd, char **stsh, char **p, char **nl)
{
	while (true)
	{
		if (!*stsh)
			*stsh = ft_extract_data(fd);
		if ((!*stsh && !**nl) || (*stsh && *stsh[0] == -1))
			return ((void)(free(*nl), *nl = NULL, free(*stsh), *stsh = NULL));
		else if (!*stsh)
			return ((void)(free(*stsh), *stsh = NULL));
		*p = *stsh;
		while (**p && **p != '\n')
			(*p)++;
		if (**p == '\n')
			(*p)++;
		line_builder(stsh, p, nl);
		if (*nl == NULL)
			return ;
		if (*p > *stsh && *(*p - 1) == '\n')
			return ((void)(*p = ft_strdup(*p), free(*stsh), *stsh = *p));
		else
		{
			free(*stsh);
			*stsh = NULL;
		}
	}
}

char	*getd_next_line(int fd)
{
	static char	*stash = NULL;
	char		*stash_ptr;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (NULL);
	stash_ptr = NULL;
	line = ft_calloc(1, sizeof(char));
	if (line == NULL)
		return (NULL);
	else
		gnl_mainloop(fd, &stash, &stash_ptr, &line);
	return (line);
}
