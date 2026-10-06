#include <stdio.h>

// VARIANT 16, BUT VARIANT 13 IS MAXIMUM, SO DOING VARIANT 3

int main(void)
{
    char str[1000];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] = str[i] - ('a' - 'A');
        }
    }

    printf("Result: %s", str);

    return 0;
}