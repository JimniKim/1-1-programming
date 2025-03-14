#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

void funcRiemannSum();
void funcRomannumerals();
void funcMysteryNumber();
int inputSelection();
int main() // 입력한 selection 값에 따라 4개의 기능을 구현 반복.
{
	int selection =0;	
	while (selection !=4)
	{
		selection = inputSelection();
		while(1)
		{
			if (selection == 1)
			{
				funcRiemannSum(); break;
			}
			else if (selection == 2)
			{
				funcRomannumerals(); break;
			}
			else if (selection == 3)
			{
				funcMysteryNumber(); break;
			}
			else if (selection == 4)
			{
				printf("Program Terminated.\n"); break;
			}
			else
			{
				printf("invalid selection\n");    // 1,2,3,4 이외의 숫자가 들어오면 다시 입력받음.
				printf("Selection: ");
				scanf("%d", &selection);
			}
		}
	}
	return 0;
}
int inputSelection() // 기본 화면을 출력합니다.
{
	int selection;
	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("CSED 101 Assignment 1\n");
	printf("Choose from the following:\n\n");
	printf("1. Rimemann Sum\n");
	printf("2. Roman Numerals\n");
	printf("3. The Mystery Number\n");
	printf("4. Terminate Program\n");
	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("Selection: ");         //  처음 출력 화면
	scanf("%d", &selection); 
	
	return selection; // 입력값을 main 함수에 반환
}
void calcLefthand(int a, int b, int c, int d, float ini, float fin) // 왼쪽 리만 합을 계산하고 출력.
{
	double sum = 0;
	double interval = (fin - ini) / d;  // 사각형 1개의 폭
	for (int i = 0; i <= d-1; i++)
		sum += interval*(a * pow(ini + interval * i, 2) + b * (ini + interval * i) + c); // 각 사각형들의 합
	printf("Lefthand sum: %.4f sq. units\n", sum);
} 
void calcRighthand(int a, int b, int c, int d, float ini, float fin) // 오른쪽 리만 합을 계산하고 출력
{
	double sum = 0;
	double interval = (fin - ini) / d;
	for (int i = 1; i <= d ; i++)
		sum += interval*(a * pow(ini + interval * i, 2) + b * (ini + interval * i) + c);
	printf("Righthand sum: %.4f sq. units\n\n", sum);
} 
void calcMidpoint(int a, int b, int c, int d, float ini, float fin) // 가운데 리만 합을 계산하고 출력
{
	double sum = 0;
	double interval = (fin - ini) / d;
	for (int i = 0; i <= d - 1; i++)
		sum += interval*(a * pow(ini + interval * i + interval/2, 2) + b * (ini + interval * i+ interval / 2) + c);
	printf("Midpoint sum: %.4f sq. units\n", sum);
} // 가운데 리만 합
void funcRiemannSum()
{
	int a, b, c, d; // a는 2차항의 계수, b는 1차항의 계수, c는 상수항을 나타내는 변수입니다.
	float ini, fin; // ini : x 범위의 처음 값, fin : x 범위의 마지막 값
	char answer;
	while (1)
	{
		printf("\nEnter integer coefficients [a b c]: "); 
		scanf("%d %d %d", &a, &b, &c);                     // 각 항의 계수를 입력받습니다.
		printf("Enter the initial value of x: ");
		scanf("%f", &ini);
		printf("Enter the final value of x: ");
		scanf("%f", &fin);
		while (fin <= ini)   // x 범위의 마지막 값이 처음 값보다 클 시, 다시 입력받습니다.
		{
			printf("Final value of x must be greater than initial value\n\n");
			printf("Enter the final value of x:");
			scanf("%f", &fin);
		}
		  
		while (1)  // 사각형의 개수가 음수일 경우, 다시 입력받습니다.
		{
			printf("Enter the number of approximating rectangles: ");
		    scanf("%d", &d);
			if (d <= 0)
				printf("Number of rectangles must be positive\n\n");
			else
				break;
		}   
		printf("\nEstimated Area: \n\n");
		calcLefthand(a, b, c, d, ini, fin);
		calcMidpoint(a, b, c, d, ini, fin);
		calcRighthand(a, b, c, d, ini, fin);
		printf("\nDo you want to continue(y/n)? ");
		int s = getchar();  // 입력 버퍼를 비우기 위해 getchar를 이용. 
		scanf("%c", &answer);

		if (answer == 'n')  // 'n'를 입력받으면 반복문 밖으로 나옴.
			break;
	} 
}
void printRoman(int num) // 입력값을 로마 숫자로 변환하고 출력합니다.
{
	int ones = num % 10;
	int tens = num % 100 - ones;
	int hund = num - tens - ones; // 각 자릿수 구분하기
	printf("Decimal Number: %d\n", num);
	printf("Roman Numberals: ");
	if (num == 1000)  // 1000이면 M 출력.
		printf("M");
	switch (hund)  // 십진수를 로마 숫자로 바꾸기
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
} 
void funcRomannumerals() 
{
	char answer;
	int num;  // 입력값
	while (1)
	{
		while (1)  // 입력값이 1~1000사이에 없으면 다시 입력받기.
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

		if (answer == 'n')
			break;
	}
}
int checkPrime(int sum) // 소수인지 아닌지 판별합니다.
{
    int result = 1;
	for (int i = 2; i < sum; i++)    // 소수인지 판별하기 위해 1과 자기자신을 제외한 모든 수로 나누기.
	{
		if (sum % i == 0)
		{
			result = 0;
			break;
		}
	}
	if (sum == 1)  // 10과 같이, 각 자릿수를 n제곱한 뒤 더한 값이 1인 경우는 따로 설정 (1은 소수가 아니므로)
		result = 0;

	return result;	// 소수이면 1, 아니면 0을 반환
} 
int maxDigit(int num3) // 각 자릿수를 분리하여 2개씩 비교한 다음, 큰 수를 변수에 입력하는 과정을 반복하고 반환.
{
	int max= num3 % 10;
	for (int i = 1; num3 != 0; i++)
	{
		max = (max < num3 % 10) ? num3 % 10: max;
		num3 /= 10;
	} 
	return max;
}
int minDigit(int num3) // 각 자릿수를 분리하여 2개씩 비교한 다음, 작은 수를 변수에 입력하는 과정을 반복하고 반환.
{
	int min =num3 % 10;
	for (int i = 1; num3 != 0; i++)
	{
		min = (min > num3 % 10) ? num3 % 10 : min;
		num3 /= 10;
	}
	return min;
} 
void funcMysteryNumber() // 정수를 입력받고 미스터리 숫자를 계산한 뒤 출력합니다. 
{	
	while (1)
	{
		int num, num2, num3; // 입력받은 수를 3개의 변수에 넣어 값을 보존하기 (나중에 써야 함)
		int sum = 0; // 각 자릿수를 n제곱한 뒤 더한 값
	    int count = 0; // 정수의 자릿수
	  while (1)  // 1~1000000000 범위 내 숫자를 입력받습니다. 
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
		num2 = num; num3 = num; 

		for (int j = 1; num != 0; j++)  // 몇 자리인지 세기
		{
			count = j;
			num /= 10;
		} 

		for (int i = 0; num2 != 0; i++)  // 각 자리 수를 n제곱한 후 더하기
		{
			sum += pow(num2 % 10, (count - i));
			num2 /= 10;
		} 
		if (checkPrime(sum) == 1)
			printf("The final result of the input %d is: %d\n", num3, sum + maxDigit(num3));
		else if (checkPrime(sum) == 0)
			printf("The final result of the input %d is: %d\n", num3, sum - minDigit(num3));

		char answer;
		printf("\nDo you want to continue(y/n)? ");
		int s = getchar();
		scanf("%c", &answer);

		if (answer == 'n')
			break;
	}
}