#include <cs50.h>
#include <math.h>
#include <stdio.h>

int checksum(long num);
int multiplyAndSum(int lastdig);
int size(long num);

int main(void)
{
    long num = get_long("Whats your number? ");

    if (checksum(num) == 0)
    {
        int firstDigit = num / pow(10, size(num) - 1);
        int firstTwoDigits = num / pow(10, size(num) - 2);
        if ((size(num) == 13 || size(num) == 16) && firstDigit == 4)
            printf("VISA\n");
        else if ((size(num) == 16) && (firstTwoDigits >= 51 && firstTwoDigits <= 55))
            printf("MASTERCARD\n");
        else if ((size(num) == 15) && (firstTwoDigits == 34 || firstTwoDigits == 37))
            printf("AMEX\n");
        else
            printf("INVALID\n");
    }
    else
        printf("INVALID\n");
    return (0);
}

int checksum(long num)
{
    int i = 0;
    int lastDig = 0;
    bool alternate = false;

    while (num > 0)
    {
        if (alternate == true)
        {
            lastDig = num % 10;
            int product = multiplyAndSum(lastDig);
            i = i + product;
        }
        else
        {
            lastDig = num % 10;
            i = i + lastDig;
        }
        alternate = !alternate;
        num = num / 10;
    }
    if (i % 10 == 0)
        return (0);
    return (1);
}

int multiplyAndSum(int lastDig)
{
    int multiply = lastDig * 2;
    int i = 0;
    int lastDigMult;

    while (multiply > 0)
    {
        lastDigMult = multiply % 10;
        i = i + lastDigMult;
        multiply = multiply / 10;
    }
    return (i);
}

int size(long num)
{
    int i = 0;
    while (num > 0)
    {
        i++;
        num = num / 10;
    }
    return (i);
}
