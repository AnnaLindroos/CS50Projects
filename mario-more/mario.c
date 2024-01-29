#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for height
    // Reprompt if input is invalid
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while ((height <= 0) || (height > 8));

    // Print hashes and spaces
    for (int i = height - 1; i >= 0; i--)
    {
        // Print spaces
        printf("%.*s", i, "       ");
        // Print left half of pyramid
        printf("%.*s", (height - i), "#########");
        //Print spaces
        printf("  ");
        //Print right half of pyramid
        printf("%.*s", (height - i), "#########");
        //Print new row
        printf("\n");
    }

}