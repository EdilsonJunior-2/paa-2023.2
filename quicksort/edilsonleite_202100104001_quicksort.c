#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define DEFAULT_HOARE 0
#define DEFAULT_LOMUTO 1
#define MEDIA_HOARE 2
#define MEDIA_LOMUTO 3
#define RANDOM_HOARE 4
#define RANDOM_LOMUTO 5

typedef struct
{
    char type[2];
    int exchangeCounter;
} Algorithm_type;

void change(int *value1, int *value2);
int media(int *entry, int i, int j);
int returnHalf(int n1, int n2, int n3, int index1, int index2, int index3);
void resetArray(int *main, int *copy, int count);
int hoare(int *entry, int i, int j, int *exchangeCounter);
void hoareQuicksort(int *entry, int i, int j, int *exchangeCounter);
int randHoare(int *entry, int i, int j, int *exchangeCounter);
void randHoareQuicksort(int *entry, int i, int j, int *exchangeCounter);
int mediaHoare(int *entry, int i, int j, int *exchangeCounter);
void mediaHoareQuicksort(int *entry, int i, int j, int *exchangeCounter);
int lomuto(int *entry, int i, int j, int *exchangeCounter);
void lomutoQuicksort(int *entry, int i, int j, int *exchangeCounter);
int randLomuto(int *entry, int i, int j, int *exchangeCounter);
void randLomutoQuicksort(int *entry, int i, int j, int *exchangeCounter);
int mediaLomuto(int *entry, int i, int j, int *exchangeCounter);
void mediaLomutoQuicksort(int *entry, int i, int j, int *exchangeCounter);
int hoareFinalArray(Algorithm_type *entry, int i, int j);
void hoareFinalArrayQuicksort(Algorithm_type *entry, int i, int j);

void change(int *value1, int *value2)
{

    int aux = *value1;
    *value1 = *value2;
    *value2 = aux;
}

int media(int *entry, int i, int j)
{
    int range = j - i;
    int st = (range / 4) + i;
    int nd = (range / 2) + i;
    int tr = (3 * range / 4) + i;
    return returnHalf(entry[st], entry[nd], entry[tr], st, nd, tr);
}

int returnHalf(int n1, int n2, int n3, int index1, int index2, int index3)
{
    if (n1 <= n2)
    {
        if (n1 >= n3)
            return index1;
        else if (n2 >= n3)
            return index3;
        return index2;
    }
    else
    {
        if (n2 >= n3)
            return index2;
        else if (n1 >= n3)
            return index3;
        return index1;
    }
}

int hoare(int *entry, int i, int j, int *exchangeCounter)
{
    int p = entry[i];
    int x = i;
    int y = j;
    while (1)
    {
        while (entry[y] >= p && y > i)
        {
            y -= 1;
        }

        while (entry[x] < p && x < j)
        {
            x += 1;
        }
        if (x < y)
        {
            *exchangeCounter += 1;
            change(&entry[x], &entry[y]);
        }
        else
            return y;
    }
}

int lomuto(int *entry, int i, int j, int *exchangeCounter)
{
    int p = entry[j];
    int x = i - 1;
    int y = i;

    for (y = i; y < j; y++)
    {
        if (entry[y] <= p)
        {
            *exchangeCounter += 1;
            x += 1;
            change(&entry[x], &entry[y]);
        }
    }
    *exchangeCounter += 1;
    x += 1;
    change(&entry[x], &entry[y]);
    return x;
}

int mediaLomuto(int *entry, int i, int j, int *exchangeCounter)
{
    if (i == j)
    {
        return i;
    }
    int index = media(entry, i, j);
    *exchangeCounter += 1;
    change(&entry[j], &entry[index]);
    return lomuto(entry, i, j, exchangeCounter);
}

