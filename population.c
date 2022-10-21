#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //Perguntar ao usuário o tamanho inicial da população
    int inicial;
    do
    {
         inicial = get_int("Start size: ");
    }
    while (inicial < 9);

    //Perguntar ao usuário o tamanho final da população
    int final;
    do
    {
        final = get_int ("Final size: ");
    }
    while (final < inicial);

    //Calcular o número de anos necessários para a população ser a final
    int years = 0;
    while (inicial < final)
    {
       inicial = inicial + inicial/3 - inicial/4;
       years++;
    }

    // Imprimir para o usuário o número de anos necessários
    printf("Years: %i\n", years);
}