#include <cs50.h>
#include <stdio.h>

int main()
{
    int height;
    //Ask the height to the user until the condition is satisfied
    do
    {
        height = get_int("height: ");
    }
    while (height < 1 || height > 8);

    //Build the pyramid
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height - 1 - i; j++)
        {
            printf(" ");
        }

        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}
