#ifndef	GOL_H
#define GOL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

void	gol(int width, int heigth, int iter);
char    **create_grid(int width, int heigth);
char    **init_grid(char **grid, int width, int heigth);
char    **iter_grid(char **grid, int width, int heigth);
int count_near(char **grid, int x, int y, int heigth, int width);
void    print_grid(char **grid, int width, int heigth);
void    free_grid(char **grid, int heigth);

#endif
