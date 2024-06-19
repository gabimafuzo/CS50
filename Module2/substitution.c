#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>


int main(int argc, char **argv)
{
    // Validations of main arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    string key = argv[1];
    int size_key = strlen(argv[1]);

    if (size_key != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < size_key; i++)
    {
        if (isdigit(key[i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }

    // Validating if there are repeated letters
    for (int k = 0; k < size_key; k++)
    {
        for (int n = k + 1; n < size_key; n++)
        {
            if (toupper(key[k]) == toupper(key[n]))
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
    }

    // Transforming the key to uppercase
    for (int i = 0; i < size_key; i++)
    {
        key[i] = toupper(key[i]);
    }

    // Building the encrypted text

    string plaintext = get_string("plaintext: ");
    int size_plaintext = strlen(plaintext);

    char ciphertext[size_plaintext]; // Declaring my encrypted text as a char array

    for (int j = 0; j < size_plaintext; j++)
    {
        if (isupper(plaintext[j]))
        {
            ciphertext[j] =  key[plaintext[j] - 65];
        }
        else if (islower(plaintext[j]))
        {
            ciphertext[j] = key[plaintext[j] - 97] + 32;
        }
        else
        {
            ciphertext[j] = plaintext[j];
        }
    }

    ciphertext[size_plaintext] = '\0'; // Last character of my array must be null

    printf("ciphertext: %s\n", ciphertext);

}
