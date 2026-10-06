#include <stdio.h>

// VARIANT 16

int main(void)
{
    char str[1000];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    int j = 0;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (i % 2 != 0)
        {
            str[j] = str[i];
            j++;
        }
    }

    str[j] = '\0';

    printf("Result: %s", str);

    return 0;
}