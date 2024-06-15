#include <stdio.h>
#include <cs50.h>
#include <math.h>

int countChangeCoins(float n);
int main()
{
    float change;
    //Ask the change to the user until the condition is satisfied
    do
    {
        change = get_float("Change Owed: ");
    }
    while (change <= 0);


    // Rounding the decimals and *100
    change = round(change * 100);

    //Calling the function that calculates the number of coins
    int coins = countChangeCoins(change);

    printf("%i\n", coins);

    return 0;

}

int countChangeCoins(float n)
{
    int coins = 0;

    do
    {
        if (n >= 25)
        {
            n = n - 25;
            coins++;
        }
        else if (n >= 10)
        {
            n = n - 10;
            coins++;
        }
        else if (n >= 5)
        {
            n = n - 5;
            coins++;
        }
        else
        {
            n = n - 1;
            coins++;
        }
    }
    while (n > 0);

    return coins;
}
