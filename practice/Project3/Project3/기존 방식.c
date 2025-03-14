#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_WORD_LENGTH 9
#define MAX_FILE_NAME 30

void userTurn(int size, char*** user_board, char*** comp_board, FILE* output, int**priority_board);   // 사용자의 턴에 게임 진행 (단어 입력 등)
void compTurn(int size, char*** user_board, char*** comp_board, int** priority_board, FILE* output);
int countBingo(char*** board, int size);
void updatePriorty(int** priorty_board, char*** comp_board, int size, int index1, int index2); // 우선 순위 보드를 업데이트 하는 함수
void freeBingo(char*** user_board, char*** comp_board, int** priorty_board, int size); // 게임이 종료되면 동적 할당 받은 빙고보드와 우선 순위 보드를 할당 해제
void printBingo(int size, char*** user_board, char*** comp_board, FILE* output);

int main()
{
	char*** user_board = NULL;
	char*** comp_board = NULL;
	char** p = NULL;
	char str[MAX_WORD_LENGTH] = "";
	int** priorty_board = NULL;
	char filename[MAX_FILE_NAME], printfile[MAX_FILE_NAME];
	int choice, total_word, size, bingo_num, i, j, result1, result2, way;
	FILE* getdata, * output;

	srand(time(NULL));
	while (1)
	{
		printf("[Bingo Game]\n");
		printf("==================================\n");
		printf("1: Start\n");
		printf("2: Exit\n");
		printf("==================================\n");
		do
		{
			printf("Choice: ");
			scanf("%d", &choice);
			if (!(choice == 1 || choice == 2))
				printf("Err: Wrong choice.\n");
		} while (!(choice == 1 || choice == 2));
		if (choice == 2)
			break;
		printf("Flie Name: ");
		scanf("%s", filename);
		getdata = fopen(filename, "r");


		if (!(getdata = fopen(filename, "r")))
		{
			printf("Err: File does not exist.\n"); continue;
		}

		fscanf(getdata, "%d\n", &total_word);
		printf("\n\nNumber of words: %d\n", total_word);
		i = 1; j = 0;
		p = (char**)calloc(total_word, sizeof(char*));

		while (fscanf(getdata, "%s", str) != EOF)
		{
			if (!(strcmp(str, "\n")))
				continue;
			printf("%d: %s\n", i, str);
			p[j] = (char*)calloc(strlen(str) + 1, sizeof(char));
			strcpy(p[j], str); // 파일에 있는 단어를 p라는 이차원 배열에 모두 저장
			i++; j++;
		}

		printf("\nBingo Board Size (2~%d): ", (int)sqrt((double)total_word));
		scanf("%d", &size);
		if (size > (int)sqrt(total_word) || size < 2)
		{
			printf("Err: Wrong bingo board size.\n"); continue;
		}
		printf("Number of bingos to win (1~%d): ", 2 * size + 2);
		scanf("%d", &bingo_num);
		if (bingo_num > 2 * size + 2 || bingo_num < 1)
		{
			printf("Err: Wrong numbers to win.\n"); continue;
		}

		user_board = (char***)calloc(size, sizeof(char**));
		comp_board = (char***)calloc(size, sizeof(char**));

		for (int i = 0; i < size; i++)
		{
			user_board[i] = (char**)calloc(size, sizeof(char*));
			comp_board[i] = (char**)calloc(size, sizeof(char*));
		}

		
		int index1, index2, n;
		int* selected1;
		selected1=(int*)malloc(total_word * sizeof(int));
		int* selected2;
		selected2 = (int*)malloc(total_word * sizeof(int));


		printf("Shuffle (1: Yes, 0: No): ");
		scanf("%d", &way);
		int k = 0, agn = 0;
		if (way == 0)
			for (i = 0; i < size; i++)
				for (j = 0; j < size; j++)
				{
					user_board[i][j] = (char*)calloc((strlen(p[k]) + 1), sizeof(char));
					strcpy(user_board[i][j], p[k]);
					comp_board[i][j] = (char*)calloc((strlen(p[total_word - 1 - k]) + 1), sizeof(char));
					strcpy(comp_board[i][j], p[total_word - 1 - k]);
					k++;
				}
		else
		{
			k = 0;
			for (i = 0; i < size; i++)
				for (j = 0; j < size; j++)
				{
					do
					{
						agn = 0;
						index1 = rand() % total_word;
						index2 = rand() % total_word;
						for (n = 0; n < k; n++)
							if (selected1[n] == index1 || selected2[n] == index2)
								agn = 1;
					} while (agn);
					selected1[k] = index1; selected2[k] = index2; k++;
					user_board[i][j] = (char*)calloc((strlen(p[index1]) + 1), sizeof(char));
					comp_board[i][j] = (char*)calloc((strlen(p[index2]) + 1), sizeof(char));
					strcpy(user_board[i][j], p[index1]);
					strcpy(comp_board[i][j], p[index2]);

				}
		}


		for (i = 0; i < total_word; i++)
			free(p[i]);
		free(p);

		sprintf(printfile, "%d%d%d_%s", size, bingo_num, way, filename);
		output = fopen(printfile, "w");

		int** priority_board;
		priority_board = (int**)calloc(size, sizeof(int*));
		for (i = 0; i < size; i++)
			priority_board[i] = (int*)calloc(size, sizeof(int));
		
		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
			{
				priority_board[i][j] = 2;
				if (i == j)
					priority_board[i][j] += 1;
				if (i + j == size - 1)
					priority_board[i][j] += 1;
				printf("%d", priority_board[i][j]);
				fprintf(output, "%d", priority_board[i][j]);
			}
			fprintf(output, "\n");
			printf("\n");
		}


		printBingo(size, user_board, comp_board, output);
		while (1)
		{
			userTurn(size, user_board, comp_board, output, priority_board);
			result1 = countBingo(user_board, size); result2 = countBingo(comp_board, size);
			printf("%d %d\n\n", result1, result2);
			if (result1 >= bingo_num || result2 >= bingo_num)
				break;
			compTurn(size, user_board, comp_board, priority_board, output);
			result1= countBingo(user_board, size); result2 = countBingo(comp_board, size);
			printf("%d %d\n\n", result1, result2);
			if (result1 >= bingo_num || result2 >= bingo_num)
				break;
		}
		if (result1 >= bingo_num && result2 >= bingo_num)      // 둘 다 빙고라면 "Draw"를 출력
		{
			printf("Draw\n"); fprintf(output, "Draw");
		}
		else if (result1 == bingo_num)
		{
			printf("You Win!\n"); fprintf(output, "You Win!");     // 플레이어만 빙고라면 "You Win"을 출력
		}
		else if (result2 == bingo_num)
		{
			printf("Computer Wins!\n"); fprintf(output, "Computer Wins!");       // 컴퓨터만 빙고라면 "Computer Wins"을 출력
		}
		
		freeBingo(user_board, comp_board, priorty_board, size);
	
		fclose(output);        // 파일 닫기
		fclose(getdata);
	}
	return 0;
}

