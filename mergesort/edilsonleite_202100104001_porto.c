#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define CODE_SIZE 12
#define CNPJ_SIZE 19

typedef struct
{
	char code[CODE_SIZE];
	char cnpj[CNPJ_SIZE];
	int weight;
	int position;
} List_type;

void conquer(List_type *entry, int start_position, int middle, int final_position);
void divide(List_type *entry, int start_position, int final_position);
int binary(List_type arr[], int start, int end, char target[CODE_SIZE]);

int binary(List_type arr[], int start, int end, char target[CODE_SIZE])
{
	if (start <= end)
	{
		int mid = start + (end - start) / 2;
		if (strcmp(arr[mid].code, target) == 0)
			return mid;
		else if (strcmp(arr[mid].code, target) < 0)
			return binary(arr, mid + 1, end, target);
		else
			return binary(arr, start, mid - 1, target);
	}

	return -1;
}

void conquer(List_type *entry, int start_position, int middle, int final_position)
{
	int start_aux = start_position;
	int ahead_middle = middle + 1;
	int start_aux_2 = 0;
	List_type *temp = (List_type *)malloc((final_position - start_position + 1) * sizeof(List_type));

	while (start_aux <= middle && ahead_middle <= final_position)
	{
		if (strcmp(entry[start_aux].code, entry[ahead_middle].code) <= 0)
		{
			strcpy(temp[start_aux_2].cnpj, entry[start_aux].cnpj);
			strcpy(temp[start_aux_2].code, entry[start_aux].code);
			temp[start_aux_2].weight = entry[start_aux].weight;
			start_aux += 1;
		}
		else
		{
			strcpy(temp[start_aux_2].cnpj, entry[ahead_middle].cnpj);
			strcpy(temp[start_aux_2].code, entry[ahead_middle].code);
			temp[start_aux_2].weight = entry[ahead_middle].weight;
			ahead_middle += 1;
		}
		start_aux_2 += 1;
	}

	while (start_aux <= middle)
	{
		strcpy(temp[start_aux_2].cnpj, entry[start_aux].cnpj);
		strcpy(temp[start_aux_2].code, entry[start_aux].code);
		temp[start_aux_2].weight = entry[start_aux].weight;
		start_aux += 1;
		start_aux_2 += 1;
	}

	while (ahead_middle <= final_position)
	{
		strcpy(temp[start_aux_2].cnpj, entry[ahead_middle].cnpj);
		strcpy(temp[start_aux_2].code, entry[ahead_middle].code);
		temp[start_aux_2].weight = entry[ahead_middle].weight;
		ahead_middle += 1;
		start_aux_2 += 1;
	}

	for (int i = 0; i < (final_position - start_position + 1); i++)
	{
		strcpy(entry[start_position + i].cnpj, temp[i].cnpj);
		strcpy(entry[start_position + i].code, temp[i].code);
		entry[start_position + i].weight = temp[i].weight;
	}

	free(temp);
}

void divide(List_type *entry, int start_position, int final_position)
{
	if (start_position < final_position)
	{
		int middle = start_position + (final_position - start_position) / 2;
		divide(entry, start_position, middle);
		divide(entry, middle + 1, final_position);
		conquer(entry, start_position, middle, final_position);
	}
}

int main(int argc, char *argv[])
{
	// clock_t start_time = clock();
	FILE *input;
	int main_list_count;

	input = fopen(argv[1], "r");
	fscanf(input, "%d", &main_list_count);

	List_type *main_list = (List_type *)malloc(main_list_count * sizeof(List_type));
	for (int i = 0; i < main_list_count; i++)
	{
		fscanf(input, "%s %s %d", main_list[i].code, main_list[i].cnpj, &main_list[i].weight);
	}
	// clock_t first_read_time = clock();
	// double elapsed_first_read_time = ((double)(first_read_time - start_time)) / CLOCKS_PER_SEC;
	// printf("Tempo de leitura do primeiro arquivo: %.4f segundos\n", elapsed_first_read_time);

	int arrived_list_count;
	fscanf(input, "%d", &arrived_list_count);

	List_type *arrived_list = (List_type *)malloc(arrived_list_count * sizeof(List_type));
	for (int i = 0; i < arrived_list_count; i++)
	{
		fscanf(input, "%s %s %d", arrived_list[i].code, arrived_list[i].cnpj, &arrived_list[i].weight);
	}

	fclose(input);

	// clock_t read_time = clock();
	// double elapsed_read_time = ((double)(read_time - first_read_time)) / CLOCKS_PER_SEC;
	// printf("Tempo de leitura do segundo arquivo: %.4f segundos\n", elapsed_read_time);

	divide(arrived_list, 0, arrived_list_count - 1);

	List_type *error_list = (List_type *)malloc(arrived_list_count * sizeof(List_type));
	int error_list_count = 0;

	for (int i = 0; i < main_list_count; i++)
	{
		int position = binary(arrived_list, 0, arrived_list_count - 1, main_list[i].code);
		if (position != -1)
		{
			strcpy(error_list[error_list_count].cnpj, arrived_list[position].cnpj);
			strcpy(error_list[error_list_count].code, arrived_list[position].code);
			error_list[error_list_count].weight = arrived_list[position].weight;
			error_list[error_list_count].position = i;
			error_list_count++;
		}
	}
	free(arrived_list);

	FILE *output = fopen(argv[2], "w");

	for (int i = 0; i < error_list_count; i++)
	{
		int j = error_list[i].position;
		if (strcmp(error_list[i].cnpj, main_list[j].cnpj) != 0)
		{
			fprintf(output, "%s: %s<->%s\n", error_list[i].code, main_list[j].cnpj, error_list[i].cnpj);
		}
	}

	for (int i = 0; i < error_list_count; i++)
	{
		int j = error_list[i].position;
		int errorWeight = error_list[i].weight;
		int mainWeight = main_list[j].weight;
		int difference = abs(errorWeight - mainWeight);
		double difference_percentage = difference * 100 / ((errorWeight + mainWeight) / 2);
		if (trunc(difference_percentage) > 10)
		{
			fprintf(output, "%s: %dkg (%.0f%c)\n", error_list[i].code, difference, difference_percentage, '%');
		}
	}

	free(main_list);
	free(error_list);
	fclose(output);

	// clock_t end_time = clock();
	// double elapsed_time = ((double)(end_time - read_time)) / CLOCKS_PER_SEC;
	// printf("Tempo de ordenar e imprimir no arquivo: %.4f segundos\n", elapsed_time);
	return 0;
}
