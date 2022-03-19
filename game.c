#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>
#include <time.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define MAX 50

int grid[MAX][MAX];
int cols, rows;
void game();
void display();
void randGrid();
void inputGrid();
void evolve();
int kbhit();
int main()
{
    int choice, opt;
    system("clear");
    printf("\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\tCONWAY'S GAME OF LIFE\n");
    usleep(600000);
    printf("\nEnter:\n1) Random input\n2) Input from file\n");
    printf("\nEnter choice: ");
    scanf("%d", &choice);
    printf("\nEnter number of rows and columns: ");
    scanf("%d%d", &rows, &cols);
    switch (choice)
    {
    case 1:
        randGrid();
        break;
    case 2:
        inputGrid();
        break;
    default:
        printf("Invalid choice\n");
        break;
    }
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
        exit(1);
    }
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            fscanf(file, "%c", &c);
            if (c == '#')
                grid[i][j] = 1;
            if (c == '\n')
                j--;
        }
    }
    fclose(file);
}

void display()
{
    int i, j;
    system("clear");
    printf("\n\n\t\t\t\tCONWAY'S GAME OF LIFE\n\n\n");
    for (i = 0; i < rows; i++)
    {
        printf("\t\t\t");
        for (j = 0; j < cols; j++)
        {
            if (grid[i][j] == 1)
                printf(ANSI_COLOR_GREEN "\u25A0  " ANSI_COLOR_RESET);
            else
                printf(ANSI_COLOR_RED "\u25A0  " ANSI_COLOR_RESET);
        }
        printf("\n");
    }
}

void evolve()
{
    int i, j, yc, xc, n;
    int new[MAX][MAX];
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            n = 0;
            for (xc = i - 1; xc <= i + 1; xc++)
            {
                if (xc < 0 || xc > rows)
                    continue;
                for (yc = j - 1; yc <= j + 1; yc++)
                {
                    if (yc < 0 || yc > cols)
                        continue;
                    if (grid[xc][yc] == 1)
                        n++;
                }
            }
            if (grid[i][j] == 1)
                n--;
            new[i][j] = (n == 3 || (n == 2 && grid[i][j] == 1));
        }
    }
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
            grid[i][j] = new[i][j];
    }
}

void game()
{
    int n = 0;
    while (!kbhit())
    {
        display();
        printf("\nGeneration: %d\n", n);
        sleep(1);
        evolve();
        n++;
    }
}

void randGrid()
{
    int i, j;
    srand(time(0));
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
            grid[i][j] = rand() % 2;
    }
}

int kbhit()
{
    struct timeval tv;
    fd_set read_fd;

    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&read_fd);
    FD_SET(0, &read_fd);

    if (select(1, &read_fd, NULL, NULL, &tv) == -1)
        return 0;

    if (FD_ISSET(0, &read_fd))
        return 1;

    return 0;
}