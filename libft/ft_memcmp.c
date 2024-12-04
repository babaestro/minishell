/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:40:55 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/04/27 12:38:44 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>*/
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*c1;
	unsigned char	*c2;

	i = 0;
	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n--)
	{
		if (c1[i] != c2[i])
			return (c1[i] - c2[i]);
		i++;
	}
	return (0);
}

/*int	main(void)
{
	const void *b;
	const void *c;
	
	b = "Onvatest";
	c = "Onvatext";
	printf("%d\n", ft_memcmp(b, c, 4));
	return (0);
}*/