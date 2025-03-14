#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int add(int x, int y);
float average(int sum);
void printResults(int x, int y, int sum, float avg);

int main ()
{
	int x, y, sum;
	float avg;
   
	printf("Enter two integers: ");
	scanf("%d %d", &x, &y);

	sum = add(x, y);
	avg = (float)average(sum);

	printResults(x, y, sum, avg);

	return 0;

}

void printResults(int x, int y, int sum, float avg)
{
	
	printf("The sum of %d and %d is %d\n", x, y, sum);
	printf("The average of numbers is %.1f\n", avg);

	return;
	
}

float average(int sum)
{
	return (float)sum / 2;
}

int add(int x, int y)
{
	return (x+y);
}

