#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

bool checkRepeat(char C, string keyString);

int main(int argc, string argv[])
{
    // Check key entered
    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];
    int keyLen = strlen(key);

    // Validate the key
    // Check key length is 26 characters
    if (keyLen != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < keyLen; i++)
    {
        char curChar = toupper(key[i]);

        // Check for non-alphabetic characters
        if (isalpha(curChar) == 0)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }

        // Skip first char
        if (i != 0)
        {
            // Check repeated characters case-sensitive
            if (checkRepeat(curChar, key))
            {
                printf("Key cannot repeat characters.\n");
                return 1;
            }
        }
    }

    // Get the plain text
    string plainText = get_string("plaintext: ");

    // Encipher
    int ptLength = strlen(plainText);

    string cipherText = plainText;

    for (int i = 0; i < ptLength; i++)
    {
        // Get char in plain text
        char curChar = plainText[i];

        // Check if is  a alphabetical char
        if (isalpha(curChar) != 0)
        {
            curChar = toupper(curChar);
            int charNum = curChar;

            // Determine the letter it applies
            char cipherChar = key[charNum - 65];

            // Make upper or lower depending on the text
            if (isupper(plainText[i]) == 0)
            {
                cipherText[i] = tolower(cipherChar);
            }
            else
            {
                cipherText[i] = toupper(cipherChar);
            }
        }
        else
        {
            // Add same if not alphabetical
            cipherText[i] = plainText[i];
        }
    }

    printf("ciphertext: %s\n", cipherText);
    return 0;
}

bool checkRepeat(char C, string keyString)
{
    int num = 0;

    for (int i = 0; i < 26; i++)
    {
        if (C == toupper(keyString[i]))
        {
            num++;
        }

        if (num == 2)
        {
            return true;
        }
    }

    return false;
}
