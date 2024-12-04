/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:32:39 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/05/01 11:30:42 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr < 1)
		len++;
	while (nbr)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

static long long	abs_val(long long n)
{
	long long	nb;

	nb = 1;
	if (n < 0)
		nb *= -n;
	else
		nb *= n;
	return (nb);
}

static char	*str_new(size_t n)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_itoa(int n)
{
	unsigned int	nbr;
	int				sign;
	int				len;
	char			*str;

	sign = 0;
	if (n < 0)
		sign = 1;
	len = nbr_len(n);
	str = str_new(len);
	if (!str)
		return (NULL);
	*(str + len) = '\0';
	nbr = abs_val(n);
	while (len--)
	{
		*(str + len) = 48 + nbr % 10;
		nbr /= 10;
	}
	if (sign)
		*(str) = 45;
	return (str);
}

/*int	main(void)
{
	int n = 0;
	printf("%s\n", ft_itoa(n));
	return (0);
}*/