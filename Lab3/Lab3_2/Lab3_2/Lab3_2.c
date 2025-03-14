#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

char upperToLower(char c);
int getPosition(char c);

int main()
{
	char a;
	
	printf("Input a character in Uppercase: ");
	scanf("%c", &a);
	

	printf("Lowercase of Entered character is: %c\n", upperToLower(a));
	
	printf("Position of '%c' in English Alphabets is: %d\n", upperToLower(a), getPosition(upperToLower(a)));

	return 0;

}

char upperToLower(char c)
{
	return (c + 32);
}

int getPosition(char c)
{
	return (int)(c - 96);
}