#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int checkScore(string word);
int getScore(char letter);

int main(void)
{
    // Get input from both players
    string p1Word = get_string("Player 1: ");
    string p2Word = get_string("Player 2: ");

    // Check both players scores
    int p1Score = checkScore(p1Word);
    int p2Score = checkScore(p2Word);

    // Print who wins or tie
    if (p1Score > p2Score)
    {
        printf("Player 1 wins!\n");
    }
    else if (p2Score > p1Score)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int checkScore(string word)
{
    int score = 0;

    for (int i = 0, length = strlen(word); i < length; i++)
    {
        int charScore = getScore(word[i]);

        score += charScore;
    }

    return score;
}

int getScore(char letter)
{
    // Check if blank space or non letter
    if (isdigit(letter) != 0 || ispunct(letter) != 0 || isspace(letter) != 0)
    {
        return 0;
    }

    // Convert to capital letter first;
    letter = toupper(letter);

    // Check what score the letter is
    if (letter == 'A' || letter == 'E' || letter == 'I' || letter == 'I' || letter == 'L' ||
        letter == 'N' || letter == 'O' || letter == 'R' || letter == 'S' || letter == 'T' ||
        letter == 'U')
    {
        return 1;
    }
    else if (letter == 'D' || letter == 'G')
    {
        return 2;
    }
    else if (letter == 'B' || letter == 'C' || letter == 'M' || letter == 'P')
    {
        return 3;
    }
    else if (letter == 'F' || letter == 'H' || letter == 'V' || letter == 'W')
    {
        return 4;
    }
    else if (letter == 'K')
    {
        return 5;
    }
    else if (letter == 'J' || letter == 'X')
    {
        return 8;
    }
    else if (letter == 'Q' || letter == 'Z')
    {
        return 10;
    }
    return 0;
}
