#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h> // Sleep (1000); -> 1초 지연!
# define MAX_SIZE 5

void printBoard(char user_board[][MAX_SIZE], char comp_board[][MAX_SIZE], int num, FILE* output);
int checkBingo(char board[][MAX_SIZE], int num);
void Bingo(char user_board[][MAX_SIZE], char comp_board[][MAX_SIZE], int num);

int main() // 플레이어와 컴퓨터 빙고 판을 구성하는 2차원 배열을 생성합니다.
{
	FILE* indata = fopen("board.txt", "r"); 
	int selection, num, i,j,k; 
	int index1, index2;
	char temp;
	char user_board[MAX_SIZE][MAX_SIZE] = { 'A' }; // 두 배열을 초기화합니다.
	char comp_board[MAX_SIZE][MAX_SIZE] = { 'A' };
	srand(time(NULL));
	do // 사용자로부터 빙고 판 생성 방식을 입력 받고 selection 변수에 저장합니다.
	{
		printf("Random or read from file? (1: Random, 2: Read) ");
		scanf("%d", &selection);
	} while (!(selection == 1 || selection == 2));
	
	if (selection == 1)
	{
		do // 사용자로부터 빙고 판의 크기를 입력 받아 num 변수에 저장합니다.
		{
			printf("\nSize of Bingo board? (3~5) ");
			scanf("%d", &num);

		} while (!(num == 3 || num == 4 || num == 5)); 
		printf("\n");
		
		k = 0;
		for (i = 0; i < num; i++) // 두 배열에 알파벳을 차례대로 입력합니다.
			for (j = 0; j < num; j++)
			{
				user_board[i][j] = (char)(65 + k);
				comp_board[i][j] = (char)(65 + k);
				k++;
			}
		
		for (i = 0; i < num; i++) //  배열의 인덱스를 무작위로 뽑아 섞음으로써 배열 원소를 랜덤으로 저장합니다.
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
		fscanf(indata, "%d", &num); // 파일 제일 위에 있는 숫자를 num 변수에 저장합니다. 이는 빙고 판의 크기를 의미합니다.

		for (i = 0; i < num; i++) // 파일에서 공백, 줄바꿈 등을 제외한 문자를 배열에 입력 받습니다.
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
	
	Bingo(user_board, comp_board, num); // 빙고 게임을 진행하는 함수를 호출합니다.
	
	return 0;
}

void printBoard(char user_board[][MAX_SIZE], char comp_board[][MAX_SIZE], int num, FILE* output) // 빙고 판의 현황을 출력하는 함수입니다. 결과를 파일에 출력하기도 합니다.
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
		for (j = 0; j < num; j++) // 컴퓨터의 알파벳은 출력이 되면 안되므로, '#'이 아니면 공백으로 출력하도록 합니다.
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
int checkBingo(char board[][MAX_SIZE], int num) // 완성된 줄이 있는지 검사하는 함수입니다. 만약 한 줄이라도 있다면 1을, 아니라면 0을 반환합니다.
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
void Bingo(char user_board[][MAX_SIZE], char comp_board[][MAX_SIZE], int num) // 빙고 게임을 진행하는 함수입니다.
{
	int i, j, wrong;
	int k = 0;
	char selected[30] = { 'z' };
	char answer;
	FILE* output = fopen("result.txt", "w");
	int index1, index2, result1, result2;
	printf("\n");
	printBoard(user_board, comp_board, num, output); // 처음 빙고 판을 출력합니다.
	while (1)
	{
		do // 플레이어로부터 올바른 알파벳을 입력 받습니다.
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
		selected[k] = answer; k++; // 입력 받은 알파벳을 새로운 1차원 배열에 저장합니다.

		for (i = 0; i < num; i++) // 배열의 어느 원소와 입력값이 일치하는지 검사하고 값을 '#'으로 바꿉니다.
			for (j = 0; j < num; j++)
				if (answer == user_board[i][j])
					user_board[i][j] = '#';
		for (i = 0; i < num; i++)
			for (j = 0; j < num; j++)
				if (answer == comp_board[i][j])
					comp_board[i][j] = '#';

		fprintf(output, "User's choice: %c\n", answer);
		printBoard(user_board, comp_board, num, output); // 빙고 판의 현황을 출력합니다.
		result1 = checkBingo(user_board, num); // 플레이어의 빙고 판을 검사합니다. 
		result2 = checkBingo(comp_board, num); // 컴퓨터의 빙고판을 검사합니다.
		if (result2 || result1) // 만약 둘 중 하나라면 빙고가 되었다면 이 반복문을 나갑니다.
			break;
		printf("Computer's choice: ");
		Sleep(1000); // 1초의 지연 시간을 설정합니다.
		do // rand 함수를 이용하여 올바른 알파벳을 무작위로 뽑습니다. 
		{
			index1 = rand() % num;
			index2 = rand() % num;
		} while (comp_board[index1][index2] == '#');
		
		selected[k] = comp_board[index1][index2]; k++;
		
		for (i = 0; i < num; i++)     // 일치하는 플레이어 배열의 원소 값을 '#'으로 바꿉니다.
			for (j = 0; j < num; j++)
			{
				if (comp_board[index1][index2] == user_board[i][j])
					user_board[i][j] = '#';
			}
		printf("%c\n", comp_board[index1][index2]);
		fprintf(output, "Computer's choice: %c\n", comp_board[index1][index2]);
		comp_board[index1][index2] = '#';            // 값을 변경합니다.
		printBoard(user_board, comp_board, num, output);
		result1 = checkBingo(user_board, num); 
		result2 = checkBingo(comp_board, num);
		if (result2 || result1)
			break;
	}
	if (result1 == 1 && result2 == 1)      // 둘 다 빙고라면 "Draw"를 출력
	{
		printf("Draw\n"); fprintf(output, "Draw");
	}
	else if (result1 == 1)
	{
		printf("You Win!\n"); fprintf(output, "You Win!");     // 플레이어만 빙고라면 "You Win"을 출력
	}
	else if (result2 == 1)
	{
		printf("Computer Wins!\n"); fprintf(output, "Computer Wins!");       // 컴퓨터만 빙고라면 "Computer Wins"을 출력
	}
	fclose(output);        // 파일 닫기
	return;
}