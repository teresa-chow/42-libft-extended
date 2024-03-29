/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:09:39 by tchow-so          #+#    #+#             */
/*   Updated: 2023/11/17 10:03:08 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_format(char spec, va_list ap);

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, format);
	count = 0;
	while (*format != '\0')
	{
		if (*format == '%')
			count += ft_print_format(*(++format), ap);
		else
			count += write(1, format, 1);
		++format;
	}
	va_end(ap);
	return (count);
}

static int	ft_print_format(char spec, va_list ap)
{
	int	count;

	count = 0;
	if (spec == 'c')
		count = ft_printchar(va_arg(ap, int));
	else if (spec == 's')
		count = ft_printstr(va_arg(ap, char *));
	else if (spec == 'p')
		count = ft_printptr((unsigned long)va_arg(ap, unsigned long));
	else if (spec == 'd' || spec == 'i')
		count = ft_printint(spec, (long)va_arg(ap, int), 10);
	else if (spec == 'u')
		count = ft_printint(spec, (long)va_arg(ap, unsigned int), 10);
	else if (spec == 'x' || spec == 'X')
		count = ft_printint(spec, (long)va_arg(ap, unsigned int), 16);
	else
		count += write(1, &spec, 1);
	return (count);
}
/*
//TESTING VARIOUS FORMAT SPECIFIERS
#include <stdio.h>

int	main(void)
{
	ft_printf("FT_PRINTF:\n\n");
	ft_printf(" count: %i\n", ft_printf("NULL %s NULL", 0));
	ft_printf("\t count: %i\n", ft_printf("%i", 2147483647));
	ft_printf("\t\t count: %d\n", ft_printf("%i", -101));
	ft_printf("\t count: %i\n", ft_printf("%i", -2147483648));
	ft_printf("\t count: %i\n", ft_printf("%u", 4294967295));
	ft_printf("\t\t count: %i\n", ft_printf("%x", 255));
	ft_printf("\t count: %i\n", ft_printf("%X", 2147483647));
	ft_printf("\t count: %i\n", ft_printf("%p", &"ola"));
	ft_printf("\t\t count: %i\n", ft_printf("%p", 0));
	ft_printf("\t count: %i\n", ft_printf(" %p %p ", 0, 0));

	printf("\n-----------------------------------\nPRINTF:\n\n");
	printf(" count: %i\n", printf("NULL %s NULL", (char *) 0));
	printf("\t count: %i\n", printf("%i", 2147483647));
	printf("\t\t count: %d\n", printf("%i", -101));
	printf("\t count: %i\n", printf("%li", -2147483648));
	printf("\t count: %i\n", printf("%ld", 4294967295));
	printf("\t\t count: %i\n", printf("%x", 255));
	printf("\t count: %i\n", printf("%X", 2147483647));
	printf("\t count: %i\n", printf("%p", &"ola"));
	printf("\t\t count: %i\n", printf("%p", (void *) 0));
	printf("\t count: %i\n", printf(" %p %p ", (void *) 0, (void *) 0));

	return (0);
}
*/
/*
//TESTING %p FORMAT SPECIFIER
#include <stdio.h>
#include <limits.h>

int	main(void)
{
	ft_printf("FT_PRINTF:\n\n");
	ft_printf("\t\t count: %i\n", ft_printf("%p", -1)); // returns 10: fr OK
	ft_printf("\t\t\t count: %i\n", ft_printf("%p", 16));
	ft_printf("\t\t\t count: %i\n", ft_printf("%p", 17));
	ft_printf("\t count: %i\n", ft_printf("%p", LONG_MIN));
	ft_printf("\t count: %i\n", ft_printf("%p", LONG_MAX));
	ft_printf("\t\t count: %i\n", ft_printf("%p", INT_MIN)); // returns 10: fr OK
	ft_printf("\t\t count: %i\n", ft_printf("%p", INT_MAX));
	ft_printf("\t count: %i\n", ft_printf("%p", ULONG_MAX));
	ft_printf("\t\t\t count: %i\n", ft_printf("%p", -ULONG_MAX));

	printf("\n-----------------------------------\nPRINTF:\n\n");
	printf("\t count: %i\n", printf("%p", (void *) -1)); // returns 18: fr OK
	printf("\t\t\t count: %i\n", printf("%p", (void *) 16));
	printf("\t\t\t count: %i\n", printf("%p", (void *) 17));
	printf("\t count: %i\n", printf("%p", (void *) LONG_MIN));
	printf("\t count: %i\n", printf("%p", (void *) LONG_MAX));
	printf("\t count: %i\n", printf("%p", (void *) INT_MIN)); // returns 18: fr OK
	printf("\t\t count: %i\n", printf("%p", (void *) INT_MAX));
	printf("\t count: %i\n", printf("%p", (void *) ULONG_MAX));
	printf("\t\t\t count: %i\n", printf("%p", (void *) -ULONG_MAX));

	return (0);
}*/
/*"ffffffff" for sign extension in 32-bit machine, incorrectly treating a 32-bit
signed int as a 32-bit unsigned int(?)*/