void mediaLomutoQuicksort(int *entry, int i, int j, int *exchangeCounter)
{
    *exchangeCounter += 1;
    if (i < j)
    {
        int pivot = mediaLomuto(entry, i, j, exchangeCounter);
        mediaLomutoQuicksort(entry, i, pivot - 1, exchangeCounter);
        mediaLomutoQuicksort(entry, pivot + 1, j, exchangeCounter);
    }
}

int mediaHoare(int *entry, int i, int j, int *exchangeCounter)
{
    if (i == j)
    {
        return i;
    }
    int index = media(entry, i, j);
    *exchangeCounter += 1;
    change(&entry[i], &entry[index]);
    return hoare(entry, i, j, exchangeCounter);
}

void mediaHoareQuicksort(int *entry, int i, int j, int *exchangeCounter)
{
    *exchangeCounter += 1;
    if (i < j)
    {
        int pivot = mediaHoare(entry, i, j, exchangeCounter);
        mediaHoareQuicksort(entry, i, pivot, exchangeCounter);
        mediaHoareQuicksort(entry, pivot + 1, j, exchangeCounter);
    }
}

int randHoare(int *entry, int i, int j, int *exchangeCounter)
{
    *exchangeCounter += 1;
    change(&entry[i], &entry[i + (abs(entry[i]) % (j - i + 1))]);
    return hoare(entry, i, j, exchangeCounter);
}

void randHoareQuicksort(int *entry, int i, int j, int *exchangeCounter)
{
    *exchangeCounter += 1;
    if (i < j)
    {
        int pivot = randHoare(entry, i, j, exchangeCounter);
        randHoareQuicksort(entry, i, pivot, exchangeCounter);
        randHoareQuicksort(entry, pivot + 1, j, exchangeCounter);
    }
}

int randLomuto(int *entry, int i, int j, int *exchangeCounter)
{
    *exchangeCounter += 1;
    change(&entry[j], &entry[i + (abs(entry[i]) % (j - i + 1))]);
    return lomuto(entry, i, j, exchangeCounter);
}

void randLomutoQuicksort(int *entry, int i, int j, int *exchangeCounter)
{
    *exchangeCounter += 1;
    if (i < j)
    {
        int pivot = randLomuto(entry, i, j, exchangeCounter);
        randLomutoQuicksort(entry, i, pivot - 1, exchangeCounter);
        randLomutoQuicksort(entry, pivot + 1, j, exchangeCounter);
    }
}

void hoareQuicksort(int *entry, int i, int j, int *exchangeCounter)
{
    *exchangeCounter += 1;
    if (i < j)
    {
        int pivot = hoare(entry, i, j, exchangeCounter);
        hoareQuicksort(entry, i, pivot, exchangeCounter);
        hoareQuicksort(entry, pivot + 1, j, exchangeCounter);
    }
}

void lomutoQuicksort(int *entry, int i, int j, int *exchangeCounter)
{
    *exchangeCounter += 1;
    if (i < j)
    {
        int pivot = lomuto(entry, i, j, exchangeCounter);
        lomutoQuicksort(entry, i, pivot - 1, exchangeCounter);
        lomutoQuicksort(entry, pivot + 1, j, exchangeCounter);
    }
}

void resetArray(int *main, int *copy, int count)
{
    for (int i = 0; i < count; i++)
    {
        main[i] = copy[i];
    }
}

int hoareFinalArray(Algorithm_type *entry, int i, int j)
{
    int p = entry[i].exchangeCounter;
    int x = i;
    int y = j;
    while (1)
    {
        while (entry[y].exchangeCounter >= p && y > i)
        {
            y -= 1;
        }

        while (entry[x].exchangeCounter < p && x < j)
        {
            x += 1;
        }
        if (x < y)
        {
            change(&entry[x].exchangeCounter, &entry[y].exchangeCounter);
            char code[2];
            strcpy(code, entry[x].type);
            strcpy(entry[x].type, entry[y].type);
            strcpy(entry[y].type, code);
        }
        else
            return y;
    }
}

