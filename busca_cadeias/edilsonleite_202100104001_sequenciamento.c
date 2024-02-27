#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[8];
    int canGetSick;
} Desease;

int notEmpty(char c);

int notEmpty(char c)
{
    if (c != 32 && c != 10 && c != -1)
        return 1;
    return 0;
}

void buildArray(char *path, int M, int *kmpArray)
{
    int len = 0;
    kmpArray[0] = 0;
    int i = 1;

    while (i < M)
    {
        if (path[i] == path[len])
        {
            len++;
            kmpArray[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = kmpArray[len - 1];
            }
            else
            {
                kmpArray[i] = 0;
                i++;
            }
        }
    }
}
void kmp(char *path, char *main, int subChainMinSize)
{
    int pathLength = strlen(path);
    int mainLength = strlen(main);
    int *kmpArray = (int *)malloc(pathLength * sizeof(int));
    buildArray(path, pathLength, kmpArray);
    printf("KMP table: ");
    for(int a = 0; a < pathLength; a++){
        printf("%d ", kmpArray[a]);
    }
    printf(", Path: %s\n", path);
    int i = 0, j = 0, subChainSize = 0, chainSizeFound = 0;
    while (i < mainLength)
    {
    printf("path[j]: %c, main[i]: %c\n",  path[j], main[i]);
        if (path[j] == main[i])
        {
            j++;
            i++;
            subChainSize++;
        }
        if (j == pathLength)
        {
            printf("Found pattern at index %d\n", i - j);
            j = kmpArray[j - 1];
        }
        else if (i < mainLength && path[j] != main[i])
        {
            if (j != 0)
            {
                j = kmpArray[j - 1];
            }
            else
                i++;
        }
    }
    printf("%d\n", subChainSize);
    free(kmpArray);
}

int main(int argc, char *argv[])
{

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    int subChainSize;
    int deseaseCount;
    int dnaSize = 0;
    char *dna = (char *)malloc(0);
    fscanf(input, "%d", &subChainSize);
    char tempChar = fgetc(input);
    while ((tempChar = fgetc(input)) != 10)
    {
        dnaSize++;
        dna = (char *)realloc(dna, sizeof(char) * (dnaSize));
        dna[dnaSize - 1] = tempChar;
    }
    fscanf(input, "%d", &deseaseCount);
    // Desease *deseases = (Desease *)malloc(sizeof(Desease));

    for (int i = 0; i < deseaseCount; i++)
    {
        char *deseaseName = (char *)malloc(sizeof(char) * 8);
        int numberOfGenes;
        fscanf(input, "%s %d", deseaseName, &numberOfGenes);
        for (int j = 0; j < numberOfGenes; j++)
        {
            char *deseaseGene = (char *)malloc(sizeof(char) * dnaSize);
            fscanf(input, "%s", deseaseGene);
            kmp(deseaseGene, dna, subChainSize);
            free(deseaseGene);
        }
        free(deseaseName);
    }
    free(dna);
    fclose(input);
    fclose(output);
    // Finalizando programa
    return 0;
}