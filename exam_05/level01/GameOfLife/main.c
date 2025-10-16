#include "gol.h"

int main(int ac, char **av)
{
	int	width;
	int	heigth;
	int	iter;

	if (ac != 4)
		return (1);
	width = atoi(av[1]);
	heigth = atoi(av[2]);
	iter = atoi(av[3]);

	if (width < 1 || heigth < 1 || iter < 0)
		return (1);
	gol(width, heigth, iter);
	return (0);
}
