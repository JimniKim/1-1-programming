#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_WORD_LENGTH 9
#define MAX_FILE_NAME 30

void userTurn(int size, char*** user_board, char*** comp_board, FILE* output, int** priority_board);   // 사용자의 턴에 게임 진행 (단어 입력 등)
void compTurn(int size, char*** user_board, char*** comp_board, int** priority_board, FILE* output);
int countBingo(char*** board, int size);
void updatePriority(int** priorty_board, char*** comp_board, int size, int index1, int index2); // 우선 순위 보드를 업데이트 하는 함수
void freeBingo(char*** user_board, char*** comp_board, int** priorty_board, int size); // 게임이 종료되면 동적 할당 받은 빙고보드와 우선 순위 보드를 할당 해제
void printBingo(int size, char*** user_board, char*** comp_board, FILE* output, int**priority_board);

int main()
{
	char*** user_board = NULL;
	char*** comp_board = NULL;
	char** p = NULL;
	char str[MAX_WORD_LENGTH+1] = ""; // 파일에서 단어를 읽어올 때 쓰일 배열입니다.
	int** priorty_board = NULL;  // 우선 순위 보드를 저장할 배열입니다.
	char filename[MAX_FILE_NAME], printfile[MAX_FILE_NAME]; // 읽기 모드로 열 파일명과 쓰기 모드로 열 파일명을 각각 저장할 배열입니다.
	int choice, total_word, size, bingo_num, i, j, result1, result2, way;
	FILE* getdata, * output;

	srand(time(NULL));
	while (1)  // 빙고 게임의 전체 흐름을 맡고 있는 반복문입니다.
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
			if (!(choice == 1 || choice == 2))  // 1, 2 이외의 숫자 입력 시 다시 입력 받습니다.
				printf("Err: Wrong choice.\n");
		} while (!(choice == 1 || choice == 2));
		if (choice == 2)    // 2를 선택할 시 반복문 밖으로 나가 게임을 종료합니다.
			break;
		printf("Flie Name: ");  // 파일명을 입력 받고, 읽기 모드로 엽니다.
		scanf("%s", filename);
		getdata = fopen(filename, "r");


		if (!(getdata = fopen(filename, "r")))
		{
			printf("Err: File does not exist.\n"); continue;
		}

		fscanf(getdata, "%d\n", &total_word);
		printf("\n\nNumber of words: %d\n", total_word);
		i = 1; j = 0;
		p = (char**)calloc(total_word, sizeof(char*)); // 단어를 저장할 임시 배열입니다.

		while (fscanf(getdata, "%s", str) != EOF)  // 파일 속 단어를 p라는 임시배열에 모두 저장합니다.
		{
			if (!(strcmp(str, "\n")))
				continue;
			printf("%d: %s\n", i, str);
			p[j] = (char*)calloc(strlen(str) + 1, sizeof(char));
			strcpy(p[j], str); 
			i++; j++;
		}

		printf("\nBingo Board Size (2~%d): ", (int)sqrt((double)total_word)); // 빙고 보드의 크기를 입력받고, 범위를 벗어나면 처음으로 돌아갑니다.
		scanf("%d", &size);
		if (size > (int)sqrt(total_word) || size < 2)
		{
			printf("Err: Wrong bingo board size.\n"); continue;
		}
		
		printf("Number of bingos to win (1~%d): ", 2 * size + 2);   // 승리 빙고 개수를 입력받고, 범위를 벗어나면 처음으로 돌아갑니다.
		scanf("%d", &bingo_num);
		if (bingo_num > 2 * size + 2 || bingo_num < 1)
		{
			printf("Err: Wrong numbers to win.\n"); continue;
		}

		user_board = (char***)calloc(size, sizeof(char**));    // 사용자와 컴퓨터 보드 배열을 빙고판 크기에 맞게 동적 할당해줍니다.
		comp_board = (char***)calloc(size, sizeof(char**));

		for (int i = 0; i < size; i++)
		{
			user_board[i] = (char**)calloc(size, sizeof(char*));
			comp_board[i] = (char**)calloc(size, sizeof(char*));
		}


		int index1, index2, n;
		int* selected1;
		selected1 = (int*)malloc(total_word * sizeof(int)); // shuffle일 때 사용할 배열로, 무작위로 뽑은 인덱스를 저장하는 곳입니다.
		int* selected2;
		selected2 = (int*)malloc(total_word * sizeof(int));


		printf("Shuffle (1: Yes, 0: No): ");   // 사용자로부터 보드 생성 방식을 입력 받습니다.
		scanf("%d", &way);
		int k = 0, agn = 0;
		
		if (way == 0) // non shuffle일 때, 사용자, 컴퓨터 보드 배열에 단어를 순서대로 저장합니다.
			for (i = 0; i < size; i++)
				for (j = 0; j < size; j++)
				{
					user_board[i][j] = (char*)calloc((strlen(p[k]) + 1), sizeof(char));
					strcpy(user_board[i][j], p[k]);
					comp_board[i][j] = (char*)calloc((strlen(p[total_word - 1 - k]) + 1), sizeof(char));
					strcpy(comp_board[i][j], p[total_word - 1 - k]);
					k++;
				}
		else // shuffle일 때, p배열의 인덱스를 무작위로 뽑아 사용자, 컴퓨터 배열에 해당 값을 복사합니다.
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
		


		for (i = 0; i < total_word; i++)    // 임시 단어 저장 배열을 동적 할당 해제합니다.
			free(p[i]);
		free(p);

		sprintf(printfile, "%d%d%d_%s", size, bingo_num, way, filename);   // 출력할 파일명을 만드는 과정입니다.
		output = fopen(printfile, "w");

		int** priority_board;
		priority_board = (int**)calloc(size, sizeof(int*));   // 우선 순위 보드를 빙고판 크기에 맞게 동적 할당합니다.
		for (i = 0; i < size; i++)
			priority_board[i] = (int*)calloc(size, sizeof(int));

		for (i = 0; i < size; i++)  // 각 원소가 가질 수 있는 줄의 개수만큼 숫자를 대입해줍니다. (우선 순위보드 초기 단계)
			for (j = 0; j < size; j++)
			{
				priority_board[i][j] = 2;
				if (i == j)
					priority_board[i][j] += 1;
				if (i + j == size - 1)
					priority_board[i][j] += 1;
			}
		
		printBingo(size, user_board, comp_board, output, priority_board);  // 빙고 판의 현황을 출력합니다.
		
		while (1) // 빙고 게임 한 판을 진행하는 반복문입니다.
		{
			userTurn(size, user_board, comp_board, output, priority_board);  // 사용자 턴입니다.
			result1 = countBingo(user_board, size); result2 = countBingo(comp_board, size); // result1, result2에는 각각 사용자, 컴퓨터 보드에 있는 빙고 개수를 저장합니다.
			
			if (result1 >= bingo_num || result2 >= bingo_num) // 만약 둘 중 하나라도 승리 빙고 개수와 같거나 크다면 반복문 밖으로 나갑니다.
				break;
			compTurn(size, user_board, comp_board, priority_board, output);  // 컴퓨터 턴입니다.
			result1 = countBingo(user_board, size); result2 = countBingo(comp_board, size);
			
			if (result1 >= bingo_num || result2 >= bingo_num)
				break;
		}
	
		if (result1 >= bingo_num && result2 >= bingo_num)      // 둘 다 빙고라면 "Draw"를 출력
		{
			printf("Draw\n\n"); fprintf(output, "\nDraw");
		}
		else if (result1 >= bingo_num)
		{
			printf("You Win!\n\n"); fprintf(output, "\nYou Win!");     // 플레이어만 빙고라면 "You Win"을 출력
		}
		else if (result2 >= bingo_num)
		{
			printf("Computer Wins!\n\n"); fprintf(output, "\nComputer Wins!");       // 컴퓨터만 빙고라면 "Computer Wins"을 출력
		}
		freeBingo(user_board, comp_board, priority_board, size); 

		fclose(output);        // 파일 닫기
		fclose(getdata);
	}
	return 0;
}

