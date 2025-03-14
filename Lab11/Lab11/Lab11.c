# define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct
{
	char name[20];
	int mid, fin;
	float average; 
	char grade;
}STUDENT;

STUDENT add_student();
void print_students(STUDENT slist[], int i);

int main()
{
	STUDENT slist[10];
	char command[10], find_human[20];
	int i = 0, j = 0;

	while (1)
	{

		printf(">> ");
		scanf("%s", command);

		if (!(strcmp(command, "add")))
		{
			slist[i] = add_student(); i++;
		}
		if (!(strcmp(command, "print")))
			print_students(slist, i);
		if (!(strcmp(command, "find")))
		{
			printf("이름: ");
			scanf("%s", find_human);
			for (j = 0; j < i; j++)
				if (!strcmp(slist[j].name, find_human))
				{
					printf("번호   이름\t\t중간  기말  평균  (학점)\n");
					printf("%d      %s\t\t %d     %d  %4.1f   (%c)\n", j + 1, slist[j].name, slist[j].mid, slist[j].fin, slist[j].average, slist[j].grade);

				}
		}
		if (!(strcmp(command, "quit")))
			break;
		printf("\n");
	}
	return 0;
}

STUDENT add_student()
{
	STUDENT person;
	printf("이름: ");
	scanf("%s", &person.name);
	printf("중간고사: ");
	scanf("%d", &person.mid);
	printf("기말고사: ");
	scanf("%d", &person.fin);
	
	person.average = (person.mid + person.fin) / 2.0;
	
	switch ((int)person.average / 10)
	{
	case 10:
	case 9: person.grade = 'A'; break;
	case 8: person.grade = 'B'; break;
	case 7: person.grade = 'C'; break;
	default: person.grade = 'D'; break;
	}
	
	return person;
}
void print_students(STUDENT slist[], int i)
{
	int j;
	printf("번호   이름\t\t중간  기말  평균  (학점)\n");
	for (j = 0; j < i; j++)
		printf("%d      %s\t\t %d     %d  %4.1f   (%c)\n", j + 1, slist[j].name, slist[j].mid, slist[j].fin, slist[j].average, slist[j].grade);
}