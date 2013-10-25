#include <stdio.h>
#include <math.h>

void tabletab(float*);
void populate_table(float*);

int main()
{
	int i;
	float table[1024];
	tabletab(table);
	for (i = 0; i < 1024; i++) {
		printf("%f\t", table[i]);
	}
	return 0;
}

void tabletab(float* table)
{
	populate_table(table);
}

void populate_table(float* table)
{
	int i;
	for (i = 0; i < 1024; i++) {
		table[i] = i;
	}
}