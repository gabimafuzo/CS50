#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2) // requires only two arguments
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int key = atoi(argv[1]);

    string plaintext = get_string("plaintext: ");

    int n = strlen(plaintext);

    char ciphertext[n + 1]; // n + 1 characters to accommodate the null terminator \0 at the end of the string

    for (int i = 0; i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (islower(plaintext[i]))
            {
                char ciphercharacter = ((plaintext[i] - 'a' + key) % 26) + 'a'; // Caesar cipher character encryption formula
                ciphertext[i] = ciphercharacter;
            }
            else
            {
                char ciphercharacter = ((plaintext[i] - 'A' + key) % 26) + 'A';
                ciphertext[i] = ciphercharacter;
            }
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    ciphertext[n] = '\0';  // Null-terminate the string

    printf("ciphertext: %s\n", ciphertext);
}
