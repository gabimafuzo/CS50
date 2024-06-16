#include <stdio.h>
#include <cs50.h>


string detectCardType(long n);

int main()
{
    long number = get_long("Number: ");
    long card_num = number;

    // Luhn's Algorithm
    int ysum = 0, xsum = 0, y, x, digits, i = 0;
    while (number)
    {
        // When i % 2 equals 0 (false), the digit at index i is even; otherwise (1/true), it is odd
        if (i % 2)
        {
            number = number / 10;
        }
        else //Access the digits at even positions.
        {
            // Step: Multiply every second digit by 2, starting with the second-to-last digit of the number (x), then sum the digits of these products
            x = number % 100 / 10;
            x = 2 * x;
            digits = x % 10 + x % 100 / 10;
            xsum += digits;

            //Sum of the digits that were not multiplied by 2 (y).
            y = number % 10;
            ysum += y;


            number = number / 10;
        }
        i++;

    }

    if ((ysum + xsum) % 10) // If the result of (ysum + xsum) modulo 10 is not equal to 0, this condition is true
    {
        printf("INVALID\n");
    }
    else
    {
        string cardType = detectCardType(card_num);
        printf("%s\n", cardType);
    }
}

string detectCardType(long n)
{
    int j = 2;
    string cardType;
    while (n >= 100) //To access only the first two digits of the card
    {
        n = n / 10;
        j++; //Digit counter (correction factor of 2)
    }
    if (j == 15 && (n == 34 || n == 37))
    {
        cardType = "AMEX";
        return cardType;
    }
    else if (j == 16 && (n == 51 || n == 52 || n == 53 || n == 54 || n == 55))
    {
        cardType = "MASTERCARD";
        return cardType;
    }
    else if (j >= 13 && j <= 16 && n / 10 == 4)
    {
        cardType = "VISA";
        return cardType;
    }
    else
    {
        cardType = "INVALID";
        return cardType;
    }
}
