#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *input = fopen("porto.input", "r");
    FILE *output = fopen("porto.output", "w");
    int main_list_count;
    fread(&main_list_count, sizeof(int), 1, input);
    printf("%d asds", main_list_count);
    //
    // ...
    //
    // Fechando arquivos
    fclose(input);
    fclose(output);
    // Finalizando programa
    return 0;
}