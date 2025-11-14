/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:59:01 by cgajean           #+#    #+#             */
/*   Updated: 2025/06/12 19:13:10 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_word_nbr(char const *s, char c)
{
	size_t	word_nbr;
	int		in_word;

	word_nbr = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (!in_word)
				word_nbr++;
			in_word = 1;
		}
		else
			in_word = 0;
		s++;
	}
	return (word_nbr);
}

static size_t	ft_word_len(char const *src, char c)
{
	size_t	len;

	len = 0;
	while (*src && *src != c)
	{
		len++;
		src++;
	}
	return (len);
}

static char	*ft_create_word(char const **src, char c)
{
	size_t	len;
	char	*new_word;
	char	*ptr_to_new_word;

	len = ft_word_len(*src, c);
	new_word = malloc((len + 1) * sizeof(char));
	if (new_word == NULL)
		return (NULL);
	ptr_to_new_word = new_word;
	while (**src && **src != c)
		*ptr_to_new_word++ = *(*src)++;
	*ptr_to_new_word = '\0';
	return (new_word);
}

char	**ft_split(char const *s, char c)
{
	size_t	word_nbr;
	char	**word_list;
	char	**ptr_to_word_list;

	if (s == NULL)
		return (NULL);
	word_nbr = ft_count_word_nbr(s, c);
	word_list = malloc((word_nbr + 1) * sizeof(char *));
	if (word_list == NULL)
		return (NULL);
	word_list[word_nbr] = NULL;
	ptr_to_word_list = word_list;
	while (word_nbr-- > 0)
	{
		while (*s && *s == c)
			s++;
		*ptr_to_word_list = ft_create_word(&s, c);
		if (*ptr_to_word_list == NULL)
		{
			ft_split_free(word_list);
			return (NULL);
		}
		ptr_to_word_list++;
	}
	return (word_list);
}
