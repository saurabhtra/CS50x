#include <cs50.h>
#include <stdio.h>

void hash_print(int i);

void blank_print(int height, int i);

int condition_cheker(void);


int main(void)
{
    int height = condition_cheker();
    for (int i = 0; i < height; i++)
    {

        blank_print(height, i);
        hash_print(i);
        printf("\n"); // seperating  rows and colums
    }
}














// # pattern printing function
void hash_print(int i)
{
    int temp = 0;
    while (temp < i + 1)
    {
        printf("#");
        temp++;
    }
}

//Blank printing function
void blank_print(int height, int i)
{
    int temp = 1; // initializine a temp variable for the easy peasy
    while (temp < height - i)
    {
        printf(" ");
        temp++;
    }

}


//condition checker function
int condition_cheker(void)
{
    do
    {
        // if get the desired number the exit this infinite do while loop
        int h = get_int("Height: ");
        if (h >= 1 && h <= 8)
        {
            return h;
            break;
        }
    }
    while (true);
}