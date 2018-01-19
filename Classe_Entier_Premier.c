/******************************************************************************\
fichier : Classe_Entier_Premier.c
\******************************************************************************/

/* Inclusion des bibliotheques standard du C */
#include <stdio.h> /* sprintf */
#include <stdint.h> /* uint64_t, uint32_t, uint16_t */

/* */
#include "Classe_Entier.h"
//#include "Entiers_Premiers.h"




/******************************************************************************/
/* Declaration des fonctions privees */
/******************************************************************************/
// static Classe_Entier Chercher_Premier_Suivant( void );



/******************************************************************************/
/* Definition des methodes publiques */
/******************************************************************************/
Classe_Liste ENTIER_Charger_Nombres_Premiers( Classe_Entier limite )
{
    Classe_Liste lst_prm = NULL;
    Classe_Entier nb_prm = NULL;
    FILE* fichier_entiers = NULL;

    if( limite==NULL )
    {
        /* retourner NULL */
    }
    else if( ENTIER_Est_Plus_Infini( limite ) )
    {
        /* retourner NULL */
    }
    else
    {
        /* Ouvrir le fichier contenant la liste des nombres entier */
        fichier_entiers = fopen( "nombres_premiers", "r" );

        /* Lire le premier entier sauvegarde dans le fichier ("+2") */
        nb_prm = ENTIER_Lire_De_Ficher( fichier_entiers );

        /* si limite >= 2 */
        if( !ENTIER_Est_Strict_Inf( limite, nb_prm ) )
        {
            lst_prm = LISTE_Creer();
            while( nb_prm!=NULL && ENTIER_Est_Strict_Inf( nb_prm, limite ) )
            {
                /* Ajouter le nb puisqu'il est <= limite */
                LISTE_Ajouter_Elmt_Fin( lst_prm, nb_prm );

                /* Charger le nombre premier suivant */
                nb_prm = ENTIER_Lire_De_Ficher( fichier_entiers );
            }

            /* Tester si il y suffisement d'entier premiers connus */
            if( nb_prm!=NULL )
            {
                /* Ajouter le dernier entier sortie du fichier si = limite */
                if( ENTIER_Est_Egal( nb_prm, limite ) )
                {
                    LISTE_Ajouter_Elmt_Fin( lst_prm, nb_prm );
                }
            }
            else
            {
                /* Retourner NULL */
                ENTIER_Detruire_Liste( &lst_prm );
            }
        }
        else
        {
            /* limite<2 */
            /* Supprimer nb_prm (=2) de la memoire */
            ENTIER_Detruire( &nb_prm );
            /* retourner NULL */
        }
        fclose( fichier_entiers );
    }
    return lst_prm;
}
/******************************************************************************/
int ENTIER_Est_Premier( Classe_Entier entier )
{
    int est_premier = 1; /* resultat du test */
    Classe_Entier DEUX = ENTIER_Creer_De_Chaine( "+2" );
    Classe_Entier TROIS = ENTIER_Creer_De_Chaine( "+3" );
    Classe_Entier limite = ENTIER_Creer_Nul();
    Classe_Entier nb_prm = NULL;
    Classe_Entier quotient = NULL; /* ne sert pas */
    Classe_Entier reste = NULL;
    Classe_Liste lst_prm = NULL;

    if( entier==NULL )
    {
        est_premier = 0;
    }
    else if( ENTIER_Est_Strict_Inf( entier, DEUX ) ) /* < 2 */
    {
        est_premier = 0;
    }
    else if( ENTIER_Est_Inferieur( entier, TROIS ) ) /* 2 ou 3 */
    {
        est_premier = 1;
    }
    else if( ENTIER_Est_Plus_Infini( entier ) ) /* +inf */
    {
        est_premier = 0;
    }
    else
    {
        ENTIER_Racine_Carree( limite, entier );

        lst_prm = ENTIER_Charger_Nombres_Premiers( limite );

        if ( lst_prm==NULL  )
        {
            /* la base de connaissance est trop petite */
            est_premier = -1;
        }
        else
        {
            nb_prm = (Classe_Entier)LISTE_Lire_Premier_Elmt( lst_prm );

            quotient = ENTIER_Creer_Nul();
            reste = ENTIER_Creer_Nul();

            /* nb_prm!=NULL <=> nb_prm<=limite */
            while( nb_prm!=NULL && est_premier==1 )
            {
                ENTIER_Diviser( quotient, reste, entier, nb_prm );
                if( ENTIER_Est_Nul( reste ) )
                {
                    est_premier = 0;
                }
                if( est_premier )
                {
                    nb_prm = (Classe_Entier)LISTE_Lire_Elmt_Suivant( lst_prm );
                }

            }
            ENTIER_Detruire( &quotient );
            ENTIER_Detruire( &reste );
            ENTIER_Detruire_Liste( &lst_prm );
        }
        ENTIER_Detruire( &limite );
    }
    ENTIER_Detruire( &DEUX );
    ENTIER_Detruire( &TROIS );
    return est_premier;
}
/******************************************************************************/
Classe_Liste ENTIER_Decomposer_Fact_Premiers( Classe_Entier entier )
{
    Classe_Liste decomposition = NULL;
    Classe_Entier DEUX = ENTIER_Creer_De_Chaine( "+2" );
    Classe_Entier TROIS = ENTIER_Creer_De_Chaine( "+3" );
    Classe_Entier limite = ENTIER_Creer_Nul();
    Classe_Entier nb_prm = NULL;
    Classe_Entier nb_prm_copie = NULL;
    Classe_Entier quotient = ENTIER_Creer_Nul();
    Classe_Entier dernier_quotient = ENTIER_Creer_Nul();
    Classe_Entier reste = ENTIER_Creer_De_Chaine( "+1" );
    Classe_Entier tmp = ENTIER_Creer_Nul();
    Classe_Entier UN = ENTIER_Creer_De_Chaine( "+1" );
    Classe_Liste lst_prm = NULL;
    int fin = 0;

    if( entier==NULL )
    {

    }
    else if( ENTIER_Est_Strict_Inf( entier, DEUX ) ) /* < 2 */
    {
        fin = 0;
    }
    else if( ENTIER_Est_Inferieur( entier, TROIS ) ) /* 2 ou 3 */
    {
        decomposition = LISTE_Creer();
        nb_prm_copie = ENTIER_Creer_Nul();
        ENTIER_Copier( entier, nb_prm_copie );
        LISTE_Ajouter_Elmt_Fin( decomposition, nb_prm_copie );
    }
    else
    {
        ENTIER_Racine_Carree( limite, entier );
        lst_prm = ENTIER_Charger_Nombres_Premiers( limite );
        if( lst_prm==NULL )
        {
            /* la base de connaissance est trop petite */
            /* Retourner NULL */
        }
        else
        {
            /* La decomposition est possible */
            decomposition = LISTE_Creer();

            /* Selectionner le premier entier connu : +2 */
            nb_prm = LISTE_Lire_Premier_Elmt( lst_prm );
            /* tmp = entiet */
            ENTIER_Copier( entier, tmp );
            /* Tant que quotient!= 1 */
            //while( !ENTIER_Est_Egal( quotient, UN ) && fin==0 )
            while( nb_prm!=NULL && fin==0 )
            {
                /* quotient = tmp / nb_prm + reste */
                ENTIER_Diviser( quotient, reste, tmp, nb_prm );

                /* si reste = 0 */
                if( ENTIER_Est_Nul( reste ) )
                {
                    /* ajouter nrb_prm a la liste de decomposition */
                    nb_prm_copie = ENTIER_Creer_Nul();
                    ENTIER_Copier( nb_prm, nb_prm_copie );
                    LISTE_Ajouter_Elmt_Fin( decomposition, nb_prm_copie );

                    /* on etudie le quotient restant : tmp = quotient */
                    if( ENTIER_Est_Egal( nb_prm, tmp ) )
                    {
                        fin = 1;
                    }
                    /* quotient obtenu quand reste  = 0 */
                    ENTIER_Copier( quotient, dernier_quotient );

                    ENTIER_Copier( quotient, tmp );
                }
                /* si reste != 0 */
                else
                {
                    /* Tester avec le nombre premier suivant */
                    nb_prm = LISTE_Lire_Elmt_Suivant( lst_prm );
                    if( nb_prm==NULL )
                    {
                        nb_prm_copie = ENTIER_Creer_Nul();
                        /* Soit le quotient restant est premier et > limite */
                        if( ENTIER_Est_Superieur( dernier_quotient, limite ) )
                        {
                            fin = 1;
                            ENTIER_Copier( dernier_quotient, nb_prm_copie );
                        }
                        /* Soit entier est premier */
                        else
                        {
                            /* entier est premier */
                            fin = 1;
                            ENTIER_Copier( entier, nb_prm_copie );
                        }
                        LISTE_Ajouter_Elmt_Fin( decomposition, nb_prm_copie );
                    }
                }
            }
        }
    }

    /* Liberer la memoire alloue dynamiquement */
    ENTIER_Detruire( &quotient );
    ENTIER_Detruire( &dernier_quotient );
    ENTIER_Detruire( &reste );
    ENTIER_Detruire( &tmp );
    ENTIER_Detruire( &UN );
    ENTIER_Detruire_Liste( &lst_prm );

    return decomposition;
}
/******************************************************************************/
void ENTIER_Chercher_Premiers_Suivants( void )
{
    Classe_Liste lst_prm = LISTE_Creer();
    Classe_Entier nb_prm = NULL;
    Classe_Entier limite = NULL;
    Classe_Entier quotient = NULL; /* ne sert pas */
    Classe_Entier reste = NULL;
    Classe_Entier nouv_prm = NULL;
    int trouve = 0;
    int est_premier = 1;
    Classe_Entier DEUX = ENTIER_Creer_De_Chaine( "+2" );
    FILE* fichier_entiers = NULL;

    /* Charger la liste des entier premiers connus */
    /* Ouvrir le fichier contenant la liste des nombres entier */
    fichier_entiers = fopen( "nombres_premiers", "r" );
    /* Lire le premier entier sauvegarde dans le fichier ("+2") */
    nb_prm = ENTIER_Lire_De_Ficher( fichier_entiers );
    while( nb_prm!=NULL )
    {
        LISTE_Ajouter_Elmt_Fin( lst_prm, nb_prm );
        nb_prm = ENTIER_Lire_De_Ficher( fichier_entiers );
    }
    /* Fermer le fichier contenant la liste des nombres entier */
    fclose( fichier_entiers );

    /* Chercher les nombres premiers suivants, jusqu'a l'arret du programme */
    /* Initialisation des variables locales */
    quotient = ENTIER_Creer_Nul();
    reste = ENTIER_Creer_Nul();
    limite = ENTIER_Creer_Nul();

    /* Boucle jusqu'a l'arret du programme */
    while( 1 )
    {
        nouv_prm = ENTIER_Creer_Nul();
        trouve = 0;
        nb_prm = (Classe_Entier)LISTE_Lire_Dernier_Elmt( lst_prm );
        ENTIER_Copier( nb_prm, nouv_prm );

        while( trouve==0  )
        {
            /* Calculer nouveau nombre a tester */
            ENTIER_Incrementer( nouv_prm, DEUX );

            /* Tester ce nombre avec tous les entiers premiers connus
            inferieur ou egaux a la racine carree du nombre */
            ENTIER_Racine_Carree( limite, nouv_prm );
            /* Selectionner premier entier premier connu */
            nb_prm = LISTE_Lire_Premier_Elmt( lst_prm );
            est_premier = 1;
            while( ENTIER_Est_Inferieur( nb_prm, limite) && est_premier==1 )
            {
                /* Tester si nb premier divise nouv_prm */
                ENTIER_Diviser( quotient, reste, nouv_prm, nb_prm );
                if( ENTIER_Est_Nul( reste ) )
                {
                    est_premier = 0;
                }
                /* Selectionner nombre premier connu suivant */
                nb_prm = LISTE_Lire_Elmt_Suivant( lst_prm );
            }
            if( est_premier==1 )
            {
                trouve = 1;
            }
        }

        /* Ajouter nouv_prm a la liste */
        LISTE_Ajouter_Elmt_Fin( lst_prm, nouv_prm );

        /* Ecrire nouv_prm dans le fichier de sauvegarde */
        fichier_entiers = fopen( "nombres_premiers", "a" );
        ENTIER_Ecrire_Fichier( fichier_entiers, nouv_prm );
        fprintf( fichier_entiers, "\n" );
        fclose( fichier_entiers );
    }
}
/******************************************************************************/
Classe_Entier ENTIER_Chercher_Premier( uint64_t indice )
{
    Classe_Entier resultat = NULL;
    uint64_t compteur = 1;
    FILE* fichier_entiers = NULL;
    char bidon[1000];

    fichier_entiers = fopen( "nombres_premiers", "r" );
    while( compteur < indice )
    {
        fscanf( fichier_entiers, "%s", bidon );
        compteur++;
    }
    resultat = ENTIER_Lire_De_Ficher( fichier_entiers );
    fclose( fichier_entiers );

    return resultat;
}
