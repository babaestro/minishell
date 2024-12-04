/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:44:34 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/05/01 12:20:40 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*buffer;

	i = 0;
	buffer = s;
	while (i < n)
	{
		buffer[i] = (char)c;
		i++;
	}
	return (s);
}

/*int	main(void)
{
	char s[10];

	ft_memset(s, 'd', 8);
	printf("%s\n", s);
	return (0);
}*/
