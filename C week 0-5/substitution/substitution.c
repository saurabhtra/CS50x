#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>



// function to convert lower to upper
string low_to_upper(string key1);
//validates that a letter in a key is unique
bool keyletter_once(string key2);

//takes plaintext from user and return encrypted cipertext
string ciper(string key3);

// making key  as a global variable
string key;


int main(int argc, string argv[])
{
    // initalizing key as argv[1]
    key = argv[1];
    // validating that argument consitis of only 2 words
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // validating the key consitis of 26 characters
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // vaidating that key consitis only alphabet
    else
    {
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (isalpha(key[i]) == 0)
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
        key = low_to_upper(key);
        // validating no repition of a latter in the key
        if (!keyletter_once(key))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }
    //calling ciper function for taking plaintext and then returning cipertext
    string cipertext = ciper(key);
    printf("ciphertext: %s\n", cipertext);
    return 0;

}

// converting lowercase to uppercase
string low_to_upper(string key1)
{
    for (int i = 0; i < strlen(key1); i++)
    {
        if (islower(key1[i]))
        {
            key1[i] = toupper(key[i]);
        }
    }
    return key1;
}

// checking ever alphabet is unique in the string
bool keyletter_once(string key2)
{
    for (int i = 0; i < strlen(key2); i++)
    {
        for (int j = i + 1; j < strlen(key2); j++)
        {
            if (key2[i] == key2[j])
            {
                return false;
            }
        }
    }
    return true;
}

string ciper(string key3)
{
    string text = get_string("plaintext: ");
    string cipertext = text;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isupper(text[i]) && !isdigit(text[i]))
        {
            int index = text[i] - 65;
            cipertext[i] = key3[index];
        }
        else if (islower(text[i]) && !isdigit(text[i]))
        {
            int index = text[i] - 97;
            cipertext[i] = key3[index] + 32;
        }
        else
        {
            cipertext[i] = text[i];
        }
    }
    return cipertext;
}

