# define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <string.h>
#include <stdlib.h>
#define MAX_LENGTH 45

typedef struct // ���� ������ �����ϴ� ����ü�Դϴ�.
{
	int count;  // ��� Ƚ���� ����
	int time;   // ��� �ð��� ����
	char title[MAX_LENGTH + 1]; // ������ ����
	char artist[MAX_LENGTH + 1]; // ��Ƽ��Ʈ�� ����
}MUSIC;
typedef struct play // ���� ������ ���� MUSIC����ü �� ���� ����, �����ͺ����� �����ϴ� ����ü�Դϴ�. 
{
	int num;
	MUSIC data;
	struct play* next;
}NODE;
typedef struct // �� ���� ������ �� ���� ������ ������ ����Ʈ ����ü�Դϴ�.
{
	int num;
	NODE* head;
}PLAYLIST;
void show(PLAYLIST* plist);
void search(PLAYLIST* plist);
void add(PLAYLIST* plist);
void delete(PLAYLIST* plist);
void move(PLAYLIST* plist);
void quit(PLAYLIST* plist);

void descending(PLAYLIST* plist);
int main()
{
	int i, j;
	FILE* getdata;  // �����͸� �ҷ��� ���� �ּҸ� �����մϴ�.
	char filename[MAX_LENGTH], command[10];  //  �����͸� �ҷ��� ���ϸ��� ������ �迭�� ��ɾ ������ �迭�Դϴ�.
	NODE* temp;
	PLAYLIST* plist = (PLAYLIST*)malloc(sizeof(PLAYLIST)); // ���� ������ ������ ����Ʈ �������Դϴ�.
	plist->head = NULL;  // plist �ʱ�ȭ
	plist->num = 0;
	PLAYLIST* pre = (PLAYLIST*)malloc(sizeof(PLAYLIST));

	do  // ���ϸ��� �Է¹޽��ϴ�.
	{
		printf("������ �÷��̸���Ʈ�� ������ ���� �̸��� �Է����ּ���. >> ");
		scanf("%s", filename);
		if (!(getdata = fopen(filename, "r")))
			printf("��ȿ���� ���� �Է��Դϴ�. ");
	} while (!(getdata = fopen(filename, "r")));

	temp = (NODE*)malloc(sizeof(NODE));

	int total = 0;

	for (i = 0;
		fscanf(getdata, "%[^\t]s", temp->data.title) != EOF     // ���Ϸκ��� �����͸� �� �پ� �о�� ����Ʈ�� �����մϴ�.
		; i++, temp = (NODE*)malloc(sizeof(NODE)))
	{
		fscanf(getdata, " %[^\t]s", temp->data.artist);  //���� ���� ������ ���ڸ� �Է� �޽��ϴ�.
		fscanf(getdata, "%d", &(temp->data.time));
		fscanf(getdata, "%d\n", &(temp->data.count));

		temp->next = NULL;

		if (plist->head == NULL)
			plist->head = temp;
		else
			pre->head->next = temp;
		pre->head = temp;
	}
	plist->num = i;  // �� ���� ������ �����մϴ�.
	int time_sum = 0;  // �� ���� ��� �ð��� �����ϴ� �����Դϴ�.

	descending(plist, total); //  plist�� ����� ����Ʈ�� ������������ �����մϴ�.

	printf("\n��� Ƚ�� Top 3 ������ �����Դϴ�.\n");  // ���� 3���� ���� ������ ����մϴ�.
	printf("==============================================================================================================================\n");
	printf("\ttitle\t\t\t\t\t\tartist\t\t\t\t\t time\t# of plays\n");
	printf("------------------------------------------------------------------------------------------------------------------------------\n");
	for (i = 0, temp = plist->head; i < 3; i++, temp = temp->next)
	{
		printf("%d\t%-45s%-45s%d\t%d\n", temp->num, temp->data.title, temp->data.artist, temp->data.time, temp->data.count);
		time_sum += temp->data.time;
	}
	printf("===============================================================================================================================\n");
	printf(" [total: %d music, %d (s)\n\n", i, time_sum);
	int check;  // ��ȿ�� ��ɾ �Է� ���� ������ �ݺ����� ���� �ϴ� �����Դϴ�. 
	while (1)
	{

		do  // ��ȿ�� ��ɾ �Է� ���� ������ �ݺ��մϴ�.
		{
			check = 0;
			printf("��ɾ �Է����ּ���. >> ");
			scanf("%s", command);
			if (strcmp(command, "show") && strcmp(command, "search") && strcmp(command, "add") && strcmp(command, "delete") && strcmp(command, "move") && strcmp(command, "quit"))
			{
				check = 1; printf("��ȿ���� ���� �Է��Դϴ�. ");
			}
		} while (check);

		if (!strcmp(command, "show"))  // �Է� ���� ��ɾ �ش��ϴ� �Լ��� ȣ���մϴ�.
			show(plist);
		else if (!strcmp(command, "search"))
			search(plist);
		else if (!strcmp(command, "add"))
			add(plist);
		else if (!strcmp(command, "delete"))
			delete (plist);
		else if (!strcmp(command, "move"))
			move(plist);
		else if (!strcmp(command, "quit"))  // quit�� �Է� ���� ��, quit�Լ��� ȣ���ϰ� �ݺ����� �������� ���α׷��� �����մϴ�.
		{
			quit(plist); break;
		}

	}
	fclose(getdata);  // ������ �ݽ��ϴ�.
	return 0;
}

