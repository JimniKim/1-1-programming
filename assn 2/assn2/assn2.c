#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h> // Sleep (1000); -> 1�� ����!
# define MAX_SIZE 5

void printBoard(char user_board[][MAX_SIZE], char comp_board[][MAX_SIZE], int num, FILE* output);
int checkBingo(char board[][MAX_SIZE], int num);
void Bingo(char user_board[][MAX_SIZE], char comp_board[][MAX_SIZE], int num);

int main() // �÷��̾�� ��ǻ�� ���� ���� �����ϴ� 2���� �迭�� �����մϴ�.
{
	FILE* indata = fopen("board.txt", "r"); 
	int selection, num, i,j,k; 
	int index1, index2;
	char temp;
	char user_board[MAX_SIZE][MAX_SIZE] = { 'A' }; // �� �迭�� �ʱ�ȭ�մϴ�.
	char comp_board[MAX_SIZE][MAX_SIZE] = { 'A' };
	srand(time(NULL));
	do // ����ڷκ��� ���� �� ���� ����� �Է� �ް� selection ������ �����մϴ�.
	{
		printf("Random or read from file? (1: Random, 2: Read) ");
		scanf("%d", &selection);
	} while (!(selection == 1 || selection == 2));
	
	if (selection == 1)
	{
		do // ����ڷκ��� ���� ���� ũ�⸦ �Է� �޾� num ������ �����մϴ�.
		{
			printf("\nSize of Bingo board? (3~5) ");
			scanf("%d", &num);

		} while (!(num == 3 || num == 4 || num == 5)); 
		printf("\n");
		
		k = 0;
		for (i = 0; i < num; i++) // �� �迭�� ���ĺ��� ���ʴ�� �Է��մϴ�.
			for (j = 0; j < num; j++)
			{
				user_board[i][j] = (char)(65 + k);
				comp_board[i][j] = (char)(65 + k);
				k++;
			}
		
		for (i = 0; i < num; i++) //  �迭�� �ε����� �������� �̾� �������ν� �迭 ���Ҹ� �������� �����մϴ�.
			for (j = 0; j < num; j++)
			{
				index1 = rand() % num + 0;
				index2 = rand() % num + 0;
				temp = user_board[i][j];
				user_board[i][j] = user_board[index1][index2];
				user_board[index1][index2] = temp;
			}
		for (i = 0; i < num; i++)
			for (j = 0; j < num; j++)
			{
				index1 = rand() % num + 0;
				index2 = rand() % num + 0;
				temp = comp_board[i][j];
				comp_board[i][j] = comp_board[index1][index2];
				comp_board[index1][index2] = temp;
			}
	}
	else
	{
		fscanf(indata, "%d", &num); // ���� ���� ���� �ִ� ���ڸ� num ������ �����մϴ�. �̴� ���� ���� ũ�⸦ �ǹ��մϴ�.

		for (i = 0; i < num; i++) // ���Ͽ��� ����, �ٹٲ� ���� ������ ���ڸ� �迭�� �Է� �޽��ϴ�.
		{
			for (j = 0; j < num; j++)
				do
				{
					fscanf(indata, "%c", &user_board[i][j]);
				} while (user_board[i][j] == '\n' || user_board[i][j] == ' ');
		}
		for (i = 0; i < num; i++)
		{
			for (j = 0; j < num; j++)
				do
				{
					fscanf(indata, "%c", &comp_board[i][j]);
				} while (comp_board[i][j] == '\n' || comp_board[i][j] == ' ');
		}
	}
	
	Bingo(user_board, comp_board, num); // ���� ������ �����ϴ� �Լ��� ȣ���մϴ�.
	
	return 0;
}