void hoareFinalArrayQuicksort(Algorithm_type *entry, int i, int j)
{
    if (i < j)
    {
        int pivot = hoareFinalArray(entry, i, j);
        hoareFinalArrayQuicksort(entry, i, pivot);
        hoareFinalArrayQuicksort(entry, pivot + 1, j);
    }
}

int main(int argc, char *argv[])
{

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");
    int count;
    fscanf(input, "%d", &count);
    Algorithm_type *types = (Algorithm_type *)malloc(sizeof(Algorithm_type));

    for (int i = 0; i < count; i++)
    {
        int arrayCount;
        fscanf(input, "%d", &arrayCount);
        int array[arrayCount], defaultArray[arrayCount];
        for (int j = 0; j < arrayCount; j++)
        {
            int value;
            fscanf(input, "%d", &value);
            array[j] = value;
            defaultArray[j] = value;
        }
        int exchangeCounter = 0;
        hoareQuicksort(array, 0, arrayCount - 1, &exchangeCounter);
        strcpy(types[DEFAULT_HOARE].type, "HP");
        types[DEFAULT_HOARE].exchangeCounter = exchangeCounter;

        resetArray(array, defaultArray, arrayCount);
        exchangeCounter = 0;
        lomutoQuicksort(array, 0, arrayCount - 1, &exchangeCounter);
        strcpy(types[DEFAULT_LOMUTO].type, "LP");
        types[DEFAULT_LOMUTO].exchangeCounter = exchangeCounter;

        resetArray(array, defaultArray, arrayCount);
        exchangeCounter = 0;
        randHoareQuicksort(array, 0, arrayCount - 1, &exchangeCounter);
        strcpy(types[RANDOM_HOARE].type, "HA");
        types[RANDOM_HOARE].exchangeCounter = exchangeCounter;

        resetArray(array, defaultArray, arrayCount);
        exchangeCounter = 0;
        randLomutoQuicksort(array, 0, arrayCount - 1, &exchangeCounter);
        strcpy(types[RANDOM_LOMUTO].type, "LA");
        types[RANDOM_LOMUTO].exchangeCounter = exchangeCounter;

        resetArray(array, defaultArray, arrayCount);
        exchangeCounter = 0;
        mediaHoareQuicksort(array, 0, arrayCount - 1, &exchangeCounter);
        strcpy(types[MEDIA_HOARE].type, "HM");
        types[MEDIA_HOARE].exchangeCounter = exchangeCounter;

        resetArray(array, defaultArray, arrayCount);
        exchangeCounter = 0;
        mediaLomutoQuicksort(array, 0, arrayCount - 1, &exchangeCounter);
        strcpy(types[MEDIA_LOMUTO].type, "LM");
        types[MEDIA_LOMUTO].exchangeCounter = exchangeCounter;

        hoareFinalArrayQuicksort(types, 0, 5);
        printf("%d: N(%d) %s(%d) %s(%d) %s(%d) %s(%d) %s(%d) %s(%d)\n", i, arrayCount, types[0].type, types[0].exchangeCounter, types[1].type, types[1].exchangeCounter, types[2].type, types[2].exchangeCounter, types[3].type, types[3].exchangeCounter, types[4].type, types[4].exchangeCounter, types[5].type, types[5].exchangeCounter);
        fprintf(output, "%d: N(%d) %s(%d) %s(%d) %s(%d) %s(%d) %s(%d) %s(%d)\n", i, arrayCount, types[0].type, types[0].exchangeCounter, types[1].type, types[1].exchangeCounter, types[2].type, types[2].exchangeCounter, types[3].type, types[3].exchangeCounter, types[4].type, types[4].exchangeCounter, types[5].type, types[5].exchangeCounter);
    }

    free(types);
    //
    // ...
    //
    // Fechando arquivos
    fclose(input);
    fclose(output);
    // Finalizando programa
    return 0;
}