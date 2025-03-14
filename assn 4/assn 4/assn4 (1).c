# define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <string.h>
#include <stdlib.h>
#define MAX_LENGTH 45

typedef struct // 음악 정보를 저장하는 구조체입니다.
{
	int count;  // 재생 횟수를 저장
	int time;   // 재생 시간을 저장
	char title[MAX_LENGTH + 1]; // 제목을 저장
	char artist[MAX_LENGTH + 1]; // 아티스트를 저장
}MUSIC;
typedef struct play // 음악 정보를 담은 MUSIC구조체 및 음악 순서, 포인터변수를 포함하는 구조체입니다. 
{
	int num;
	MUSIC data;
	struct play* next;
}NODE;
typedef struct // 총 음악 개수와 각 음악 정보를 연결할 리스트 구조체입니다.
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
	FILE* getdata;  // 데이터를 불러올 파일 주소를 저장합니다.
	char filename[MAX_LENGTH], command[10];  //  데이터를 불러올 파일명을 저장할 배열과 명령어를 저장할 배열입니다.
	NODE* temp;
	PLAYLIST* plist = (PLAYLIST*)malloc(sizeof(PLAYLIST)); // 음악 정보를 연결할 리스트 포인터입니다.
	plist->head = NULL;  // plist 초기화
	plist->num = 0;
	PLAYLIST* pre = (PLAYLIST*)malloc(sizeof(PLAYLIST));

	do  // 파일명을 입력받습니다.
	{
		printf("기존의 플레이리스트를 저장한 파일 이름을 입력해주세요. >> ");
		scanf("%s", filename);
		if (!(getdata = fopen(filename, "r")))
			printf("유효하지 않은 입력입니다. ");
	} while (!(getdata = fopen(filename, "r")));

	temp = (NODE*)malloc(sizeof(NODE));

	int total = 0;

	for (i = 0;
		fscanf(getdata, "%[^\t]s", temp->data.title) != EOF     // 파일로부터 데이터를 한 줄씩 읽어와 리스트로 연결합니다.
		; i++, temp = (NODE*)malloc(sizeof(NODE)))
	{
		fscanf(getdata, " %[^\t]s", temp->data.artist);  //탭이 나올 때까지 문자를 입력 받습니다.
		fscanf(getdata, "%d", &(temp->data.time));
		fscanf(getdata, "%d\n", &(temp->data.count));

		temp->next = NULL;

		if (plist->head == NULL)
			plist->head = temp;
		else
			pre->head->next = temp;
		pre->head = temp;
	}
	plist->num = i;  // 총 음악 개수를 연결합니다.
	int time_sum = 0;  // 총 음악 재생 시간을 저장하는 변수입니다.

	descending(plist, total); //  plist와 연결된 리스트를 내림차순으로 연결합니다.

	printf("\n재생 횟수 Top 3 음악의 정보입니다.\n");  // 상위 3개의 음악 정보를 출력합니다.
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
	int check;  // 유효한 명령어를 입력 받을 때까지 반복문을 돌게 하는 변수입니다. 
	while (1)
	{

		do  // 유효한 명령어를 입력 받을 때까지 반복합니다.
		{
			check = 0;
			printf("명령어를 입력해주세요. >> ");
			scanf("%s", command);
			if (strcmp(command, "show") && strcmp(command, "search") && strcmp(command, "add") && strcmp(command, "delete") && strcmp(command, "move") && strcmp(command, "quit"))
			{
				check = 1; printf("유효하지 않은 입력입니다. ");
			}
		} while (check);

		if (!strcmp(command, "show"))  // 입력 받은 명령어에 해당하는 함수를 호출합니다.
			show(plist);
		else if (!strcmp(command, "search"))
			search(plist);
		else if (!strcmp(command, "add"))
			add(plist);
		else if (!strcmp(command, "delete"))
			delete (plist);
		else if (!strcmp(command, "move"))
			move(plist);
		else if (!strcmp(command, "quit"))  // quit을 입력 받을 시, quit함수를 호출하고 반복문을 빠져나가 프로그램을 종료합니다.
		{
			quit(plist); break;
		}

	}
	fclose(getdata);  // 파일을 닫습니다.
	return 0;
}

