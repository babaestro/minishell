/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:05:22 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/06/04 17:39:46 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	i = 0;
	little_len = ft_strlen(little);
	if (*little == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		if (len - i < little_len)
			return (NULL);
		if (big[i] == little[0])
		{
			while ((big[i + j] == little[j]) && ((i + j) < len))
			{
				j++;
				if (little[j] == '\0')
					return ((char *) big + i);
			}
		}
		i++;
	}
	return (NULL);
}
