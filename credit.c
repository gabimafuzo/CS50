#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // Pedir o número do cartão do usuário
    long cartão;
    int c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16;
    do
    {
        cartão = get_long("Número do cartão: ");
    }
    while (cartão <= 0);

    // Verificar a validade pelo algoritmo de Luhn
    // dígitos c8 c16 c7 c15 c6 c14 c5 c13 c4 c12 c3 c11 c2 c10 c1 c9
    c1 = ((cartão % 100) / 10) * 2;
    c2 = ((cartão % 10000)/1000)*2;
    c3 = ((cartão % 1000000)/100000)*2;
    c4 = ((cartão % 100000000)/10000000)*2;
    c5 = ((cartão % 10000000000)/1000000000)*2;
    c6 = ((cartão % 1000000000000)/100000000000)*2;
    c7 = ((cartão % 100000000000000)/10000000000000)*2;
    c8 = ((cartão % 10000000000000000)/1000000000000000)*2;

    // Soma, ex: c6=12, c6= 1 + 2
    c1 = (c1/10) + (c1 % 10);
    c2 = (c2/10) + (c2 % 10);
    c3 = (c3/10) + (c3 % 10);
    c4 = (c4/10) + (c4 % 10);
    c5 = (c5/10) + (c5 % 10);
    c6 = (c6/10) + (c6 % 10);
    c7 = (c7/10) + (c7 % 10);
    c8 = (c8/10) + (c8 % 10);

    int soma1 = c1 + c2 + c3 + c4 + c5 + c6 + c7 + c8;

    c9 = ((cartão % 10));
    c10 = ((cartão % 1000)/100);
    c11 = ((cartão % 100000)/10000);
    c12 = ((cartão % 10000000)/1000000);
    c13 = ((cartão % 1000000000)/100000000);
    c14 = ((cartão % 100000000000)/10000000000);
    c15 = ((cartão % 10000000000000)/1000000000000);
    c16 = ((cartão % 1000000000000000)/100000000000000);

    int soma2 = c9 + c10 + c11 + c12 + c13 + c14 + c15 + c16;

    int soma3 = soma1 + soma2;

    if ((soma3 % 10) != 0)
    {
        printf("INVALID\n");
        return 0;
    }

// Armazenar o número de dígitos ("comprimento") que o cartão possui.
    int comprimento = 0;
    long visa = cartão;
    long master = cartão;
    long amex = cartão;

    while (cartão > 0)
    {
        cartão = cartão/10;
        comprimento++;
    }

// Classificar o cartão
// Visa: começa com 4 e tem 13 ou 16 dígitos
   while (visa >= 10)
   {
    visa /= 10;
   }
   if (visa == 4 && (comprimento == 13 || comprimento == 16))
   {
    printf("VISA\n");
    return 0;
   }

// MasterCard: começa com 51, 52, 53, 54, 55 e tem 16 dígitos
    while (master >= 100000000000000)
    {
        master /= 100000000000000;
    }
    if (comprimento == 16 && (master == 51 || master == 52 || master == 53 || master == 54 || master == 55))
    {
        printf("MASTERCARD\n");
        return 0;
    }

// AmericanExpress: começa com 34 ou 37 e tem 15 dígitos
   while (amex >= 10000000000000)
    {
      amex /= 10000000000000;
    }
    if (comprimento == 15 && (amex == 34 || amex == 37))
    {
        printf("AMEX\n");
        return 0;
    }
}
