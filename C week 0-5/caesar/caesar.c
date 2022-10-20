#include <cs50.h>
#include <stdio.h>
#include <math.h>
// string to int
#include <stdlib.h>
// include for calu the length of string
#include <string.h>
// include for checking stings contains only digits
#include <ctype.h>

// function to check string of only intergers or not
bool is_all_int(string argv);

// For implementing caesar's algo
void caesar(int int_key, string key);

// converting string int key to  actual integer
int string_int_map(string key);

int main(int argc, string argv[])
{

    // checking only one word
    if (argc == 2)
    {
        // key conversion to int function
        int int_key = string_int_map(argv[1]);
        // checking string of only intergers
        if (is_all_int(argv[1]))
        {
            // calling caesar funtion
            caesar(int_key, argv[1]);
            return 0;
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

// function to check string of only intergers or not
bool is_all_int(string argv)
{
    int count = 0;

    int length = strlen(argv);
    for (int i = 0; i < length; i++)
    {

        if (argv[i] >= 0 && argv[i] <= 9)
        {
            count++;
        }
    }
    if (count == length)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// implemanting string key to int key function
int string_int_map(string key)
{
    int int_key = 0;
    int len = strlen(key);
    int mul = pow(10, len - 1);
    for (int i = 0; i < len; i++)
    {
        key[i] = (int)key[i] - 48;
        int_key += key[i] * mul;
        mul = mul / 10;
    }
    return int_key;
}

void caesar(int int_key, string key)
{
    // taking inpur string from the user

    string input = get_string("plaintext: ");
    // string
    printf("%s \n", input);

    int length = strlen(input);

    for (int i = 0; i < length; i++)
    {
        if (islower(input[i]))
        {
            int temp1 = input[i] - 96;
            temp1 = (temp1 + int_key) % 26 + 96;

            input[i] = (char)temp1;
            
        }
        else if (isupper(input[i]))
        {
            int temp1 = input[i] - 64;
            temp1 = (temp1 + int_key) % 26 + 64;

            input[i] = (char)temp1;
        }
    }
    printf("ciphertext: %s\n", input);
}
