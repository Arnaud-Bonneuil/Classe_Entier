/******************************************************************************\
fichier : Classe_Entier_Liste.c
\******************************************************************************/

/* Inclusion des bibliotheques standard du C */
#include <stdint.h> /* uint32_t */


/* */
#include "Classe_Entier.h"



/******************************************************************************/
/* Definition des methodes publiques */
/******************************************************************************/
void ENTIER_Detruire_Liste( Classe_Liste* ptr_liste )
{
    Classe_Entier entier = NULL;
    if( ptr_liste!=NULL )
    {
        entier = LISTE_Retirer_Premier_Elmt( *ptr_liste );
        while( entier!=NULL )
        {
            ENTIER_Detruire( &entier );
            entier = LISTE_Retirer_Premier_Elmt( *ptr_liste );
        }
        LISTE_Detruire( ptr_liste );
    }
}
/******************************************************************************/
uint32_t ENTIER_Compter_Occurrences( Classe_Liste liste_entiers,
                                     Classe_Entier entier )
{
    uint32_t resultat = 0;
    Classe_Entier entier_courant = NULL;

    if( liste_entiers!=NULL && entier!=NULL )
    {
        entier_courant = LISTE_Lire_Premier_Elmt( liste_entiers );
        while( entier_courant!=NULL )
        {
            if( ENTIER_Est_Egal( entier, entier_courant ) )
            {
                resultat++; /* pas de depassement possible car taille liste
                            majoree par uint_32 max */
            }
            entier_courant = LISTE_Lire_Elmt_Suivant( liste_entiers );
        }
    }
    return resultat;
}
/******************************************************************************/
Classe_Entier ENTIER_Sommer_Liste( Classe_Liste liste_entiers )
{
    Classe_Entier somme = NULL;
    Classe_Entier entier_courant = NULL;
    if( liste_entiers!=NULL )
    {
        somme = ENTIER_Creer_Nul();
        if( somme!=NULL )
        {
            entier_courant = LISTE_Lire_Premier_Elmt( liste_entiers );
            while( entier_courant!=NULL )
            {
                ENTIER_Incrementer( somme, entier_courant );
                entier_courant = LISTE_Lire_Elmt_Suivant( liste_entiers );
            }
        }
    }
    return somme;
}
/******************************************************************************/
int ENTIER_Est_Present( Classe_Liste liste_entiers, Classe_Entier entier )
{
    int resultat = 0;
    Classe_Entier entier_courant = NULL;
    if( liste_entiers!=NULL )
    {
        /* Parcourir la liste */
        entier_courant = LISTE_Lire_Premier_Elmt( liste_entiers );
        while( entier_courant!=NULL && resultat==0 )
        {
            /* Tester si l'element courant est egale a l'entier */
            if( ENTIER_Est_Egal( entier_courant, entier ) )
            {
                resultat = 1;
            }

            /* Selectionner l'element suivant de la liste */
            entier_courant = LISTE_Lire_Elmt_Suivant( liste_entiers );
        }
    }
    return resultat;
}
/******************************************************************************/
Classe_Liste ENTIER_Extraire_Unique( Classe_Liste liste_entiers )
{
    Classe_Liste resultat = NULL;
    Classe_Entier entier_courant = NULL;
    Classe_Entier copie = NULL;

    if( liste_entiers==NULL )
    {
        /* retourner NULL */
    }
    else
    {
        resultat = LISTE_Creer();

        /* Parcourir la liste "complete" */
        /* Selectionner le premier element de la liste "complete" */
        entier_courant = LISTE_Lire_Premier_Elmt( liste_entiers );
        while( entier_courant!=NULL )
        {
            /* Si l'entier n'est pas dans la liste "unique" */
            if( !ENTIER_Est_Present( resultat, entier_courant ) )
            {
                /* Creer une copie de l'entier */
                copie = ENTIER_Creer_Nul();
                ENTIER_Copier( entier_courant, copie );

                /* Ajouter la copie a la liste unique */
                LISTE_Ajouter_Elmt_Fin( resultat, copie );
            }
            /* Selectionner l'element suivant de la liste complete */
            entier_courant = LISTE_Lire_Elmt_Suivant( liste_entiers );
        }
    }
    return resultat;
}
/******************************************************************************/

