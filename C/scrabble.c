#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

int ft_strlen(char *str);
int ft_compute(char *str);

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    // prompt for 2 words
    string s1 = get_string("Player 1 word: ");
    string s2 = get_string("Player 2 word: ");

    // compute score
    int score1, score2;

    score1 = ft_compute(s1);
    score2 = ft_compute(s2);

    // print winner
    if (score1 > score2)
        printf("Player 1 wins!\n");
    else if (score2 > score1)
        printf("Player 2 wins!\n");
    else
        printf("Tie!\n");
}

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return (i);
}

int ft_compute(char *str)
{
    int score = 0;

    for (int i = 0; i < ft_strlen(str); i++)
    {
        if (isupper(str[i]))
            score += POINTS[str[i] - 'A'];
        else if (islower(str[i]))
            score += POINTS[str[i] - 'a'];
    }
    return (score);
}
