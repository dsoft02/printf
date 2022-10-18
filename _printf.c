#include "main.h"

/**
 * _printf - produces output according to a format
 * @format: input string
 * Return: number of characters printed
 */
int _printf(const char *format, ...)
{
	unsigned int i = 0, len = 0, buf = 0;
	va_list args;
	int (*function)(va_list, char *, unsigned int);
	char *buffer;

	va_start(args, format), buffer = malloc(sizeof(char) * 1024);
	if (!format || !buffer || (format[i] == '%' && !format[i + 1]))
		return (-1);
	if (!format[i])
		return (0);
	for (i = 0; format && format[i]; i++)
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == '\0')
			{
				print_buf(buffer, buf), free(buffer), va_end(args);
				return (-1);
			}
			else
			{
				function = get_print_func(format, i + 1);
				if (function == NULL)
				{
					if (format[i + 1] == ' ' && !format[i + 2])
						return (-1);
					handl_buf(buffer, format[i], buf), len++, i--;
				}
				else
				{
					len += function(args, buffer, buf);
					i += ev_print_func(fomat, i + 1);
				}
			} i++;
		}
		else
			handl_buf(buffer, format[i], buf), len++;
		for (buf = len; buf > 1024; buf -= 1024)
			;
	}
	print_buf(buffer, buf), free(buffer), va_end(args);
	return (len);
}
