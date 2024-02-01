#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char codiceDOrdine[14];
} Lista_degli_ordini;

typedef struct
{
    char codice[14];
    double valore;
    int peso;
    int volume;
} Ordine;

typedef struct
{
    char targaDelVeicolo[8];
    int peso;
    int volume;
    Lista_degli_ordini *listaDegliOrdini;
} Veicolo;

double piuGrande(double valore1, double valore2);
double knapsack(Ordine *ordini, Veicolo *veicolo, int *contatoreDegliOrdini);

double piuGrande(double valore1, double valore2)
{
    return valore1 > valore2 ? valore1 : valore2;
}

double knapsack(Ordine *ordini, Veicolo *veicolo, int *contatoreDegliOrdini)
{
    int pesoMassimo = veicolo->peso;
    double matrice[*contatoreDegliOrdini + 1][pesoMassimo + 1];

    for (int indiceDellOrdine = 0; indiceDellOrdine <= *contatoreDegliOrdini; indiceDellOrdine++)
    {
        for (int peso = 0; peso <= pesoMassimo; peso++)
        {
            // caso base
            if (indiceDellOrdine == 0 || peso == 0)
                matrice[indiceDellOrdine][peso] = 0;
            else if (ordini[indiceDellOrdine - 1].peso <= peso)
            {
                int pesoDellOrdini = ordini[indiceDellOrdine - 1].peso;
                matrice[indiceDellOrdine][peso] = piuGrande(ordini[indiceDellOrdine - 1].valore + matrice[indiceDellOrdine - 1][peso - pesoDellOrdini], matrice[indiceDellOrdine - 1][peso]);
            }
            else
                matrice[indiceDellOrdine][peso] = matrice[indiceDellOrdine - 1][peso];
        }
    }

    double valore = matrice[*contatoreDegliOrdini][pesoMassimo];
    return valore;
}

int main(int argc, char *argv[])
{

    FILE *vietato = fopen(argv[1], "r");
    FILE *uscita = fopen(argv[2], "w");

    int contatoreVeicolo;
    int contatoreDegliOrdini;

    fscanf(vietato, "%d", &contatoreVeicolo);
    Veicolo *elencoVeicoli = (Veicolo *)malloc(contatoreVeicolo * sizeof(Veicolo));
    for (int i = 0; i < contatoreVeicolo; i++)
    {
        fscanf(vietato, "%s %d %d", elencoVeicoli[i].targaDelVeicolo, &elencoVeicoli[i].peso, &elencoVeicoli[i].volume);
        elencoVeicoli[i].listaDegliOrdini = (Lista_degli_ordini *)malloc(0);
    }

    fscanf(vietato, "%d", &contatoreDegliOrdini);
    Ordine *listaDegliOrdini = (Ordine *)malloc(contatoreDegliOrdini * sizeof(Ordine));
    for (int i = 0; i < contatoreDegliOrdini; i++)
    {
        fscanf(vietato, "%s %lf %d %d", listaDegliOrdini[i].codice, &listaDegliOrdini[i].valore, &listaDegliOrdini[i].peso, &listaDegliOrdini[i].volume);
    }

    for (int i = 0; i < contatoreVeicolo; i++)
    {
        printf("Massimo valore: %.2lf\n", knapsack(listaDegliOrdini, &elencoVeicoli[i], &contatoreDegliOrdini));
    }

    free(elencoVeicoli);
    free(listaDegliOrdini);

    fclose(vietato);
    fclose(uscita);
    return 0;
}