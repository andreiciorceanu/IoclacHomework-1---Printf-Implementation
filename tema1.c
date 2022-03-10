#include <unistd.h>

#include <stdarg.h>

#include <string.h>

#include <stdio.h>

#include <stdlib.h>

int iocla_printf(const char *format, ...);
char* convert(unsigned int, int);
char* itoa(int value, char* buffer, int base);


static int write_stdout(const char *token, int length)
{
	int rc;
	int bytes_written = 0;

	do {
		rc = write(1, token + bytes_written, length - bytes_written);
		if (rc < 0)
			return rc;

		bytes_written += rc;
	} while (bytes_written < length);

	return bytes_written;
}

int iocla_printf(const char *format, ...)
{
	unsigned int i;
	int dim=0,deplasament=0,index;
	char *s,caracter;
	int j;
	char string_int[11];
	int nr;
	int anterior = 0;
	int ok = 0;
	int cnt = 0;
	va_list args;
	va_start(args, format);


	for (j = 0; j < strlen(format); j++){
		//printf("\nformat = %s\n", format+j);
		if(format[j] == '%') {
			cnt = 1;
			j++;
		switch (format[j]) {

		case 'd' : 
			if(j != 0){
				nr = write_stdout(format + anterior, j - 1 - deplasament);
				deplasament = j - 1;
				dim += nr;
			}

			i = va_arg(args,int);
			deplasament += 2;
			memset(string_int, 0 ,11);
			index=0;
			itoa(i, string_int, 10);
			index = strlen(string_int);
			dim += index;
			nr = write_stdout(string_int, index);
			j++;
			anterior = j;
			cnt = 0;
			ok = j;
			break;


		case 'u' : 
			if(j != 0){
				nr = write_stdout(format + anterior, j - 1 - deplasament);
				deplasament = j - 1;
				dim += nr;
			}

			i = va_arg(args,int);
			deplasament +=2;
			memset(string_int, 0 ,11);
			index=0;
			itoa(i, string_int, 10);
			index = strlen(string_int);
			dim += index;
			nr = write_stdout(string_int, index);
			j++;
			anterior = j;
			cnt =0;
			ok = j;
			break;

		case 's' : 
			if(j != 0){
				nr = write_stdout(format + anterior, j - 1 - deplasament);
				deplasament = j - 1;
				dim += nr;
			}

			s =  va_arg(args, char *);
			deplasament += 2;
			index =  strlen(s);
			dim += index;
			nr = write_stdout(s, index);
			j++;
			anterior = j;
			cnt = 0;
			ok = j;
			break;

		case 'x' :
			if(j != 0){
				nr = write_stdout(format + anterior, j - 1 - deplasament);
				deplasament = j - 1;
				dim += nr;
			}

			i = va_arg(args,int);
			deplasament +=2;
			memset(string_int, 0 ,11);
			index=0;
			itoa(i, string_int, 16);
			index = strlen(string_int);
			dim += index;
			nr = write_stdout(string_int, index);
			j++;
			anterior = j;
			cnt = 0;
			ok = j;
			break;

		
		case 'c' :
		if(j != 0){
			nr	= write_stdout(format + anterior, j - 1 - deplasament);
				deplasament = j - 1;
				dim += nr;
			}
		caracter = (char)va_arg(args, int);
		deplasament += 2;
		dim += 1;
		nr = write_stdout(&caracter, 1);
		j++;
		anterior = j;
		cnt = 0;
		ok = j;
		break;

		case '%' :
		if(j != 0){
				nr = write_stdout(format + anterior, j - 1 - deplasament);
				deplasament = j - 1;
				dim += nr;
			}
		deplasament += 2;
		dim += 1;
		nr = write_stdout(format+j-1, 1);
		j++;
		anterior = j;
		cnt = 0;
		ok = j;
		break;
		}
		}

	}
	if(cnt == 0) {
		nr = write_stdout(format + ok,strlen(format)-ok);
		dim += nr;
	}
	return dim;
}

void swap(char *x, char *y) {
	char t = *x; *x = *y; *y = t;
}


char* reverse(char *buffer, int i, int j)
{
	while (i < j)
		swap(&buffer[i++], &buffer[j--]);

	return buffer;
}


char* itoa(int value, char* buffer, int base)
{

	unsigned n;
	if(value < 0){
		if(base == 16)
			n = 4294967295 + value +1;
		else
		n = -value;
	}
	else
		n = value;
		
	int i = 0;
	while (n)
	{
		int r = n % base;

		if (r >= 10) 
			buffer[i++] = 97 + (r - 10);
		else
			buffer[i++] = 48 + r;

		n = n / base;
	}

	if (i == 0)
		buffer[i++] = '0';

	if (value < 0 && base == 10)
		buffer[i++] = '-';

	buffer[i] = '\0';
	
	return reverse(buffer, 0, i - 1);
}