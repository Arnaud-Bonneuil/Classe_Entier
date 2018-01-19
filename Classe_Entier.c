/******************************************************************************\
fichier : Classe_Entier.c
\******************************************************************************/

/* Inclusion des bibliotheques standard du C */
#include <stdlib.h> /* malloc, strtol */
#include <string.h> /* memset */
#include <stdio.h> /* printf */
#include <stdint.h> /* uint64_t, uint32_t, uint16_t, int32_t */



/******************************************************************************/
/* Definition des attributs de la classe */
/******************************************************************************/
/* Un objet de classe Classe_Entier est represente par un tableau de
RANG_MAXIMUM entiers non signes de 32 bits (uint32_t).
Le signe de l'entier est donne par l'attribut signe qui vaut soit POSITIF, soit
NEGATIF (INVALIDE est utilise en interne mais aucun entier ne doit etre cree
avec signe = INVALIDE ).
L'attribut rg_util donne le rang maximal utile pour representer l'entier. C'est
le dernier rang different de 0. Si rg_util = RANG_MAXIMUM, l'entier vaut infini.
rg_util va de 0 a (RANG_MAXIMUM-1).
entier = [rg_0]*BASE^0 + [rg_1]*BASE^1 + ... + [rg_rg_util]*BASE^rg_util
([rg_n] = liste_rangs[n])
*/

/* Nombre maximum de rangs de l'entier */
/* arbitraire, minimum = 1, a adapter suivant les besoins... */
#define RANG_MAXIMUM ((uint16_t)1)

typedef enum type_signe{ POSITIF, NEGATIF, INVALIDE } type_signe;

typedef struct _classe_entier
{
    uint32_t liste_rangs[RANG_MAXIMUM];
    uint16_t rg_util; /*  */
    type_signe signe;
} _classe_entier, *Classe_Entier;

/* Plus grande puissance de 10 codable sur un uint32_t */
static const uint32_t BASE = 1000000000;

/* Nombre de chiffres par rang, depend de BASE */
#define NB_CHIFFRES_PAR_RANG ((uint16_t)9)

/* Nombre de chiffres par rang sous forme de chaine de caractere,
depend de NB_CHIFFRES_PAR_RANG */
#define NB_CHIFFRES_PAR_RANG_CH "9"

/* Nombre maximum de chiffres representant un entier (en base 10) */
#define NB_CHIFFRES_MAX NB_CHIFFRES_PAR_RANG*RANG_MAXIMUM
/******************************************************************************/



/******************************************************************************/
/* Classe_Entier est defini, on peut maintenant inclure le fichier d'en-tete
declarant les methodes de la classe */
#define CLASSE_ENTIER_C
#include "Classe_Entier.h"
#undef CLASSE_ENTIER_C



/******************************************************************************/
/* Declaration des fonctions privees */
/******************************************************************************/
/* Annuler
Description :
    Modifie un entier en le valorisant a 0.
Parametres :
    entier
Retour :
    aucun
*/
static void Annuler( Classe_Entier entier );

/******************************************************************************/
/* Verifier_Chaine_Entier
Description :
    Verifie qu'une chaine de caracteres ne contient que des chiffres et le
    signe '+' ou bien '-' au debut.
    Renvoie INVALIDE si ces conditions ne sont pas remplies.
    Renvoie POSITIF si le premier caractere est '+'.
    Renvoie NEGATIF si le premier caractere est '-'.
Parametres :
    chaine
Retour :
    type_signe
*/
static type_signe Verifier_Chaine_Entier( const char* const chaine );

/******************************************************************************/
/* Convertir_Chaine_U32
Description :
Parametres :
    chaine
    nb_chiffre
Retour :
    uint32_t
*/
static uint32_t Convertir_Chaine_U32( const char* chaine, size_t nb_chiffre );

/******************************************************************************/
/* Ajouter_Rangs
Description :
Parametres :
Retour :
    aucun
*/
static void Ajouter_Rangs( Classe_Entier resultat,
                           Classe_Entier entier_1,
                           Classe_Entier entier_2 );

/******************************************************************************/
/* Soustraire_Rangs
Description :
Parametres :
Retour :
    aucun
*/
static void Soustraire_Rangs( Classe_Entier resultat,
                              Classe_Entier entier_1,
                              Classe_Entier entier_2 );

/******************************************************************************/
/* Calculer_Signe_Res_Mul_Div
Description :
Parametres :
Retour :
    aucun
*/
static type_signe Calculer_Signe_Res_Mul_Div( Classe_Entier entier_1,
                                              Classe_Entier entier_2 );

/******************************************************************************/
/* Calculer_Somme_Cofacteurs
Description :
Parametres :
Retour :
    aucun
*/
static void Calculer_Somme_Cofacteurs( Classe_Entier resultat,
                                       Classe_Entier entier_1,
                                       Classe_Entier entier_2,
                                       uint16_t rang );

/******************************************************************************/
/* Decaler_Rang
Description :
Parametres :
Retour :
    aucun
*/
static void Decaler_Rang( Classe_Entier resultat,
                          Classe_Entier entier,
                          uint16_t decalage );

/******************************************************************************/
/* Diviser_Entier_Positifs
Description :
Parametres :
Retour :
    aucun
*/
static void Diviser_Entier_Positifs( Classe_Entier quotient,
                                     Classe_Entier reste,
                                     Classe_Entier dividende,
                                     Classe_Entier diviseur );

/******************************************************************************/
/* Diviser_Par_Deux
Description :
Parametres :
Retour :
    aucun
*/
static void Diviser_Par_Deux( Classe_Entier quotient,
                              Classe_Entier entier );

/******************************************************************************/
/* Gerer_Infini
Description :
Parametres :
Retour :
    1 si entier_1 ou entier_2 vaut + ou - infini
*/
static int Gerer_Infini( Classe_Entier resultat,
                         Classe_Entier entier_1,
                         Classe_Entier entier_2 );

/******************************************************************************/
/* Sommer_Chiffres
Description :
Parametres :
Retour :
    aucun
*/
static void Sommer_Chiffres( Classe_Entier resultat, uint32_t nombre );

/******************************************************************************/



