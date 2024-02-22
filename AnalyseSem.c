#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX_IDFS 100 // Maximum d'identificateurs

enum TSYM { TPROG, TCONST, TVAR }; // Types de symboles

struct T_TAB_IDF {
    char NOM[20];
    enum TSYM TIDF;
    int value;
};

struct T_TAB_IDF TAB_IDFS[MAX_IDFS]; // Tableau pour stocker les identificateurs
int NbrIDFS = 0; // Nombre d'identificateurs stockés

// Fonction pour vérifier si un mot est un mot-clé réservé
int estMotCleReserve(char *mot) {
    char motsCles[7][10] = {"program", "const", "var", "begin", "end", "read", "write"};
    for (int i = 0; i < 7; i++) {
        if (strcmp(mot, motsCles[i]) == 0)
            return 1;
    }
    return 0;
}

// Fonction pour effectuer l'analyse sémantique
void analyseSemantique(char *programme) {
    // Analyse sémantique
    char *token = strtok(programme, " ;,");
    while (token != NULL) {
        if (strcmp(token, "program") == 0) {
            // Si le mot-clé est "program", il doit être suivi d'un identificateur de programme
            token = strtok(NULL, " ;,");
            strcpy(TAB_IDFS[NbrIDFS].NOM, token);
            TAB_IDFS[NbrIDFS].TIDF = TPROG;
            NbrIDFS++;
        } else if (strcmp(token, "const") == 0) {
            // Si le mot-clé est "const", il doit être suivi de paires identifiant-valeur
            token = strtok(NULL, " ;,");
            while (token != NULL && strcmp(token, "var") != 0 && strcmp(token, "begin") != 0) {
                strcpy(TAB_IDFS[NbrIDFS].NOM, token);
                TAB_IDFS[NbrIDFS].TIDF = TCONST;
                token = strtok(NULL, " ;,");
                if (token != NULL && strcmp(token, "=") == 0) {
                    token = strtok(NULL, " ;,");
                    TAB_IDFS[NbrIDFS].value = atoi(token); // Convertit la valeur de la constante en entier
                    token = strtok(NULL, " ;,");
                }
                NbrIDFS++;
            }
        } else if (strcmp(token, "var") == 0) {
            // Si le mot-clé est "var", il doit être suivi d'une liste d'identificateurs de variables
            token = strtok(NULL, " ;,");
            while (token != NULL && strcmp(token, "const") != 0 && strcmp(token, "begin") != 0) {
                strcpy(TAB_IDFS[NbrIDFS].NOM, token);
                TAB_IDFS[NbrIDFS].TIDF = TVAR;
                NbrIDFS++;
                token = strtok(NULL, " ;,");
            }
        }
        token = strtok(NULL, " ;,");
    }


    printf("Felicitation l'analyse semantique est bon\n");
}

int main() {
    // Ouverture du fichier
    FILE *fichier;
    fichier = fopen("C:/Users/preem/OneDrive/Bureau/program.p", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    // Lecture du contenu du fichier
    char programme[1000];
    fgets(programme, 1000, fichier);

    // Fermeture du fichier
    fclose(fichier);

    // Appel de la fonction d'analyse sémantique
    analyseSemantique(programme);

    return 0;
}
