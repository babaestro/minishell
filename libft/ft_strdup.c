/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:06:05 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/04/29 12:07:13 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>*/

char	*ft_strdup(const char *s)
{
	char			*duplicate;
	unsigned int	j;

	j = 0;
	duplicate = malloc(ft_strlen(s) + 1);
	if (!duplicate)
		return (NULL);
	while (s[j] != '\0')
	{
		duplicate[j] = s[j];
		j++;
	}
	duplicate[j] = '\0';
	return (duplicate);
}

/*int	main(void)
{
	const char *s = "bonjour";
	printf("%s\n", s);
	return (0);
}*/