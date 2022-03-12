#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define MAX 50

int grid[MAX][MAX];
int w, h;
void game();
void display();
void randGrid();
void inputGrid();

int main()
{
    int choice;
    system("clear");
    printf("\t\t\t\t CONWAY'S GAME OF LIFE\n");
    sleep(1);
    printf("Enter:\n1)Random input\n2) Input from file\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    printf("Enter width and height: ");
    scanf("%d%d", &w, &h);
    if (choice == 1)
    {
        randGrid();
    }
    else
        inputGrid();
    game();
    return 0;
}
void inputGrid()
{
    int i, j;
    FILE *file;
    char c;
    file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("No file found\n");
    }
    for (i = 0; i < h; i++)
    {
        for (j = 0; j < w; j++)
        {
            fscanf(file, "%c", &c);
            if (c == '#')
                grid[i][j] = 1;
            if (c == '\n')
                j--;
        }
    }
}

void display()
{
    int i, j;
    system("clear");
    for (i = 0; i < h; i++)
    {
        for (j = 0; j < w; j++)
        {
            if (grid[i][j] == 1)
                printf("#   ");
            else
                printf("-   ");
        }
        printf("\n");
    }
}
// 0,1 : dies
// 2 : stays
// 3 : alive
// >3 : dies

void evolve()
{
    int i, j, yc, xc, n;
    int new[MAX][MAX];
    for (i = 0; i < h; i++)
    {
        for (j = 0; j < w; j++)
        {
            n = 0;
            for (yc = i - 1; yc <= i + 1; yc++)
            {
                for (xc = j - 1; xc <= j + 1; xc++)
                {
                    if (grid[(yc + h) % h][(xc + w) % w] == 1)
                        n++;
                }
            }
            if (grid[i][j] == 1)
                n--;
            new[i][j] = (n == 3 || (n == 2 && grid[i][j] == 1));
        }
    }
    for (i = 0; i < h; i++)
    {
        for (j = 0; j < w; j++)
            grid[i][j] = new[i][j];
    }
}

void game()
{
    while (1)
    {
        display();
        sleep(1);
        evolve();
    }
}

void randGrid()
{
    int i, j;
    for (i = 0; i < h; i++)
    {
        for (j = 0; j < w; j++)
            grid[i][j] = rand() < RAND_MAX / 10 ? 1 : 0;
    }
}