void printBingo(int size, char*** user_board, char*** comp_board, FILE* output)
{
	int i, j, k;
	for (i = 0; i < size; i++)
	{
		for (k = 0; k < size; k++)
			printf("+---------");
		printf("+\t");
		for (k = 0; k < size; k++)
			printf("+---------");
		printf("+\n");  fprintf(output, "+\n");
		for (j = 0; j < size; j++)
		{
			printf("|%-9s", user_board[i][j]);
			fprintf(output, "%-9s", user_board[i][j]);
		}

		printf("|\t"); fprintf(output, "\t");
		for (j = 0; j < size; j++)
		{
			printf("|%-9s", comp_board[i][j]);
			fprintf(output, "%-9s", comp_board[i][j]);
		}
		printf("|\n"); fprintf(output, "\n");
	}
	for (k = 0; k < size; k++)
		printf("+---------");
	printf("+\t");
	for (k = 0; k < size; k++)
		printf("+---------");
	printf("+\n\n"); fprintf(output, "\n\n");
}

void userTurn(int size, char*** user_board, char*** comp_board, FILE* output, int** priority_board)
{
	int i, j, index1, index2;
	char selection[MAX_WORD_LENGTH];
	int check = 1;
	do
	{
		printf("Your Choice: ");
		scanf("%s", selection);

		for (i = 0; i < size; i++)
			for (j = 0; j < size; j++)
				if (!(strcmp(user_board[i][j], selection)))
					check = 0;
		if (check)
		printf("Wrong Input. '%s' does not exist.\n", selection);

	} while (check);

	fprintf(output, "Your choice: %s\n", selection);
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
		{
			if (!(strcmp(user_board[i][j], selection)))
				user_board[i][j] = "#########";
			if (!(strcmp(comp_board[i][j], selection)))
			{
				comp_board[i][j] = "#########"; priority_board[i][j] = 0; index1 = i; index2 = j;
				updatePriorty(priority_board, comp_board, size, index1, index2);
			}
		}
	
	printBingo(size, user_board, comp_board, output);
}

