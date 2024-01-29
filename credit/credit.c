#include <cs50.h>
#include <stdio.h>
int sum_doubled = 0;
int sum = 0;
int checksum = 0;
int extractDigits(long card_number);
int digit = 0;

int main(void)
{
    int card_length = 0;
    int sum_evens = 0;
    int sum_odds = 0;

    // Get valid input for card number
    long card_number;
    do
    {
        card_number = get_long("Number: ");
        card_length = log10(card_number) + 1;
    }
    // The card number is going to be at least 13 numbers
    while (card_length <= 12);

    // Extract digits out of the card number
    for (int i = 0; i < card_length; i++)
    {
        digit = card_number % 10;

        if (i % 2 == 0)
        {
            sum_evens += digit;
            continue;
        }

        digit *= 2;
        if (digit < 10)
        {
            sum_odds += digit;
            continue;
        }

        extractDigits
        sum_odds += digit;
    }
    // Check if card is valid.
    int checksum = sum_doubled + sum;
    if (checksum % 10 == 0)
    {
        continue;
    }
    else
    {
        printf("INVALID");
        return 1;
    }

    // Print accurate card brand
}

// Extract digits out of card number
int extractDigits(long card_number, int digit, int digit_count, int sum)
{
    // Keep extracting every number from the card (for loop unnecessary?)
    // Or will the "return digit" fuck things up?
    while (card_number > 0)
    {
        // If the number isn't supposed to be multiplied by 2
        if (digit_count % 2 == 0)
        {
            // Get the individual digit
            digit = card_number % 10;
            // get to the next number by dividing it ny ten(?) or number in card?
            card_number = card_number / 10;
            // Add digit to the sum
            sum = sum + (digit % 10);
            digit_count++;
        }
        else
        {
            // Multiply digit by two
            digit = (card_number % 10) * 2;
            // Get to the next card number
            card_number = card_number / 10;
            digit_count++;
            return digit;
        }
    }
}