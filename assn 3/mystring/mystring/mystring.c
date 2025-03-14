#include <stddef.h>
#include <stdio.h>
int mystrlen(char *str)
{
	int i=0;
	while (1)  // NULL을 만날 때까지의 문자 수를 셉니다.
	{
		if (str[i] != NULL)
			i++;
		else
			break;
	}
	return i;
}

char *mystrcpy(char *toStr, char *fromStr)
{
	int i;
	for (i = 0 ; toStr[i] = fromStr[i]; i++); // NULL값이 들어가기 전 문자까지 복사해줍니다.
	return toStr;
}

int mystrcmp(char *str1, char *str2)
{
	
	for (; *str1 == *str2 && *str2 && *str1; str1++, str2++); // 각 문자가 같고, NULL이 아닐 때까지 반복하여 비교합니다.
	if (*str1 > *str2) // 만약 1 문자열이 크다면 1을 반환합니다.
		return 1;
	else if (*str2 > *str1)  // 만약 2 문자열이 크다면 -1을 반환합니다.
		return -1;
	else if (*str1 == *str2) // 같으면 0을 반환합니다.
		return 0;
}
