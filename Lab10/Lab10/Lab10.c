# define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

void find_minmax(int* arr, int size, int* max, int* min);
int main()
{
	int* arr;
	int size, min, max;

	printf("Enter array size: ");
	scanf("%d", &size);
	
	arr = (int*)malloc(sizeof(int) * size);
	
	for (int i = 0; i < size; i++)
		scanf("%d", &arr[i]);
	
	printf("\nEntered numbers are\n");
	
	for (int i = 0; i < size; i++)
		printf("%d ", arr[i]);
	
	find_minmax(arr, size, &max, &min);
	
	printf("\nMaximum is %d\n", max);
	printf("Minimum is %d\n\n", min);

	printf("Enter changed array size: ");
	scanf("%d", &size);
	
	arr = (int*)realloc(arr, sizeof(int) * size);
	
	for (int i = 0; i < size; i++)
		scanf("%d", &arr[i]);
	
	printf("\nEntered numbers are\n");
	for (int i = 0; i < size; i++)
		printf("%d ", arr[i]);
	
	find_minmax(arr, size, &max, &min);
	
	printf("\nMaximum is %d\n", max);
	printf("Minimum is %d\n\n", min);

	free(arr);
	return 0;
}
void find_minmax(int* arr, int size, int* max, int* min)
{
	*max = arr[0]; *min = arr[0];
	for (int i = 0; i+1 < size; i++)
	{
		if (arr[i + 1] > *max)
			*max = arr[i + 1];
		if (arr[i + 1] < *min)
			*min = arr[i + 1];
	}
}