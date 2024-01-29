#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Ask user how much change is owed in dollars
    float dollar;
    do
    {
        dollar = get_float("Change owed: ");
    }
    while (dollar <= 0);

    // Transform dollars into cents
    int cents = round(dollar * 100);

    // Keep track of amount of coins needed
    int coins = 0;

    // Quarters
    while (cents >= 25)
    {
        cents -= 25;
        coins++;
    }

    // Dimes
    while (cents >= 10)
    {
        cents -= 10;
        coins++;
    }

    // Nickles
    while (cents >= 5)
    {
        cents -= 5;
        coins++;
    }

    // Pennies
    while (cents >= 1)
    {
        cents -= 1;
        coins++;
    }

    // Print the amount of coins needed
    printf("%i\n", coins);

}