/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_or_pointer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:32:11 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/06/04 17:07:33 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putcharpoint(char c)
{
	write(1, &c, 1);
}

void	ft_printpointer_recursive(uintptr_t number, int *count)
{
	unsigned int	remainder;
	char			hexdigit;

	if (number >= 16)
		ft_printpointer_recursive(number / 16, count);
	remainder = number % 16;
	if (remainder < 10)
		hexdigit = remainder + '0';
	else
		hexdigit = remainder - 10 + 'a';
	ft_putcharpoint(hexdigit);
	(*count)++;
}

int	ft_printpointer(va_list args, const char **format, int *count)
{
	uintptr_t	number;

	number = (uintptr_t)va_arg (args, void *);
	if (!number)
	{
		write(1, "(nil)", 5);
		*count += 5;
		(*format)++;
		return (*count);
	}
	write(1, "0x", 2);
	*count += 2;
	ft_printpointer_recursive(number, count);
	(*format)++;
	return (*count);
}

int	ft_putunsigned_recursive(unsigned int number, int *count)
{
	if (number >= 10)
		ft_putunsigned_recursive(number / 10, count);
	number = number % 10 + '0';
	write(1, &number, 1);
	(*count)++;
	return (*count);
}

int	ft_putunsigned(va_list args, const char **format, int *count)
{
	unsigned int	number;

	number = va_arg(args, unsigned int);
	(*format)++;
	return (ft_putunsigned_recursive(number, count));
}
