#include <stdio.h>

int main()
{
	FILE* infile, * outfile;
	int stdid, mid, fin;
	float score, average;
	float sum = 0;
	char grade;
	int i = 0;

	infile = fopen("score.txt", "r");
	outfile = fopen("report.txt", "w");
	fprintf(outfile, "==================================\n");
	fprintf(outfile, "    ÇÐ¹ø              ÃÑÁ¡ (ÇÐÁ¡)\n");
	fprintf(outfile, "==================================\n");
	while (fscanf(infile, "%d %d %d", &stdid, &mid, &fin) != EOF)
	{
		
		score = mid * 0.4 + fin * 0.6;
		if (score >= 90)
			grade = 'A';
		else if (score >= 80)
			grade = 'B';
		else if (score >= 70)
			grade = 'C';
		else if (score >= 60)
			grade = 'D';
		else 
			grade = 'F';

		sum += score;
		fprintf(outfile, "%d               %.1f (%c)\n",stdid, score, grade);
		i++;
	}
	average = sum / i;
	
	fprintf(outfile, "============================================\n");
	fprintf(outfile, "      Æò±Õ              %.1f\n", average);
	fprintf(outfile, "============================================\n");
	return 0;

}