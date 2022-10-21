#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Máximo de eleitores e candidatos
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// referências[i][j] é a jª preferência do eleitor i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Os candidatos têm nome, contagem de votos, status de eliminado
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array de candidatos
candidate candidates[MAX_CANDIDATES];

// Número de votos e candidatos
int voter_count;
int candidate_count;

// Protótipos das funções
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Verificar se há uso inválido
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Preencher matriz de candidatos
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Continuar perguntando os votos
    for (int i = 0; i < voter_count; i++)
    {

        // Perguntar cada classificação
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Guardar voto, a menos que seja inválido
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Continuar fazendo turnos até que o vencedor exista
    while (true)
    {
        // Calcular os votos dados para os cadidatos que permaneceram
        tabulate();

        // Checar se a eleição foi ganha
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminar candidatos do último lugar
        int min = find_min();
        bool tie = is_tie(min);

        // Se empatar, todos ganham
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminar todos com o número mínimo de votos
        eliminate(min);

        // Redefinir a contagem de votos para zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Guardar preferência se o voto for válido
bool vote(int voter, int rank, string name)
{
    for(int i = 0; i < candidate_count; i++)
    {
        if(strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabular os votos dos candidatos não eliminados
void tabulate(void)
{
    for(int i = 0; i < voter_count; i ++)
    {
        for(int j = 0; j < candidate_count; j++)
        {
            if(candidates[preferences[i][j]].eliminated == false)
            {
                candidates[preferences[i][j]].votes++;
                break;
            }
        }
    }
    return;
}

// Imprimir o ganhador, se tiver um
bool print_winner(void)
{
    for(int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].votes > voter_count/2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Retornar o número mínimo de votos que o candidato restante tem
int find_min(void)
{
    int min = voter_count;
    for(int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].votes < min && candidates[i].eliminated == false)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

//Retornar verdadeiro se a eleição estiver empatada entre todos os candidatos, do contrário falso
bool is_tie(int min)
{
    int eliminate = 0;
    int counter = 0;
    for(int i = 0; i < candidate_count; i++)
    {
        if(!candidates[i].eliminated)
        {
            eliminate++;
        }
        if(candidates[i].votes == min)
        {
            counter++;
        }
    }
        if(eliminate == counter)
        {
            return true;
        }
        return false;
}

//Eliminar o candidato (ou candidatos) da última posição
void eliminate(int min)
{
    for(int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
