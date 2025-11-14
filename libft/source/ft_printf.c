/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:58:27 by cgajean           #+#    #+#             */
/*   Updated: 2025/06/19 10:25:47 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_function_caller(const char *format, va_list args, size_t *count)
{
	if (*format == 'c')
		*count += ft_putchar(va_arg(args, int));
	else if (*format == 's')
		*count += ft_putstr(va_arg(args, char *));
	else if (*format == 'd' || *format == 'i')
		*count += ft_putnbr(va_arg(args, int));
	else if (*format == 'u')
		*count += ft_putunbr(va_arg(args, unsigned int));
	else if (*format == 'x')
		*count += ft_putunbr_base(va_arg(args, unsigned int), \
														"0123456789abcdef");
	else if (*format == 'X')
		*count += ft_putunbr_base(va_arg(args, unsigned int), \
														"0123456789ABCDEF");
	else if (*format == 'p')
		*count += ft_putaddr_hex(va_arg(args, uintptr_t));
	else if (*format == '%')
		*count += ft_putchar('%');
}

int	ft_printf(const char *__format, ...)
{
	size_t	count;
	va_list	ap;

	if (!__format)
		return (-1);
	va_start(ap, __format);
	count = 0;
	while (*__format)
	{
		if (*__format == '%')
			ft_function_caller(++__format, ap, &count);
		else
		{
			ft_putchar(*__format);
			count++;
		}
		__format++;
	}
	va_end(ap);
	return (count);
}
