#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h> // Sleep (1000); -> 1초 지연!
# define MAX_SIZE 5

void printBoard(char user_board[][MAX_SIZE], char comp_board[][MAX_SIZE], int num, FILE* output);
int checkBingo(char board[][MAX_SIZE], int num);
void Bingo(char user_board[][MAX_SIZE], char comp_board[][MAX_SIZE], int num);

int main()
{
	FILE* indata = fopen("board.txt", "r");
	int selection, num, i,j,k;
	int index1, index2;
	char temp;
	char user_board[MAX_SIZE][MAX_SIZE] = { 'A' };
	char comp_board[MAX_SIZE][MAX_SIZE] = { 'A' };
	srand(time(NULL));
	do
	{
		printf("Random or read from file? (1: Random, 2: Read) ");
		scanf("%d", &selection);
	} while (!(selection == 1 || selection == 2));
	
	if (selection == 1)
	{
		do
		{
			printf("\nSize of Bingo board? (3~5) ");
			scanf("%d", &num);

		} while (!(num == 3 || num == 4 || num == 5));
		printf("\n");
		
		k = 0;
		for (i = 0; i < num; i++)
			for (j = 0; j < num; j++)
			{
				user_board[i][j] = (char)(65 + k);
				comp_board[i][j] = (char)(65 + k);
				k++;
			}
		
		for (i = 0; i < num; i++)
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
		fscanf(indata, "%d", &num);

		for (i = 0; i < num; i++)
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
	printf("%d\n\n", num);
	Bingo(user_board, comp_board, num);
	
	return 0;
}

void printBoard(char user_board[][MAX_SIZE], char comp_board[][MAX_SIZE], int num, FILE* output)
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
		for (j = 0; j < num; j++)
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
	printf("+\n\n");
}
int checkBingo(char board[][MAX_SIZE], int num)
{
	int i, j;
	int result = 0;
	for (i = 0; i < num; i++) // 가로줄 빙고 체크
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
	for (j = 0; j < num; j++) // 세로줄 빙고 체크
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
	for (i = 0; i < num; i++) // 왼쪽 대각선 빙고 체크
	{
		if (board[i][i] != '#')
			break;
		else if (i == num - 1 && board[i][i] == '#')
			result = 1;
	}
	for (i = 0; i < num; i++) // 오른쪽 대각선 빙고 체크
		for (j = num - 1; j >= 0; j--)
		{
			if (board[i][j] != '#')
				break;
			else if (j == 0 && board[i][j] == '#')
				result = 1;
		}
	return result;
}
void Bingo(char user_board[][MAX_SIZE], char comp_board[][MAX_SIZE], int num)
{
	int i, j, wrong;
	int k = 0;
	char selected[20] = { 'z' };
	char answer;
	FILE* output = fopen("result.txt", "w");
	int index1, index2, result1, result2;
	printBoard(user_board, comp_board, num, output);
	while (1)
	{
		do
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
		selected[k] = answer; k++;

		for (i = 0; i < num; i++)
			for (j = 0; j < num; j++)
				if (answer == user_board[i][j])
					user_board[i][j] = '#';
		for (i = 0; i < num; i++)
			for (j = 0; j < num; j++)
				if (answer == comp_board[i][j])
					comp_board[i][j] = '#';

		fprintf(output, "User's choice: %c\n", answer);
		printBoard(user_board, comp_board, num, output);
		result1 = checkBingo(user_board, num);
		result2 = checkBingo(comp_board, num);
		if (result2 || result1)
			break;
		printf("Computer's choice: ");
		Sleep(1000);
		do
		{
			index1 = rand() % num;
			index2 = rand() % num;
		} while (comp_board[index1][index2] == '#');
		for (i = 0; i < num; i++)
			for (j = 0; j < num; j++)
			{
				if (comp_board[index1][index2] == user_board[i][j])
					user_board[i][j] = '#';
			}
		printf("%c\n", comp_board[index1][index2]);
		fprintf(output, "Computer's choice: %c\n", comp_board[index1][index2]);
		comp_board[index1][index2] = '#';
		printBoard(user_board, comp_board, num, output);
		result1 = checkBingo(user_board, num);
		result2 = checkBingo(comp_board, num);
		if (result2 || result1)
			break;
	}
	if (result1 == 1 && result2 == 1)
	{
		printf("Draw\n"); fprintf(output, "Draw");
	}
	else if (result1 == 1)
	{
		printf("You Wins!\n"); fprintf(output, "You Wins!");
	}
	else if (result2 == 1)
	{
		printf("Computer Wins!\n"); fprintf(output, "Computer Wins!");
	}
	fclose(output);
	return;
}