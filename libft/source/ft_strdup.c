/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:40:44 by cgajean           #+#    #+#             */
/*   Updated: 2025/05/22 17:36:17 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	char	*ptr_to_str;

	if (s == NULL)
		return (NULL);
	str = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ptr_to_str = str;
	while (*s)
		*ptr_to_str++ = *s++;
	*ptr_to_str = '\0';
	return (str);
}
