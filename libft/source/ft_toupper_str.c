/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:41:02 by cgajean           #+#    #+#             */
/*   Updated: 2025/06/25 12:44:58 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_toupper_str(char *str)
{
	char	*ptr;

	if (!str)
		return (NULL);
	ptr = str;
	while (*ptr)
	{
		if (ft_islower(*ptr))
			*ptr = ft_toupper(*ptr);
		ptr++;
	}
	return (str);
}
