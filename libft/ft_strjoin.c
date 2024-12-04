/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:17:28 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/11/15 11:21:51 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>*/

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*newstr;
// 	size_t	total_l;

// 	if (!s1 || !s2)
// 		return (0);
// 	total_l = ft_strlen(s1) + ft_strlen(s2);
// 	newstr = (char *)malloc(total_l + 1);
// 	if (!newstr)
// 		return (NULL);
// 	ft_strlcpy(newstr, s1, total_l + 1);
// 	ft_strlcat(newstr, s2, total_l + 1);
// 	return (newstr);
// }

char	*ft_strjoin(char *l_limit, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!l_limit)
	{
		l_limit = (char *)malloc(1 * sizeof(char));
		l_limit[0] = '\0';
	}
	if (!l_limit || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(l_limit) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (l_limit)
		while (l_limit[++i] != '\0')
			str[i] = l_limit[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(l_limit) + ft_strlen(buff)] = '\0';
	free(l_limit);
	return (str);
}
