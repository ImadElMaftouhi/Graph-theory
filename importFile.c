//
// Created by imadt on 2/10/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include "importFile.h"

/**
 * Cette fonction a comme but d'importer un fichier qui contient la matrice d'adjacence d'un graphe.\n
 * il faut obligatoirement respecter la format de la matrice indiquer comme suit:\n
 * \n
 *   *,*,*,\n
 *   *,*,*,\n
 *   *,*,*\n
 *   \n
 * Aucun espace n'est autoriser, ni aprés la matrice, ni avant, ni entre les valeurs.\n
 * les valeurs sont séparer justement par des virgules.\n
 * la retourne a la ligne signifie une nouvelle ligne.\n
 * La dernier colonne dans la dernier ligne ne doit pas se terminer pas une virgule.\n
 * @param fichier : Chemin de fichier ( Relative/Absolut ) contenant le nom de fichier
 * @param nbrSommet : Passage par reference a la taille de la matrice ( A determinée d'après la fonction )
 * @return : Retourner l'address dans la mémoire de la matrice d'adjacence.
 */
int** ImporterFichier(char* fichier, int* nbrSommet) {
    FILE* file = fopen(fichier, "r");
    if (file == NULL) {
        printf("Error lors d'ouverture de fichier: %s\n", fichier);
        return NULL;
    }

    // Determiner la taille de la matrice
    int rows = 0, cols = 0;
    char ch;

    while (fscanf(file, "%c", &ch) == 1) {
        if (ch == '\n') {
            rows++;
        }
        else if ( ch == ',' || ch <= '9') {

            if ( ch == ','  && rows == 0) {
                cols++;
            }

        } else {
            printf("Character étranger dans la matrice: << %c >> \tVerifier dans le fichier\n ", ch);
            return NULL;
        }
    }
    fclose(file);

    // Verifiez si vraiment la matrice est carrée
    if (rows != cols) {
        printf("Error: La matrice n'est pas carrée! \n"
               "\n\t\t\tDimension trouvée =>  Ligne: %d  \t Colonne %d ", rows, cols);
        return NULL;
    }

    *nbrSommet = rows;

    int** matrice = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrice[i] = (int*)malloc(cols * sizeof(int));
    }

    file = fopen(fichier, "r");
    if (file == NULL) {
        fprintf(stderr, "Error lors d'ouverture de fichier: %s\n", fichier);
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (fscanf(file, "%d,", &matrice[i][j]) != 1) {
                printf("Error de lecture de la matrice d'adjacence de fichier %s.\n", fichier);
                return NULL;
            }
        }
    }
    fclose(file);
    return matrice;
}
