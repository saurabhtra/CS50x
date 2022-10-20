#include <cs50.h>
#include <stdio.h>
//for calculating string length
#include <string.h>
#include <ctype.h>

#include <math.h>

//Function to count letters
int count_letter(string text);

//Function to count words
int count_word(string text);

//Function to count the sentence
int count_sentence(string text);

void grade(int l, int s, int w);

int main(void)
{
    string text = get_string("Text: ");
    int l = count_letter(text);
    int w = count_word(text);
    int s = count_sentence(text);

    grade(l, s, w);



}

//Implementation of letter counting function
int count_letter(string text)
{
    int count = 0;
    for (int i = 0, len = strlen(text); i < len ; i++)
    {
        if (isalpha(text[i]) == 0)
        {

        }
        else
        {
            count++;
        }


    }
    // printf("Letter: %i\n",count);
    return count ;
}

int count_word(string text)
{
    int count = 0 ;
    for (int i = 0, len = strlen(text); i < len ; i++)
    {
        if ((int)text[i] == 32)
        {
            count++;
        }


    }
    // printf("Words: %i\n",count+1);

    return count + 1 ;

}

//Function for implemeanting  for counting no. of Sentences

int count_sentence(string text)
{
    int count = 0 ;
    for (int i = 0, len = strlen(text); i < len ; i++)
    {
        if ((int)text[i] == 46 || (int)text[i] == 33 || (int)text[i] == 63)
        {
            count++;
        }


    }
    // printf("Sentence: %i\n",count);

    return count ;

}

// Function for calculating Grade of the given string
void grade(int l, int s, int w)
{
    float L = (l * 100.00) / w;
    float S = (s * 100.00) / w;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}
