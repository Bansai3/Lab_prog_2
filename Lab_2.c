
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define UINT1024_T_SIZE 1024

typedef struct
{
	uint8_t digit[UINT1024_T_SIZE];
	uint8_t pos;
} uint1024_t;


void init(uint1024_t* x)
{
	x->pos = 0;
	for (size_t i = 0; i < UINT1024_T_SIZE; i++)
	{
		x->digit[i] = 0;
	}
}

void scanf_value(uint1024_t* x)
{
	int i = 0;
	char line[UINT1024_T_SIZE];
	init(x);
	fgets(line, UINT1024_T_SIZE, stdin);
	int size = strlen(line) - 1;
	for (size_t i = 0; i < size; i++)
	{
		if (line[i] >= '0' && line[i] <= '9')
		{
			x->digit[size - i - 1] = line[i] - '0';
		}
	}
	x->pos = size;
}

uint1024_t add_op(uint1024_t x, uint1024_t y)
{
	uint1024_t num;
	init(&num);
	int length = x.pos > y.pos ? x.pos : y.pos;
	int carry = 0;
	for (size_t i = 0; i < length || carry > 0; i++)
	{
		num.digit[i] = (x.digit[i] + y.digit[i] + carry) % 10;
		carry = (x.digit[i] + y.digit[i] + carry) / 10;
		num.pos++;
	}
	return num;
}

uint1024_t subtr_op(uint1024_t x, uint1024_t y)
{
	uint1024_t num;
	init(&num);
	int carry = 0;
	for (size_t i = 0; i < UINT1024_T_SIZE; i++)
	{
		num.digit[i] = (10 + x.digit[i] - y.digit[i] - carry) % 10;
		carry = (x.digit[i] - y.digit[i] - carry) < 0 ? 1 : 0;
	}

	int n = 0;
	for (size_t i = UINT1024_T_SIZE - 1; i >= 0; i--)
	{
		if (num.digit[i] != 0)
			break;
		n++;
	}
	num.pos = UINT1024_T_SIZE - n;

	return num;
}

uint1024_t mult_op(uint1024_t x, uint1024_t y)
{
	uint1024_t num;
	init(&num);
	int carry = 0;
	int p;
	for (size_t i = 0; i < UINT1024_T_SIZE; i++)
	{
		for (size_t j = 0; (i + j) < UINT1024_T_SIZE; j++)
		{
			p = (long)x.digit[i] * (long)y.digit[j];
			p += carry;
			num.digit[i + j] += p % 10;
			carry = p / 10;
		}
	}

	int n = 0;
	for (size_t i = UINT1024_T_SIZE - 1; i >= 0; i--)
	{
		if (num.digit[i] != 0)
			break;
		n++;
	}
	num.pos = UINT1024_T_SIZE - n;
	return num;
}

uint1024_t from_uint(unsigned int x)
{
	uint1024_t num;
	init(&num);
	int i = 0;
	while (x > 0)
	{
		num.digit[i++] = x % 10;
		x /= 10;
	}
	num.pos = i;
	for (size_t i = num.pos; i < UINT1024_T_SIZE; i++)
		num.digit[i] = 0;
	return num;
}

void printf_value(uint1024_t x)
{
	for (int i = x.pos - 1 ; i >= 0; i--)
		printf("%d", x.digit[i]);
	printf("\n");
}


int main()
{
	uint1024_t x1;
	uint1024_t x2;
	scanf_value(&x1);
	scanf_value(&x2);
	printf_value(subtr_op(x1, x2));
	printf_value(mult_op(x1, x2));
	printf_value(add_op(x1, x2));

	return 0;
}
