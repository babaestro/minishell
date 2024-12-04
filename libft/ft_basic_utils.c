/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basic_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 12:29:16 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/06/04 17:07:52 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(va_list args, const char **format, int *count)
{
	char	c;

	c = va_arg(args, int);
	write(1, &c, 1);
	(*format)++;
	(*count)++;
	return (1);
}

int	ft_printpercent(const char **format, int *count)
{
	write(1, "%", 1);
	(*format)++;
	(*count)++;
	return (1);
}

int	ft_printstr(va_list args, const char **format, int *count)
{
	char	*s;
	int		i;

	s = va_arg(args, char *);
	i = 0;
	if (!s)
	{
		write (1, "(null)", 6);
		(*format)++;
		(*count) += 6;
		return (6);
	}
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
		(*count)++;
	}
	(*format)++;
	return (i);
}

int	ft_putnbr_recursive(int number, int *count)
{
	if (number < 0)
	{
		write(1, "-", 1);
		*count += 1;
		number = -number;
	}
	if (number >= 10)
		ft_putnbr_recursive(number / 10, count);
	number = number % 10 + '0';
	write(1, &number, 1);
	(*count)++;
	return (*count);
}

int	ft_putnbr(va_list args, const char **format, int *count)
{
	int	number;

	number = va_arg(args, int);
	if (number == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*count) += 11;
		(*format)++;
		return (*count);
	}
	(*format)++;
	return (ft_putnbr_recursive(number, count));
}
