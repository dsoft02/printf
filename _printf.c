#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include "main.h"

/**
 * _printf - produces output according to a format
 * @format: format string containing the characters and the specifiers
 * Description: this function will call the select_printf() function that will
 * determine which printing function to call depending on the format specified
 *
 * Return: length of the formatted output string
 */
int _printf(const char *format, ...)
{
	int (*print_funcs)(va_list, flags_t *);
	const char *p;
	va_list args;
	flags_t flags = {0, 0, 0};

	register int len = 0;

	va_start(args, format);
	if (format[0] == '%' && format[1] == '\0')
		return (-1);
	if (!format || (format[0] == '%' && !format[1]))
		return (-1);
	if (format[0] == '%' && format[1] == ' ' && !format[2])
		return (-1);
	for (p = format; *p; p++)
	{
		if (*p == '%')
		{
			p++;
			if (*p == '%')
			{
				len += _putchar('%');
				continue;
			}
			while (check_flag(*p, &flags))
				p++;
			print_funcs = select_printf(*p);
			len += (print_funcs)
				? print_funcs(args, &flags)
				: _printf("%%%c", *p);
		}
		else
			len += _putchar(*p);
	}
	_putchar(-1);
	va_end(args);
	return (len);
}
