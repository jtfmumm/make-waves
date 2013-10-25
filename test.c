#include <stdio.h>

int higher(int (*)(int, int), int, int);
int sum(int, int);

int main()
{
	printf("%d", higher(&sum, 5, 6));
	return 0;
}

int higher(int (*funct_ptr)(int, int), int x, int y)
{
	return funct_ptr(x, y);
}

int sum(int x, int y) 
{
	return x + y;
}