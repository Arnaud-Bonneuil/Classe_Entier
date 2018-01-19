/******************************************************************************\
fichier : Classe_Entier.h
\******************************************************************************/

#ifndef CLASSE_ENTIER_H
#define CLASSE_ENTIER_H

/* Inclusion des bibliotheques standard du C */
#include <stdio.h> /* FILE */
#include <stdint.h> /* uint32_t */

/* Inclusion de classes utiles pour implementer Classe_Entier */
#include "Classe_Liste.h"

#ifndef CLASSE_ENTIER_C
    typedef void* Classe_Entier;
#endif


/******************************************************************************/
/* ENTIER_Creer_Nul
Description :
    Constructeur : cree un entier = 0.
Parametres :
    aucun
Retour :
    entier
        = 0, NULL si la memoire n'a pas pus etre allouee.
*/
Classe_Entier ENTIER_Creer_Nul( void );

Classe_Entier ENTIER_Creer_De_Nombre( int32_t nombre );

/******************************************************************************/
/* ENTIER_Creer_De_Chaine
Description :
    Constructeur : cree un entier à partir d'une chaine de caractere reprentant
    un entier ecrit en decimal.
Parametres :
    chaine_entiers
        Au format "+12345679" ou "-9876543210" (par exemple...).
        Le premier caractere doit etre '+' ou '-' selon le signe de l'entier.
        Les autres caracteres doivent tous etre des chiffres. Sinon la chaine
        est invalide.
        Les chaines "-0" et "+0" sont valides et retourne un entier "positif".
Retour :
    entier
        Equivalent a la chaine, NULL si la memoire n'a pas pus etre allouee
        ou bien si la chaine n'est pas valide.
*/
Classe_Entier ENTIER_Creer_De_Chaine( const char* chaine_entiers );

/******************************************************************************/
/* ENTIER_Modifier_De_Chaine
Description :
Parametres :
    chaine_entiers
        Au format "+12345679" ou "-9876543210" (par exemple...).
        Le premier caractre doit etre '+' ou '-' selon le signe de l'entier. Les
        autres caracteres doivent tous etre des chiffres. Sinon la chaine est
        invalide.
Retour :
    aucun
*/
void ENTIER_Modifier_De_Chaine( Classe_Entier entier, const char* chaine );

/******************************************************************************/
/* ENTIER_Lire_De_Ficher
Description :
    Constructeur : cree un entier à partir d'une chaine de caractere - contenue
    dans un fichier - reprentant un entier ecrit en decimal.
Parametres :
    fichier
        Pointeur vers un flux de donnees associe a un fichier externe.
        Le fichier doit contenir une seule ligne reprentant l'entier.
Retour :
    entier
        Equivalent a la chaine contenue dans le fichier.
        NULL si fichier = NULL ou bien si la memoire n'a pas pus etre allouee
        ou bien si la chaine contenue dans le fichier n'est pas valide.
*/
Classe_Entier ENTIER_Lire_De_Ficher( FILE* fichier );

/******************************************************************************/
/* ENTIER_Detruire
Description :
    Destructeur : libere la memoire allouee a l'objet entier.
Parametres :
    pointeur sur un entier
Retour :
    aucun
*/
void ENTIER_Detruire( Classe_Entier* p_entier );

/******************************************************************************/
/* ENTIER_Ecrire_Fichier
Description :
    Affiche un entier dans la console
Parametres :
    aucun
Retour :
    aucun
*/
void ENTIER_Ecrire_Fichier( FILE* fichier, Classe_Entier entier );

/******************************************************************************/
/* ENTIER_Afficher_Console
Description :
    Affiche un entier dans la console.
    Un entier nul s'affiche "+0".
Parametres :
    aucun
Retour :
    aucun
*/
void ENTIER_Afficher_Console( Classe_Entier entier );

/******************************************************************************/
/* ENTIER_Copier
Description :
Parametres :
    entier a copier
Retour :
    aucun
*/
void ENTIER_Copier( Classe_Entier original, Classe_Entier copie );

/******************************************************************************/
/* ENTIER_Est_Egal
Description :
Parametres :
Retour :
    int : 1 si egal, 0 sinon
*/
int ENTIER_Est_Egal( Classe_Entier entier, Classe_Entier entier_compare );

/******************************************************************************/
/* ENTIER_Est_Superieur
Description :
Parametres :
Retour :
    int : 1 si plus grand (ou egal), 0 sinon
*/
int ENTIER_Est_Superieur( Classe_Entier entier, Classe_Entier entier_compare );

/******************************************************************************/
/* ENTIER_Est_Inferieur
Description :
Parametres :
Retour :
    int : 1 si plus petit (ou egal), 0 sinon
*/
int ENTIER_Est_Inferieur( Classe_Entier entier, Classe_Entier entier_compare );

/******************************************************************************/
/* ENTIER_Est_Strict_Sup
Description :
Parametres :
Retour :
    int :
*/
int ENTIER_Est_Strict_Sup( Classe_Entier entier, Classe_Entier entier_compare );

/******************************************************************************/
/* ENTIER_Est_Strict_Inf
Description :
Parametres :
Retour :
    int :
*/
int ENTIER_Est_Strict_Inf( Classe_Entier entier, Classe_Entier entier_compare );

/******************************************************************************/
/* ENTIER_Ajouter
Description :
    resultat doit déjà avoir ete cree
Parametres :
    resultat : resultat de l'addition
    entier_1, entier_2 : operandes
Retour :
    aucun
*/
void ENTIER_Ajouter( Classe_Entier resultat,
                     Classe_Entier entier_1,
                     Classe_Entier entier_2 );

