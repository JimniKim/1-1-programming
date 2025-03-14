#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	float p = 3.141592;
	double r;

	printf("반지름을 입력하시오: ");
	scanf("%lf", &r);
	printf("원 둘레 : %f\n", 2 * p * r);
	printf("원 넓이 : %f\n", p * r * r);
	
	return 0;


    

}