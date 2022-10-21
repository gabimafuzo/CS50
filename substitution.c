#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{

// ./substitution key: dois comandos no total.
    if( argc!= 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
// A chave deve ser formada apenas por letras
    string key = argv[1];
    for (int i = 0; i < strlen(key); i ++)
    {
        if(!isalpha(key[i]))
        {
             printf("Usage: ./substitution key\n");
             return 1;
        }
    }
// A chave deve conter 26 caracteres
     if(strlen(key) != 26)
     {
        printf("Usage: ./substitution  key\n");
        return 1;
     }

// A chave não deve ter caracteres repetidos (comparar os caracteres da chave)
     for ( int i = 0; i < strlen(key); i++)
     {
        for (int j = i + 1; j < strlen(key); j++)
        {
            if(toupper(key[i]) == toupper(key[j]))
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }

     }
//Deixar sempre a chave em maiúscula
   for(int i = 0; i < strlen(key); i++)
   {
    key[i] = key[i] - 32;
   }
// Prompt the user
// Substituir os caracteres usando a chave

    string plaintext = get_string("Plaintext: ");
    printf("Ciphertext: ");
    for (int c = 0; c < strlen(plaintext); c++)
    {
        if(isupper(plaintext[c]))
        {
            char ciphertext =  key[plaintext[c] - 65];
            printf("Ciphertext: %c", ciphertext );
        }
        else if(islower(plaintext[c]))
        {
            char ciphertext =key[plaintext[c] - 97] + 32;
            printf("%c", ciphertext);
        }
        else
        {
            char ciphertext =plaintext[c];
            printf("%c", ciphertext);
        }
    }
    printf("\n");
    return 0;
}
