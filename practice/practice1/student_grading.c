#include <stdio.h>


int main()
{
	int table [6][6];
	int row, column;
	
	for (row = 0; row < 6; row++)
		for (column = 0; column < 6; column++)
		{
			if (row == column)
				table[row][column] = 0;
			else if (row > column)
				table[row][column] = -1;
			else
				table[row][column] = 1;
		}

    for (row = 0; row < 6; row++)
	{
		for (column = 0; column < 6; column++)
			printf("%3d", table [row][column]);
		printf("\n");
	}
    return 0;
}
