#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for height between 1 through 8.

    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    // Iterate until user's prompted height is reached

    // print new row
    for (int r = 0; r < n; r++)
    {
        //print spaces
        for (int s = n - 1; r < s; s--)
        {
            printf(" ");
        }
        // print hashes
        for (int h = -1; h < r; h++)
        {
            printf("#");
        }

        printf("\n");
    }

}



