/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 14:19:07 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/04/27 12:42:45 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>*/
#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int				i;
	unsigned int	res;
	int				negative;

	i = 0;
	res = 0;
	negative = 1;
	while (nptr[i] != '\0' && (nptr[i] == ' ' || nptr[i] == '\n'
			|| nptr[i] == '\t' || nptr[i] == '\v' || nptr[i] == '\f'
			|| nptr[i] == '\r'))
		i++;
	if (nptr[i] == '-')
		negative = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		nptr++;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * negative);
}
/*
int	main(void)
{
	const char	nptr[3] = "42";

	printf("%d\n", ft_atoi(nptr));
	return (0);
}
*/
