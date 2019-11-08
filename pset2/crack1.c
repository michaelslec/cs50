#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>

const string kALPHABET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

bool hash_match(string hash, string attempt);

int main(int argc, string argv[])
{
    // Check for hash after command
    if (argc != 2)
    {
        puts("Usage: ./crack <hash>");
        return 1;
    }

    // User typed hash to break
    string hash = argv[1];

    puts(hash);
}

bool hash_match(string hash, string attempt)
{
    if (strcmp(hash, attempt) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