void compTurn(int size, char*** user_board, char*** comp_board, int** priority_board, FILE* output)
{
	int i, j, k, maxIndex1, maxIndex2, max;

	max = 0; maxIndex1 = 0; maxIndex2 = 0;
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			if (max < priority_board[i][j])
			{
				max = priority_board[i][j];
				maxIndex1 = i;
				maxIndex2 = j;
			}
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			if (max == priority_board[i][j])
			{
				if (maxIndex1 > i)
				{
					maxIndex1 = i;
					maxIndex2 = j;
				}
				else if (maxIndex1 == i && maxIndex2 > j)
					maxIndex2 = j;
			}
	priority_board[maxIndex1][maxIndex2] = 0;
	printf("Computer's Choice: %s\n", comp_board[maxIndex1][maxIndex2]);
	fprintf(output, "Computer's choice: %s\n", comp_board[maxIndex1][maxIndex2]);
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
		{
			if (!(strcmp(user_board[i][j], comp_board[maxIndex1][maxIndex2])))
				user_board[i][j] = "#########";
			if (!(strcmp(comp_board[i][j], comp_board[maxIndex1][maxIndex2])))
				comp_board[i][j] = "#########";
		}
	updatePriorty(priority_board, comp_board, size, maxIndex1, maxIndex2);
	printBingo(size, user_board, comp_board, output);
}

void updatePriorty(int** priority_board, char*** comp_board, int size, int index1, int index2)
{
	int i,j, k;
	int num[4] = { 0 };

	for (i = 0; i < size; i++)
	{
		if (priority_board[index1][i] == 0)
			num[0] += 1;
		if (priority_board[i][index2] == 0)
			num[1] += 1;
	}
	if (index1 == index2)
		for (i = 0; i < size; i++)
			if (priority_board[i][i] == 0)
				num[2] += 1;
	if (index1 + index2 == size - 1)
		for (i = 0; i < size; i++)
			if (priority_board[i][size - i - 1] == 0)
				num[3] += 1;

	for (k = 0; k < size; k++)
	{
		if (priority_board[index1][k] != 0)
			priority_board[index1][k] += num[0];

		if (priority_board[k][index2] != 0)
			priority_board[k][index2] += num[1];
	}
	if (index1 == index2)
		for (k = 0; k < size; k++)
			if (priority_board[k][k] != 0)
				priority_board[k][k] += num[2];

	if (index1 + index2 == size - 1)
		for (k = 0; k < size; k++)
			if (priority_board[k][size - 1 - k] != 0)
				priority_board[k][size - 1 - k] += num[3];
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
			printf("%d ", priority_board[i][j]);
		printf("\n");
	}
}

int countBingo(char*** board, int size)
{
	int i, j;
	int result = 0;
	for (i = 0; i < size; i++) // 가로줄 빙고 체크
	{
		for (j = 0; j < size; j++)
		{
			if (strcmp(board[i][j], "#########"))
				break;
			else if (j == size - 1 && !(strcmp(board[i][j], "#########")))
				result += 1;
		}
	}
	for (j = 0; j < size; j++) // 세로줄 빙고 체크
	{
		for (i = 0; i < size; i++)
		{
			if (strcmp(board[i][j], "#########"))
				break;
			else if (i == size - 1 && !(strcmp(board[i][j], "#########")))
				result += 1;
		}
	}
	for (i = 0; i < size; i++) // 왼쪽 대각선 빙고 체크
	{
		if (strcmp(board[i][i], "#########"))
			break;
		else if (i == size - 1 && !(strcmp(board[i][i], "#########")))
			result += 1;
	}
	for (i = 0; i < size; i++) // 오른쪽 대각선 빙고 체크
		for (j = size - 1; j >= 0; j--)
		{
			if (strcmp(board[i][j], "#########"))
				break;
			else if (j == 0 && !(strcmp(board[i][j], "#########")))
				result += 1;
		}
	return result;
}

void freeBingo(char*** user_board, char*** comp_board, int** priority_board, int size)
{
	int i, j;
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
		{
			free(user_board[i][j]);
			free(comp_board[i][j]);
		}
	for (i = 0; i < size; i++)
	{
		free(user_board[i]); free(comp_board[i]); free(priority_board[i]);
	}
	free(user_board); free(comp_board); free(priority_board);
}