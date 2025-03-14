#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define limit1  10000.00
#define limit2  20000.00
#define limit3  30000.00
#define limit4  50000.00
#define rate1  0.02
#define rate2  0.05
#define rate3  0.07
#define rate4  0.1
#define rate5  0.15

#define dedn_per_dpndnt 1000

void getdata (int*, double*, double*);
void calctax(int, double, double, double*, double*);
void printtax(int, double, double, double, double);
double tax(double, double, double, double);
double tax2(double, double, double);

int main()
{
	int number;
	double totinc, totddt, taxable, tottax;
	
	

	getdata (&number, &totinc, &totddt);
	calctax(number,totinc, totddt, &taxable, &tottax);
	printtax(number, totinc, totddt, taxable, tottax);

	return 0;
}

void getdata(int* number, double* totinc, double* totddt)
{
	printf("Enter your total income for last year: ");
	scanf("%lf", totinc);

	printf("Enter total of payroll deduction: ");
	scanf("%lf", totddt);

	printf("Enter the number of dependents: ");
	scanf("%d", number);

}

void calctax(int number, double totinc, double totddt, double* taxable, double* tottax)
{

	*taxable = totinc - (double)number * dedn_per_dpndnt;

	*tottax = tax(*taxable, 0.00, limit1, rate1) + tax(*taxable, limit1, limit2, rate2) + tax(*taxable, limit2, limit3, rate3) + tax(*taxable, limit3, limit4, rate4) +
		tax2(*taxable, limit4, rate5);
}

double tax(double taxable, double start, double stop, double rate)
{
	double a; 
	if (taxable <= start)
		a = 0;
	else if (taxable > start && taxable <= stop)
		a = (taxable - start) * rate;
	else
		a = (stop - start) * rate;

	return a;
 
}

double tax2(double taxable, double start, double rate)
{
	double a;
	if (taxable > start)
		a = (taxable - start) * rate;
	else
		a = 0;

	return a;


}

void printtax(int number, double totinc, double totddt, double taxable, double tottax)
{
	printf("Total income: %.2f\n", totinc);
	printf("Number of dependents: %d\n", number);
	printf("Taxable income: %.2f\n", taxable);
	printf("Total Tax: %.2f\n", tottax);
	printf("Total already paid: %.2f\n", totddt);
	printf("Tax due: %.2f\n", tottax - totddt);

}