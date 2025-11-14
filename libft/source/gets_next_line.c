/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets_next_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:21:09 by cgajean           #+#    #+#             */
/*   Updated: 2025/06/19 10:29:57 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	clean_stash(char *stsh)
{
	if (!stsh)
		return ;
	ft_memset(stsh, 0, BUFFER_SIZE);
}

static void	ft_extract_data(int fd, char *stash)
{
	int		bytes_read;

	bytes_read = read(fd, stash, BUFFER_SIZE);
	if (bytes_read > 0)
	{
		stash[bytes_read] = '\0';
		return ;
	}
	else if (bytes_read == 0)
		return ;
	else
		return ((void)(stash[0] = -1));
}

static void	line_builder(char *stsh, char *p, char **nl)
{
	char		*temp;
	size_t		len;

	len = ft_strlen(*nl);
	temp = ft_realloc((void **) nl, len + 1, len + (p - stsh) + 1);
	if (!temp)
		return ((void)(free(*nl), *nl = NULL));
	*nl = ft_strnjoin(temp, stsh, p - stsh);
	free(temp);
}

void	gnl_mainloop(int fd, char *stsh, char *p, char **nl)
{
	while (true)
	{
		if (!*stsh)
			ft_extract_data(fd, stsh);
		if ((!*stsh && !**nl) || (*stsh && stsh[0] == -1))
			return ((void)(clean_stash(stsh), free(*nl) \
			, *nl = NULL));
		else if (!*stsh)
			return ;
		p = stsh;
		while (*p && *p != '\n')
			p++;
		if (*p == '\n')
			p++;
		line_builder(stsh, p, nl);
		if (p > stsh && *(p - 1) == '\n')
			return ((void)(ft_memcpy(stsh, p, ft_strlen(p) + 1)));
		if (!*p)
			clean_stash(stsh);
	}
}

char	*gets_next_line(int fd)
{
	static char	stash[FD_MAX][BUFFER_SIZE] = {0};
	char		*stash_ptr;
	char		*line;

	if (fd < 0 || fd >= FD_MAX || read(fd, 0, 0) == -1)
		return (NULL);
	stash_ptr = NULL;
	line = ft_calloc(1, sizeof(char));
	if (!line)
		return (NULL);
	else
		gnl_mainloop(fd, stash[fd], stash_ptr, &line);
	return (line);
}
