/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:23:56 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/04/29 18:25:03 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;

	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (0);
	ft_strlcpy(new, s + start, len + 1);
	return (new);
}

/*int	main(void)
{
	char const *s = "Bonjour tout le monde";

	printf("%s\n", ft_substr(s, 1000015555555454, 4));
	return (0);
}*/