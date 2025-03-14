#include <stdio.h>
#define SIZE 10

int seqSearch(int a[], int want);
int main()
{
	int a[SIZE];
	int i, want;
	printf("Input 10 integer values: ");
	for (i = 0; i < SIZE; i++)
		scanf("%d", &a[i]);
	printf("\nEntered number is      : ");
	for (i = 0; i < SIZE; i++)
		printf("%d ", a[i]);
	printf("\nInput an integer that you want to find: ");
	scanf("%d", &want);
	if (seqSearch(a, want) == -1)
		printf("Not Found\n");
	else
		printf("The index of %d is %d\n", want, seqSearch(a, want));

}
int seqSearch(int a[], int want)
{
	int i;
	int index;
	for (i = 0; i < SIZE; i++)
	{
		if (a[i] == want)
		{
			index = i;  break;
		}
		else
			index = -1;
	}
	return index;
}