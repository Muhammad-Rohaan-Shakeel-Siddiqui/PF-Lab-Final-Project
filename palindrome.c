#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 1024

static int read_line(char *buf, int size)
{
    if (fgets(buf, size, stdin) == NULL)
        return 0;

    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    } else {

        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
    return 1;
}

static void trim(char *s)
{
    size_t len = strlen(s);
    size_t start = 0;

    while (len > 0 && isspace((unsigned char)s[len - 1]))
        s[--len] = '\0';
    while (s[start] != '\0' && isspace((unsigned char)s[start]))
        start++;
    if (start > 0)
        memmove(s, s + start, strlen(s + start) + 1);
}

static int is_palindrome_text(const char *s)
{
    int left = 0;
    int right = (int)strlen(s) - 1;
    int found = 0;

    while (left < right) {
        while (left < right && !isalnum((unsigned char)s[left]))
            left++;
        while (left < right && !isalnum((unsigned char)s[right]))
            right--;

        if (left < right) {
            found = 1;
            if (tolower((unsigned char)s[left]) != tolower((unsigned char)s[right]))
                return 0;
            left++;
            right--;
        }
    }

    if (!found) {
        for (int i = 0; s[i] != '\0'; i++)
            if (isalnum((unsigned char)s[i]))
                return 1;
        return -1;
    }
    return 1;
}

static int is_palindrome_exact(const char *s)
{
    int left = 0;
    int right = (int)strlen(s) - 1;

    while (left < right) {
        if (s[left] != s[right])
            return 0;
        left++;
        right--;
    }
    return 1;
}

/* ---------- Feature 1: words and sentences ---------- */

static void check_text(void)
{
    char input[MAX_INPUT];

    printf("\nEnter a word or sentence: ");
    if (!read_line(input, sizeof input))
        return;
    trim(input);

    int result = is_palindrome_text(input);

    if (result == -1)
        printf("Result: Please enter at least one letter or digit.\n");
    else if (result == 1)
        printf("Result: \"%s\" IS a palindrome.\n", input);
    else
        printf("Result: \"%s\" is NOT a palindrome.\n", input);
}

/* ---------- Feature 2: numbers ---------- */

static void check_number(void)
{
    char input[MAX_INPUT];

    printf("\nEnter a number: ");
    if (!read_line(input, sizeof input))
        return;
    trim(input);

    if (input[0] == '\0') {
        printf("Result: Input cannot be empty.\n");
        return;
    }

    const char *digits = input;
    int negative = 0;
    if (input[0] == '-' || input[0] == '+') {
        negative = (input[0] == '-');
        digits = input + 1;
    }

    if (*digits == '\0') {
        printf("Result: Invalid number.\n");
        return;
    }
    for (int i = 0; digits[i] != '\0'; i++) {
        if (!isdigit((unsigned char)digits[i])) {
            printf("Result: Invalid number. Use digits only (0-9).\n");
            return;
        }
    }

    if (negative) {
        printf("Result: %s is NOT a palindrome (the minus sign does not "
               "match at the end).\n", input);
    } else if (is_palindrome_exact(digits)) {
        printf("Result: %s IS a palindrome.\n", digits);
    } else {
        printf("Result: %s is NOT a palindrome.\n", digits);
    }
}

/* ---------- Feature 3: dates ---------- */

static int is_leap_year(int y)
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

static int days_in_month(int m, int y)
{
    static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2 && is_leap_year(y))
        return 29;
    return days[m - 1];
}

static int is_valid_date(int d, int m, int y)
{
    if (y < 1 || y > 9999) return 0;
    if (m < 1 || m > 12)   return 0;
    if (d < 1 || d > days_in_month(m, y)) return 0;
    return 1;
}

static void check_date(void)
{
    char input[MAX_INPUT];
    int d, m, y, consumed = 0;

    printf("\nEnter a date as DD/MM/YYYY (e.g. 12/02/2021): ");
    if (!read_line(input, sizeof input))
        return;
    trim(input);

    for (int i = 0; input[i] != '\0'; i++)
        if (input[i] == '-' || input[i] == '.')
            input[i] = '/';

    if (sscanf(input, "%d/%d/%d%n", &d, &m, &y, &consumed) != 3 ||
        input[consumed] != '\0') {
        printf("Result: Invalid format. Please use DD/MM/YYYY.\n");
        return;
    }
    if (!is_valid_date(d, m, y)) {
        printf("Result: That is not a valid calendar date.\n");
        return;
    }

    char dmy[16], mdy[16], ymd[16];
    snprintf(dmy, sizeof dmy, "%02d%02d%04d", d, m, y);   /* DDMMYYYY */
    snprintf(mdy, sizeof mdy, "%02d%02d%04d", m, d, y);   /* MMDDYYYY */
    snprintf(ymd, sizeof ymd, "%04d%02d%02d", y, m, d);   /* YYYYMMDD */

    int p_dmy = is_palindrome_exact(dmy);
    int p_mdy = is_palindrome_exact(mdy);
    int p_ymd = is_palindrome_exact(ymd);

    printf("\nDate entered: %02d/%02d/%04d\n", d, m, y);
    printf("  DD/MM/YYYY  -> %s : %s\n", dmy, p_dmy ? "palindrome" : "not a palindrome");
    printf("  MM/DD/YYYY  -> %s : %s\n", mdy, p_mdy ? "palindrome" : "not a palindrome");
    printf("  YYYY/MM/DD  -> %s : %s\n", ymd, p_ymd ? "palindrome" : "not a palindrome");

    if (p_dmy || p_mdy || p_ymd)
        printf("Result: This date IS a palindrome in at least one format.\n");
    else
        printf("Result: This date is NOT a palindrome in any common format.\n");
}

/* ---------- Menu / main ---------- */

static void print_menu(void)
{
    printf("\n========================================\n");
    printf("          PALINDROME CHECKER\n");
    printf("========================================\n");
    printf("  1. Check a word or sentence\n");
    printf("  2. Check a number\n");
    printf("  3. Check a date\n");
    printf("  4. Exit\n");
    printf("----------------------------------------\n");
    printf("Enter your choice (1-4): ");
}

int main(void)
{
    char line[MAX_INPUT];
    int choice;

    for (;;) {
        print_menu();

        if (!read_line(line, sizeof line))
            break;                         /* end of input */

        trim(line);
        if (sscanf(line, "%d", &choice) != 1) {
            printf("Invalid choice. Please enter a number from 1 to 4.\n");
            continue;
        }

        switch (choice) {
            case 1: check_text();   break;
            case 2: check_number(); break;
            case 3: check_date();   break;
            case 4:
                printf("\nThank you for using the Palindrome Checker. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please enter a number from 1 to 4.\n");
        }
    }

    return 0;
}