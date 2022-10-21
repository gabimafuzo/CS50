#include <stdio.h>
#include <cs50.h>

int get_cents(void);
int calculate_quarters(int quarters);
int calculate_dimes(int dimes);
int calculate_nickels(int nickels);
int calculate_pennies(int pennies);

int main(void)
{

// Perguntar para o usuário quantos centavos de troco o usuário precisa
int cents = get_cents();

// Calcular o número de quarters que o usuário precisa
int quarters = calculate_quarters(cents);
cents = cents - quarters * 25;

// Calcular número de dimes (10) que o usuário precisa
int dimes = calculate_dimes(cents);
cents = cents - dimes * 10;

// Calcular o número de nickels que o usuário precisa
int nickels = calculate_nickels(cents);
cents = cents - nickels * 5;

// Calcular o número de pennies que o usuário precisa
int pennies = calculate_pennies(cents);
cents = cents - pennies * 1;

//Somar as moedas
int moedas = quarters + dimes + nickels + pennies;

//Imprimir o resultado
printf("%i\n", moedas);
}

int get_cents(void)
{
   int cents;
   do
   {
      cents = get_int("Quantos centavos vc quer? ");
   }
   while (cents < 0);
   return cents;
}

int calculate_quarters(int cents)
{
   int quarters = 0;
   while (cents >= 25)
   {
      cents = cents - 25;
      quarters++;
   }
   return quarters;
}

int calculate_dimes(int cents)
{
   int dimes = 0;
   while (cents >= 10)
   {
      cents = cents - 10;
      dimes ++;
   }
   return dimes;
}

int calculate_nickels(int cents)
{
   int nickels = 0;
   while(cents >= 5)
   {
      cents = cents - 5;
      nickels++;
   }
   return nickels;
}

int calculate_pennies(int cents)
{
   int pennies = 0;
   while(cents >= 1)
   {
      cents = cents - 1;
      pennies++;
   }
   return pennies;
}
