#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

typedef struct
{
	char *code;
	char *cnpj;
	int weight;
} Main_list_type;

typedef struct
{
	char *code;
	char *cnpj;
	int *weight;
	int *position;
} Arrived_list_type;

void conquer(Arrived_list_type *entry, int start_position, int middle, int final_position);
void divide(Arrived_list_type *entry, int start_position, int final_position);

void conquer(Arrived_list_type *entry, int start_position, int middle, int final_position)
{
	int start_aux = start_position;
	int ahead_middle = middle + 1;
	int start_aux_2 = 0;
	Arrived_list_type *temp = (Arrived_list_type *)malloc((final_position - start_position + 1) * sizeof(Arrived_list_type));

	while (start_aux <= middle && ahead_middle <= final_position)
	{
		temp[start_aux_2].cnpj = (char *)malloc(20 * sizeof(char));
		temp[start_aux_2].code = (char *)malloc(15 * sizeof(char));
		temp[start_aux_2].weight = (int *)malloc(sizeof(int));
		temp[start_aux_2].position = (int *)malloc(sizeof(int));

		if (entry[start_aux].position[0] <= entry[ahead_middle].position[0])
		{
			strcpy(temp[start_aux_2].cnpj, entry[start_aux].cnpj);
			strcpy(temp[start_aux_2].code, entry[start_aux].code);
			temp[start_aux_2].position[0] = entry[start_aux].position[0];
			temp[start_aux_2].weight[0] = entry[start_aux].weight[0];
			start_aux += 1;
		}
		else
		{
			strcpy(temp[start_aux_2].cnpj, entry[ahead_middle].cnpj);
			strcpy(temp[start_aux_2].code, entry[ahead_middle].code);
			temp[start_aux_2].position[0] = entry[ahead_middle].position[0];
			temp[start_aux_2].weight[0] = entry[ahead_middle].weight[0];
			ahead_middle += 1;
		}
		start_aux_2 += 1;
	}

	while (start_aux <= middle)
	{
		temp[start_aux_2].cnpj = (char *)malloc(20 * sizeof(char));
		temp[start_aux_2].code = (char *)malloc(15 * sizeof(char));
		temp[start_aux_2].weight = (int *)malloc(sizeof(int));
		temp[start_aux_2].position = (int *)malloc(sizeof(int));

		strcpy(temp[start_aux_2].cnpj, entry[start_aux].cnpj);
		strcpy(temp[start_aux_2].code, entry[start_aux].code);
		temp[start_aux_2].position[0] = entry[start_aux].position[0];
		temp[start_aux_2].weight[0] = entry[start_aux].weight[0];
		start_aux += 1;
		start_aux_2 += 1;
	}

	while (ahead_middle <= final_position)
	{
		temp[start_aux_2].cnpj = (char *)malloc(20 * sizeof(char));
		temp[start_aux_2].code = (char *)malloc(15 * sizeof(char));
		temp[start_aux_2].weight = (int *)malloc(sizeof(int));
		temp[start_aux_2].position = (int *)malloc(sizeof(int));

		strcpy(temp[start_aux_2].cnpj, entry[ahead_middle].cnpj);
		strcpy(temp[start_aux_2].code, entry[ahead_middle].code);
		temp[start_aux_2].position[0] = entry[ahead_middle].position[0];
		temp[start_aux_2].weight[0] = entry[ahead_middle].weight[0];
		ahead_middle += 1;
		start_aux_2 += 1;
	}

	for (int i = 0; i < (final_position - start_position + 1); i++)
	{
		strcpy(entry[start_position + i].cnpj, temp[i].cnpj);
		strcpy(entry[start_position + i].code, temp[i].code);
		entry[start_position + i].position[0] = temp[i].position[0];
		entry[start_position + i].weight[0] = temp[i].weight[0];

		free(temp[i].cnpj);
		free(temp[i].code);
		free(temp[i].position);
		free(temp[i].weight);
	}

	free(temp);
}

void divide(Arrived_list_type *entry, int start_position, int final_position)
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
	FILE *input;
	clock_t start_time = clock();
	int main_list_count;

	input = fopen(argv[1], "r");
	fscanf(input, "%d", &main_list_count);

	Main_list_type *main_list = (Main_list_type *)malloc(main_list_count * sizeof(Main_list_type));
	for (int i = 0; i < main_list_count; i++)
	{
		main_list[i].code = (char *)malloc(15 * sizeof(char));
		main_list[i].cnpj = (char *)malloc(20 * sizeof(char));
		fscanf(input, "%s %s %d", main_list[i].code, main_list[i].cnpj, &main_list[i].weight);
	}

	int arrived_list_count;
	fscanf(input, "%d", &arrived_list_count);

	Arrived_list_type *arrived_list = (Arrived_list_type *)malloc(arrived_list_count * sizeof(Arrived_list_type));
	for (int i = 0; i < arrived_list_count; i++)
	{
		arrived_list[i].code = (char *)malloc(15 * sizeof(char));
		arrived_list[i].cnpj = (char *)malloc(20 * sizeof(char));
		arrived_list[i].weight = (int *)malloc(sizeof(int));
		arrived_list[i].position = (int *)malloc(sizeof(int));
		fscanf(input, "%s %s %d", arrived_list[i].code, arrived_list[i].cnpj, arrived_list[i].weight);
		int flag = 0;
		int main_aux_count = -1;
		while (flag == 0)
		{
			if (strcmp(main_list[++main_aux_count].code, arrived_list[i].code) == 0)
			{
				arrived_list[i].position[0] = main_aux_count;
				flag += 1;
			}
		}
	}
	fclose(input);

	divide(arrived_list, 0, arrived_list_count - 1);

	FILE *output = fopen(argv[2], "w");

	for (int i = 0; i < arrived_list_count; i++)
	{
		int j = arrived_list[i].position[0];
		if (strcmp(arrived_list[i].cnpj, main_list[j].cnpj) != 0)
		{
			fprintf(output, "%s: %s<->%s\n", arrived_list[i].code, main_list[j].cnpj, arrived_list[i].cnpj);
		}
	}

	for (int i = 0; i < arrived_list_count; i++)
	{
		int j = arrived_list[i].position[0];
		if (*arrived_list[i].weight != main_list[j].weight)
		{
			int arrivedWeight = *arrived_list[i].weight;
			int mainWeight = main_list[j].weight;
			int difference = abs(arrivedWeight - mainWeight);
			double difference_percentage = difference * 100 / ((arrivedWeight + mainWeight) / 2);
			fprintf(output, "%s: %dkg (%.0f%c)\n", arrived_list[i].code, difference, difference_percentage, '%');
		}

		free(arrived_list[i].cnpj);
		free(arrived_list[i].code);
		free(arrived_list[i].weight);
		free(arrived_list[i].position);
	}
	free(arrived_list);

	for (int i = 0; i < main_list_count; i++)
	{
		free(main_list[i].cnpj);
		free(main_list[i].code);
	}
	free(main_list);

	fclose(output);
	clock_t end_time = clock();
	double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
	printf("Tempo de execucao: %.4f segundos\n", elapsed_time);

	return 0;
}