void descending(PLAYLIST* plist)  // 리스트를 내림차순으로 정렬하는 함수입니다.
{
	NODE* temp, * pre, * p; // pre는 temp의 이전 노드를 가리키고, p는 temp->next->next를 임시로 저장합니다.
	int i, j;
	for (i = 0; i < (plist->num) - 1; i++)
	{
		for (pre = plist->head, temp = plist->head->next, j = 0; temp->next != NULL; temp = pre->next, j++) // 노드를 2개씩 차례대로 비교하며 순서를 바꿉니다. (총 음악 개수)정도 반복해줍니다. 
		{
			if (j == 0 && plist->head->data.count < temp->data.count) // 첫 번째 노드와 두 번째 노드의 순서를 바꾸는 경우입니다.
			{
				plist->head->next = temp->next;
				temp->next = plist->head;
				plist->head = temp; pre = plist->head;
			}
			else if (temp->data.count < temp->next->data.count)  // 중간이나 끝 부분에서 순서를 바꾸는 경우입니다.
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
	for (temp = plist->head, i = 1; temp != NULL; temp = temp->next, i++)  // 각 음악 정보의 순서를 저장합니다.
		temp->num = i;
}
void show(PLAYLIST* plist)  // 현재 플레이리스트를 출력합니다.
{
	int time_sum = 0;
	NODE* temp = malloc(sizeof(NODE));
	printf("\n==============================================================================================================================\n");
	printf("\ttitle\t\t\t\t\t\tartist\t\t\t\t\t time\t# of plays\n");
	printf("------------------------------------------------------------------------------------------------------------------------------\n");
	for (temp = plist->head; temp != NULL; temp = temp->next) // 리스트의 첫 번째 노드부터 마지막 노드에 있는 정보들을 출력합니다.
	{
		printf("%d\t%-45s%-45s%d\t%d\n", temp->num, temp->data.title, temp->data.artist, temp->data.time, temp->data.count);
		time_sum += temp->data.time;
	}
	printf("===============================================================================================================================\n");
	printf(" [total: %d music, %d (s)\n\n", (plist->num), time_sum); // 총 음악 개수와 재생 시간의 합을 출력합니다.

}
void search(PLAYLIST* plist)  // 원하는 아티스트의 음악 정보를 출력합니다.
{
	int total = 0, time_sum = 0, check = 1;  // 각각 찾고자 하는 아티스트의 음악 개수, 재생 시간의 합, 반복문 조건 검사할 때 쓰이는 변수들입니다.
	NODE* temp = malloc(sizeof(NODE));
	char find_artist[MAX_LENGTH];  // 입력 받은 아티스트 이름을 저장합니다.

	printf("어떤 아티스트의 음악을 검색할까요? >> ");  // 원하는 아티스트를 입력 받습니다.
	scanf(" %[^\n]s", find_artist);
	for (temp = plist->head; temp != NULL; temp = temp->next) // 아티스트가 존재하는지 검사합니다.
		if (!strcmp(temp->data.artist, find_artist))
			check = 0;
	if (check) // 찾고자 하는 아티스트가 존재하지 않을 시, 다시 메인 화면으로 돌아갑니다.
	{
		printf("플레이리스트에 해당 아티스트의 음악이 없습니다.\n\n");
		return;
	}
	printf("\n==============================================================================================================================\n");
	printf("\ttitle\t\t\t\t\t\tartist\t\t\t\t\t time\t# of plays\n");
	printf("------------------------------------------------------------------------------------------------------------------------------\n");
	for (temp = plist->head; temp != NULL; temp = temp->next)  // 원하는 아티스트의 정보만 출력합니다.
		if (!strcmp(temp->data.artist, find_artist))
		{
			printf("%d\t%-45s%-45s%d\t%d\n", temp->num, temp->data.title, temp->data.artist, temp->data.time, temp->data.count);
			time_sum += temp->data.time; total++;
		}
	printf("===============================================================================================================================\n");
	printf(" [total: %d music, %d (s)\n\n", total, time_sum);
	return;
}
void add(PLAYLIST* plist) // 원하는 순서에 음악 정보를 추가합니다.
{
	NODE* temp = malloc(sizeof(NODE));
	NODE* pnew = malloc(sizeof(NODE));  // 새로 추가할 노드를 가리키는 포인터변수입니다.
	NODE* pre = malloc(sizeof(NODE));
	int check, i;
	do  // 범위 내로 순서를 입력 받습니다.
	{
		check = 0;
		printf("몇 번째 순서로 음악을 추가할까요? >> ");
		scanf("%d", &(pnew->num));
		if (pnew->num < 1 || pnew->num >(plist->num) + 1)
		{
			check = 1; printf("유효하지 않은 입력입니다. ");
		}
	} while (check);
	(plist->num)++; // 총 음악 개수를 늘립니다.
	printf("추가할 음악의 제목을 입력해주세요. >> ");
	scanf(" %[^\n]s", pnew->data.title);
	printf("추가할 음악의 아티스트를 입력해주세요. >> ");
	scanf("\n%[^\n]s", pnew->data.artist);
	printf("추가할 음악의 재생 시간을 입력해주세요. >> ");
	scanf("%d", &(pnew->data.time));
	printf("추가할 음악의 재생 횟수를 입력해주세요. >> ");
	scanf("%d", &(pnew->data.count));
	pnew->next = NULL;
	if (plist->head == NULL) // 빈 리스트에 추가할 경우입니다.
	{
		pnew->next = plist->head;
		plist->head = pnew;
	}
	else // 나머지 경우입니다.
	{
		for (pre = plist->head, temp = pre; temp != NULL; pre = pre->next, temp = pre->next)
		{
			temp = pre->next;
			if (pnew->num == 1) // 첫 번째에 추가하는 경우입니다.
			{
				pnew->next = plist->head;
				plist->head = pnew;
				break;
			}
			else if (temp->num == (plist->num) - 1 && pnew->num == (plist->num)) // 맨 마지막 순서에 추가하는 경우입니다.
			{
				temp->next = pnew; break;
			}
			else if (temp->num == pnew->num) // 중간에 추가하는 경우입니다.
			{
				pnew->next = pre->next;
				pre->next = pnew;
				break;
			}
		}
	}
	for (temp = plist->head, i = 1; temp != NULL; temp = temp->next, i++)  // 각 음악 정보의 순서를 다시 저장합니다.
		temp->num = i;

}
void delete(PLAYLIST* plist)  // 원하는 순서의 음악을 삭제합니다.
{
	NODE* temp = malloc(sizeof(NODE));
	NODE* pre = malloc(sizeof(NODE));
	int check, i, delete_node; // delete_node는 삭제할 음악 순서를 저장하는 변수입니다.

	if (plist->head == NULL)  // 빈 리스트일 경우 동작을 수행하지 않고 메인 함수로 돌아갑니다.
	{
		printf("플레이리스트에 삭제할 음악이 없습니다."); return;
	}

	do  // 범위 내로 순서를 입력 받습니다.
	{
		check = 0;
		printf("몇 번째 순서의 음악을 삭제할까요? >> ");
		scanf(" %d", &delete_node);
		if (delete_node < 1 || delete_node >(plist->num))
		{
			check = 1; printf("유효하지 않은 입력입니다. ");
		}
	} while (check);
	(plist->num)--;
	printf("\n==============================================================================================================================\n");
	printf("\ttitle\t\t\t\t\t\tartist\t\t\t\t\t time\t# of plays\n");
	printf("------------------------------------------------------------------------------------------------------------------------------\n");

	for (pre = plist->head; temp != NULL; temp = pre->next)
	{
		temp = pre->next;
		if (delete_node == 1)  // 첫 번째 노드를 삭제하는 경우입니다.
		{
			printf("%d\t%-45s%-45s%d\t%d\n", pre->num, pre->data.title, pre->data.artist, pre->data.time, pre->data.count);

			printf("===============================================================================================================================\n");
			printf(" [total: 1 music, %d (s)\n", pre->data.time);
			plist->head = temp; free(pre); break;  // 해당 노드의 정보를 출력하고 동적 할당 해제합니다.
		}
		else if (delete_node == temp->num)  // 나머지 경우입니다.
		{
			printf("%d\t%-45s%-45s%d\t%d\n", temp->num, temp->data.title, temp->data.artist, temp->data.time, temp->data.count);

			printf("===============================================================================================================================\n");
			printf(" [total: 1 music, %d (s)\n", temp->data.time);
			pre->next = temp->next;  free(temp); break;
		}
		pre = temp;
	}
	printf("위 음악이 삭제되었습니다.\n\n");
	for (temp = plist->head, i = 1; temp != NULL; temp = temp->next, i++)  // 각 음악 정보의 순서를 다시 저장합니다.
		temp->num = i;

}
void move(PLAYLIST* plist)  // 특정 음악의 순서를 원하는 순서로 바꿉니다.
{
	NODE* temp = malloc(sizeof(NODE)); // 리스트의 처음에서 시작하여 마지막 노드까지 이동하며 가리킵니다.
	NODE* pnew = malloc(sizeof(NODE)); // 순서를 옮기고자 하는 노드를 가리킵니다.
	NODE* pre = malloc(sizeof(NODE)); // temp가 가리키는 노드의 이전 노드를 가리킵니다.
	int check, order1, order2, i;
	if ((plist->num) <= 1) // 음악이 1개 이하일 경우 동작을 수행하지 않고 다시 메인 화면으로 돌아갑니다.
	{
		printf("플레이리스트에 순서를 이동할 음악이 없습니다.\n\n"); return;
	}

	do  // 옮기고자 하는 음악의 순서를 입력 받습니다.
	{
		check = 0;
		printf("몇 번째 순서의 음악의 위치를 바꿀까요? >> ");
		scanf("%d", &(order1));
		if (order1 < 1 || order1 >(plist->num))
		{
			check = 1; printf("유효하지 않은 입력입니다. ");
		}
	} while (check);
	do // 범위 내로 원하는 순서를 입력 받습니다.
	{
		check = 0;
		printf("몇 번째 순서로 이동시킬까요? >> ");
		scanf("%d", &(order2));
		if (order2 < 1 || order2 >(plist->num) || order2 == order1)
		{
			check = 1; printf("유효하지 않은 입력입니다. ");
		}
	} while (check);

	for (pre = plist->head, temp = plist->head; temp != NULL; pre = temp, temp = temp->next) // 옮기고자 하는 노드를 pnew로 가리키고 리스트에서 잠시 제외시킵니다.
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
	for (pre = plist->head, temp = plist->head; temp != NULL; pre = temp, temp = temp->next)  // 원하는 위치에 다시 pnew가 가리키는 노드를 삽입합니다.
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
	for (temp = plist->head, i = 1; temp != NULL; temp = temp->next, i++) // 각 노드의 순서를 다시 저장합니다.
		temp->num = i;
	return;
}
void quit(PLAYLIST* plist) // 파일 출력 및 동적 할당 받은 메모리를 해제시킵니다.
{
	NODE* temp = malloc(sizeof(NODE));
	NODE* pre = malloc(sizeof(NODE));

	FILE* output;
	char new_file[MAX_LENGTH];  // 출력할 파일명을 입력 받을 배열입니다. 

	if (plist->head == NULL)  // 빈 리스트일 경우 파일 출력을 하지 않습니다.
		printf("플레이리스트에 저장할 내용이 없습니다.\n");
	else
	{
		printf("저장할 파일이름을 입력해주세요. >> ");  // 저장할 파일명을 입력 받습니다.
		scanf("%s", new_file);
		output = fopen(new_file, "w");
		for (temp = plist->head; temp != NULL; temp = temp->next) // 리스트에 연결된 노드의 음악정보를 처음부터 끝까지 출력합니다.
			fprintf(output, "%s\t%s\t%d\t%d\n", temp->data.title, temp->data.artist, temp->data.time, temp->data.count);
		fclose(output);
	}

	for (pre = plist->head, temp = pre; temp != NULL; pre = temp) // 동적 할당 해제합니다.
	{
		temp = pre->next;
		free(pre);
	}

	free(plist);
	return;
}
