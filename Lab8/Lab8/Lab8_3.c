#include<stdio.h>
#define MAX 6

void bubble_sort(int a[], int size);
void swap(int* x, int* y);
void print_array(int a[], int size);
void input_array(int a[], int size);
int main()
{
	int ary[MAX];
	printf("Input integer numbers to be sorted: ");
	input_array(ary, MAX);
	printf(" Unsorted: ");
	print_array(ary, MAX);
	printf("----------------------------------\n");
	bubble_sort(ary, MAX);
	printf("----------------------------------\n");
	printf(" Sorted: ");
	print_array(ary, MAX);
	return 0;
}
void input_array(int a[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		scanf("%d", &a[i]);
	return;
}
void print_array(int a[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d  ", a[i]);
	printf("\n");
	return;
}
void bubble_sort(int a[], int size)
{
	int i, j, z;
	for (j = 1; j < size ; j++)
	{
		for (i = size - 1; i >= j; i--)
			if (a[i] < a[i - 1])
				swap(&a[i], &a[i - 1]);
		printf("[step  %d]:", j);
		for (z = 0; z < size; z++)
			printf("  %d", a[z]);
		printf("\n");
	}

}

void swap(int* x, int* y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
	return;
}