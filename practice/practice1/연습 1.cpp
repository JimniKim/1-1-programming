#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void getdata(int*, int*);
void divide(int, int);
void remainder(int, int);

int main()
{
	int num1, num2;

	getdata(&num1, &num2);
	divide(num1, num2);
	remainder(num1, num2);

	return 0;
}

void getdata(int* a, int*b)
{
	printf("Enter two integers: ");
	scanf("%d %d", a, b);

}

void divide(int num1, int num2)
{
	int q;
	q = (num1 / num2);
	printf("The quotient of %d/%d is %d\n", num1, num2, q);
}

void remainder(int num1, int num2)
{
	int r;
	r = num1 % num2;
	printf("The remainder of %d/%d is %d\n", num1, num2, r);
}