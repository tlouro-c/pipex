/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlouro-c <tlouro-c@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 19:05:31 by tlouro-c          #+#    #+#             */
/*   Updated: 2023/12/04 19:06:00 by tlouro-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char			*pointer;
	unsigned long	i;

	pointer = (char *)malloc(count * size);
	if (pointer != NULL)
	{
		i = 0;
		while (i < (count * size))
		{
			pointer[i] = 0;
			i++;
		}
	}
	return (pointer);
}
