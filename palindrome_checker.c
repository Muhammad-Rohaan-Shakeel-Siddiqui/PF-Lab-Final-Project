#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define SIZE 200

/* Checks whether the characters read the same forwards and backwards. */
int isPalindrome(char text[])
{
    int left = 0;
    int right = strlen(text) - 1;

    while (left < right)
    {
        /* Ignore spaces and punctuation in words and sentences. */
        while (left < right && !isalnum((unsigned char)text[left]))
            left++;

        while (left < right && !isalnum((unsigned char)text[right]))
            right--;

        if (tolower((unsigned char)text[left]) !=
            tolower((unsigned char)text[right]))
            return 0;

        left++;
        right--;
    }

    return 1;
}

/* Checks that a string contains digits only. */
int isNumber(char text[])
{
    int i;

    if (text[0] == '\0')
        return 0;

    for (i = 0; text[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)text[i]))
            return 0;
    }

    return 1;
}

void checkText(void)
{
    char text[SIZE];

    printf("\nEnter a word or sentence: ");
    fgets(text, SIZE, stdin);
    text[strcspn(text, "\n")] = '\0';

    if (isPalindrome(text))
        printf("This is a palindrome.\n");
    else
        printf("This is not a palindrome.\n");
}

void checkNumber(void)
{
    char number[SIZE];

    printf("\nEnter a whole number: ");
    fgets(number, SIZE, stdin);
    number[strcspn(number, "\n")] = '\0';

    if (!isNumber(number))
    {
        printf("Invalid input. Please enter digits only.\n");
        return;
    }

    if (isPalindrome(number))
        printf("%s is a palindrome.\n", number);
    else
        printf("%s is not a palindrome.\n", number);
}

int isLeapYear(int year)
{
    if (year % 400 == 0)
        return 1;
    if (year % 100 == 0)
        return 0;
    if (year % 4 == 0)
        return 1;

    return 0;
}

void checkDate(void)
{
    char date[SIZE];
    char digits[9];
    int day, month, year;
    int daysInMonth[] = {31, 28, 31, 30, 31, 30,
                         31, 31, 30, 31, 30, 31};
    int i, j = 0;

    printf("\nEnter a date (DD/MM/YYYY): ");
    fgets(date, SIZE, stdin);
    date[strcspn(date, "\n")] = '\0';

    /* Read the date's digits, ignoring the slashes. */
    for (i = 0; date[i] != '\0'; i++)
    {
        if (isdigit((unsigned char)date[i]))
        {
            if (j >= 8)
            {
                printf("Invalid date format.\n");
                return;
            }
            digits[j] = date[i];
            j++;
        }
        else if (date[i] != '/')
        {
            printf("Invalid date format. Use DD/MM/YYYY.\n");
            return;
        }
    }

    digits[j] = '\0';

    if (j != 8)
    {
        printf("Invalid date format. Use DD/MM/YYYY.\n");
        return;
    }

    /* Convert DDMMYYYY into day, month and year. */
    day = (digits[0] - '0') * 10 + (digits[1] - '0');
    month = (digits[2] - '0') * 10 + (digits[3] - '0');
    year = (digits[4] - '0') * 1000 + (digits[5] - '0') * 100
         + (digits[6] - '0') * 10 + (digits[7] - '0');

    if (month < 1 || month > 12 || year < 1)
    {
        printf("That is not a valid date.\n");
        return;
    }

    if (isLeapYear(year))
        daysInMonth[1] = 29;

    if (day < 1 || day > daysInMonth[month - 1])
    {
        printf("That is not a valid date.\n");
        return;
    }

    /* Check the date as DDMMYYYY, without the slashes. */
    if (isPalindrome(digits))
        printf("%s is a palindrome date (DDMMYYYY).\n", digits);
    else
        printf("%s is not a palindrome date (DDMMYYYY).\n", digits);
}

int main(void)
{
    char choiceText[SIZE];
    int choice;

    do
    {
        printf("\n===== PALINDROME CHECKER =====\n");
        printf("1. Check a word or sentence\n");
        printf("2. Check a number\n");
        printf("3. Check a date\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        fgets(choiceText, SIZE, stdin);
        choice = atoi(choiceText);

        switch (choice)
        {
            case 1:
                checkText();
                break;

            case 2:
                checkNumber();
                break;

            case 3:
                checkDate();
                break;

            case 4:
                printf("Thank you for using the Palindrome Checker!\n");
                break;

            default:
                printf("Invalid choice. Please select 1 to 4.\n");
        }

    } while (choice != 4);

    return 0;
}
