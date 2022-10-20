#include<stdio.h>
#include<cs50.h>

int main(void)
{
    // Geting string with  return value and without having anyside effect
    string name = get_string("What is your name?");
    // displaying Name return from get_string fun.
    printf("Hello,%s\n", name);
}