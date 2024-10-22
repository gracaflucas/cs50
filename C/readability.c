#include <cs50.h>
#include <math.h>
#include <stdio.h>

int ft_charcount(char *str);
int ft_wordcount(char *str);
int ft_sentencecount(char *str);

int main(void)
{
    string str = get_string("Text: ");

    int letters = ft_charcount(str);
    int words = ft_wordcount(str);
    int sentences = ft_sentencecount(str);

    float L = ((float) letters / words) * 100;
    float S = ((float) sentences / words) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
        printf("Before Grade 1\n");
    else if (index >= 1 && index <= 15)
        printf("Grade %i\n", index);
    else
        printf("Grade 16+\n");
}

int ft_charcount(char *str)
{
    int i = 0;
    int count = 0;

    while (str[i] != '\0')
    {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
        {
            count++;
        }
        i++;
    }
    return (count);
}

int ft_wordcount(char *str)
{
    int i = 0;
    int count = 0;

    while (str[i] != '\0')
    {
        if (str[i] == ' ')
        {
            count++;
        }
        i++;
    }
    count++;
    return (count);
}

int ft_sentencecount(char *str)
{
    int i = 0;
    int count = 0;

    while (str[i] != '\0')
    {
        if (str[i] == '.' || str[i] == '!' || str[i] == '?')
        {
            count++;
        }
        i++;
    }
    return (count);
}
