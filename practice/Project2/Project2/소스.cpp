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
	printf("Selection: ");         //  처음 출력 화면
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
	}  // x의 마지막 값이 처음 값보다 작을 경우 다시 입력값을 받음.
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
	}   // 사각형의 수에 음수를 넣었을 경우, 다시 입력값을 받음.

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
	// 계속 할 것인지 물은 다음, y이면 자기 자신을 다시 호출, n이면 화면 출력으로 다시 돌아감.
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
} //왼쪽 리만 합
void calcRighthand(int a, int b, int c, int d, float ini, float fin)
{
	double sum = 0;
	double interval = (fin - ini) / d;
	for (int i = 1; i <= d; i++)
	{
		sum += interval * (a * pow(ini + interval * i, 2) + b * (ini + interval * i) + c);
	}
	printf("Righthand sum: %.4f sq. units\n\n", sum);
} // 오른쪽 리만 합
void calcMidpoint(int a, int b, int c, int d, float ini, float fin)
{
	double sum = 0;
	double interval = (fin - ini) / d;
	for (int i = 0; i <= d - 1; i++)
	{
		sum += interval * (a * pow(ini + interval * i + interval / 2, 2) + b * (ini + interval * i + interval / 2) + c);
	}
	printf("Midpoint sum: %.4f sq. units\n", sum);
} // 가운데 리만 합
void printRoman(int num)
{
	int ones = num % 10;
	int tens = num % 100 - ones;
	int hund = num - tens - ones; // 각 자릿수 구분하기
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
} // 십진수를 로마 숫자로 바꾸기
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
	} // 숫자가 1~1000 범위 밖에 있을 때 입력값을 다시 받음.
	printRoman(num); // 입력값을 로마 숫자로 바꿈

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
	for (int i = 2; i < sum; i++)    // 소수인지 판별하기 위해 1과 자기자신을 제외한 모든 수로 나누기.
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
	} // 각 자릿수를 분리하여 2개씩 비교한 다음, 큰 수를 변수에 입력.
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
} // 각 자릿수를 분리하여 2개씩 비교한 다음, 작은 수를 변수에 입력.
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
	} // 범위 밖에 있는 수를 입력받으면 다시 입력받음.
	num2 = num; num3 = num; // 입력받은 수를 3개의 변수에 넣어 값을 보존하기 (나중에 써야 함)

	for (int j = 1; num != 0; j++)
	{
		count = j;
		num /= 10;
	} // 몇 자리 수인지 세기

	for (int i = 0; num2 != 0; i++)
	{
		sum += pow(num2 % 10, (count - i));
		num2 /= 10;
	} // 각 자리 수를 n제곱한 후 더하기

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
		
	} // 1,2,3이 들어오면 계속 프로그램을 돌려야 하므로 반복문 사용
	if (selection == 4)
		printf("Program Terminated.\n"); // 4가 입력되면 바로 종료

	return 0;
}