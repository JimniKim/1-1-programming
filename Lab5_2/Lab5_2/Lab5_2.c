#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void season_print(int);

int main()
{
	int month1, month2, month3;
	srand(time(NULL));
	month1 = rand() % 12 + 1;
	month2 = rand() % 12 + 1;
	month3 = rand() % 12 + 1;
	
	season_print(month1);
	season_print(month2);
	season_print(month3);

	return 0;
}

void season_print(int month)
{
	switch (month)
	{
	case 3:
	case 4:
	case 5: printf("%d월, 봄\n", month);
		break;

	case 6:
	case 7:
	case 8: printf("%d월, 여름\n", month);
		break;

	case 9:
	case 10:
	case 11: printf("%d월, 가을\n", month);
		break;
	case 12:
	case 1:
	case 2: printf("%d월, 겨울\n", month);
		break;
	}
}