void descending(PLAYLIST* plist)  // ����Ʈ�� ������������ �����ϴ� �Լ��Դϴ�.
{
	NODE* temp, * pre, * p; // pre�� temp�� ���� ��带 ����Ű��, p�� temp->next->next�� �ӽ÷� �����մϴ�.
	int i, j;
	for (i = 0; i < (plist->num) - 1; i++)
	{
		for (pre = plist->head, temp = plist->head->next, j = 0; temp->next != NULL; temp = pre->next, j++) // ��带 2���� ���ʴ�� ���ϸ� ������ �ٲߴϴ�. (�� ���� ����)���� �ݺ����ݴϴ�. 
		{
			if (j == 0 && plist->head->data.count < temp->data.count) // ù ��° ���� �� ��° ����� ������ �ٲٴ� ����Դϴ�.
			{
				plist->head->next = temp->next;
				temp->next = plist->head;
				plist->head = temp; pre = plist->head;
			}
			else if (temp->data.count < temp->next->data.count)  // �߰��̳� �� �κп��� ������ �ٲٴ� ����Դϴ�.
			{

				p = temp->next->next;
				temp->next->next = temp;
				temp = temp->next;
				pre->next->next = p;
				pre->next = temp;
				pre = pre->next;
			}
			else if (j != 0)
				pre = temp;
		}
	}
	for (temp = plist->head, i = 1; temp != NULL; temp = temp->next, i++)  // �� ���� ������ ������ �����մϴ�.
		temp->num = i;
}
void show(PLAYLIST* plist)  // ���� �÷��̸���Ʈ�� ����մϴ�.
{
	int time_sum = 0;
	NODE* temp = malloc(sizeof(NODE));
	printf("\n==============================================================================================================================\n");
	printf("\ttitle\t\t\t\t\t\tartist\t\t\t\t\t time\t# of plays\n");
	printf("------------------------------------------------------------------------------------------------------------------------------\n");
	for (temp = plist->head; temp != NULL; temp = temp->next) // ����Ʈ�� ù ��° ������ ������ ��忡 �ִ� �������� ����մϴ�.
	{
		printf("%d\t%-45s%-45s%d\t%d\n", temp->num, temp->data.title, temp->data.artist, temp->data.time, temp->data.count);
		time_sum += temp->data.time;
	}
	printf("===============================================================================================================================\n");
	printf(" [total: %d music, %d (s)\n\n", (plist->num), time_sum); // �� ���� ������ ��� �ð��� ���� ����մϴ�.

}
void search(PLAYLIST* plist)  // ���ϴ� ��Ƽ��Ʈ�� ���� ������ ����մϴ�.
{
	int total = 0, time_sum = 0, check = 1;  // ���� ã���� �ϴ� ��Ƽ��Ʈ�� ���� ����, ��� �ð��� ��, �ݺ��� ���� �˻��� �� ���̴� �������Դϴ�.
	NODE* temp = malloc(sizeof(NODE));
	char find_artist[MAX_LENGTH];  // �Է� ���� ��Ƽ��Ʈ �̸��� �����մϴ�.

	printf("� ��Ƽ��Ʈ�� ������ �˻��ұ��? >> ");  // ���ϴ� ��Ƽ��Ʈ�� �Է� �޽��ϴ�.
	scanf(" %[^\n]s", find_artist);
	for (temp = plist->head; temp != NULL; temp = temp->next) // ��Ƽ��Ʈ�� �����ϴ��� �˻��մϴ�.
		if (!strcmp(temp->data.artist, find_artist))
			check = 0;
	if (check) // ã���� �ϴ� ��Ƽ��Ʈ�� �������� ���� ��, �ٽ� ���� ȭ������ ���ư��ϴ�.
	{
		printf("�÷��̸���Ʈ�� �ش� ��Ƽ��Ʈ�� ������ �����ϴ�.\n\n");
		return;
	}
	printf("\n==============================================================================================================================\n");
	printf("\ttitle\t\t\t\t\t\tartist\t\t\t\t\t time\t# of plays\n");
	printf("------------------------------------------------------------------------------------------------------------------------------\n");
	for (temp = plist->head; temp != NULL; temp = temp->next)  // ���ϴ� ��Ƽ��Ʈ�� ������ ����մϴ�.
		if (!strcmp(temp->data.artist, find_artist))
		{
			printf("%d\t%-45s%-45s%d\t%d\n", temp->num, temp->data.title, temp->data.artist, temp->data.time, temp->data.count);
			time_sum += temp->data.time; total++;
		}
	printf("===============================================================================================================================\n");
	printf(" [total: %d music, %d (s)\n\n", total, time_sum);
	return;
}
void add(PLAYLIST* plist) // ���ϴ� ������ ���� ������ �߰��մϴ�.
{
	NODE* temp = malloc(sizeof(NODE));
	NODE* pnew = malloc(sizeof(NODE));  // ���� �߰��� ��带 ����Ű�� �����ͺ����Դϴ�.
	NODE* pre = malloc(sizeof(NODE));
	int check, i;
	do  // ���� ���� ������ �Է� �޽��ϴ�.
	{
		check = 0;
		printf("�� ��° ������ ������ �߰��ұ��? >> ");
		scanf("%d", &(pnew->num));
		if (pnew->num < 1 || pnew->num >(plist->num) + 1)
		{
			check = 1; printf("��ȿ���� ���� �Է��Դϴ�. ");
		}
	} while (check);
	(plist->num)++; // �� ���� ������ �ø��ϴ�.
	printf("�߰��� ������ ������ �Է����ּ���. >> ");
	scanf(" %[^\n]s", pnew->data.title);
	printf("�߰��� ������ ��Ƽ��Ʈ�� �Է����ּ���. >> ");
	scanf("\n%[^\n]s", pnew->data.artist);
	printf("�߰��� ������ ��� �ð��� �Է����ּ���. >> ");
	scanf("%d", &(pnew->data.time));
	printf("�߰��� ������ ��� Ƚ���� �Է����ּ���. >> ");
	scanf("%d", &(pnew->data.count));
	pnew->next = NULL;
	if (plist->head == NULL) // �� ����Ʈ�� �߰��� ����Դϴ�.
	{
		pnew->next = plist->head;
		plist->head = pnew;
	}
	else // ������ ����Դϴ�.
	{
		for (pre = plist->head, temp = pre; temp != NULL; pre = pre->next, temp = pre->next)
		{
			temp = pre->next;
			if (pnew->num == 1) // ù ��°�� �߰��ϴ� ����Դϴ�.
			{
				pnew->next = plist->head;
				plist->head = pnew;
				break;
			}
			else if (temp->num == (plist->num) - 1 && pnew->num == (plist->num)) // �� ������ ������ �߰��ϴ� ����Դϴ�.
			{
				temp->next = pnew; break;
			}
			else if (temp->num == pnew->num) // �߰��� �߰��ϴ� ����Դϴ�.
			{
				pnew->next = pre->next;
				pre->next = pnew;
				break;
			}
		}
	}
	for (temp = plist->head, i = 1; temp != NULL; temp = temp->next, i++)  // �� ���� ������ ������ �ٽ� �����մϴ�.
		temp->num = i;

}
void delete(PLAYLIST* plist)  // ���ϴ� ������ ������ �����մϴ�.
{
	NODE* temp = malloc(sizeof(NODE));
	NODE* pre = malloc(sizeof(NODE));
	int check, i, delete_node; // delete_node�� ������ ���� ������ �����ϴ� �����Դϴ�.

	if (plist->head == NULL)  // �� ����Ʈ�� ��� ������ �������� �ʰ� ���� �Լ��� ���ư��ϴ�.
	{
		printf("�÷��̸���Ʈ�� ������ ������ �����ϴ�."); return;
	}

	do  // ���� ���� ������ �Է� �޽��ϴ�.
	{
		check = 0;
		printf("�� ��° ������ ������ �����ұ��? >> ");
		scanf(" %d", &delete_node);
		if (delete_node < 1 || delete_node >(plist->num))
		{
			check = 1; printf("��ȿ���� ���� �Է��Դϴ�. ");
		}
	} while (check);
	(plist->num)--;
	printf("\n==============================================================================================================================\n");
	printf("\ttitle\t\t\t\t\t\tartist\t\t\t\t\t time\t# of plays\n");
	printf("------------------------------------------------------------------------------------------------------------------------------\n");

	for (pre = plist->head; temp != NULL; temp = pre->next)
	{
		temp = pre->next;
		if (delete_node == 1)  // ù ��° ��带 �����ϴ� ����Դϴ�.
		{
			printf("%d\t%-45s%-45s%d\t%d\n", pre->num, pre->data.title, pre->data.artist, pre->data.time, pre->data.count);

			printf("===============================================================================================================================\n");
			printf(" [total: 1 music, %d (s)\n", pre->data.time);
			plist->head = temp; free(pre); break;  // �ش� ����� ������ ����ϰ� ���� �Ҵ� �����մϴ�.
		}
		else if (delete_node == temp->num)  // ������ ����Դϴ�.
		{
			printf("%d\t%-45s%-45s%d\t%d\n", temp->num, temp->data.title, temp->data.artist, temp->data.time, temp->data.count);

			printf("===============================================================================================================================\n");
			printf(" [total: 1 music, %d (s)\n", temp->data.time);
			pre->next = temp->next;  free(temp); break;
		}
		pre = temp;
	}
	printf("�� ������ �����Ǿ����ϴ�.\n\n");
	for (temp = plist->head, i = 1; temp != NULL; temp = temp->next, i++)  // �� ���� ������ ������ �ٽ� �����մϴ�.
		temp->num = i;

}
void move(PLAYLIST* plist)  // Ư�� ������ ������ ���ϴ� ������ �ٲߴϴ�.
{
	NODE* temp = malloc(sizeof(NODE)); // ����Ʈ�� ó������ �����Ͽ� ������ ������ �̵��ϸ� ����ŵ�ϴ�.
	NODE* pnew = malloc(sizeof(NODE)); // ������ �ű���� �ϴ� ��带 ����ŵ�ϴ�.
	NODE* pre = malloc(sizeof(NODE)); // temp�� ����Ű�� ����� ���� ��带 ����ŵ�ϴ�.
	int check, order1, order2, i;
	if ((plist->num) <= 1) // ������ 1�� ������ ��� ������ �������� �ʰ� �ٽ� ���� ȭ������ ���ư��ϴ�.
	{
		printf("�÷��̸���Ʈ�� ������ �̵��� ������ �����ϴ�.\n\n"); return;
	}

	do  // �ű���� �ϴ� ������ ������ �Է� �޽��ϴ�.
	{
		check = 0;
		printf("�� ��° ������ ������ ��ġ�� �ٲܱ��? >> ");
		scanf("%d", &(order1));
		if (order1 < 1 || order1 >(plist->num))
		{
			check = 1; printf("��ȿ���� ���� �Է��Դϴ�. ");
		}
	} while (check);
	do // ���� ���� ���ϴ� ������ �Է� �޽��ϴ�.
	{
		check = 0;
		printf("�� ��° ������ �̵���ų���? >> ");
		scanf("%d", &(order2));
		if (order2 < 1 || order2 >(plist->num) || order2 == order1)
		{
			check = 1; printf("��ȿ���� ���� �Է��Դϴ�. ");
		}
	} while (check);

	for (pre = plist->head, temp = plist->head; temp != NULL; pre = temp, temp = temp->next) // �ű���� �ϴ� ��带 pnew�� ����Ű�� ����Ʈ���� ��� ���ܽ�ŵ�ϴ�.
	{

		if (order1 == 1)
		{
			pnew = plist->head;
			plist->head = plist->head->next; break;
		}
		else if (order1 == temp->num)
		{
			pnew = temp;
			pre->next = temp->next; break;
		}
	}
	for (pre = plist->head, temp = plist->head; temp != NULL; pre = temp, temp = temp->next)  // ���ϴ� ��ġ�� �ٽ� pnew�� ����Ű�� ��带 �����մϴ�.
	{

		if (order2 == 1)
		{
			pnew->next = plist->head;
			plist->head = pnew; break;
		}
		else if (order1 > order2 && order2 == temp->num)
		{
			pnew->next = pre->next;
			pre->next = pnew;
			break;
		}
		else if (order1 < order2 && order2 == temp->num)
		{
			pnew->next = temp->next;
			temp->next = pnew; break;
		}
	}
	for (temp = plist->head, i = 1; temp != NULL; temp = temp->next, i++) // �� ����� ������ �ٽ� �����մϴ�.
		temp->num = i;
	return;
}
void quit(PLAYLIST* plist) // ���� ��� �� ���� �Ҵ� ���� �޸𸮸� ������ŵ�ϴ�.
{
	NODE* temp = malloc(sizeof(NODE));
	NODE* pre = malloc(sizeof(NODE));

	FILE* output;
	char new_file[MAX_LENGTH];  // ����� ���ϸ��� �Է� ���� �迭�Դϴ�. 

	if (plist->head == NULL)  // �� ����Ʈ�� ��� ���� ����� ���� �ʽ��ϴ�.
		printf("�÷��̸���Ʈ�� ������ ������ �����ϴ�.\n");
	else
	{
		printf("������ �����̸��� �Է����ּ���. >> ");  // ������ ���ϸ��� �Է� �޽��ϴ�.
		scanf("%s", new_file);
		output = fopen(new_file, "w");
		for (temp = plist->head; temp != NULL; temp = temp->next) // ����Ʈ�� ����� ����� ���������� ó������ ������ ����մϴ�.
			fprintf(output, "%s\t%s\t%d\t%d\n", temp->data.title, temp->data.artist, temp->data.time, temp->data.count);
		fclose(output);
	}

	for (pre = plist->head, temp = pre; temp != NULL; pre = temp) // ���� �Ҵ� �����մϴ�.
	{
		temp = pre->next;
		free(pre);
	}

	free(plist);
	return;
}