void printBingo(int size, char*** user_board, char*** comp_board, FILE* output, int** priority_board) // 빙고 판의 현황을 출력합니다.
{
	int i, j, k;
	for (i = 0; i < size; i++)
	{
		for (k = 0; k < size; k++)
			printf("+---------");
		printf("+\t");
		for (k = 0; k < size; k++)
			printf("+---------");
		printf("+\n");  fprintf(output, "\n");
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
	printf("+\n\n"); fprintf(output, "\n\nComputer's priority array\n");
	
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
			fprintf(output, "%2d", priority_board[i][j]);
		fprintf(output, "\n");
	}
}

void userTurn(int size, char*** user_board, char*** comp_board, FILE* output, int** priority_board)  // 사용자 턴입니다.
{
	int i, j, index1, index2;
	char selection[MAX_WORD_LENGTH+1];  // 사용자로부터 입력 받은 단어를 저장하는 배열입니다.
	int check = 1;
	
	do  // 사용자로부터 입력 받은 단어가 사용자 보드에 없다면 다시 입력 받습니다.
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

	fprintf(output, "\nYour choice: %s\n", selection);
	
	for (i = 0; i < size; i++) // 사용자, 컴퓨터 보드 배열에서 입력값과 일치하는 원소의 메모리를 재할당하고 값을 바꿉니다.
		for (j = 0; j < size; j++)
		{
			if (!(strcmp(user_board[i][j], selection)))
			{
				user_board[i][j] = (char*)realloc(user_board[i][j], 10 * sizeof(char));
				strcpy(user_board[i][j], "#########");
			}
			if (!(strcmp(comp_board[i][j], selection)))  
			{
				comp_board[i][j] = (char*)realloc(comp_board[i][j], 10 * sizeof(char)); 
				strcpy(comp_board[i][j], "#########"); index1 = i; index2 = j;
				updatePriority(priority_board, comp_board, size, index1, index2);  // 만약 컴퓨터 보드 배열 원소 중 일치하는 것이 있을 시 우선 순위 보드를 업데이트 합니다.
			}
		}
	printBingo(size, user_board, comp_board, output, priority_board);
}

