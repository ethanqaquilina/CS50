#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int calcWords(string text);
int calcSents(string text);
int calcLets(string text);
void calcLevel(int words, int lets, int sents);

int main(void)
{
    // Get text from user
    string Text = get_string("Text: ");

    // Calculate amount of words, letters, sentences;
    int numOfWords = calcWords(Text);
    int numOfLets = calcLets(Text);
    int numOfSents = calcSents(Text);

    // Calculate the algo and print level
    calcLevel(numOfWords, numOfLets, numOfSents);
}

int calcWords(string text)
{
    int words = 0;

    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (isspace(text[i]) != 0)
        {
            words++;
        }
    }

    return words + 1;
}

int calcLets(string text)
{
    int letters = 0;

    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (isalpha(text[i]) != 0)
        {
            letters++;
        }
    }

    return letters;
}

int calcSents(string text)
{
    int sents = 0;

    for (int i = 0, length = strlen(text); i < length; i++)
    {
        char curChar = text[i];

        if (ispunct(curChar) != 0)
        {
            if (curChar == '.' || curChar == '!' || curChar == '?')
            {
                sents++;
            }
        }
    }

    return sents;
}

void calcLevel(int words, int lets, int sents)
{
    // Calac L S for the Algo
    double L = (((double) lets) / words) * 100;
    double S = (((double) sents) / words) * 100;

    // Calc the index
    double index = 0.0588 * L - 0.296 * S - 15.8;

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", ((int) round(index)));
    }
}
