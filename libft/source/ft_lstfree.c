/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:18:09 by cgajean           #+#    #+#             */
/*   Updated: 2025/07/14 18:19:57 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstfree(t_list *data)
{
	t_list	*ptr;
	t_list	*temp;

	if (data)
	{
		ptr = data;
		while (ptr)
		{
			temp = ptr->next;
			if (ptr->content)
				free(ptr->content);
			free(ptr);
			ptr = temp;
		}
	}	
}
