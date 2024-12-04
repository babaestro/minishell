/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:23:17 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/06/04 17:39:26 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>*/
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	find;
	int		i;

	find = (unsigned char)c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == find)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
