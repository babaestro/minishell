/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:50:21 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/04/27 12:26:30 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char			*p;
	size_t			i;

	p = (char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}
