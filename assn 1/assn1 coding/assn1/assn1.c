#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

void funcRiemannSum();
void funcRomannumerals();
void funcMysteryNumber();
int inputSelection();
int main() // �Է��� selection ���� ���� 4���� ����� ���� �ݺ�.
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
				printf("invalid selection\n");    // 1,2,3,4 �̿��� ���ڰ� ������ �ٽ� �Է¹���.
				printf("Selection: ");
				scanf("%d", &selection);
			}
		}
	}
	return 0;
}
int inputSelection() // �⺻ ȭ���� ����մϴ�.
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
	printf("Selection: ");         //  ó�� ��� ȭ��
	scanf("%d", &selection); 
	
	return selection; // �Է°��� main �Լ��� ��ȯ
}
void calcLefthand(int a, int b, int c, int d, float ini, float fin) // ���� ���� ���� ����ϰ� ���.
{
	double sum = 0;
	double interval = (fin - ini) / d;  // �簢�� 1���� ��
	for (int i = 0; i <= d-1; i++)
		sum += interval*(a * pow(ini + interval * i, 2) + b * (ini + interval * i) + c); // �� �簢������ ��
	printf("Lefthand sum: %.4f sq. units\n", sum);
} 
void calcRighthand(int a, int b, int c, int d, float ini, float fin) // ������ ���� ���� ����ϰ� ���
{
	double sum = 0;
	double interval = (fin - ini) / d;
	for (int i = 1; i <= d ; i++)
		sum += interval*(a * pow(ini + interval * i, 2) + b * (ini + interval * i) + c);
	printf("Righthand sum: %.4f sq. units\n\n", sum);
} 
void calcMidpoint(int a, int b, int c, int d, float ini, float fin) // ��� ���� ���� ����ϰ� ���
{
	double sum = 0;
	double interval = (fin - ini) / d;
	for (int i = 0; i <= d - 1; i++)
		sum += interval*(a * pow(ini + interval * i + interval/2, 2) + b * (ini + interval * i+ interval / 2) + c);
	printf("Midpoint sum: %.4f sq. units\n", sum);
} // ��� ���� ��
void funcRiemannSum()
{
	int a, b, c, d; // a�� 2������ ���, b�� 1������ ���, c�� ������� ��Ÿ���� �����Դϴ�.
	float ini, fin; // ini : x ������ ó�� ��, fin : x ������ ������ ��
	char answer;
	while (1)
	{
		printf("\nEnter integer coefficients [a b c]: "); 
		scanf("%d %d %d", &a, &b, &c);                     // �� ���� ����� �Է¹޽��ϴ�.
		printf("Enter the initial value of x: ");
		scanf("%f", &ini);
		printf("Enter the final value of x: ");
		scanf("%f", &fin);
		while (fin <= ini)   // x ������ ������ ���� ó�� ������ Ŭ ��, �ٽ� �Է¹޽��ϴ�.
		{
			printf("Final value of x must be greater than initial value\n\n");
			printf("Enter the final value of x:");
			scanf("%f", &fin);
		}
		  
		while (1)  // �簢���� ������ ������ ���, �ٽ� �Է¹޽��ϴ�.
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
		int s = getchar();  // �Է� ���۸� ���� ���� getchar�� �̿�. 
		scanf("%c", &answer);

		if (answer == 'n')  // 'n'�� �Է¹����� �ݺ��� ������ ����.
			break;
	} 
}
void printRoman(int num) // �Է°��� �θ� ���ڷ� ��ȯ�ϰ� ����մϴ�.
{
	int ones = num % 10;
	int tens = num % 100 - ones;
	int hund = num - tens - ones; // �� �ڸ��� �����ϱ�
	printf("Decimal Number: %d\n", num);
	printf("Roman Numberals: ");
	if (num == 1000)  // 1000�̸� M ���.
		printf("M");
	switch (hund)  // �������� �θ� ���ڷ� �ٲٱ�
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
	int num;  // �Է°�
	while (1)
	{
		while (1)  // �Է°��� 1~1000���̿� ������ �ٽ� �Է¹ޱ�.
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

		if (answer == 'n')
			break;
	}
}
int checkPrime(int sum) // �Ҽ����� �ƴ��� �Ǻ��մϴ�.
{
    int result = 1;
	for (int i = 2; i < sum; i++)    // �Ҽ����� �Ǻ��ϱ� ���� 1�� �ڱ��ڽ��� ������ ��� ���� ������.
	{
		if (sum % i == 0)
		{
			result = 0;
			break;
		}
	}
	if (sum == 1)  // 10�� ����, �� �ڸ����� n������ �� ���� ���� 1�� ���� ���� ���� (1�� �Ҽ��� �ƴϹǷ�)
		result = 0;

	return result;	// �Ҽ��̸� 1, �ƴϸ� 0�� ��ȯ
} 
int maxDigit(int num3) // �� �ڸ����� �и��Ͽ� 2���� ���� ����, ū ���� ������ �Է��ϴ� ������ �ݺ��ϰ� ��ȯ.
{
	int max= num3 % 10;
	for (int i = 1; num3 != 0; i++)
	{
		max = (max < num3 % 10) ? num3 % 10: max;
		num3 /= 10;
	} 
	return max;
}
int minDigit(int num3) // �� �ڸ����� �и��Ͽ� 2���� ���� ����, ���� ���� ������ �Է��ϴ� ������ �ݺ��ϰ� ��ȯ.
{
	int min =num3 % 10;
	for (int i = 1; num3 != 0; i++)
	{
		min = (min > num3 % 10) ? num3 % 10 : min;
		num3 /= 10;
	}
	return min;
} 
void funcMysteryNumber() // ������ �Է¹ް� �̽��͸� ���ڸ� ����� �� ����մϴ�. 
{	
	while (1)
	{
		int num, num2, num3; // �Է¹��� ���� 3���� ������ �־� ���� �����ϱ� (���߿� ��� ��)
		int sum = 0; // �� �ڸ����� n������ �� ���� ��
	    int count = 0; // ������ �ڸ���
	  while (1)  // 1~1000000000 ���� �� ���ڸ� �Է¹޽��ϴ�. 
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
		num2 = num; num3 = num; 

		for (int j = 1; num != 0; j++)  // �� �ڸ����� ����
		{
			count = j;
			num /= 10;
		} 

		for (int i = 0; num2 != 0; i++)  // �� �ڸ� ���� n������ �� ���ϱ�
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