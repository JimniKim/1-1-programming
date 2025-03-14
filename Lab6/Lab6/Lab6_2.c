#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int num;
	int sum = 0;
	printf("Enter a number: ");
	scanf("%d", &num);
	while (num != 0)
	{
		sum += num % 10;
		num /= 10;
	}
	printf("\nThe sum of the digits is %d\n",sum);
	return 0;
}