#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#define MAX 50

int grid[MAX][MAX];
int cols, rows;
void game();
void display();
void randGrid();
void inputGrid(char[]);
int kbhit();
int main()
{
    int choice, opt;
    system("clear");
    printf("\t\t\t\t\t CONWAY'S GAME OF LIFE\n");
    usleep(600000);
    printf("Enter:\n1) Random input\n2) Input from file\n3) Popular patterns\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    printf("Enter number of rows and columns: ");
    scanf("%d%d", &rows, &cols);
    switch (choice)
    {
    case 1:
        randGrid();
        break;
    case 2:
        inputGrid("input.txt");
        break;
    case 3:
    {

        printf("Enter 1) STILL LIFES\t2) OSCILLATORS\t3) SPACESHIPS\n");
        scanf("%d", &opt);
        switch (opt)
        {
        case 1:
            inputGrid("stilllife.txt");
            break;
        case 2:
            inputGrid("oscillators.txt");
            break;
        case 3:
            inputGrid("gliders.txt");
            break;
        default:
            printf("Invalid input\n");
            break;
        }
    }
    default:
        printf("Invalid choice\n");
        break;
    }
    game();

    return 0;
}
void inputGrid(char fname[])
{
    int i, j;
    FILE *file;
    char c;
    file = fopen(fname, "r");
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
}

void display()
{
    int i, j;
    system("clear");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (grid[i][j] == 1)
                printf("#   ");
            else
                printf("-   ");
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
            for (yc = i - 1; yc <= i + 1; yc++)
            {
                for (xc = j - 1; xc <= j + 1; xc++)
                {
                    if (grid[(yc + rows) % rows][(xc + cols) % cols] == 1)
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
    while (1)
    {
        if (kbhit())
            break;
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