#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[8];
    double canGetSick;
} Desease;

int notEmpty(char c);

int notEmpty(char c)
{
    if (c != 32 && c != 10 && c != -1)
        return 1;
    return 0;
}

void conquer(Desease *entry, int start_position, int middle, int final_position)
{
	int start_aux = start_position;
	int ahead_middle = middle + 1;
	int start_aux_2 = 0;
	Desease *temp = (Desease *)malloc((final_position - start_position + 1) * sizeof(Desease));

	while (start_aux <= middle && ahead_middle <= final_position)
	{
		if (entry[start_aux].canGetSick >= entry[ahead_middle].canGetSick)
		{
			strcpy(temp[start_aux_2].name, entry[start_aux].name);
			temp[start_aux_2].canGetSick = entry[start_aux].canGetSick;
			start_aux += 1;
		}
		else
		{
			strcpy(temp[start_aux_2].name, entry[ahead_middle].name);
			temp[start_aux_2].canGetSick = entry[ahead_middle].canGetSick;
			ahead_middle += 1;
		}
		start_aux_2 += 1;
	}

	while (start_aux <= middle)
	{
		strcpy(temp[start_aux_2].name, entry[start_aux].name);
		temp[start_aux_2].canGetSick = entry[start_aux].canGetSick;
		start_aux += 1;
		start_aux_2 += 1;
	}

	while (ahead_middle <= final_position)
	{
		strcpy(temp[start_aux_2].name, entry[ahead_middle].name);
		temp[start_aux_2].canGetSick = entry[ahead_middle].canGetSick;
		ahead_middle += 1;
		start_aux_2 += 1;
	}

	for (int i = 0; i < (final_position - start_position + 1); i++)
	{
		strcpy(entry[start_position + i].name, temp[i].name);
		entry[start_position + i].canGetSick = temp[i].canGetSick;
	}

	free(temp);
}

void divide(Desease *entry, int start_position, int final_position)
{
	if (start_position < final_position)
	{
		int middle = start_position + (final_position - start_position) / 2;
		divide(entry, start_position, middle);
		divide(entry, middle + 1, final_position);
		conquer(entry, start_position, middle, final_position);
	}
}

void buildTable(int *kmpArray, char *pattern, int patternLength)
{
    int j = -1;
    for (int i = 1; i < patternLength; i++)
    {
        while (j >= 0 && pattern[j + 1] != pattern[i])
        {
            j = kmpArray[j];
        }
        if (pattern[j + 1] == pattern[i])
            j++;
        kmpArray[i] = j;
    }
}

int kmp(char *path, char *main, int subChainMinSize, int *kmpArray)
{
    int pathLength = strlen(path);
    int mainLength = strlen(main);
    for (int i = 0; i < pathLength; i++)
        kmpArray[i] = -1;
    buildTable(kmpArray, path, pathLength);
    int subChainSize = 0;
    
    for (int i = 0, j = -1; i < mainLength; i++)
    {
        while (j >= 0 && path[j + 1] != main[i])
        {
            if (j + 1 >= subChainMinSize)
            {
                subChainSize += j + 1;
                // verificando se já atingiu 90% de compatibilidade do gene
                if (subChainSize / (double)pathLength >= 0.9)
                {
                    printf("Gene found\n");
                    return 1;
                }
                for (long long unsigned int k = 0; k < strlen(path) - j + 1; k++)
                {
                    path[k] = path[k + j + 1];
                    kmpArray[k] = -1;
                }
                path[pathLength - subChainSize] = 0;
                buildTable(kmpArray, path, strlen(path));
                j = -1;
            }
            else
            {
                j = kmpArray[j];
            }
        }
        if (path[j + 1] == main[i])
            j++;
    }
    return 0;
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
    Desease *deseases = (Desease *)malloc(deseaseCount * sizeof(Desease));

    for (int i = 0; i < deseaseCount; i++)
    {
        char *deseaseName = (char *)malloc(sizeof(char) * 8);
        int numberOfGenes;
        int compatibleGeneCount = 0;
        fscanf(input, "%s %d", deseaseName, &numberOfGenes);
        printf("%s\n", deseaseName);
        strcpy(deseases[i].name, deseaseName);
        for (int j = 0; j < numberOfGenes; j++)
        {
            char *deseaseGene = (char *)malloc(sizeof(char) * dnaSize);
            fscanf(input, "%s", deseaseGene);
            int *kmpArray = (int *)malloc(strlen(deseaseGene) * sizeof(int));
            compatibleGeneCount += kmp(deseaseGene, dna, subChainSize, kmpArray);
            free(deseaseGene);
            free(kmpArray);
        }
        deseases[i].canGetSick = (double)compatibleGeneCount/(double)numberOfGenes;
        free(deseaseName);
    }

    divide(deseases, 0, deseaseCount - 1);
    for(int i = 0; i < deseaseCount; i++){
        fprintf(output, "%s=>%.0lf%\n", deseases[i].name, (deseases[i].canGetSick*100));
    }

    free(deseases);
    free(dna);
    fclose(input);
    fclose(output);
    // Finalizando programa
    return 0;
}