/******************************************************************************/
/* Definition des methodes publiques */
/******************************************************************************/
Classe_Entier ENTIER_Creer_Nul( void )
{
    Classe_Entier entier = NULL;
    entier = (Classe_Entier)malloc( sizeof( _classe_entier ) );
    if( entier != NULL )
    {
        Annuler( entier );
    }
    return entier;
}
/******************************************************************************/
Classe_Entier ENTIER_Creer_De_Nombre( int32_t nombre )
{
    Classe_Entier entier = NULL; /* entier retourne */

    entier = ENTIER_Creer_Nul();
    if( entier == NULL )
    {
        /* si la creation echoue, retourne NULL */
    }
    else
    {
        if( nombre<0 )
        {
            if( nombre > (int32_t)(-BASE) )
            {
                entier->signe = NEGATIF;
                entier->liste_rangs[0] = (uint32_t)(0-nombre);
            }
            else
            {
                /* Retourner NULL */
                ENTIER_Detruire( &entier );
            }
        }
        else if( nombre < (int32_t)BASE )
        {
            entier->liste_rangs[0] = (uint32_t)nombre;
        }
        else
        {
            /* Retourner NULL */
            ENTIER_Detruire( &entier );
        }
    }
    return entier;
}
/******************************************************************************/
Classe_Entier ENTIER_Creer_De_Chaine( const char* chaine_entiers )
{
    Classe_Entier entier = NULL; /* entier retourne */
    type_signe signe = INVALIDE;
    uint16_t nb_chiffres;
    uint16_t nb_rangs; /* va de 1 a RANG_MAXIMUM */
    uint16_t id_rang;
    size_t nb_chiff_dern_rg; /* dernier rang = puissance la + elevee */
    size_t decalage;

    /* Verifier la validite de la chaine */
    signe = Verifier_Chaine_Entier( chaine_entiers );
    if( signe==INVALIDE )
    {
        /* retourne NULL */
    }
    else /* la chaine est valide */
    {
        /* Creation de l'entier */
        entier = ENTIER_Creer_Nul();
        if( entier == NULL )
        {
            /* si la creation echoue, retourne NULL */
        }
        else
        {
            /* Valoriser signe */
            entier->signe = signe;

            /* Calcul du nombre de rangs */
            nb_chiffres = (uint16_t)strlen( chaine_entiers ) - 1;
            nb_rangs = (nb_chiffres-1)/NB_CHIFFRES_PAR_RANG + 1;

            /* Valorisation des rangs de l'entier */
            /*  Attention nb_rangs va de 1 à RANG_MAXIMUM alors que rg_util va
            de 0 a (RANG_MAXIMUM-1) */
            if( nb_rangs > RANG_MAXIMUM )
            {
                /* l'entier vaut l'infini */
                entier->rg_util = RANG_MAXIMUM;
            }
            else
            {
                /* Valoriser rg_util */
                entier->rg_util = nb_rangs - 1;

                /* Calcul du nombre de chiffres du dernier rang */
                if( entier->rg_util==0 )
                {
                    nb_chiff_dern_rg = nb_chiffres;
                }
                else
                {
                    nb_chiff_dern_rg = nb_chiffres % NB_CHIFFRES_PAR_RANG;
                    if( nb_chiff_dern_rg==0 )
                    {
                        nb_chiff_dern_rg = NB_CHIFFRES_PAR_RANG;
                    }
                }

                /* Trouver le nombre du rang le plus eleve */
                (entier->liste_rangs)[entier->rg_util] =
                                Convertir_Chaine_U32( &chaine_entiers[1],
                                                      nb_chiff_dern_rg );

                /* Trouver la valeur des autres rangs  */
                id_rang = entier->rg_util;
                if( id_rang!=0 )
                {
                    decalage = 1 + nb_chiff_dern_rg;
                    do
                    {
                        id_rang--;
                        (entier->liste_rangs)[id_rang] =
                                Convertir_Chaine_U32( &chaine_entiers[decalage],
                                                      NB_CHIFFRES_PAR_RANG );
                        decalage += NB_CHIFFRES_PAR_RANG;
                    } while( id_rang > 0 );
                }
                /* Gerer le cas ou chaine = "-0" */
                if( entier->rg_util==0 && (entier->liste_rangs)[0]==0 )
                {
                    entier->signe = POSITIF;
                }
            }
        }
    }
    return entier;
}
/******************************************************************************/
void ENTIER_Modifier_De_Chaine( Classe_Entier entier, const char* chaine )
{
    Classe_Entier tmp = NULL;
    if( entier!=NULL )
    {
        tmp = ENTIER_Creer_De_Chaine( chaine );
        if( tmp!=NULL )
        {
            ENTIER_Copier( tmp, entier );
            ENTIER_Detruire( &tmp );
        }
    }
}
/******************************************************************************/
Classe_Entier ENTIER_Lire_De_Ficher( FILE* fichier )
{
    Classe_Entier entier = NULL;
    char chaine[NB_CHIFFRES_MAX+2];
    int nb_caractere_lu;
    if( fichier!=NULL )
    {
        nb_caractere_lu = fscanf( fichier, "%s", chaine);
        if( nb_caractere_lu > 0 )
        {
            entier = ENTIER_Creer_De_Chaine( chaine );
        }
        else
        {
            /* retourner NULL */
        }
    }
    return entier;
}
/******************************************************************************/
void ENTIER_Detruire( Classe_Entier* p_entier )
{
    /* Tester l'adresse de l'entier */
    if( p_entier!=NULL )
    {
        /* Tester l'entier */
        if( *p_entier!=NULL )
        {
            /* Mettre a zero de la memoire allouee a l'entier */
            memset( *p_entier, 0, sizeof( _classe_entier ) );
            /* Liberer l'entier */
            free( *p_entier );
            *p_entier = NULL;
        }
    }
}
/******************************************************************************/
void ENTIER_Ecrire_Fichier( FILE* fichier, Classe_Entier entier )
{
    uint16_t idx_rang = 0;

    if( fichier!=NULL )
    {
        if( entier == NULL )
        {
            fprintf( fichier, "entier invalide" );
        }
        else
        {
            if( entier->signe==POSITIF )
            {
               fprintf( fichier, "+" );
            }
            else
            {
                fprintf( fichier, "-" );
            }
            idx_rang = entier->rg_util;
            if( idx_rang==RANG_MAXIMUM )
            {
                fprintf( fichier, "inf" );
            }
            else
            {
                /* Ecriture du premier rang */
                /* le premier rang est ecrit sans 0 "a gauche" */
                fprintf( fichier, "%u", (entier->liste_rangs)[idx_rang] );

                /* Ecriture des rangs suivants */
                if( idx_rang!=0 )
                {
                    do
                    {
                        idx_rang--;
                        /* Ecriture des rangs suivants */
                        /* "0" ajoutes pour toujours ecrire NB_CHIFFRES_PAR_RANG
                        chiffres */
                        fprintf( fichier, "%0"NB_CHIFFRES_PAR_RANG_CH"u",
                                 (entier->liste_rangs)[idx_rang] );
                    } while( idx_rang > 0 );
                }
            }
        }
    }
}
/******************************************************************************/
void ENTIER_Afficher_Console( Classe_Entier entier )
{
    ENTIER_Ecrire_Fichier( stdout, entier );
    printf( "\n" );
}
/******************************************************************************/
void ENTIER_Copier( Classe_Entier original, Classe_Entier copie )
{
    memcpy( copie, original, sizeof( _classe_entier ) );
}
/******************************************************************************/
int ENTIER_Est_Egal( Classe_Entier entier, Classe_Entier entier_compare )
{
    int est_egal = 1;
    uint16_t rang = entier->rg_util + 1;
    if( entier!=NULL && entier_compare!=NULL )
    {
        if(    ( entier->rg_util == entier_compare->rg_util )
            && ( entier->signe == entier_compare->signe )
            && ( entier->rg_util != RANG_MAXIMUM )
          )
        {
            do
            {
                rang--;
                if(   ((entier->liste_rangs)[rang])
                   != ((entier_compare->liste_rangs)[rang])
                  )
                {
                    est_egal = 0;
                }
            } while( est_egal==1 && rang>0 );
        }
         else
        {
            est_egal = 0;
        }
    }
    else
    {
        est_egal = 0;
    }
    return est_egal;
}
/******************************************************************************/
int ENTIER_Est_Superieur( Classe_Entier entier, Classe_Entier entier_compare )
{
    int est_plus_grand = 1;
    int comparaison_terminee = 0;
    uint16_t idx_rang = entier->rg_util + 1;

    if( entier!=NULL && entier_compare!=NULL )
    {
        if( entier->signe==POSITIF && entier_compare->signe==POSITIF )
        {
            if( entier->rg_util == RANG_MAXIMUM
                && entier_compare->rg_util == RANG_MAXIMUM )
            {
                est_plus_grand = 0; /* on ne compare pas l'infini */
            }
            else if( entier->rg_util > entier_compare->rg_util )
            {
                est_plus_grand = 1;
            }
            else if( entier->rg_util < entier_compare->rg_util )
            {
                est_plus_grand = 0;
            }
            else /*le nombre de rangs utilises est le meme */
            {
                do
                {
                    idx_rang--;
                    if( entier->liste_rangs[idx_rang] >
                                    entier_compare->liste_rangs[idx_rang] )
                    {
                        est_plus_grand = 1;
                        comparaison_terminee = 1;
                    }
                    else if( entier->liste_rangs[idx_rang] ==
                                    entier_compare->liste_rangs[idx_rang] )
                    {
                        /* continuer */
                    }
                    else
                    {
                        est_plus_grand = 0;
                        comparaison_terminee = 1;
                    }

                }while( comparaison_terminee==0 && idx_rang>0 );
            }
        }
        else if( entier->signe==NEGATIF && entier_compare->signe==POSITIF )
        {
            est_plus_grand = 0;
        }
        else if( entier->signe==POSITIF && entier_compare->signe==NEGATIF )
        {
            est_plus_grand = 1;
        }
        else if( entier->signe==NEGATIF && entier_compare->signe==NEGATIF )
        {
            entier->signe = POSITIF;
            entier_compare->signe = POSITIF;
            est_plus_grand = ENTIER_Est_Superieur( entier_compare, entier );
            entier->signe = NEGATIF;
            entier_compare->signe = NEGATIF;
        }
    }
    else
    {
        est_plus_grand = 0;
    }
    return est_plus_grand;
}
/******************************************************************************/
int ENTIER_Est_Inferieur( Classe_Entier entier, Classe_Entier entier_compare )
{
   int est_plus_petit = 1;
    int comparaison_terminee = 0;
    uint16_t idx_rang = entier->rg_util + 1;

    if( entier!=NULL && entier_compare!=NULL )
    {
        if( entier->signe==POSITIF && entier_compare->signe==POSITIF )
        {
            if( entier->rg_util == RANG_MAXIMUM
                && entier_compare->rg_util == RANG_MAXIMUM )
            {
                est_plus_petit = 0; /* on ne compare pas l'infini */
            }
            else if( entier->rg_util < entier_compare->rg_util )
            {
                est_plus_petit = 1;
            }
            else if( entier->rg_util > entier_compare->rg_util )
            {
                est_plus_petit = 0;
            }
            else /*le nombre de rangs utilises est le meme */
            {
                do
                {
                    idx_rang--;
                    if( entier->liste_rangs[idx_rang] <
                                    entier_compare->liste_rangs[idx_rang] )
                    {
                        est_plus_petit = 1;

                        comparaison_terminee = 1;
                    }
                    else if( entier->liste_rangs[idx_rang] ==
                                    entier_compare->liste_rangs[idx_rang] )
                    {
                        /* continuer */
                    }
                    else
                    {
                        est_plus_petit = 0;

                        comparaison_terminee = 1;
                    }

                }while( comparaison_terminee==0 && idx_rang>0 );
            }
        }
        else if( entier->signe==NEGATIF && entier_compare->signe==POSITIF )
        {
            est_plus_petit = 1;
        }
        else if( entier->signe==POSITIF && entier_compare->signe==NEGATIF )
        {
            est_plus_petit = 0;
        }
        else if( entier->signe==NEGATIF && entier_compare->signe==NEGATIF )
        {
            entier->signe = POSITIF;
            entier_compare->signe = POSITIF;
            est_plus_petit = ENTIER_Est_Inferieur( entier_compare, entier );
            entier->signe = NEGATIF;
            entier_compare->signe = NEGATIF;
        }
    }
    else
    {
        est_plus_petit = 0;
    }
    return est_plus_petit;
}
/******************************************************************************/
int ENTIER_Est_Strict_Sup( Classe_Entier entier, Classe_Entier entier_compare )
{
    int est_strict_sup = 1;
    if( entier!=NULL && entier_compare!=NULL )
    {
        /* a > b <=> !( a<=b), sauf pour l'infini */
        if( entier->rg_util == RANG_MAXIMUM
            && entier_compare->rg_util == RANG_MAXIMUM
            && entier->signe == entier_compare->signe )
        {
            est_strict_sup = 0;
        }
        else if( ENTIER_Est_Inferieur( entier, entier_compare ) )
        {
            est_strict_sup = 0;
        }
    }
    return est_strict_sup;
}
/******************************************************************************/
int ENTIER_Est_Strict_Inf( Classe_Entier entier, Classe_Entier entier_compare )
{
    int est_strict_inf = 1;
    if( entier!=NULL && entier_compare!=NULL )
    {
        /* a < b <=> !( a>=b), sauf pour l'infini */
        if( entier->rg_util == RANG_MAXIMUM
            && entier_compare->rg_util == RANG_MAXIMUM
            && entier->signe == entier_compare->signe )
        {
            est_strict_inf = 0;
        }
        else if( ENTIER_Est_Superieur( entier, entier_compare ) )
        {
            est_strict_inf = 0;
        }
    }
    return est_strict_inf;
}
/******************************************************************************/
void ENTIER_Ajouter( Classe_Entier resultat,
                     Classe_Entier entier_1,
                     Classe_Entier entier_2 )
{
    if( resultat!=NULL && entier_1!=NULL && entier_2!=NULL )
    {
        if( Gerer_Infini( resultat, entier_1, entier_2 ) )
        {
            /* resultat vaut + ou - inf */
        }
        else if( entier_1->signe==POSITIF && entier_2->signe==POSITIF )
        {
            Ajouter_Rangs( resultat, entier_1, entier_2 );
            resultat->signe = POSITIF;
        }
        else if( entier_1->signe==NEGATIF && entier_2->signe==NEGATIF )
        {
            Ajouter_Rangs( resultat, entier_1, entier_2 );
            resultat->signe = NEGATIF;
        }
        else if( entier_1->signe==POSITIF && entier_2->signe==NEGATIF )
        {
            entier_2->signe = POSITIF;
            ENTIER_Soustraire( resultat, entier_1, entier_2 );
            entier_2->signe = NEGATIF;
        }
        else /* entier_1->signe==NEGATIF && entier_2->signe==POSITIF */
        {
            entier_1->signe = POSITIF;
            ENTIER_Soustraire( resultat, entier_2, entier_1 );
            entier_1->signe = NEGATIF;
        }
    }
}
/******************************************************************************/
void ENTIER_Incrementer( Classe_Entier resultat, Classe_Entier increment )
{
    _classe_entier copie;
    ENTIER_Copier( resultat, &copie );
    ENTIER_Ajouter( resultat, &copie, increment );
}
/******************************************************************************/
void ENTIER_Soustraire( Classe_Entier resultat,
                        Classe_Entier entier_1,
                        Classe_Entier entier_2 )
{
    if( resultat!=NULL && entier_1!=NULL && entier_2!=NULL )
    {
        if( Gerer_Infini( resultat, entier_1, entier_2 ) )
        {
            /* resultat vaut + ou - inf */
        }
        else if( entier_1->signe==POSITIF && entier_2->signe==POSITIF )
        {
            if( ENTIER_Est_Superieur( entier_1, entier_2 ) )
            {
                Soustraire_Rangs( resultat, entier_1, entier_2 );
            }
            else
            {
                Soustraire_Rangs( resultat, entier_2, entier_1 );
                resultat->signe = NEGATIF;
            }
        }
        else if( entier_1->signe==NEGATIF && entier_2->signe==NEGATIF )
        {
            entier_1->signe = POSITIF;
            entier_2->signe = POSITIF;
            ENTIER_Soustraire( resultat, entier_2, entier_1 );
            entier_1->signe = NEGATIF;
            entier_2->signe = NEGATIF;
        }
        else if( entier_1->signe==POSITIF && entier_2->signe==NEGATIF )
        {
            entier_2->signe = POSITIF;
            Ajouter_Rangs( resultat, entier_2, entier_1 );
            resultat->signe = POSITIF;
            entier_2->signe = NEGATIF;
        }
        else /* entier_1->signe==NEGATIF && entier_2->signe==POSITIF */
        {
            entier_1->signe = POSITIF;
            Ajouter_Rangs( resultat, entier_1, entier_2 );
            resultat->signe = NEGATIF;
            entier_1->signe = NEGATIF;
        }
    }
}
/******************************************************************************/
void ENTIER_Decrementer( Classe_Entier resultat, Classe_Entier decrement )
{
    _classe_entier copie;
    ENTIER_Copier( resultat, &copie );
    ENTIER_Soustraire( resultat, &copie, decrement );
}
/******************************************************************************/
void ENTIER_Multiplier( Classe_Entier resultat,
                        Classe_Entier entier_1,
                        Classe_Entier entier_2 )
{
    _classe_entier retenue;
    _classe_entier cofacteurs;
    _classe_entier tmp;
    uint16_t rang;
    uint32_t rg_le_plus_haut_min_du_res; /* uint32_t pour eviter depassement */

    if( resultat==NULL || entier_1==NULL || entier_2==NULL )
    {
        /* ne rien faire */
    }
    else if( ENTIER_Est_Nul( entier_1 ) || ENTIER_Est_Nul( entier_2 ) )
    {
        Annuler( resultat );
    }
    else
    {

        Annuler( &retenue );
        Annuler( &cofacteurs );
        Annuler( &tmp );

        /* Calcul du signe du resultat */
        resultat->signe = Calculer_Signe_Res_Mul_Div( entier_1, entier_2 );

        /* Calcul du rang le plus haut (au moins) */
        rg_le_plus_haut_min_du_res = (entier_1->rg_util + entier_2->rg_util);

        if( rg_le_plus_haut_min_du_res>RANG_MAXIMUM )
        {
            /* le resultat est l'infini */
            resultat->rg_util = RANG_MAXIMUM;
        }
        else
        {
            for( rang=0; rang<=rg_le_plus_haut_min_du_res ; rang++ )
            {
                Calculer_Somme_Cofacteurs( &cofacteurs,
                                                     entier_1, entier_2, rang );
                Ajouter_Rangs( &tmp, &cofacteurs, &retenue);
                resultat->liste_rangs[rang] = tmp.liste_rangs[0];
                Decaler_Rang( &retenue, &tmp, 1 );
            }
            resultat->rg_util = (uint16_t)rg_le_plus_haut_min_du_res;
            if( !ENTIER_Est_Nul( &retenue ) )
            {
                if( (retenue.rg_util + resultat->rg_util) < RANG_MAXIMUM )
                {
                    resultat->rg_util++;
                    for( rang=0 ; rang<=retenue.rg_util ; rang++ )
                    {
                        (resultat->liste_rangs)[(resultat->rg_util + rang)] =
                                                     retenue.liste_rangs[rang];
                    }
                    resultat->rg_util = resultat->rg_util + retenue.rg_util;
                }
                else
                {
                    /* le resultat est l'infini */
                    resultat->rg_util = RANG_MAXIMUM;
                }
            }
        }
    }
}
/******************************************************************************/
int ENTIER_Est_Nul( Classe_Entier entier )
{
    int resultat = 0;
    if( entier!=NULL )
    {
        if( entier->rg_util==0 && (entier->liste_rangs)[0]==0 )
        {
            resultat = 1;
        }
    }
    return resultat;
}
/******************************************************************************/
void ENTIER_Diviser( Classe_Entier quotient,
                     Classe_Entier reste,
                     Classe_Entier dividende,
                     Classe_Entier diviseur )
{
    type_signe signe_dividende = dividende->signe;
    type_signe signe_diviseur = diviseur->signe;

    if( quotient!=NULL && reste!=NULL && dividende!=NULL && diviseur!=NULL )
    {
        Annuler( quotient );
        Annuler( reste );

        if( ENTIER_Est_Nul( diviseur ) )
        {
            /* quotient = infini, reste = 0 */
            quotient->rg_util = RANG_MAXIMUM;
        }
        else if( (dividende->rg_util)==RANG_MAXIMUM )
        {
            /* infini / x = infini, reste = 0 */
            quotient->rg_util = RANG_MAXIMUM;
        }
        else if( (diviseur->rg_util)==RANG_MAXIMUM )
        {
            /* x / infini = 0 */
            /* quotient = 0, reste = dividende */
            ENTIER_Copier( dividende, reste );
        }
        else
        {
            dividende->signe = POSITIF;
            diviseur->signe = POSITIF;
            Diviser_Entier_Positifs( quotient, reste, dividende, diviseur );
            dividende->signe = signe_dividende;
            diviseur->signe = signe_diviseur;
        }

        /* Calcul du signe du quotient */
        if( ENTIER_Est_Nul( quotient ) )
        {
            quotient->signe = POSITIF; /* +0 */
            reste->signe = dividende->signe; /* reste = dividende */
        }
        else
        {
            quotient->signe = Calculer_Signe_Res_Mul_Div( dividende, diviseur );
        }
    }
}
/******************************************************************************/
void ENTIER_Racine_Carree( Classe_Entier resultat, Classe_Entier entier )
{
    /** On utilise l'algorithme de Heron
        resultat est la convergence de la suite :
                    1 (                      entier     )
        resultat =  - ( resultat_prec + --------------- )
                    2 (                  resultat_prec  )
    **/
    _classe_entier tampon;
    _classe_entier resultat_prec;
    _classe_entier reste; /* ne sert pas */

    if( resultat!=NULL && entier!=NULL )
    {
        Annuler( resultat );
        if( entier->signe==POSITIF )
        {
            if( entier->rg_util==0 && entier->liste_rangs[0]==1 )
            {
                resultat->liste_rangs[0] = 1;
            }
            else if( entier->rg_util==RANG_MAXIMUM  )
            {
                resultat->rg_util = RANG_MAXIMUM;
            }
            else
            {
                /* Initialisation des elements */
                Annuler( &tampon );

                Diviser_Par_Deux( resultat, entier );
                ENTIER_Copier( entier, &resultat_prec );
                while( ENTIER_Est_Strict_Inf( resultat, &resultat_prec) )
                {
                    /* resultat_prec = resultat */
                    ENTIER_Copier( resultat, &resultat_prec );

                    /* resultat = ( resultat + entier / resultat) / 2 */
                    ENTIER_Diviser( &tampon, &reste, entier, resultat );
                    ENTIER_Incrementer( &tampon, resultat );
                    Diviser_Par_Deux( resultat, &tampon );
                }
                ENTIER_Copier( &resultat_prec, resultat );
            }
        }
        else
        {
            /* entier < 0 */
            /* Annuler resultat */
        }
    }
}
/******************************************************************************/
void ENTIER_Puissance( Classe_Entier resultat,
                       Classe_Entier entier,
                       Classe_Entier puissance )
{
    Classe_Liste lst_p_deux = NULL;
    Classe_Liste lst_entier_p = NULL;
    Classe_Entier p_deux = NULL;
    Classe_Entier entier_p = NULL;
    _classe_entier tmp;
    _classe_entier DEUX;
    _classe_entier somme_p_deux;

    if( resultat!=NULL && entier!=NULL && puissance!=NULL )
    {
        /* Initialiser variables locales */
        ENTIER_Modifier_De_Chaine( resultat, "+1" );
        lst_p_deux = LISTE_Creer();
        lst_entier_p = LISTE_Creer();
        Annuler( &DEUX );
        DEUX.liste_rangs[0] = 2;
        Annuler( &somme_p_deux );

        /* Construire liste de entier^(2n) */
        p_deux = ENTIER_Creer_De_Nombre( 1 );
        entier_p = ENTIER_Creer_Nul();
        ENTIER_Copier( entier, entier_p );
        while( ENTIER_Est_Inferieur( p_deux, puissance) )
        {
            LISTE_Ajouter_Elmt_Fin( lst_p_deux, p_deux );
            LISTE_Ajouter_Elmt_Fin( lst_entier_p, entier_p );

            /* entier_p = entier_p * entier_p */
            ENTIER_Copier( entier_p, &tmp );
            ENTIER_Multiplier( &tmp, entier_p, entier_p );
            entier_p = ENTIER_Creer_Nul();
            ENTIER_Copier( &tmp, entier_p );

            /* p_deux = p_deux * 2 */
            ENTIER_Multiplier( &tmp, p_deux, &DEUX );
            p_deux = ENTIER_Creer_Nul();
            ENTIER_Copier( &tmp, p_deux );
        }
        /* Supprimer entiers superflus */
        ENTIER_Detruire( &p_deux );
        ENTIER_Detruire( &entier_p );

        p_deux = LISTE_Lire_Dernier_Elmt( lst_p_deux );
        entier_p = LISTE_Lire_Dernier_Elmt( lst_entier_p );
        while( !ENTIER_Est_Egal( &somme_p_deux, puissance ) )
        {
            /* somme_p_deux += p_deux */
            ENTIER_Incrementer( &somme_p_deux, p_deux );

            /* si somme_p_deux <= puissance */
            if( ENTIER_Est_Inferieur( &somme_p_deux, puissance ) )
            {
                /* resultat = resultat * entier_p */
                ENTIER_Copier( resultat, &tmp );
                ENTIER_Multiplier( resultat, &tmp, entier_p );
            }
            /* si somme_p_deux > puissance */
            else
            {
                /* Annuler incrementation */
                ENTIER_Decrementer( &somme_p_deux, p_deux );

                /* Selectionner puissance suivante */
                p_deux = LISTE_Lire_Elmt_Precedant( lst_p_deux );
                entier_p = LISTE_Lire_Elmt_Precedant( lst_entier_p );
            }
        }
        /* Liberer memoire */
        ENTIER_Detruire_Liste( &lst_p_deux );
        ENTIER_Detruire_Liste( &lst_entier_p );
    }
}
/******************************************************************************/
void ENTIER_Factorielle( Classe_Entier resultat, Classe_Entier entier )
{
    /* Calculer n! = n*(n-1)* ... *3**2*1 */
    _classe_entier produit;
    _classe_entier facteur;
    _classe_entier UN;

    if( resultat!=NULL && entier!=NULL )
    {
        Annuler( resultat );
        Annuler( &produit );
        Annuler( &UN );
        UN.liste_rangs[0] = 1;

        /* n */
        ENTIER_Copier( entier, &produit );
        /* n-1 */
        ENTIER_Copier( entier, &facteur );
        ENTIER_Decrementer( &facteur, &UN );
        /* Tant que n-x different de 0 */
        while( !ENTIER_Est_Egal( &facteur, &UN ) )
        {
            ENTIER_Multiplier( resultat, &produit, &facteur );
            ENTIER_Copier( resultat, &produit );
            ENTIER_Decrementer( &facteur, &UN );
        }
    }
}
/******************************************************************************/
void ENTIER_Combinaison( Classe_Entier resultat,
                         Classe_Entier n,
                         Classe_Entier k )
{
    _classe_entier factorielle_n;
    _classe_entier factorielle_k;
    _classe_entier n_moins_k;
    _classe_entier factorielle_n_moins_k;
    _classe_entier tmp;
    _classe_entier reste;

    if( resultat!=NULL && n!=NULL && k!=NULL )
    {
        if( ENTIER_Est_Superieur( n, k) )
        {
            ENTIER_Factorielle( &factorielle_n, n );
            ENTIER_Factorielle( &factorielle_k, k );
            ENTIER_Soustraire( &n_moins_k, n, k );
            ENTIER_Factorielle( &factorielle_n_moins_k, &n_moins_k );
            ENTIER_Diviser( &tmp, &reste, &factorielle_n, &factorielle_k );
            ENTIER_Diviser( resultat, &reste, &tmp, &factorielle_n_moins_k );
        }
    }
}
/******************************************************************************/
void ENTIER_Sommer_Chiffres( Classe_Entier resultat, Classe_Entier entier )
{
    uint16_t rang;
    _classe_entier somme_rang;
    if( resultat!=NULL && entier!=NULL )
    {
        Annuler( resultat );
        if( entier->rg_util== RANG_MAXIMUM)
        {
            /* resulat = infini */
            resultat->rg_util = RANG_MAXIMUM;

            /* Signer le resultat */
            if( entier->signe==NEGATIF )
            {
                resultat->signe = NEGATIF;
            }
            else
            {
                /* resultat est positif */
            }
        }
        else
        {
            for( rang=0 ; rang<RANG_MAXIMUM ; rang++ )
            {
                Sommer_Chiffres( &somme_rang, entier->liste_rangs[rang] );
                ENTIER_Incrementer( resultat, &somme_rang );
            }
        }
    }
}
/******************************************************************************/
uint32_t ENTIER_Convertir( Classe_Entier entier )
{
    uint32_t resultat = 0;
    if( entier!=NULL )
    {
        if( entier->signe==POSITIF && entier->rg_util==0 )
        {
            resultat = (entier->liste_rangs)[0];
        }
    }
    return resultat;
}
/******************************************************************************/
int ENTIER_Est_Plus_Infini( Classe_Entier entier )
{
    int est_p_inf = 0;
    if( entier!=NULL )
    {
        if( entier->rg_util==RANG_MAXIMUM && entier->signe==POSITIF )
        {
            est_p_inf = 1;
        }
    }
    return est_p_inf;
}
/******************************************************************************/






