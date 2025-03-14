#include <stddef.h>
#include <stdio.h>
int mystrlen(char *str)
{
	int i=0;
	while (1)  // NULL�� ���� �������� ���� ���� ���ϴ�.
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
	for (i = 0 ; toStr[i] = fromStr[i]; i++); // NULL���� ���� �� ���ڱ��� �������ݴϴ�.
	return toStr;
}

int mystrcmp(char *str1, char *str2)
{
	
	for (; *str1 == *str2 && *str2 && *str1; str1++, str2++); // �� ���ڰ� ����, NULL�� �ƴ� ������ �ݺ��Ͽ� ���մϴ�.
	if (*str1 > *str2) // ���� 1 ���ڿ��� ũ�ٸ� 1�� ��ȯ�մϴ�.
		return 1;
	else if (*str2 > *str1)  // ���� 2 ���ڿ��� ũ�ٸ� -1�� ��ȯ�մϴ�.
		return -1;
	else if (*str1 == *str2) // ������ 0�� ��ȯ�մϴ�.
		return 0;
}
