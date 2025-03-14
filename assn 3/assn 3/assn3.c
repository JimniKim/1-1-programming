#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_WORD_LENGTH 9
#define MAX_FILE_NAME 30

void userTurn(int size, char*** user_board, char*** comp_board, FILE* output, int** priority_board);   // ������� �Ͽ� ���� ���� (�ܾ� �Է� ��)
void compTurn(int size, char*** user_board, char*** comp_board, int** priority_board, FILE* output);
int countBingo(char*** board, int size);
void updatePriority(int** priorty_board, char*** comp_board, int size, int index1, int index2); // �켱 ���� ���带 ������Ʈ �ϴ� �Լ�
void freeBingo(char*** user_board, char*** comp_board, int** priorty_board, int size); // ������ ����Ǹ� ���� �Ҵ� ���� ������� �켱 ���� ���带 �Ҵ� ����
void printBingo(int size, char*** user_board, char*** comp_board, FILE* output, int**priority_board);

int main()
{
	char*** user_board = NULL;
	char*** comp_board = NULL;
	char** p = NULL;
	char str[MAX_WORD_LENGTH+1] = ""; // ���Ͽ��� �ܾ �о�� �� ���� �迭�Դϴ�.
	int** priorty_board = NULL;  // �켱 ���� ���带 ������ �迭�Դϴ�.
	char filename[MAX_FILE_NAME], printfile[MAX_FILE_NAME]; // �б� ���� �� ���ϸ�� ���� ���� �� ���ϸ��� ���� ������ �迭�Դϴ�.
	int choice, total_word, size, bingo_num, i, j, result1, result2, way;
	FILE* getdata, * output;

	srand(time(NULL));
	while (1)  // ���� ������ ��ü �帧�� �ð� �ִ� �ݺ����Դϴ�.
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
			if (!(choice == 1 || choice == 2))  // 1, 2 �̿��� ���� �Է� �� �ٽ� �Է� �޽��ϴ�.
				printf("Err: Wrong choice.\n");
		} while (!(choice == 1 || choice == 2));
		if (choice == 2)    // 2�� ������ �� �ݺ��� ������ ���� ������ �����մϴ�.
			break;
		printf("Flie Name: ");  // ���ϸ��� �Է� �ް�, �б� ���� ���ϴ�.
		scanf("%s", filename);
		getdata = fopen(filename, "r");


		if (!(getdata = fopen(filename, "r")))
		{
			printf("Err: File does not exist.\n"); continue;
		}

		fscanf(getdata, "%d\n", &total_word);
		printf("\n\nNumber of words: %d\n", total_word);
		i = 1; j = 0;
		p = (char**)calloc(total_word, sizeof(char*)); // �ܾ ������ �ӽ� �迭�Դϴ�.

		while (fscanf(getdata, "%s", str) != EOF)  // ���� �� �ܾ p��� �ӽù迭�� ��� �����մϴ�.
		{
			if (!(strcmp(str, "\n")))
				continue;
			printf("%d: %s\n", i, str);
			p[j] = (char*)calloc(strlen(str) + 1, sizeof(char));
			strcpy(p[j], str); 
			i++; j++;
		}

		printf("\nBingo Board Size (2~%d): ", (int)sqrt((double)total_word)); // ���� ������ ũ�⸦ �Է¹ް�, ������ ����� ó������ ���ư��ϴ�.
		scanf("%d", &size);
		if (size > (int)sqrt(total_word) || size < 2)
		{
			printf("Err: Wrong bingo board size.\n"); continue;
		}
		
		printf("Number of bingos to win (1~%d): ", 2 * size + 2);   // �¸� ���� ������ �Է¹ް�, ������ ����� ó������ ���ư��ϴ�.
		scanf("%d", &bingo_num);
		if (bingo_num > 2 * size + 2 || bingo_num < 1)
		{
			printf("Err: Wrong numbers to win.\n"); continue;
		}

		user_board = (char***)calloc(size, sizeof(char**));    // ����ڿ� ��ǻ�� ���� �迭�� ������ ũ�⿡ �°� ���� �Ҵ����ݴϴ�.
		comp_board = (char***)calloc(size, sizeof(char**));

		for (int i = 0; i < size; i++)
		{
			user_board[i] = (char**)calloc(size, sizeof(char*));
			comp_board[i] = (char**)calloc(size, sizeof(char*));
		}


		int index1, index2, n;
		int* selected1;
		selected1 = (int*)malloc(total_word * sizeof(int)); // shuffle�� �� ����� �迭��, �������� ���� �ε����� �����ϴ� ���Դϴ�.
		int* selected2;
		selected2 = (int*)malloc(total_word * sizeof(int));


		printf("Shuffle (1: Yes, 0: No): ");   // ����ڷκ��� ���� ���� ����� �Է� �޽��ϴ�.
		scanf("%d", &way);
		int k = 0, agn = 0;
		
		if (way == 0) // non shuffle�� ��, �����, ��ǻ�� ���� �迭�� �ܾ ������� �����մϴ�.
			for (i = 0; i < size; i++)
				for (j = 0; j < size; j++)
				{
					user_board[i][j] = (char*)calloc((strlen(p[k]) + 1), sizeof(char));
					strcpy(user_board[i][j], p[k]);
					comp_board[i][j] = (char*)calloc((strlen(p[total_word - 1 - k]) + 1), sizeof(char));
					strcpy(comp_board[i][j], p[total_word - 1 - k]);
					k++;
				}
		else // shuffle�� ��, p�迭�� �ε����� �������� �̾� �����, ��ǻ�� �迭�� �ش� ���� �����մϴ�.
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
		


		for (i = 0; i < total_word; i++)    // �ӽ� �ܾ� ���� �迭�� ���� �Ҵ� �����մϴ�.
			free(p[i]);
		free(p);

		sprintf(printfile, "%d%d%d_%s", size, bingo_num, way, filename);   // ����� ���ϸ��� ����� �����Դϴ�.
		output = fopen(printfile, "w");

		int** priority_board;
		priority_board = (int**)calloc(size, sizeof(int*));   // �켱 ���� ���带 ������ ũ�⿡ �°� ���� �Ҵ��մϴ�.
		for (i = 0; i < size; i++)
			priority_board[i] = (int*)calloc(size, sizeof(int));

		for (i = 0; i < size; i++)  // �� ���Ұ� ���� �� �ִ� ���� ������ŭ ���ڸ� �������ݴϴ�. (�켱 �������� �ʱ� �ܰ�)
			for (j = 0; j < size; j++)
			{
				priority_board[i][j] = 2;
				if (i == j)
					priority_board[i][j] += 1;
				if (i + j == size - 1)
					priority_board[i][j] += 1;
			}
		
		printBingo(size, user_board, comp_board, output, priority_board);  // ���� ���� ��Ȳ�� ����մϴ�.
		
		while (1) // ���� ���� �� ���� �����ϴ� �ݺ����Դϴ�.
		{
			userTurn(size, user_board, comp_board, output, priority_board);  // ����� ���Դϴ�.
			result1 = countBingo(user_board, size); result2 = countBingo(comp_board, size); // result1, result2���� ���� �����, ��ǻ�� ���忡 �ִ� ���� ������ �����մϴ�.
			
			if (result1 >= bingo_num || result2 >= bingo_num) // ���� �� �� �ϳ��� �¸� ���� ������ ���ų� ũ�ٸ� �ݺ��� ������ �����ϴ�.
				break;
			compTurn(size, user_board, comp_board, priority_board, output);  // ��ǻ�� ���Դϴ�.
			result1 = countBingo(user_board, size); result2 = countBingo(comp_board, size);
			
			if (result1 >= bingo_num || result2 >= bingo_num)
				break;
		}
	
		if (result1 >= bingo_num && result2 >= bingo_num)      // �� �� ������ "Draw"�� ���
		{
			printf("Draw\n\n"); fprintf(output, "\nDraw");
		}
		else if (result1 >= bingo_num)
		{
			printf("You Win!\n\n"); fprintf(output, "\nYou Win!");     // �÷��̾ ������ "You Win"�� ���
		}
		else if (result2 >= bingo_num)
		{
			printf("Computer Wins!\n\n"); fprintf(output, "\nComputer Wins!");       // ��ǻ�͸� ������ "Computer Wins"�� ���
		}
		freeBingo(user_board, comp_board, priority_board, size); 

		fclose(output);        // ���� �ݱ�
		fclose(getdata);
	}
	return 0;
}

