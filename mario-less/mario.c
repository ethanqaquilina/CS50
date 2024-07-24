#include <cs50.h>
#include <stdio.h>

void print_row(int spaces, int bricks);

int main(void)
{
    // Ask for for height of pyramid
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1);

    // Print the pyramid with height give
    for (int i = 0; i < n; i++)
    {
        // Print row of bricks
        print_row(n - (i + 1), i + 1);
    }
}

void print_row(int spaces, int bricks)
{
    // Print spaces
    for (int j = 0; j < spaces; j++)
    {
        printf(" ");
    }

    // Print bricks
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
    printf("\n");
}
