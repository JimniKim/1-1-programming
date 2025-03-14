#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int main()
{

	double x1, x2, y1, y2, d;

	printf("Enter P1 (x1, y1) : ");
	scanf("%lf %lf", &x1, &y1);

	printf("Enter P1 (x2, y2) : ");
	scanf("%lf %lf", &x2, &y2);

	d = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));

	printf("Distance between P1 and P2 : %f\n", d);

	return 0;
	
}