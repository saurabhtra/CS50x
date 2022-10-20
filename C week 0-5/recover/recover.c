#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

char name[] = {"card.raw"};
typedef uint8_t BYTE;
//defining the buffer size == 512 as jpeg files are stored in blockes of 512
//so the we can read as well as can write the header of our lost images
BYTE buffer[512];
//declearing int for conting the no. of recovered images
int a = -1;
char recovered[sizeof("###.jpg")];
int main(int argc, char *argv[])
{
    //checking the command line argument is valid or not
    if (argc != 2 || strcmp(argv[1], name))
    {
        printf("Name of the card is wrong Do you mean card.raw\n");
        return 1;
    }
    //creating file pointer for opening of our card.raw
    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        printf("file doesn't open");
        return 2;
    }
    //creating FILE pointer for our output file
    FILE *output = NULL;
    // keep reading while the end of the file
    //more formally saying reading till the last block (which is of 512 bytes) of our file(card.raw)
    while (fread(&buffer, 512, 1, card))
    {
        //checking the header(starting) of jpeg file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            a++;
            // close previous output stream
            if (output != NULL)
            {
                fclose(output);
            }
            sprintf(recovered, "%03d.jpg", a);
            output = fopen(recovered, "w");
            if (output == NULL)
            {
                printf("THE output file can't be opened");
                return 3;
            }


        }
        if (output != NULL)
        {
            fwrite(&buffer, 512, 1, output);
        }
    }
    // close the last output stream
    if (output != NULL)
    {
        fclose(output);
    }
    fclose(card);
    return 0;
}