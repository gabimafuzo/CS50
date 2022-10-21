#include <cs50.h>
#include <stdio.h>

const int total = 3;
float media(int comprimento, int array[]);
int main (void)
{
    int scores[total];
    for(int i = 0; i < total; i ++)
    {
        scores[i] = get_int("Score: ");
    }
    printf("Média: %f\n", media(total, scores));
}

float media(int comprimento, int array[])
{
    int soma = 0;
    for(int i = 0; i < comprimento; i++)
    {
        soma = soma + array[i];
    }
    return soma / (float) comprimento;
}