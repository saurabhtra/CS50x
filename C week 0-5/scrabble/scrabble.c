#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);
void winner(int score1, int score2);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);


    // TODO: Print the winner
    winner(score1, score2);
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int length = strlen(word);
    int sum_point = 0;
    int index = 0 ;
    // converting every alphabet to integer and mapping alphbetically form 0 to 26
    //by doing this it help in indexing and retriving the point associated to that alphabet
    for (int i = 0; i < length; i++)
    {
        if (islower(word[i]))
        {
            index = (int)word[i] - 97;

            sum_point += POINTS[index];

        }
        else if (isupper(word[i]))
        {
            index = (int)word[i] - 65;
            sum_point += POINTS[index];

        }


    }
    return sum_point;
}

//Function for deciding winner
void winner(int score1, int score2)
{
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}