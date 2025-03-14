#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int inputSelection()

{
	int selection;
	printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("CSED 101 Assignment 1\n");
	printf("Choose from the following:\n\n");
	printf("1. Rimemann Sum\n");
	printf("2. Roman Numerals\n");
	printf("3. The Mystery Number\n");
	printf("4. Terminate Program\n");
	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("Selection: ");         //  ó�� ��� ȭ��
	scanf("%d", &selection);

	return selection;
}
void calcLefthand(int, int, int, int, float, float);
void calcRighthand(int, int, int, int, float, float);
void calcMidpoint(int, int, int, int, float, float);
void funcRiemannSum(int* selection)
{
	int a, b, c, d;
	float ini, fin;
	char answer;
	printf("\nEnter integer coefficients [a b c]: ");
	scanf("%d %d %d", &a, &b, &c);
	printf("Enter the initial value of x: ");
	scanf("%f", &ini);
	printf("Enter the final value of x: ");
	scanf("%f", &fin);
	while (1)
	{
		if (fin <= ini)
		{
			printf("Final value of x must be greater than initial value\n\n");
			printf("Enter the final value of x:");
			scanf("%f", &fin);
		}
		else
			break;
	}  // x�� ������ ���� ó�� ������ ���� ��� �ٽ� �Է°��� ����.
	printf("Enter the number of approximating rectangles: ");
	scanf("%d", &d);
	while (1)
	{
		if (d <= 0)
		{
			printf("Number of rectangles must be positive\n\n");
			printf("Enter he number of approximating rectangles:");
			scanf("%d", &d);
		}
		else
			break;
	}   // �簢���� ���� ������ �־��� ���, �ٽ� �Է°��� ����.

	printf("\nEstimated Area: \n\n");
	calcLefthand(a, b, c, d, ini, fin);
	calcMidpoint(a, b, c, d, ini, fin);
	calcRighthand(a, b, c, d, ini, fin);

	printf("\nDo you want to continue(y/n)? ");
	int s = getchar();
	scanf("%c", &answer);

	if (answer == 'y')
		funcRiemannSum(selection);
	else
		*selection = inputSelection();
	// ��� �� ������ ���� ����, y�̸� �ڱ� �ڽ��� �ٽ� ȣ��, n�̸� ȭ�� ������� �ٽ� ���ư�.
}
void calcLefthand(int a, int b, int c, int d, float ini, float fin)
{
	double sum = 0;
	double interval = (fin - ini) / d;
	for (int i = 0; i <= d - 1; i++)
	{
		sum += interval * (a * pow(ini + interval * i, 2) + b * (ini + interval * i) + c);
	}
	printf("Lefthand sum: %.4f sq. units\n", sum);
} //���� ���� ��
void calcRighthand(int a, int b, int c, int d, float ini, float fin)
{
	double sum = 0;
	double interval = (fin - ini) / d;
	for (int i = 1; i <= d; i++)
	{
		sum += interval * (a * pow(ini + interval * i, 2) + b * (ini + interval * i) + c);
	}
	printf("Righthand sum: %.4f sq. units\n\n", sum);
} // ������ ���� ��
void calcMidpoint(int a, int b, int c, int d, float ini, float fin)
{
	double sum = 0;
	double interval = (fin - ini) / d;
	for (int i = 0; i <= d - 1; i++)
	{
		sum += interval * (a * pow(ini + interval * i + interval / 2, 2) + b * (ini + interval * i + interval / 2) + c);
	}
	printf("Midpoint sum: %.4f sq. units\n", sum);
} // ��� ���� ��
void printRoman(int num)
{
	int ones = num % 10;
	int tens = num % 100 - ones;
	int hund = num - tens - ones; // �� �ڸ��� �����ϱ�
	printf("Decimal Number: %d\n", num);
	printf("Roman Numberals: ");

	switch (hund)
	{
	case 0: break;
	case 100: printf("C"); break;
	case 200: printf("CC"); break;
	case 300: printf("CCC"); break;
	case 400: printf("CD"); break;
	case 500: printf("D"); break;
	case 600: printf("DC"); break;
	case 700: printf("DCC"); break;
	case 800: printf("DCCC"); break;
	case 900: printf("CM"); break;
	}
	switch (tens)
	{
	case 0: break;
	case 10: printf("X"); break;
	case 20: printf("XX"); break;
	case 30: printf("XXX"); break;
	case 40: printf("XL"); break;
	case 50: printf("L"); break;
	case 60: printf("LX"); break;
	case 70: printf("LXX"); break;
	case 80: printf("LXXX"); break;
	case 90: printf("XC"); break;
	}
	switch (ones)
	{
	case 0: printf("\n\n");  break;
	case 1: printf("I\n\n"); break;
	case 2: printf("II\n\n"); break;
	case 3: printf("III\n\n"); break;
	case 4: printf("IV\n\n"); break;
	case 5: printf("V\n\n"); break;
	case 6: printf("VI\n\n"); break;
	case 7: printf("VII\n\n"); break;
	case 8: printf("VIII\n\n"); break;
	case 9: printf("IX\n\n"); break;
	}
} // �������� �θ� ���ڷ� �ٲٱ�
void funcRomannumerals(int* selection)
{
	char answer;
	int num;

	while (1)
	{
		printf("\nEnter number: ");
		scanf("%d", &num);
		if (num < 1)
			printf("The number should be positive\n\n");
		else if (num > 1000)
			printf("The number should be epual to or less than 1000\n\n");
		else
			break;
	} // ���ڰ� 1~1000 ���� �ۿ� ���� �� �Է°��� �ٽ� ����.
	printRoman(num); // �Է°��� �θ� ���ڷ� �ٲ�

	printf("\nDo you want to continue(y/n)? ");
	int s = getchar();
	scanf("%c", &answer);

	if (answer == 'y')
		funcRomannumerals(selection);
	else
		*selection = inputSelection();
}
int checkPrime(int sum)
{
	int result = 0;
	for (int i = 2; i < sum; i++)    // �Ҽ����� �Ǻ��ϱ� ���� 1�� �ڱ��ڽ��� ������ ��� ���� ������.
	{
		if (sum % i == 0)
			break;

		else
			result = 1;
	}

	return result;
}
int maxDigit(int num)
{
	int max = 0;
	for (int i = 1; num != 0; i++)
	{
		max = (num % 10 < (num / 10) % 10) ? (num / 10) % 10 : num % 10;
		num /= 10;
	} // �� �ڸ����� �и��Ͽ� 2���� ���� ����, ū ���� ������ �Է�.
	return max;
}
int minDigit(int num)
{
	int min = 0;
	for (int i = 1; num / 10 != 0; i++)
	{
		min = (num % 10 > (num / 10) % 10) ? (num / 10) % 10 : num % 10;
		num /= 10;
	}
	return min;
} // �� �ڸ����� �и��Ͽ� 2���� ���� ����, ���� ���� ������ �Է�.
void funcMysteryNumber(int* selection)
{
	int num, num2, num3;
	int sum = 0;
	int count = 0;


	while (1)
	{
		printf("\nEnter your number: ");
		scanf("%d", &num);

		if (num < 1)
			printf("The number should be positive\n\n");

		else if (num > 1000000000)
			printf("The number should be epual to or less than 1000000000\n\n");

		else
			break;
	} // ���� �ۿ� �ִ� ���� �Է¹����� �ٽ� �Է¹���.
	num2 = num; num3 = num; // �Է¹��� ���� 3���� ������ �־� ���� �����ϱ� (���߿� ��� ��)

	for (int j = 1; num != 0; j++)
	{
		count = j;
		num /= 10;
	} // �� �ڸ� ������ ����

	for (int i = 0; num2 != 0; i++)
	{
		sum += pow(num2 % 10, (count - i));
		num2 /= 10;
	} // �� �ڸ� ���� n������ �� ���ϱ�

	if (checkPrime(sum) == 1)
		printf("The final result of the input %d is: %d\n", num3, sum - maxDigit(num3));
	else if (checkPrime(sum) == 0)
		printf("The final result of the input %d is: %d\n", num3, sum - minDigit(num3));

	char answer;
	printf("\nDo you want to continue(y/n)? ");
	int s = getchar();
	scanf("%c", &answer);

	if (answer == 'y')
		funcMysteryNumber(selection);
	else
		*selection = inputSelection();
}
int main()
{
	int selection = inputSelection();

	while (selection != 4)
	{
		if (selection == 1)
           funcRiemannSum(&selection); 
		else if (selection ==2)
		   funcRomannumerals(&selection);
		else if (selection ==3)
		   funcMysteryNumber(&selection); 
		else
		{
			printf("invalid selection\n");
			printf("Selection: ");
			scanf("%d", &selection);
		}
		
	} // 1,2,3�� ������ ��� ���α׷��� ������ �ϹǷ� �ݺ��� ���
	if (selection == 4)
		printf("Program Terminated.\n"); // 4�� �ԷµǸ� �ٷ� ����

	return 0;
}