/******************************************************************************/
/* Definition des fonctions privees */
/******************************************************************************/
static void Annuler( Classe_Entier entier )
{
    if( entier!=NULL )
    {
        memset( entier, 0, sizeof( _classe_entier ) );
        entier->signe = POSITIF;
    }
}
/******************************************************************************/
static type_signe Verifier_Chaine_Entier( const char* const chaine )
{
    type_signe signe = INVALIDE;
    size_t nb_caracteres = 0;
    size_t id_chiff = 0;
    if( chaine==NULL )
    {
        /* retourne INVALIDE */
    }
    else
    {
        nb_caracteres = strlen( chaine );
        if( nb_caracteres < 2 )
        {
            /* retourne INVALIDE */
        }
        else /* nb_caracteres >= 2 */
        {
            /* Recherche du signe de l'entier */
            if( chaine[0]=='-' )
            {
                signe = NEGATIF;
            }
            else if( chaine[0]=='+' )
            {
                signe = POSITIF;
            }
            else
            {
                /* le premier caractere n'est ni '+' ni '-' */
                /* retourne INVALIDE */
            }
            if( signe != INVALIDE )
            {
                /* Tester si tous les caractere restants sont des chiffres */
                /* tant que la chaine contient un chiffre */
                id_chiff = 1;
                while( chaine[id_chiff] >= '0' && chaine[id_chiff] <= '9')
                {
                    /* on parcoure la chaine */
                    id_chiff++;
                }
                /* si on n'a pas atteint la fin de la chaine */
                if( id_chiff!=nb_caracteres )
                {
                    /* retourne INVALIDE */
                    signe = INVALIDE;
                }
                else
                {
                    /* retourne signe calcule precedement */
                }
            }
        }
    }
    return signe;
}
/******************************************************************************/
static uint32_t Convertir_Chaine_U32( const char* chaine, size_t nb_chiffre )
{
    uint32_t resultat;
    char* p_bidon; /* non utilise, necessaire pour strtol */
    char chaine_tmp[NB_CHIFFRES_PAR_RANG] = {0};

    memcpy( chaine_tmp, chaine, nb_chiffre );
    resultat = (uint32_t)strtol( chaine_tmp, &p_bidon, 10 );
    return resultat;
}
/******************************************************************************/
static void Ajouter_Rangs( Classe_Entier resultat,
                           Classe_Entier entier_1,
                           Classe_Entier entier_2 )
{
    uint16_t rang_utilise_max;
    uint16_t idx_rang;
    uint32_t tampon;
    uint32_t retenue = 0;

    Annuler( resultat );

    /* Trouver le plus grand rg_util des deux operandes */
    if( entier_1->rg_util > entier_2->rg_util )
    {
        rang_utilise_max = entier_1->rg_util;
    }
    else
    {
        rang_utilise_max = entier_2->rg_util;
    }

    /* Ajouter rangs */
    for( idx_rang=0 ; idx_rang<=rang_utilise_max ; idx_rang++ )
    {
        tampon = (entier_1->liste_rangs)[idx_rang]
             + (entier_2->liste_rangs)[idx_rang]
            + retenue;
        if( tampon >= BASE )
        {
            tampon-=BASE;
            retenue = 1;
        }
        else
        {
            retenue = 0;
        }
        (resultat->liste_rangs)[idx_rang] = tampon;
    }

    /* Gerer la retenue */
    if( retenue==1 )
    {
        rang_utilise_max = rang_utilise_max + 1;
        if( rang_utilise_max >= RANG_MAXIMUM )
        {
            /* resultat vaut infini */
            resultat->rg_util = RANG_MAXIMUM;
        }
        else
        {
            (resultat->liste_rangs)[rang_utilise_max] = 1;
            resultat->rg_util = rang_utilise_max;
        }
    }
    else
    {
        resultat->rg_util = rang_utilise_max;
    }

    /* Remplir les rangs non utilises avec des 0 */
    for( idx_rang = (rang_utilise_max+1) ; idx_rang<RANG_MAXIMUM ; idx_rang++ )
    {
        (resultat->liste_rangs)[idx_rang] = 0;
    }
}
/******************************************************************************/
static void Soustraire_Rangs( Classe_Entier resultat,
                              Classe_Entier entier_1,
                              Classe_Entier entier_2 )
{
    uint16_t rang_utilise_max;
    uint16_t idx_rang;
    uint32_t tampon;
    uint32_t retenue = 0;
    uint32_t tmp1;
    uint32_t tmp2;

    Annuler( resultat );

    /* Trouver le plus grand rg_util des deux operandes */
    if( entier_1->rg_util > entier_2->rg_util )
    {
        rang_utilise_max = entier_1->rg_util;
    }
    else
    {
        rang_utilise_max = entier_2->rg_util;
    }
    resultat->rg_util = rang_utilise_max;

    /* Soustraires les rangs */
    for( idx_rang=0 ; idx_rang<=rang_utilise_max ; idx_rang++ )
    {
        tmp1 = (entier_1->liste_rangs)[idx_rang];
        tmp2 = (entier_2->liste_rangs)[idx_rang] + retenue;


        if( tmp1 >= tmp2 )
        {
            tampon = tmp1 - tmp2;
            retenue = 0;
        }
        else
        {
            tampon = BASE - ( tmp2 - tmp1 );
            retenue = 1;
        }
        (resultat->liste_rangs)[idx_rang] = tampon;
    }

    /* Recherche du nombre de rang utilise = suppression des '0' de tete */
    tampon = resultat->liste_rangs[resultat->rg_util];
    while( tampon==0 && resultat->rg_util>0 )
    {
       (resultat->rg_util)--;
       tampon = resultat->liste_rangs[resultat->rg_util];
    }

}
/******************************************************************************/
static type_signe Calculer_Signe_Res_Mul_Div( Classe_Entier entier_1,
                                              Classe_Entier entier_2 )
{
    type_signe signe;
    if( entier_1->signe==entier_2->signe )
    {
        signe = POSITIF;
    }
    else
    {
        signe = NEGATIF;
    }
    return signe;
}
/******************************************************************************/
static void Calculer_Somme_Cofacteurs( Classe_Entier resultat,
                                       Classe_Entier entier_1,
                                       Classe_Entier entier_2,
                                       uint16_t rang )
{
    uint16_t rang_1;
    uint16_t rang_2;
    uint64_t tampon;
    _classe_entier entier_tmp;

    Annuler( resultat );
    Annuler( &entier_tmp );
    if( rang<=RANG_MAXIMUM )
    {
        for( rang_1=0 ; rang_1<=rang ; rang_1++ )
        {
            rang_2 = rang - rang_1;
            if( ( rang_1<=(entier_1->rg_util) ) &&
                                     ( rang_2<=(entier_2->rg_util) ) )
            {
                tampon = (uint64_t)(entier_1->liste_rangs[rang_1])
                    * (uint64_t)(entier_2->liste_rangs[rang_2]);
                if( tampon >= (uint64_t)BASE )
                {
                    entier_tmp.rg_util = 1;
                    (entier_tmp.liste_rangs)[0] = (uint32_t)(tampon%BASE);
                    (entier_tmp.liste_rangs)[1] = (uint32_t)(tampon/BASE);
                }
                else
                {
                    entier_tmp.rg_util  = 0;
                    (entier_tmp.liste_rangs)[0] = (uint32_t)tampon;
                    (entier_tmp.liste_rangs)[1] = 0;
                }
                /* resultat = resultat + entier_tmp */
                ENTIER_Incrementer( resultat, &entier_tmp );
            }
        }
    }
}
/******************************************************************************/
static void Decaler_Rang( Classe_Entier resultat,
                          Classe_Entier entier,
                          uint16_t decalage )
{
   uint16_t rg;

    Annuler( resultat );
   resultat->signe = entier->signe;
   if( decalage == 0 )
   {
       /* resulat = entier */
       ENTIER_Copier( entier, resultat );
   }
   else if( decalage >= (entier->rg_util +1 ) )
   {
        /* resultat = 0 */
   }
   else
   {
      resultat->rg_util = (entier->rg_util - decalage);
      for( rg=0; rg<=resultat->rg_util; rg++ )
      {
         (resultat->liste_rangs)[rg] = (entier->liste_rangs)[rg+decalage];
      }
   }
}
/******************************************************************************/
static void Diviser_Entier_Positifs( Classe_Entier quotient,
                                     Classe_Entier reste,
                                     Classe_Entier dividende,
                                     Classe_Entier diviseur )
{
    Classe_Liste l_p_deux = LISTE_Creer(); /* liste puissances de 2 */
    Classe_Liste l_minorants = LISTE_Creer(); /* liste minorants */
    Classe_Entier minorant = ENTIER_Creer_Nul(); /* 2^n * diviseur */
    Classe_Entier p_deux = ENTIER_Creer_Nul(); /* puissance de 2 */
    Classe_Entier p_deux_tmp = ENTIER_Creer_Nul();
    _classe_entier deux; /* = 2 */
    _classe_entier reste_tmp;

    Annuler( &deux );
    Annuler( &reste_tmp );

    /* Initialiser quotient et reste de la division */
    Annuler( quotient );
    ENTIER_Copier( dividende, reste );

    /* Initialiser liste des minorants */
    ENTIER_Copier( diviseur, minorant ); /* diviseur * 2^0 */
    LISTE_Ajouter_Elmt_Debut( l_minorants, minorant );

    /* Initialiser liste des puissances de deux */
    deux.liste_rangs[0] = 2;
    p_deux->liste_rangs[0] = 1; /* 2^0 */
    ENTIER_Copier( p_deux, p_deux_tmp );
    LISTE_Ajouter_Elmt_Debut( l_p_deux, p_deux_tmp );

    /* Construire la liste des minorants et des puissances de deux */
    /* Tant que le minorant <= dividende */
    while( ENTIER_Est_Inferieur( minorant, dividende ) )
    {
        /* p_deux = p_deux * 2 */
        p_deux_tmp = ENTIER_Creer_Nul();
        ENTIER_Multiplier( p_deux_tmp, p_deux, &deux );
        ENTIER_Copier( p_deux_tmp, p_deux );
        LISTE_Ajouter_Elmt_Debut( l_p_deux, p_deux_tmp );

        /* minorant = minorant * p_deux */
        minorant = ENTIER_Creer_Nul();
        ENTIER_Multiplier( minorant, diviseur, p_deux );
        LISTE_Ajouter_Elmt_Debut( l_minorants, minorant );
    }


    /* Parcourir la liste pour claculer quotient et reste */
    /* le premier element n'est pas utile, on repart du deuxieme */
    LISTE_Lire_Premier_Elmt( l_p_deux );
    p_deux_tmp = LISTE_Lire_Elmt_Suivant( l_p_deux );
    LISTE_Lire_Premier_Elmt( l_minorants );
    minorant = LISTE_Lire_Elmt_Suivant( l_minorants );

    /* tant qu'il y des elements dans la liste */
    while( minorant!=NULL )
    {
        /* Si reste > minorant */
        if( ENTIER_Est_Superieur( reste, minorant ) )
        {
            /* quotient = quotient + p_deux */
            ENTIER_Incrementer( quotient, p_deux_tmp );

            /* reste = reste - minorant */
            ENTIER_Decrementer( reste, minorant );

        }
        p_deux_tmp = LISTE_Lire_Elmt_Suivant( l_p_deux );
        minorant = LISTE_Lire_Elmt_Suivant( l_minorants );
    }

    /* Detruire les elements alloue dynamiquement */
    ENTIER_Detruire( &p_deux );
    ENTIER_Detruire_Liste( &l_p_deux );
    ENTIER_Detruire_Liste( &l_minorants );
}
/******************************************************************************/
static void Diviser_Par_Deux( Classe_Entier resultat,
                              Classe_Entier entier )
{
   int32_t rang = entier->rg_util;
   uint32_t dividende;
   uint32_t quotient;
   uint32_t retenue = 0;

    Annuler( resultat );
   if( entier!=NULL )
   {
      while( rang>=0 )
      {
         dividende = (retenue*BASE) + entier->liste_rangs[rang];
         quotient = dividende / 2;
         retenue = dividende % 2;
         resultat->liste_rangs[rang] = quotient;
         rang--;
      }
      resultat->rg_util = entier->rg_util;

      /* on supprime un eventuel 0 (si le premier élément du tableau de
           entier valait 1) */
      if(resultat->liste_rangs[resultat->rg_util]==0 && resultat->rg_util!=0)
      {
         resultat->rg_util--;
      }
   }
}
/******************************************************************************/
static int Gerer_Infini( Classe_Entier resultat,
                         Classe_Entier entier_1,
                         Classe_Entier entier_2 )
{
    int est_infini = 0;
    Annuler( resultat );
    if( entier_1->rg_util==RANG_MAXIMUM )
    {
        resultat->rg_util = RANG_MAXIMUM;
        resultat->signe = entier_1->signe;
        est_infini = 1;
    }
    else if( entier_2->rg_util==RANG_MAXIMUM )
    {
        resultat->rg_util = RANG_MAXIMUM;
        resultat->signe = entier_2->signe;
        est_infini = 1;
    }
    return est_infini;
}
/******************************************************************************/
static void Sommer_Chiffres( Classe_Entier resultat, uint32_t nombre )
{
    /* resultat est <= 9*NB_CHIFFRES_PAR_RANG donc seul 1 rang est nécessaire */
    uint16_t id_chiffre;
    uint32_t modulo = BASE;
    uint32_t diviseur = BASE/10;
    if( resultat!=NULL )
    {
        Annuler( resultat );

        for( id_chiffre=0;  id_chiffre<NB_CHIFFRES_PAR_RANG; id_chiffre++ )
        {
            resultat->liste_rangs[0] += ( ( nombre % modulo )/ diviseur );
            modulo = diviseur;
            diviseur /= 10;
        }
    }
}
