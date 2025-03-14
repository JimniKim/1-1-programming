#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

float calc_average(float, float);
char calc_grade(float);

int main()
{
	float mid, fin, avg;
	char grd;

	printf("Enter your midterm score: ");
	scanf("%f", &mid);
	printf("Enter your final score: ");
	scanf("%f", &fin);

	avg = calc_average(mid, fin);
	grd = calc_grade(avg);

	printf("Average: %.1f\n", avg);
	printf("Grade: %c\n", grd);

	return 0;
}

float calc_average(float mid, float fin)
{
	return (mid + fin)/2;
}

char calc_grade(float avg)
{
	char grade;
	if (avg >= 90)
		grade = 'A';
	else if (avg >= 80)
		grade = 'B';
	else if (avg >= 70)
		grade = 'C';
	else if (avg >= 60)
		grade = 'D';
	else if (avg < 60)
		grade = 'F';

	return grade;
}