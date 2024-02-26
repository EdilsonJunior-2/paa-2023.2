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
void kmp(char *path, char *main)
{
    int pathLength = strlen(path);
    int mainLength = strlen(main);
    int *kmpArray = (int *)malloc(pathLength * sizeof(int));
    buildArray(path, pathLength, kmpArray);

    int i = 0, j = 0;
    while ((mainLength - i) >= (pathLength - j))
    {
        if (path[j] == main[i])
        {
            j++;
            i++;
        }
        if (j == pathLength)
        {
            printf("%s Found pattern at index %d\n", path, i - j);
            j = kmpArray[j - 1];
        }
        else if (i < mainLength && path[j] != main[i])
        {
            if (j != 0)
                j = kmpArray[j - 1];
            else
                i++;
        }
    }
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
    tempChar = fgetc(input);
    Desease *deseases = (Desease *)malloc(sizeof(Desease));

    for (int i = 0; i < deseaseCount; i++)
    {
        int deseaseNameSize = 1;
        char *deseaseName = (char *)malloc(sizeof(char) * deseaseNameSize);
        while ((tempChar = fgetc(input)) != 32)
        {
            deseaseName[deseaseNameSize - 1] = tempChar;
            deseaseNameSize++;
            deseaseName = (char *)realloc(deseaseName, sizeof(char) * deseaseNameSize);
        }
        deseaseName[deseaseNameSize - 1] = '\0';
        strcpy(deseases[i].name, deseaseName);
        free(deseaseName);
        int numberOfGenes;
        fscanf(input, "%d", &numberOfGenes);
        tempChar = fgetc(input);

        for (int j = 0; j < numberOfGenes; j++)
        {
            int deseaseGeneSize = 1;
            char *deseaseGene = (char *)malloc(deseaseGeneSize);
            while (notEmpty(tempChar = fgetc(input)) == 1)
            {
                deseaseGene[deseaseGeneSize - 1] = tempChar;
                deseaseGeneSize++;
                deseaseGene = realloc(deseaseGene, deseaseGeneSize);
            }
            deseaseGene[deseaseGeneSize - 1] = '\0';
            kmp(deseaseGene, dna);
            free(deseaseGene);
        }
    }
    free(dna);
    fclose(input);
    fclose(output);
    // Finalizando programa
    return 0;
}