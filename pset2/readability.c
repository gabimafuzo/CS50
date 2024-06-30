#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main()
{
    string text = get_string("Text: ");

    float letters = 0, words = 1, sentences = 0, n = strlen(text);

    for (int i = 0; i < n;
         i++) // Letters count, word count, and phrase count based on ASCII-classified characters.
    {
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            letters++;
        }
        else if (text[i] == 32)
        {
            words++;
        }
        else if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences++;
        }
    }

    // Coleman-Liau index
    // Here, L is the average number of letters per 100 words in the text, and S is the average
    // number of sentences per 100 words in the text.
    float L = (letters * 100) / words;
    float S = (sentences * 100) / words;

    float index = ((0.0588 * L) - (0.296 * S)) - 15.8;

    int Grade = round(index);

    if (Grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (Grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", Grade);
    }
}
