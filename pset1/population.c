#include <stdio.h>
#include <cs50.h>

int main()
{
    int x, y; //prompts the user for the initial size (x) and the final size (y) of the population
    do
    {
        x = get_int("Start size: ");

    }
    while (x < 9);

    do
    {
        y = get_int("End size: ");
    }
    while (y < x);

    int years = 0;

    while (x < y)
    {
        x += (x / 3) - (x / 4); // n/3 new individuals are born each year, and n/4 individuals die each year
        years++;
    }

    printf("Years: %i\n", years);

}