void printBingo(int size, char*** user_board, char*** comp_board, FILE* output, int** priority_board) // ���� ���� ��Ȳ�� ����մϴ�.
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

void userTurn(int size, char*** user_board, char*** comp_board, FILE* output, int** priority_board)  // ����� ���Դϴ�.
{
	int i, j, index1, index2;
	char selection[MAX_WORD_LENGTH+1];  // ����ڷκ��� �Է� ���� �ܾ �����ϴ� �迭�Դϴ�.
	int check = 1;
	
	do  // ����ڷκ��� �Է� ���� �ܾ ����� ���忡 ���ٸ� �ٽ� �Է� �޽��ϴ�.
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
	
	for (i = 0; i < size; i++) // �����, ��ǻ�� ���� �迭���� �Է°��� ��ġ�ϴ� ������ �޸𸮸� ���Ҵ��ϰ� ���� �ٲߴϴ�.
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
				updatePriority(priority_board, comp_board, size, index1, index2);  // ���� ��ǻ�� ���� �迭 ���� �� ��ġ�ϴ� ���� ���� �� �켱 ���� ���带 ������Ʈ �մϴ�.
			}
		}
	printBingo(size, user_board, comp_board, output, priority_board);
}

void compTurn(int size, char*** user_board, char*** comp_board, int** priority_board, FILE* output)  // ��ǻ�� ���Դϴ�.
{
	int i, j, k, maxIndex1, maxIndex2, max;
	max = 0; maxIndex1 = 0; maxIndex2 = 0; // �켱 ������ ���� ���� ������ ���� �ε����� �����ϴ� �������Դϴ�.
	
	for (i = 0; i < size; i++)  // �켱������ ���� ���� ������ ��ġ�� ã���ϴ�.
		for (j = 0; j < size; j++)
			if (max < priority_board[i][j])
			{
				max = priority_board[i][j];
				maxIndex1 = i;
				maxIndex2 = j;
			}

	printf("Computer's Choice: %s\n", comp_board[maxIndex1][maxIndex2]); // �켱 ������ ���� ���� ��ġ�� �ִ� ���� ����մϴ�.
	fprintf(output, "\nComputer's choice: %s\n", comp_board[maxIndex1][maxIndex2]);
	
	for (i = 0; i < size; i++) // // �����, ��ǻ�� ���� �迭���� ��°��� ��ġ�ϴ� ������ �޸𸮸� ���Ҵ��ϰ� ���� �ٲߴϴ�.
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

void updatePriority(int** priority_board, char*** comp_board, int size, int index1, int index2)   // �켱 ������ ������Ʈ �մϴ�.
{
	int i, j, k;
	int num[4] = { 0 };
	priority_board[index1][index2] = 0; // ���õ� �ܾ ��ġ�� �켱 ���� ���� ���� 0���� �ٲߴϴ�.
	
	for (i = 0; i < size; i++) // ���õ� �ܾ�� ����� �ٿ� 0�� � �ִ��� �˻��ϰ� num�迭�� ���� �����մϴ�.
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

	for (k = 0; k < size; k++) // ����� �ٿ� �ִ�, 0�� �ƴ� ������ ���� �ش� ���� 0�� ������ŭ ������ŵ�ϴ�.
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

int countBingo(char*** board, int size) // ���� ���� ������ ��ȯ�մϴ�.
{
	int i, j;
	int result = 0;  // ���� ���� ������ �����մϴ�.
	for (i = 0; i < size; i++) // ������ ���� üũ
	{
		for (j = 0; j < size; j++)
		{
			if (strcmp(board[i][j], "#########"))
				break;
			else if (j == size - 1 && !(strcmp(board[i][j], "#########")))
				result += 1;
		}
	}
	for (j = 0; j < size; j++) // ������ ���� üũ
	{
		for (i = 0; i < size; i++)
		{
			if (strcmp(board[i][j], "#########"))
				break;
			else if (i == size - 1 && !(strcmp(board[i][j], "#########")))
				result += 1;
		}
	}
	for (i = 0; i < size; i++) // ���� �밢�� ���� üũ
	{
		if (strcmp(board[i][i], "#########"))
			break;
		else if (i == size - 1 && !(strcmp(board[i][i], "#########")))
			result += 1;
	}
	for (i = 0; i < size; i++) // ������ �밢�� ���� üũ
	{
		if (strcmp(board[i][size-1-i], "#########"))
			break;
		else if (j == 0 && !(strcmp(board[i][size - 1 - i], "#########")))
			result += 1;
	}
	return result;
}

void freeBingo(char*** user_board, char*** comp_board, int** priority_board, int size)  // ���� �Ҵ� ���� �迭���� ���� �Ҵ� ���� ���ݴϴ�.
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