/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 16:21:59 by ababa-ai          #+#    #+#             */
/*   Updated: 2024/06/04 17:07:20 by ababa-ai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*handle_format(const char *format, va_list args, int *count)
{
	if (*format == 'c')
		ft_printchar(args, &format, count);
	else if (*format == 's')
		ft_printstr(args, &format, count);
	else if (*format == 'i' || *format == 'd')
		ft_putnbr(args, &format, count);
	else if (*format == 'u')
		ft_putunsigned(args, &format, count);
	else if (*format == 'x')
		ft_puthex(args, &format, count);
	else if (*format == 'X')
		ft_puthexup(args, &format, count);
	else if (*format == '%')
		ft_printpercent(&format, count);
	else if (*format == 'p')
		ft_printpointer(args, &format, count);
	else
	{
		write(1, format, 1);
		count++;
	}
	return (format);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
			format = handle_format(format + 1, args, &count);
		else
		{
			write(1, format, 1);
			count++;
			format++;
		}
	}
	va_end(args);
	return (count);
}
