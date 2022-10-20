#include <cs50.h>
#include <stdio.h>
#include <math.h>

bool condition_cheker(void);

void validaton_cheker(long numb, int n);

int even_pos_product(int sum_even);

int odd_pos_sum(long numb, int n);

//Global variable for counting the lenght aka number of digits of the card
int digit;
//making a long global variable for storing card number from user as a input
long num;
int main(void)
{
    //checking or validating that the lenght of input is exactly = either
    // 13,15 or 16 if not return error and exit
    if (!condition_cheker())
    {
        printf("INVALID\n");
        return 0;
    }

    //actual functin for validating the card by appling Lunar's Algorithm
    validaton_cheker(num, digit);


}



//implementation of condition checker
bool condition_cheker(void)
{

    do
    {
        //get card number as input
        num = get_long("Number: ");
        int count = 0;
        long temp = num;
        // int digit = 0;

        //counting the length of card no.
        while (temp > 10)
        {
            temp = temp / 10;
            count++;
        }

        digit = count + 1;
        // as card number can of only 13,15 or 16
        //if not so return false
        if (digit == 15 || digit == 16 || digit == 13)
        {
            return true;
        }
        else
        {

            return false;
        }
    }
    while (true);
}

//implementaion of validation function
void validaton_cheker(long numb, int n)
{
    int sum = 0;
    long temp = numb;
    int count = n;

    long start_two_digit = numb / pow(10, n - 2);
    long start_first_digit = numb / pow(10, n - 1);

// for the sum of even positon numbers
    for (int i = count - 1 ; count > 0 ; i++)
    {
        int temp_int = 0 ;
        temp = temp / 10 ;
        temp_int = (temp % 10) * 2;
        temp_int = temp_int % 10 + temp_int / 10;
        sum += temp_int;
        temp = temp / 10;
        count = count - 2;
    }


    int odd_sum = odd_pos_sum(numb, n);

    int final_sum = sum + odd_sum ;
    //this will actual validates and tell us that, the card no is belong to which card
    //and if so put an error msg on termial
    while (true)
    {
        if (final_sum % 10 == 0)
        {
            if (start_two_digit == 34 || start_two_digit == 37)
            {
                printf("AMEX\n");
                break;
            }
            else if (start_two_digit >= 51 && start_two_digit <= 55)
            {
                printf("MASTERCARD\n");
                break;
            }
            else if (start_first_digit == 4)
            {
                printf("VISA\n");
                break;
            }
            else
            {
                printf("INVALID\n");
                break;
            }
        }
        else
        {
            //
            printf("INVALID\n");
            break;
        }
    }



}

int even_pos_product(int sum_even)
{
    int even_sum_pro = sum_even * 2;
    return even_sum_pro;
}

int odd_pos_sum(long numb, int n)
{
    int sum_odd = 0;
    long temp2 = numb;
    int count2 = n;

    for (int i = count2 - 1 ; count2 > 0 ; i++)
    {
        // temp = temp /10 ;
        sum_odd += temp2 % 10;

        temp2 = temp2 / 100;
        count2 = count2 - 2;
    }


    return sum_odd ;

}