/******************************************************************************/
/* ENTIER_Incrementer
Description :
    resultat doit déjà avoir ete cree
Parametres :
Retour :
    aucun
*/
void ENTIER_Incrementer( Classe_Entier resultat,
                         Classe_Entier increment );

/******************************************************************************/
/* ENTIER_Soustraire
Description :
    entier doit déjà avoir ete cree
Parametres :
    entier : resultat de la soustraction
    entier_1, entier_2 : operandes
Retour :
    aucun
*/
void ENTIER_Soustraire( Classe_Entier resultat,
                        Classe_Entier entier_1,
                        Classe_Entier entier_2 );

/******************************************************************************/
/* ENTIER_Decrementer
Description :
    resultat doit déjà avoir ete cree
Parametres :
Retour :
    aucun
*/
void ENTIER_Decrementer( Classe_Entier resultat, Classe_Entier decrement );

/******************************************************************************/
/* ENTIER_Multiplier
Description :
Parametres :
Retour :
    aucun
*/
void ENTIER_Multiplier( Classe_Entier resultat,
                        Classe_Entier entier_1,
                        Classe_Entier entier_2 );

/******************************************************************************/
/* ENTIER_Est_Nul
Description :
Parametres :
Retour :
    int : 1 si entier==0, 0 sinon
*/
int ENTIER_Est_Nul( Classe_Entier entier );

/******************************************************************************/
/* ENTIER_Diviser
Description :
Parametres :
Retour :
    aucun
*/
void ENTIER_Diviser( Classe_Entier quotient,
                     Classe_Entier reste,
                     Classe_Entier dividende,
                     Classe_Entier diviseur );

/******************************************************************************/
/* ENTIER_Racine_Carree
Description :
Parametres :
Retour :
    aucun
*/
void ENTIER_Racine_Carree( Classe_Entier resultat, Classe_Entier entier );

/******************************************************************************/
/* ENTIER_Puissance
Description :
Parametres :
Retour :
    aucun
*/
void ENTIER_Puissance( Classe_Entier resultat,
                       Classe_Entier entier,
                       Classe_Entier puissance );

/******************************************************************************/
/* ENTIER_Factorielle
Description :
Parametres :
Retour :
    aucun
*/
void ENTIER_Factorielle( Classe_Entier resultat, Classe_Entier entier );

/******************************************************************************/
/* ENTIER_Combinaison
Description :
Parametres :
Retour :
    aucun
*/
void ENTIER_Combinaison( Classe_Entier resultat,
                         Classe_Entier n,
                         Classe_Entier k );

/******************************************************************************/
/* ENTIER_Sommer_Chiffres
Description :
Parametres :
Retour :
    aucun
*/
void ENTIER_Sommer_Chiffres( Classe_Entier resultat, Classe_Entier entier );

/******************************************************************************/
/* ENTIER_Convertir
Description :
Parametres :
Retour :
    aucun
*/
uint32_t ENTIER_Convertir( Classe_Entier entier );

/******************************************************************************/
/* ENTIER_Charger_Nombres_Premiers
Description :
Parametres :
Retour :
    liste des nombres premiers <= limite
*/
Classe_Liste ENTIER_Charger_Nombres_Premiers( Classe_Entier limite );

/******************************************************************************/
/* ENTIER_Est_Premier
Description :
Parametres :
Retour :
    -1 si on ne sait pas repondre, 1 si entier est premier, 0 sinon
*/
int ENTIER_Est_Premier( Classe_Entier entier );

/******************************************************************************/
/* Decomposer_Fact_Premiers
Description :
Parametres :
Retour :
    liste d'entier
*/
Classe_Liste ENTIER_Decomposer_Fact_Premiers( Classe_Entier entier );


void ENTIER_Detruire_Liste( Classe_Liste* ptr_liste );

int ENTIER_Est_Plus_Infini( Classe_Entier entier );

void ENTIER_Chercher_Premiers_Suivants( void );

/******************************************************************************/
/* ENTIER_Chercher_Premier
Description :
    Retourne le 'indice'ieme nombre entier premier.
Parametres :
Retour :
    entier, NULL si la base de connaissances est trop petite.
*/
Classe_Entier ENTIER_Chercher_Premier( uint64_t indice );

/******************************************************************************/
/* ENTIER_Compter_Occurrence
Description :
    Compte le nombre d'occurences de 'entier' dans 'liste_entiers'.
Parametres :
Retour :
    nb occurences
*/
uint32_t ENTIER_Compter_Occurrences( Classe_Liste liste_entiers,
                                     Classe_Entier entier );

/******************************************************************************/
/* ENTIER_Sommer_Liste
Description :
    Calcule la somme de tous les entiers presents dans  'liste_entiers'.
Parametres :
Retour :
    somme
*/
Classe_Entier ENTIER_Sommer_Liste( Classe_Liste liste_entiers );

/******************************************************************************/
/* ENTIER_Est_Present
Description :
Parametres :
Retour :
    1 si entier est present, 0 sinon
*/
int ENTIER_Est_Present( Classe_Liste liste, Classe_Entier entier );

/******************************************************************************/
/* ENTIER_Sommer_Liste
Description :
    Cree une liste d'entiers avec les memes elements que dans la liste
    'liste_entiers' mais sans repetitions.
Parametres :
Retour :
    somme
*/
Classe_Liste ENTIER_Extraire_Unique( Classe_Liste liste_entiers );

#endif
