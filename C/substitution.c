#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

char *ft_tolower(char *str);
int ft_check(char *str);
int ft_strlen(char *str);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Wrong Command line argument!\n");
        return (1);
    }
    char *lowkey = ft_tolower(argv[1]);

    if (ft_check(argv[1]) == 1)
        return (1);

    string text = get_string("plaintext: ");

    // Calc cipher
    int size = ft_strlen(text);
    char cipher[size + 1];
    int i = 0;
    int j = 0;

    while (text[i] != '\0')
    {
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            j = text[i] - 'a';
            cipher[i] = lowkey[j];
        }
        else if (text[i] >= 'A' && text[i] <= 'Z')
        {
            j = text[i] - 'A';
            cipher[i] = toupper(lowkey[j]);
        }
        else
            cipher[i] = text[i];
        i++;
    }
    cipher[i] = '\0';
    // print cipher
    printf("ciphertext: %s\n", cipher);
    return (0);
}

int ft_check(char *str)
{
    int i = 0;

    while (str[i] != '\0')
        i++;

    if (i != 26)
    {
        printf("Key must contain 26 characters.\n");
        return (1);
    }

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] > 'z' || str[i] < 'a')
        {
            printf("Key must only contain alphabetic characters.\n");
            return (1);
        }
        i++;
    }

    i = 0;
    // check for all letters
    int alphabet[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    while (str[i] != '\0')
    {
        alphabet[(int) (str[i] - 'a')]++;
        i++;
    }
    i = 0;
    while (i < 26)
    {
        if (alphabet[i] == 1)
            i++;
        else
        {
            printf("Key must not contain repeated characters.\n");
            return (1);
        }
    }
    return (0);
}

char *ft_tolower(char *str)
{
    int i = 0;

    while (str[i] != '\0')
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
        i++;
    }
    return (str);
}

int ft_strlen(char *str)
{
    int i = 0;

    while (str[i] != '\0')
        i++;
    return (i);
}
