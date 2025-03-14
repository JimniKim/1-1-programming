#include <stdio.h>

void print_matrix(int a[][20], int size);
int main()
{
	int a[20][20] = { 0 };
	int size, i, j;
	printf("Enter the size of square: ");
	scanf("%d", &size);
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (i + j == size - 1)
				a[i][j] = 0;
			else if (i + j < size - 1)
				a[i][j] = 1;
			else
				a[i][j] = -1;
		}
	}
	print_matrix(a, size);
	return 0;
}
void print_matrix(int a[][20], int size)
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
			printf("%3d", a[i][j]);
		printf("\n");
	}
}