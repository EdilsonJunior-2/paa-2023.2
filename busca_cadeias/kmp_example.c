#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void build_kmp_table(char *pattern, int *table, int m)
{
    int j = 0;

    for (int i = 1; i < m; i++)
    {
        while (j > 0 && pattern[i] != pattern[j])
        {
            j = table[j - 1];
        }

        if (pattern[i] == pattern[j])
        {
            j++;
        }

        table[i] = j;
    }
}

void kmp_search(char *text, char *pattern)
{
    int m = strlen(pattern);
    int n = strlen(text);

    if (m == 0)
    {
        for (int i = 0; i < n; i++)
        {
            printf("%d ", i);
        }
        return;
    }

    int *kmp_table = (int *)malloc(m * sizeof(int));
    build_kmp_table(pattern, kmp_table, m);

    int j = 0;
    for (int i = 0; i < n; i++)
    {
        while (j > 0 && text[i] != pattern[j])
        {
            j = kmp_table[j - 1];
        }

        if (text[i] == pattern[j])
        {
            j++;
        }

        if (j == m)
        {
            printf("Pattern found at position: %d\n", i - m + 1);
            j = kmp_table[j - 1];
        }
    }

    free(kmp_table);
}

int main()
{
    char text[] = "ABABDABACDABABCABAB";
    char pattern[] = "ABABCABAB";

    printf("Text: %s\n", text);
    printf("Pattern: %s\n", pattern);

    printf("Pattern found at positions: ");
    kmp_search(text, pattern);

    return 0;
}
