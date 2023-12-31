#include "main.h"
/**
 * handle_print - Prints an argument based on its type
 * @fmt: Formatted string in which to print the arguments.
 * @ap: List of arguments to be printed.
 * @index: index
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int handle_print(const char *fmt, int *index, va_list ap, char buffer[],
		int flags, int width, int precision, int size)
{
	int k, unknown_len = 0, printed_letters = -1;
	fmt_t fmt_types[] = {
		{'c', prints_char}, {'s', prints_string}, {'%', prints_percent},
		{'i', prints_int}, {'d', prints_int}, {'b', prints_binary},
		{'u', prints_unsigned}, {'o', prints_octal}, {'x', prints_hexadecimal},
		{'X', prints_hex_upper}, {'p', prints_pointers}, {'S', prints_non_printable},
		{'r', prints_reverse}, {'R', prints_rot13string}, {'\0', NULL}
	};
	for (k = 0; fmt_types[k].fmt != '\0'; k++)
		if (fmt[*index] == fmt_types[k].fmt)
			return (fmt_types[k].fn(ap, buffer, flags, width, precision, size));
	if (fmt_types[k].fmt == '\0')
	{
		if (fmt[*index] == '\0')
			return (-1);
		unknown_len += write(1, "%%", 1);
		if (fmt[*index - 1] == ' ')
			unknown_len += write(1, " ", 1);
		else if (width)
		{
			--(*index);
			while (fmt[*index] != ' ' && fmt[*index] != '%')
				--(*index);
			if (fmt[*index] == ' ')
				--(*index);
			return (1);
		}
		unknown_len += write(1, &fmt[*index], 1);
		return (unknown_len);
	}
	return (printed_letters);
}