void printBoard(char user_board[][MAX_SIZE], char comp_board[][MAX_SIZE], int num, FILE* output) // ���� ���� ��Ȳ�� ����ϴ� �Լ��Դϴ�. ����� ���Ͽ� ����ϱ⵵ �մϴ�.
{
	int i, j, k;
	for (i = 0; i < num; i++)
	{
		for (k = 0; k < num; k++)
			printf("+-");
		printf("+\t");
		for (k = 0; k < num; k++)
			printf("+-");
		printf("+\n");
		for (j = 0; j < num; j++)
		{
			printf("|%c", user_board[i][j]);
			fprintf(output, "%c ", user_board[i][j]);
		}
		printf("|\t"); fprintf(output, "\t");
		for (j = 0; j < num; j++) // ��ǻ���� ���ĺ��� ����� �Ǹ� �ȵǹǷ�, '#'�� �ƴϸ� �������� ����ϵ��� �մϴ�.
		{
			if (comp_board[i][j] == '#')
				printf("|%c", comp_board[i][j]);
			else
				printf("| ");
			fprintf(output, "%c ", comp_board[i][j]);
		}
		printf("|\n"); fprintf(output, "\n");
	}
	for (k = 0; k < num; k++)
		printf("+-");
	printf("+\t");
	for (k = 0; k < num; k++)
		printf("+-");
	printf("+\n\n"); fprintf(output, "\n\n");
}
int checkBingo(char board[][MAX_SIZE], int num) // �ϼ��� ���� �ִ��� �˻��ϴ� �Լ��Դϴ�. ���� �� ���̶� �ִٸ� 1��, �ƴ϶�� 0�� ��ȯ�մϴ�.
{
	int i, j;
	int result = 0;
	for (i = 0; i < num; i++) // ������ ���� üũ
	{
		for (j = 0; j < num; j++)
		{
			if (board[i][j] != '#')
				break;
			else if (j == num - 1 && board[i][j] == '#')
				result = 1;
		}
		if (result == 1)
			break;
	}
	for (j = 0; j < num; j++) // ������ ���� üũ
	{
		for (i = 0; i < num; i++)
		{
			if (board[i][j] != '#')
				break;
			else if (i == num - 1 && board[i][j] == '#')
				result = 1;
		}
		if (result == 1)
			break;
	}
	for (i = 0; i < num; i++) // ���� �밢�� ���� üũ
	{
		if (board[i][i] != '#')
			break;
		else if (i == num - 1 && board[i][i] == '#')
			result = 1;
	}
	for (i = 0; i < num; i++) // ������ �밢�� ���� üũ
		for (j = num - 1; j >= 0; j--)
		{
			if (board[i][j] != '#')
				break;
			else if (j == 0 && board[i][j] == '#')
				result = 1;
		}
	return result;
}
void Bingo(char user_board[][MAX_SIZE], char comp_board[][MAX_SIZE], int num) // ���� ������ �����ϴ� �Լ��Դϴ�.
{
	int i, j, wrong;
	int k = 0;
	char selected[30] = { 'z' };
	char answer;
	FILE* output = fopen("result.txt", "w");
	int index1, index2, result1, result2;
	printf("\n");
	printBoard(user_board, comp_board, num, output); // ó�� ���� ���� ����մϴ�.
	while (1)
	{
		do // �÷��̾�κ��� �ùٸ� ���ĺ��� �Է� �޽��ϴ�.
		{
			wrong = 0;
			printf("Your choice: ");
			scanf(" %c", &answer);
			if ((int)answer >= 65 + num * num)
				wrong = 1;
			for (i = 0; i < 20; i++)
				if (answer == selected[i])
					wrong = 1;
		} while (wrong);
		selected[k] = answer; k++; // �Է� ���� ���ĺ��� ���ο� 1���� �迭�� �����մϴ�.

		for (i = 0; i < num; i++) // �迭�� ��� ���ҿ� �Է°��� ��ġ�ϴ��� �˻��ϰ� ���� '#'���� �ٲߴϴ�.
			for (j = 0; j < num; j++)
				if (answer == user_board[i][j])
					user_board[i][j] = '#';
		for (i = 0; i < num; i++)
			for (j = 0; j < num; j++)
				if (answer == comp_board[i][j])
					comp_board[i][j] = '#';

		fprintf(output, "User's choice: %c\n", answer);
		printBoard(user_board, comp_board, num, output); // ���� ���� ��Ȳ�� ����մϴ�.
		result1 = checkBingo(user_board, num); // �÷��̾��� ���� ���� �˻��մϴ�. 
		result2 = checkBingo(comp_board, num); // ��ǻ���� �������� �˻��մϴ�.
		if (result2 || result1) // ���� �� �� �ϳ���� ���� �Ǿ��ٸ� �� �ݺ����� �����ϴ�.
			break;
		printf("Computer's choice: ");
		Sleep(1000); // 1���� ���� �ð��� �����մϴ�.
		do // rand �Լ��� �̿��Ͽ� �ùٸ� ���ĺ��� �������� �̽��ϴ�. 
		{
			index1 = rand() % num;
			index2 = rand() % num;
		} while (comp_board[index1][index2] == '#');
		
		selected[k] = comp_board[index1][index2]; k++;
		
		for (i = 0; i < num; i++)     // ��ġ�ϴ� �÷��̾� �迭�� ���� ���� '#'���� �ٲߴϴ�.
			for (j = 0; j < num; j++)
			{
				if (comp_board[index1][index2] == user_board[i][j])
					user_board[i][j] = '#';
			}
		printf("%c\n", comp_board[index1][index2]);
		fprintf(output, "Computer's choice: %c\n", comp_board[index1][index2]);
		comp_board[index1][index2] = '#';            // ���� �����մϴ�.
		printBoard(user_board, comp_board, num, output);
		result1 = checkBingo(user_board, num); 
		result2 = checkBingo(comp_board, num);
		if (result2 || result1)
			break;
	}
	if (result1 == 1 && result2 == 1)      // �� �� ������ "Draw"�� ���
	{
		printf("Draw\n"); fprintf(output, "Draw");
	}
	else if (result1 == 1)
	{
		printf("You Win!\n"); fprintf(output, "You Win!");     // �÷��̾ ������ "You Win"�� ���
	}
	else if (result2 == 1)
	{
		printf("Computer Wins!\n"); fprintf(output, "Computer Wins!");       // ��ǻ�͸� ������ "Computer Wins"�� ���
	}
	fclose(output);        // ���� �ݱ�
	return;
}