§#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main(void)
{
    string name = get_string("What's your name?\n");
    
    for (int i = 0; i < strlen(name); i++)
    {
        
    printf("Hello, %s\n", name);

    }
}