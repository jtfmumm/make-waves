#include <stdio.h>
#include <math.h>
#include "wave_tables.h"

int main()
{
	int i;
	float table[1024];
	populate_sin_table(table, 1024);
	for (i = 0; i < 1024; i++) {
		printf("%f\t", table[i]);
	}
	return 0;
}