#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	if (ac == 3)
		printf("POWF  %d * %d = %f\n", atoi(av[1]), atoi(av[2]), powf(atoi(av[1]), atoi(av[2])));
	else if (ac == 2)
		printf("SQRTF %d  = %f\n", atoi(av[1]), sqrtf(atoi(av[1])));
	else
		puts("coin");
	return (0);
}
