#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void partial_print(int* arr_start, int size);
int partial_sum(int* arr_start, int* arr_end);

int main()
{
	int arr[10];
	int start_index, size, end_index,i,sum;

	printf("Enter 10 elements of array: ");
	for (i = 0; i < 10; i++)
		scanf("%d", &arr[i]);

	printf("Numbes that you enter are: ");
	for (i = 0; i < 10; i++)
		printf("%d ", arr[i]);
	
	printf("\nEnter the starting and ending index: ");
	scanf("%d %d", &start_index, &end_index);
	size = end_index - start_index + 1;
	
	sum= partial_sum(&arr[start_index], &arr[end_index]);
	printf("\n\nSum from array[%d] to array[%d] is %d\n", start_index, end_index, sum);
	
	partial_print(&arr[start_index], size);
	
	return 0;
}

int partial_sum(int* arr_start, int* arr_end)
{
	int sum=0;
	int num = arr_end - arr_start + 1;
	for (int i = 0; i < num; i++)
		sum += *(arr_start + i);

	return sum;
}

void partial_print(int* arr_start, int size)
{
	int i;
	printf("Partial array output: ");
	for (i = 0; i < size; i++)
		printf("%d ", *(arr_start + i));
	printf("\n");
	return;
}