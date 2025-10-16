#include "gol.h"

void    gol(int width, int heigth, int iter)
{
    char    **grid;

    grid = create_grid(width, heigth);
    if (!grid)
        return ;
    grid = init_grid(grid, width, heigth);
    if (!grid)
        return ;

    for (int i = 0; i < iter; i++)
    {
        grid = iter_grid(grid, width, heigth);
        if (!grid)
            return ;
    }
    print_grid(grid, width, heigth);
    free_grid(grid, heigth);
}

char    **create_grid(int width, int heigth)
{
    char    **grid;
    int     i;
    int     j;

    grid = calloc(heigth, sizeof(char *));
    if (!grid)
        return (NULL);
    for (i = 0; i < heigth; i++)
    {
        grid[i] = calloc(width, sizeof(char));
        if (!grid[i])
        {
            free_grid(grid, i);
            return (NULL);
        }
        for (j = 0; j < width; j++)
            grid[i][j] = ' ';
        grid[i][j] = '\0';
    }
    return (grid);
}

char    **init_grid(char **grid, int width, int heigth)
{
    char    buf;
    int     x;
    int     y;
    bool    draw;

    x = 0;
    y = 0;
    draw = false;
    while (read(0, &buf, 1) > 0)
    {
        if (buf == 'x')
            draw = !draw;
        else if(buf == 'w')
        {
            if (y > 0)
                y--;
        }
        else if(buf == 'a')
        {
            if (x > 0)
                x--;
        }
        else if(buf == 's')
        {
            if (y < heigth - 1)
                y++;
        }
        else if(buf == 'd')
        {
            if (x < width - 1)
                x++;
        }
        if (draw)
            grid[y][x] = '0';
    }
    return (grid);
}

char    **iter_grid(char **grid, int width, int heigth)
{
    char    **new_grid;
    int count;
    bool alive;

    new_grid = create_grid(width, heigth);
    if (!new_grid)
        return (NULL);
    for (int y = 0; y < heigth; y++)
    {
        for (int x = 0; x < width; x++)
        {
            count = count_near(grid, x, y, width, heigth);
            alive = (grid[y][x] == '0');
            if (alive && (count == 2 || count == 3))
                new_grid[y][x] = '0';
            else if (!alive && count == 3)
                new_grid[y][x] = '0';
        }
    }
    free_grid(grid, heigth);
    return (new_grid);
}

int count_near(char **grid, int x, int y, int width, int heigth)
{
    int count = 0;

    for (int j = -1; j <= 1; j++)
    {
        for (int i = -1; i <= 1; i++)
        {
            if (i == 0 && j == 0)
                continue ;
            if (x + i >= 0 && x + i < width && y + j >= 0 && y + j < heigth)
            {
                if (grid[y + j][x + i] == '0')
                    count++;
            }
        }
    }
    return (count);
}

void    print_grid(char **grid, int width, int heigth)
{
    for (int y = 0; y < heigth; y++)
    {
        for (int x = 0; x < width; x++)
        {
            write(1, &grid[y][x], 1);
        }
        write(1, "\n", 1);
    }
}

void    free_grid(char **grid, int heigth)
{
    for (int i = 0; i < heigth; i++)
    {
        free(grid[i]);
    }
    free(grid);
}