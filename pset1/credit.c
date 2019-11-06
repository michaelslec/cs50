#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

bool luhn_valid(long credit_number);
int sum_others(long number);
int split_sum(long number);
short get_length(long credit_number);
bool valid_length(long credit_number);
long get_positive_long(string prompt);
int get_first_two_digits(long credit_number);
string merchant_provider(long credit_number);

int main(void)
{
    long credit_number = 0;

    // Get only positive number
    credit_number = get_positive_long("Number: ");

    // Validates length of input
    if (!valid_length(credit_number))
    {
        printf("INVALID\n");
        return 0;
    }
    // Valides format with Luhn algorithm
    else if (!luhn_valid(credit_number))
    {
        printf("INVALID\n");
        return 0;
    }


    // Check merchant provider
    printf("%s\n", merchant_provider(credit_number));

    return 0;
}


bool luhn_valid(long credit_number)
{
    int luhn_number = split_sum(credit_number) + sum_others(credit_number);
    if (luhn_number % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int sum_others(long number)
{
    int sum = 0;
    short length = get_length(number);

    for (int i = 0; i < ceil((double) length / 2); ++i)
    {
        sum += number % 10;
        number /= 100;
    }

    return sum;
}

int split_sum(long number)
{
    int sum = 0;
    int temp = 0;
    short length = get_length(number);

    for (int i = 0; i < length / 2; ++i)
    {
        number /= 10;
        temp = number % 10;

        if (temp * 2 > 9)
        {
            temp *= 2;
            sum += temp % 10;
            temp /= 10;
            sum += temp % 10;
        }
        else
        {
            sum += temp * 2;
        }

        number /= 10;
    }

    return sum;
}

short get_length(long credit_number)
{
    //log10 of 0 impossible
    if (credit_number == 0)
    {
        return 1;
    }

    //log10 of any number is 1 less than the number of digits in that number
    return floor(log10(labs(credit_number))) + 1;
}

bool valid_length(long credit_number)
{
    short length = get_length(credit_number);
    if (length < 13 || length > 16)
    {
        return false;
    }
    return true;
}

long get_positive_long(string prompt)
{
    long n;
    do
    {
        n = get_long("%s", prompt);
    }
    while (n < 1);
    return n;
}

int get_first_two_digits(long credit_number)
{
    // length of input
    short length = get_length(credit_number);

    // removes all but first two digits
    for (int i = 0; i < length - 2; ++i)
    {
        credit_number /= 10;
    }

    return (int) credit_number;
}

string merchant_provider(long credit_number)
{
    short first_two = get_first_two_digits(credit_number);

    // Check for visa
    if (first_two / 10 == 4)
    {
        return "VISA";
    }
    else
    {
        switch (first_two)
        {
            case 34:
                return "AMEX";
            case 37:
                return "AMEX";
            case 51:
                return "MASTERCARD";
            case 52:
                return "MASTERCARD";
            case 53:
                return "MASTERCARD";
            case 54:
                return "MASTERCARD";
            case 55:
                return "MASTERCARD";
            default:
                return "INVALID";
        }
    }
}
