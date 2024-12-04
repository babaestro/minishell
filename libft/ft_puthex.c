/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:41:34 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/11/04 15:27:29 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_puthex_recursive(int number, int *count)
{
	int		remainder;
	char	hexdigit;

	if (number < 0)
	{
		ft_putchar('-');
		(*count)++;
		number = -number;
	}
	if (number >= 16)
		ft_puthex_recursive(number / 16, count);
	remainder = number % 16;
	if (remainder < 10)
		hexdigit = remainder + '0';
	else
		hexdigit = remainder - 10 + 'a';
	ft_putchar(hexdigit);
	(*count)++;
}

int	ft_puthex(va_list args, const char **format, int *count)
{
	int	number;

	number = va_arg(args, int);
	ft_puthex_recursive(number, count);
	(*format)++;
	return (*count);
}

void	ft_puthexup_recursive(int number, int *count)
{
	int		remainder;
	char	hexdigit;

	if (number < 0)
	{
		ft_putchar('-');
		(*count)++;
		number = -number;
	}
	if (number >= 16)
		ft_puthexup_recursive(number / 16, count);
	remainder = number % 16;
	if (remainder < 10)
		hexdigit = remainder + '0';
	else
		hexdigit = remainder - 10 + 'A';
	ft_putchar(hexdigit);
	(*count)++;
}

int	ft_puthexup(va_list args, const char **format, int *count)
{
	int	number;

	number = va_arg(args, int);
	ft_puthexup_recursive(number, count);
	(*format)++;
	return (*count);
}
