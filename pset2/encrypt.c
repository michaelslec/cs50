#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./encrypt <password> <salt>");
        return 1;
    }
    puts(crypt(argv[1], argv[2]));
}