void compTurn(int size, char*** user_board, char*** comp_board, int** priority_board, FILE* output)  // 컴퓨터 턴입니다.
{
	int i, j, k, maxIndex1, maxIndex2, max;
	max = 0; maxIndex1 = 0; maxIndex2 = 0; // 우선 순위가 가장 높은 원소의 값과 인덱스를 저장하는 변수들입니다.
	
	for (i = 0; i < size; i++)  // 우선순위가 가장 높은 원소의 위치를 찾습니다.
		for (j = 0; j < size; j++)
			if (max < priority_board[i][j])
			{
				max = priority_board[i][j];
				maxIndex1 = i;
				maxIndex2 = j;
			}

	printf("Computer's Choice: %s\n", comp_board[maxIndex1][maxIndex2]); // 우선 순위가 가장 높은 위치에 있는 값을 출력합니다.
	fprintf(output, "\nComputer's choice: %s\n", comp_board[maxIndex1][maxIndex2]);
	
	for (i = 0; i < size; i++) // // 사용자, 컴퓨터 보드 배열에서 출력값과 일치하는 원소의 메모리를 재할당하고 값을 바꿉니다.
		for (j = 0; j < size; j++)
			if (!(strcmp(user_board[i][j], comp_board[maxIndex1][maxIndex2]))) 
			{
				user_board[i][j] = (char*)realloc(user_board[i][j], 10 * sizeof(char));
				strcpy(user_board[i][j], "#########");
			}
	comp_board[maxIndex1][maxIndex2] = (char*)realloc(comp_board[maxIndex1][maxIndex2], 10 * sizeof(char));
	strcpy(comp_board[maxIndex1][maxIndex2], "#########");
	updatePriority(priority_board, comp_board, size, maxIndex1, maxIndex2); 
	printBingo(size, user_board, comp_board, output, priority_board);
}

void updatePriority(int** priority_board, char*** comp_board, int size, int index1, int index2)   // 우선 순위를 업데이트 합니다.
{
	int i, j, k;
	int num[4] = { 0 };
	priority_board[index1][index2] = 0; // 선택된 단어가 위치한 우선 순위 보드 값을 0으로 바꿉니다.
	
	for (i = 0; i < size; i++) // 선택된 단어와 연결된 줄에 0이 몇개 있는지 검사하고 num배열에 각각 저장합니다.
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

	for (k = 0; k < size; k++) // 연결된 줄에 있는, 0이 아닌 원소의 값을 해당 줄의 0의 개수만큼 증가시킵니다.
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
	
}

int countBingo(char*** board, int size) // 빙고 줄의 개수를 반환합니다.
{
	int i, j;
	int result = 0;  // 빙고 줄의 개수를 저장합니다.
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
	{
		if (strcmp(board[i][size-1-i], "#########"))
			break;
		else if (j == 0 && !(strcmp(board[i][size - 1 - i], "#########")))
			result += 1;
	}
	return result;
}

void freeBingo(char*** user_board, char*** comp_board, int** priority_board, int size)  // 동적 할당 받은 배열들을 동적 할당 해제 해줍니다.
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