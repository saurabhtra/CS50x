// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table

const unsigned long N = 27 * 26;

// Hash table
node *table[N];

// variable we use latter in this file
unsigned int word_count;
unsigned int hash_value;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    // getting the hash value or say the bucket number the word belongs to
    hash_value = hash(word);
    // creating a node pointer pointing the node which the hash_value no bucket is pointing to
    node *cursor = table[hash_value];



    // itrate untill find the NULL or The Word(which we are finding)
    while (cursor)
    {
        // words matches then return true otherwise move to next node
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        // move the cursor to the next node
        cursor = cursor->next;
    }



    // hash function
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // a aa ab ......az b ba bb bc ....bz c.......zz(this is how our hash table will look like)
    int ch1 = toupper(word[0]) - 'A';

    int ch2 = 0;
    // if second latter of word is an alphabet
    if (isalpha(word[1]) != 0)
    {
        // 64 because the we are taking the second latters value starting from 1 instead of 0

        ch2 = toupper(word[1]) - '@';


        // if first letter is a or A then index of the word will be the index of the second word
        if (ch1 == 0)
        {
            return ch2;
        }
        // if second word is not a or A then do the math
        return ch1 * 27 - 1 + ch2;
    }
    // if only one word and first word is a or A
    if (ch1 == 0)
    {
        return 0;
    }
    // else do the math
    return ch1 * 27 - 1;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Unable to open the %s\n", dictionary);
        return false;
    }
    // buffer to store the word we are reading
    char word[LENGTH + 1];

    // Read the file word by word(string by string) untill we reached the end of the file EOF(End Of File)
    while (fscanf(file, "%s", word) != EOF)
    {
        // allocate the memory for new node dynamically
        node *n = malloc(sizeof(node));
        // if malloc doesnt allocate the memory return false
        if (n == NULL)
        {

            return false;
        }
        // copy the word(string) we have just read into the new node we have created
        strcpy(n->word, word);
        // puting this new node into the hash table's linked list using hash_value of the word
        // getting hash_value of the this word
        hash_value = hash(word);

        // making this new node to point the hash_table to its perticular bucket it belongs to
        n->next = table[hash_value];
        // derefrencing the buckets's pointer to this new node
        // NOTE: hash tables entry contains pointers to the linked list of the particular bucket
        // at this point of time the new node has been appended to its destination bucket as first node of that linked list
        table[hash_value] = n;

        word_count++; // number of the word loded in the hash table is increased by one after adding this word

    }


    fclose(file); // closing the file
    // return true as file is succesfully loaded to the memory
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO


    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // itrate to all the buckets
    for (int i = 0; i < N; i++)
    {
        // set cursor the the start of the ith linked list
        node *cursor = table[i];


        // freeing the ith linked list
        while (cursor)
        {
            // creating temp node pointer
            node *temp = cursor;
            // move cursor to the next node as the present node is pointed by our temo node pointer so no Worry of lossing the present linked list
            cursor = cursor->next;
            // now at this movment be can free the node pointed by the temp node pointer
            free(temp);
        }
        // if curror is NULL it means we successfull freed the ith linked list
        if (cursor != NULL)
        {
            free(cursor);
            return false;
        }
    }
    return true;
}
