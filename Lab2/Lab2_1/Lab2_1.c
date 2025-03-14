#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{

	int a;
	int b;

	printf("Enter two integers:");
	scanf("%d %d",&a, &b );
	printf("%d + %d = %d \n", a, b, a + b);
	printf("%d - %d = %d \n", a, b, a - b);
	printf("%d * %d = %d \n", a, b, a * b);
	printf("%d / %d = %d \n", a, b, a / b);
	printf("%d %% %d = %d\n", a, b, a % b);

	return 0;

	



}