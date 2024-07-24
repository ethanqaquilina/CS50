#include <cs50.h>
#include <stdio.h>

bool checkSum(long number);
void checkCard(long number);

int main(void)
{
    long cardNumber;

    // Prompt for Input
    cardNumber = get_long("Number: ");

    // Calculate checksum
    if (checkSum(cardNumber))
    {
        // Check card length and starting digits
        // Print AMEX, MASTERCARD, VISA, or INVALID
        checkCard(cardNumber);
    }
    else
    {
        // If false print INVALID
        printf("INVALID\n");
    }
}

bool checkSum(long number)
{
    int sum = 0;
    int lastDigit;
    int counter = 0;

    while (number > 0)
    {
        counter++;

        // Gets the last digit
        lastDigit = (number % 10);

        // Subtracts it from the number and moves the decimal a tenth
        number = (number - (number % 10)) / 10;

        // Checks if the last digit is needs to be multiplied
        if ((counter % 2 == 0) && (lastDigit > 0))
        {
            lastDigit = lastDigit * 2;

            // If the the digit is greater then ten
            if (lastDigit >= 10)
            {
                // Adds the digits seperately
                sum += lastDigit % 10;
                sum += (lastDigit - (lastDigit % 10)) / 10;
            }
            else
            {
                // Adds the digit times 2
                sum += lastDigit;
            }
        }
        else
        {
            // Adds the last digit to the sum
            sum += lastDigit;
        }
    }

    // Returns true if the sum ends in 0
    return (sum % 10 == 0);
}

void checkCard(long number)
{
    long tempNum = number;
    int numLength = 0;
    int firDig = 0;
    int secDig = 0;

    // Gets the length of the number
    while (tempNum > 0)
    {
        // Gets the starting digits
        secDig = firDig;
        firDig = (tempNum % 10);

        tempNum = (tempNum - (tempNum % 10)) / 10;

        numLength++;
    }

    // Checks card length and first two digits
    if ((numLength == 13 || numLength == 16) && firDig == 4)
    {
        printf("VISA\n");
    }
    else if (numLength == 16 && firDig == 5)
    {
        if (secDig == 1 || secDig == 2 || secDig == 3 || secDig == 4 || secDig == 5)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (numLength == 15 && firDig == 3)
    {
        if (secDig == 4 || secDig == 7)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
