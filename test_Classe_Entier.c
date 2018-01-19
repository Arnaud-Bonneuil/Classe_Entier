/******************************************************************************\
fichier : test_Classe_Entier.c

Les tests sont ecrits pour RANG_MAXIMUM = 2
\******************************************************************************/

#include <stdio.h> /* printf, getchar */
#include <stdlib.h> /* EXIT_SUCCESS */

#include "Classe_Entier.h"

//#define TEST

int main ( int argc, char *argv[] )
{
 #ifdef TEST

    Classe_Entier e_1 = NULL;
    Classe_Entier e_2 = NULL;
    Classe_Entier e_3 = NULL;
    Classe_Entier e_4 = NULL;
    Classe_Entier e_zero = NULL;
    Classe_Entier e_p_inf = NULL;
    Classe_Entier e_m_inf = NULL;
    Classe_Entier e_null = NULL;
    Classe_Liste liste_prm = NULL;
    Classe_Liste dec_fct_prm = NULL;

    int i;
    for (i=0; i < argc; i++)
    {
        printf("Argument %d : %s \n", i+1, argv[i]);
    }

    printf( "\nTests de la classe Classe_Entier\n\n" );

    /* ENTIER_Creer_Nul */
    printf( "\n** ENTIER_Creer_Nul **\n" );
    e_1 = ENTIER_Creer_Nul();
    printf( "e_1 = +0 ?\n" );
    printf( "e_1 = " );
    ENTIER_Afficher_Console( e_1 );

    /* ENTIER_Creer_De_Chaine */
    printf( "\n** ENTIER_Creer_De_Chaine **\n" );

    e_2 = ENTIER_Creer_De_Chaine( "+17" );
    printf( "e_2 = +17 ?\n" );
    printf( "e_2 = " );
    ENTIER_Afficher_Console( e_2 );

    e_3 = ENTIER_Creer_De_Chaine( "-100000089569" );
    printf( "e_3 = -100000089569 ?\n" );
    printf( "e_3 = " );
    ENTIER_Afficher_Console( e_3 );

    e_zero = ENTIER_Creer_De_Chaine( "-0" );
    printf( "e_zero= +0 ?\n" );
    printf( "e_zero= " );
    ENTIER_Afficher_Console( e_zero );

    e_null = ENTIER_Creer_De_Chaine( "-abc" );
    printf( "e_null est : NULL ?\n" );
    printf( "e_null est : %0X\n",(unsigned int) e_null );

    e_null = ENTIER_Creer_De_Chaine( "abc" );
    printf( "e_null est : NULL ?\n" );
    printf( "e_nullest : %0X\n", (unsigned int)e_null );

    e_null = ENTIER_Creer_De_Chaine( "25" );
    printf( "e_null est : NULL ?\n" );
    printf( "e_null est : %0X\n", (unsigned int)e_null );

    e_p_inf = ENTIER_Creer_De_Chaine( "+1000000000000000000" );
    printf( "e_p_inf = +inf ?\n" );
    printf( "e_p_inf = " );
    ENTIER_Afficher_Console( e_p_inf );

    e_m_inf = ENTIER_Creer_De_Chaine( "-1234567890000000000" );
    printf( "e_m_inf = -inf ?\n" );
    printf( "e_m_inf = " );
    ENTIER_Afficher_Console( e_m_inf );

    ENTIER_Detruire_Entier( &e_3 );
    e_3 = ENTIER_Creer_De_Chaine( "-999999999999999999" );
    printf( "e_3 = -999999999999999999 ?\n" );
    printf( "e_3 = " );
    ENTIER_Afficher_Console( e_3 );


    /* ENTIER_Detruire_Entier */
    printf( "\n** ENTIER_Detruire_Entier **\n" );
    ENTIER_Detruire_Entier( &e_1 );
    printf( "e1_ est : NULL ?\n" );
    printf( "e_1 est : %0X\n", (unsigned int)e_1 );
    printf( "e_1 = inavalide ?\n" );
    printf( "e_1 = " );
    ENTIER_Afficher_Console( e_1 );
    ENTIER_Detruire_Entier( &e_1 );

    /* ENTIER_Creer_De_Nombre */
    printf( "\n** ENTIER_Creer_De_Nombre **\n" );
    e_1 = ENTIER_Creer_De_Nombre( 5587496 );
    ENTIER_Afficher_Console( e_1 );
    ENTIER_Detruire_Entier( &e_1 );

    e_1 = ENTIER_Creer_De_Nombre( -5124578 );
    ENTIER_Afficher_Console( e_1 );
    ENTIER_Detruire_Entier( &e_1 );

    e_1 = ENTIER_Creer_De_Nombre( 999999998 );
    ENTIER_Afficher_Console( e_1 );
    ENTIER_Detruire_Entier( &e_1 );

    e_1 = ENTIER_Creer_De_Nombre( 999999999 );
    ENTIER_Afficher_Console( e_1 );
    ENTIER_Detruire_Entier( &e_1 );

    e_1 = ENTIER_Creer_De_Nombre( 1000000000 );
    ENTIER_Afficher_Console( e_1 );
    ENTIER_Detruire_Entier( &e_1 );

    e_1 = ENTIER_Creer_De_Nombre( 1234567890 );
    ENTIER_Afficher_Console( e_1 );
    ENTIER_Detruire_Entier( &e_1 );

    e_1 = ENTIER_Creer_De_Nombre( -999999998 );
    ENTIER_Afficher_Console( e_1 );
    ENTIER_Detruire_Entier( &e_1 );

    e_1 = ENTIER_Creer_De_Nombre( -999999999 );
    ENTIER_Afficher_Console( e_1 );
    ENTIER_Detruire_Entier( &e_1 );

    e_1 = ENTIER_Creer_De_Nombre( -1000000000 );
    ENTIER_Afficher_Console( e_1 );
    ENTIER_Detruire_Entier( &e_1 );

    e_1 = ENTIER_Creer_De_Nombre( -1234567890 );
    ENTIER_Afficher_Console( e_1 );
    ENTIER_Detruire_Entier( &e_1 );

    /* ENTIER_Modifier_De_Chaine */
    printf( "\n** ENTIER_Modifier_De_Chaine **\n" );
    e_1 = ENTIER_Creer_De_Chaine( "+17" );
    printf( "e1_ est : %0X ?\n", (unsigned int)e_1 );
    ENTIER_Modifier_De_Chaine( e_1, "+69" );
    printf( "e_1 est : %0X\n", (unsigned int)e_1 );
    printf( "e_1 = +69 ?\n" );
    printf( "e_1 = " );
    ENTIER_Afficher_Console( e_1 );


    /* ENTIER_Est_Egal */
    printf( "\n** ENTIER_Est_Egal **\n" );
    printf( "+17 == +69 ? %u\n", ENTIER_Est_Egal( e_2, e_1 ) );
    printf( "+17 == +17 ? %u\n", ENTIER_Est_Egal( e_2, e_2 ) );
    ENTIER_Modifier_De_Chaine( e_3, "+17" );
    printf( "+17 == +17 ? %u\n", ENTIER_Est_Egal( e_2, e_3 ) );
    ENTIER_Modifier_De_Chaine( e_3, "-17" );
    printf( "+17 == -17 ? %u\n", ENTIER_Est_Egal( e_2, e_3 ) );
    ENTIER_Modifier_De_Chaine( e_3, "+0" );
    printf( "+0 == +0 ? %u\n", ENTIER_Est_Egal( e_zero, e_3 ) );
    printf( "+inf == +inf ? %u\n", ENTIER_Est_Egal( e_p_inf, e_p_inf ) );
    printf( "-inf == -inf ? %u\n", ENTIER_Est_Egal( e_m_inf, e_m_inf ) );
    printf( "+inf == -inf ? %u\n", ENTIER_Est_Egal( e_p_inf, e_m_inf ) );

    /* ENTIER_Est_Superieur */
    printf( "\n** ENTIER_Est_Superieur **\n" );
    printf( "+17 >= +69 ? %u\n", ENTIER_Est_Superieur( e_2, e_1 ) );
    printf( "+17 >= +17 ? %u\n", ENTIER_Est_Superieur( e_2, e_2 ) );
    printf( "+69 >= +17 ? %u\n", ENTIER_Est_Superieur( e_1, e_2 ) );
    printf( "+0 >= +0 ? %u\n", ENTIER_Est_Superieur( e_zero, e_3 ) );
    printf( "+inf >= +inf ? %u\n", ENTIER_Est_Superieur( e_p_inf, e_p_inf ) );
    printf( "-inf >= -inf ? %u\n", ENTIER_Est_Superieur( e_m_inf, e_m_inf ) );
    printf( "+inf >= -inf ? %u\n", ENTIER_Est_Superieur( e_p_inf, e_m_inf ) );
    printf( "-inf >= +inf ? %u\n", ENTIER_Est_Superieur( e_m_inf, e_p_inf ) );


    /* ENTIER_Est_Inferieur */
    printf( "\n** ENTIER_Est_Inferieur **\n" );
    printf( "+17 <= +69 ? %u\n", ENTIER_Est_Inferieur( e_2, e_1 ) );
    printf( "+17 <= +17 ? %u\n", ENTIER_Est_Inferieur( e_2, e_2 ) );
    printf( "+69 <= +17 ? %u\n", ENTIER_Est_Inferieur( e_1, e_2 ) );
    printf( "+0 <= +0 ? %u\n", ENTIER_Est_Inferieur( e_zero, e_3 ) );
    printf( "+inf <= +inf ? %u\n", ENTIER_Est_Inferieur( e_p_inf, e_p_inf ) );
    printf( "-inf <= -inf ? %u\n", ENTIER_Est_Inferieur( e_m_inf, e_m_inf ) );
    printf( "+inf <= -inf ? %u\n", ENTIER_Est_Inferieur( e_p_inf, e_m_inf ) );
    printf( "-inf <= +inf ? %u\n", ENTIER_Est_Inferieur( e_m_inf, e_p_inf ) );


    /* ENTIER_Est_Strict_Inf */
    printf( "\n** ENTIER_Est_Strict_Inf **\n" );
    printf( "+17 < +69 ? %u\n", ENTIER_Est_Strict_Inf( e_2, e_1 ) );
    printf( "+17 < +17 ? %u\n", ENTIER_Est_Strict_Inf( e_2, e_2 ) );
    printf( "+69 < +17 ? %u\n", ENTIER_Est_Strict_Inf( e_1, e_2 ) );
    printf( "+0 < +0 ? %u\n", ENTIER_Est_Strict_Inf( e_zero, e_3 ) );
    printf( "+inf < +inf ? %u\n", ENTIER_Est_Strict_Inf( e_p_inf, e_p_inf ) );
    printf( "-inf < -inf ? %u\n", ENTIER_Est_Strict_Inf( e_m_inf, e_m_inf ) );
    printf( "+inf < -inf ? %u\n", ENTIER_Est_Strict_Inf( e_p_inf, e_m_inf ) );
    printf( "-inf < +inf ? %u\n", ENTIER_Est_Strict_Inf( e_m_inf, e_p_inf ) );


    /* ENTIER_Est_Strict_Sup */
    printf( "\n** ENTIER_Est_Strict_Sup **\n" );
    printf( "+17 > +69 ? %u\n", ENTIER_Est_Strict_Sup( e_2, e_1 ) );
    printf( "+17 > +17 ? %u\n", ENTIER_Est_Strict_Sup( e_2, e_2 ) );
    printf( "+69 > +17 ? %u\n", ENTIER_Est_Strict_Sup( e_1, e_2 ) );
    printf( "+0 > +0 ? %u\n", ENTIER_Est_Strict_Sup( e_zero, e_3 ) );
    printf( "+inf > +inf ? %u\n", ENTIER_Est_Strict_Sup( e_p_inf, e_p_inf ) );
    printf( "-inf > -inf ? %u\n", ENTIER_Est_Strict_Sup( e_m_inf, e_m_inf ) );
    printf( "+inf > -inf ? %u\n", ENTIER_Est_Strict_Sup( e_p_inf, e_m_inf ) );
    printf( "-inf > +inf ? %u\n", ENTIER_Est_Strict_Sup( e_m_inf, e_p_inf ) );


    /* ENTIER_Ajouter_Entiers */
    printf( "\n** ENTIER_Ajouter_Entiers **\n" );
    ENTIER_Ajouter_Entiers( e_3, e_1, e_2 );
    printf( "69 + 17 = 86 ?\n" );
    printf( "        = " );
    ENTIER_Afficher_Console( e_3 );

    ENTIER_Ajouter_Entiers( e_3, e_p_inf, e_2 );
    printf( "+inf + 17 = +inf ?\n" );
    printf( "          = " );
    ENTIER_Afficher_Console( e_3 );

    ENTIER_Ajouter_Entiers( e_3, e_m_inf, e_2 );
    printf( "-inf + 17 = -inf ?\n" );
    printf( "          = " );
    ENTIER_Afficher_Console( e_3 );

    ENTIER_Ajouter_Entiers( e_3, e_m_inf, e_m_inf );
    printf( "-inf + -inf = -inf ?\n" );
    printf( "            = " );
    ENTIER_Afficher_Console( e_3 );

    ENTIER_Ajouter_Entiers( e_3, e_p_inf, e_p_inf );
    printf( "+inf + +inf = +inf ?\n" );
    printf( "            = " );
    ENTIER_Afficher_Console( e_3 );

    ENTIER_Ajouter_Entiers( e_3, e_m_inf, e_p_inf );
    printf( "-inf + +inf = -inf ?\n" );
    printf( "            = " );
    ENTIER_Afficher_Console( e_3 );

    ENTIER_Modifier_De_Chaine( e_1, "+999999999999999999" );
    ENTIER_Modifier_De_Chaine( e_2, "+1" );
    ENTIER_Ajouter_Entiers( e_3, e_1, e_2 );
    printf( "999999999999999999 + 1 = +inf ?\n" );
    printf( "                       = " );
    ENTIER_Afficher_Console( e_3 );

    ENTIER_Modifier_De_Chaine( e_1, "+999999997" );
    ENTIER_Modifier_De_Chaine( e_2, "+4" );
    ENTIER_Ajouter_Entiers( e_3, e_1, e_2 );
    printf( "999999997 + 4 = +1000000001 ?\n" );
    printf( "              = " );
    ENTIER_Afficher_Console( e_3 );

    ENTIER_Modifier_De_Chaine( e_1, "+999999997" );
    ENTIER_Modifier_De_Chaine( e_2, "-999999997" );
    ENTIER_Ajouter_Entiers( e_3, e_1, e_2 );
    printf( "999999997 + -999999997 = +0 ?\n" );
    printf( "                       = " );
    ENTIER_Afficher_Console( e_3 );

    ENTIER_Modifier_De_Chaine( e_1, "-123456789" );
    ENTIER_Modifier_De_Chaine( e_2, "-123456789" );
    ENTIER_Ajouter_Entiers( e_3, e_1, e_2 );
    printf( "-123456789 + -123456789 = -246913578 ?\n" );
    printf( "                        = " );
    ENTIER_Afficher_Console( e_3 );

    ENTIER_Modifier_De_Chaine( e_1, "-1234567890" );
    ENTIER_Modifier_De_Chaine( e_2, "-1234567890" );
    ENTIER_Ajouter_Entiers( e_3, e_1, e_2 );
    printf( "-1234567890 + -1234567890 = -2469135780 ?\n" );
    printf( "                          = " );
    ENTIER_Afficher_Console( e_3 );


    /* ENTIER_Multiplier_Entiers */
    printf( "\n** ENTIER_Multiplier_Entiers **\n" );
    ENTIER_Modifier_De_Chaine( e_1, "+12" );
    ENTIER_Modifier_De_Chaine( e_2, "+8" );
    ENTIER_Multiplier_Entiers( e_3, e_1, e_2 );
    printf( "12 * 8 = +96 ?\n" );
    printf( "       = " );
    ENTIER_Afficher_Console( e_3 );

    ENTIER_Modifier_De_Chaine( e_1, "-1234567890" );
    ENTIER_Modifier_De_Chaine( e_2, "-1234567890" );
    ENTIER_Multiplier_Entiers( e_3, e_1, e_2 );
    printf( "-1234567890 * -1234567890 = +inf ?\n" );
    printf( "                          = " );
    ENTIER_Afficher_Console( e_3 );

    ENTIER_Modifier_De_Chaine( e_2, "+5" );
    ENTIER_Multiplier_Entiers( e_3, e_1, e_2 );
    printf( "-1234567890 * 5 = -6172839450 ?\n" );
    printf( "                = " );
    ENTIER_Afficher_Console( e_3 );

    ENTIER_Multiplier_Entiers( e_3, e_1, e_zero );
    printf( "-1234567890 * 0 = +0 ?\n" );
    printf( "                = " );
    ENTIER_Afficher_Console( e_3 );

    ENTIER_Multiplier_Entiers( e_3, e_p_inf, e_2 );
    printf( "+inf * 8 = +inf ?\n" );
    printf( "         = " );
    ENTIER_Afficher_Console( e_3 );

    ENTIER_Multiplier_Entiers( e_3, e_m_inf, e_2 );
    printf( "-inf * 8 = -inf ?\n" );
    printf( "         = " );
    ENTIER_Afficher_Console( e_3 );

    ENTIER_Multiplier_Entiers( e_3, e_m_inf, e_m_inf );
    printf( "-inf * -inf = +inf ?\n" );
    printf( "            = " );
    ENTIER_Afficher_Console( e_3 );

    ENTIER_Multiplier_Entiers( e_3, e_p_inf, e_p_inf );
    printf( "+inf * +inf = +inf ?\n" );
    printf( "            = " );
    ENTIER_Afficher_Console( e_3 );

    ENTIER_Multiplier_Entiers( e_3, e_m_inf, e_p_inf );
    printf( "-inf * +inf = -inf ?\n" );
    printf( "            = " );
    ENTIER_Afficher_Console( e_3 );

    ENTIER_Multiplier_Entiers( e_3, e_p_inf, e_m_inf );
    printf( "+inf * -inf = -inf ?\n" );
    printf( "            = " );
    ENTIER_Afficher_Console( e_3 );

    ENTIER_Multiplier_Entiers( e_3, e_m_inf, e_zero );
    printf( "-inf * 0 = +0 ?\n" );
    printf( "         = " );
    ENTIER_Afficher_Console( e_3 );

    ENTIER_Multiplier_Entiers( e_3, e_zero, e_p_inf );
    printf( "0 * +inf = +0 ?\n" );
    printf( "         = " );
    ENTIER_Afficher_Console( e_3 );

    /* ENTIER_Diviser_Entiers */
    printf( "\n** ENTIER_Diviser_Entiers **\n" );
    e_4 = ENTIER_Creer_Nul();
    printf( "\n" );
    ENTIER_Modifier_De_Chaine( e_1, "+1234678" );
    ENTIER_Modifier_De_Chaine( e_2, "+88789" );
    ENTIER_Diviser_Entiers( e_3, e_4, e_1, e_2 );
    printf( "1234678 / 88789 = ?\n" );
    printf( "quotient = +13 ?\n" );
    printf( "         = " );
    ENTIER_Afficher_Console( e_3 );
    printf( "reste = +80421 ?\n" );
    printf( "      = " );
    ENTIER_Afficher_Console( e_4 );

    printf( "\n" );
    ENTIER_Modifier_De_Chaine( e_1, "+12" );
    ENTIER_Modifier_De_Chaine( e_2, "+8" );
    ENTIER_Diviser_Entiers( e_3, e_4, e_1, e_2 );
    printf( "12 / 8 = ?\n" );
    printf( "quotient = +1 ?\n" );
    printf( "         = " );
    ENTIER_Afficher_Console( e_3 );
    printf( "reste = +4 ?\n" );
    printf( "      = " );
    ENTIER_Afficher_Console( e_4 );

    printf( "\n" );
    ENTIER_Diviser_Entiers( e_3, e_4, e_1, e_p_inf );
    printf( "12 / +inf = ?\n" );
    printf( "quotient = +0 ?\n" );
    printf( "         = " );
    ENTIER_Afficher_Console( e_3 );
    printf( "reste = +12 ?\n" );
    printf( "      = " );
    ENTIER_Afficher_Console( e_4 );

    printf( "\n" );
    ENTIER_Diviser_Entiers( e_3, e_4, e_1, e_zero );
    printf( "12 / 0 = ?\n" );
    printf( "quotient = +inf ?\n" );
    printf( "         = " );
    ENTIER_Afficher_Console( e_3 );
    printf( "reste = +0 ?\n" );
    printf( "      = " );
    ENTIER_Afficher_Console( e_4 );

    printf( "\n" );
    ENTIER_Modifier_De_Chaine( e_1, "-12" );
    ENTIER_Diviser_Entiers( e_3, e_4, e_1, e_zero );
    printf( "-12 / 0 = ?\n" );
    printf( "quotient = -inf ?\n" );
    printf( "         = " );
    ENTIER_Afficher_Console( e_3 );
    printf( "reste = +0 ?\n" );
    printf( "      = " );
    ENTIER_Afficher_Console( e_4 );

    printf( "\n" );
    ENTIER_Diviser_Entiers( e_3, e_4, e_p_inf, e_2 );
    printf( "+inf / 8 = ?\n" );
    printf( "quotient = +inf ?\n" );
    printf( "         = " );
    ENTIER_Afficher_Console( e_3 );
    printf( "reste = +0 ?\n" );
    printf( "      = " );
    ENTIER_Afficher_Console( e_4 );

    printf( "\n" );
    ENTIER_Modifier_De_Chaine( e_2, "-8" );
    ENTIER_Diviser_Entiers( e_3, e_4, e_m_inf, e_2 );
    printf( "-inf / -8 = ?\n" );
    printf( "quotient = +inf ?\n" );
    printf( "         = " );
    ENTIER_Afficher_Console( e_3 );
    printf( "reste = +0 ?\n" );
    printf( "      = " );
    ENTIER_Afficher_Console( e_4 );


    /* ENTIER_Racine_Carree */
    printf( "\n** ENTIER_Racine_Carree **\n" );

    ENTIER_Modifier_De_Chaine( e_2, "+145" );
    ENTIER_Racine_Carree( e_1, e_2 );
    printf( "racine(145) = +12 ?\n" );
    printf( "            = " );
    ENTIER_Afficher_Console( e_1 );

    ENTIER_Modifier_De_Chaine( e_2, "+15" );
    ENTIER_Racine_Carree( e_1, e_2 );
    printf( "racine(15) = +3 ?\n" );
    printf( "           = " );
    ENTIER_Afficher_Console( e_1 );

    ENTIER_Modifier_De_Chaine( e_2, "+1" );
    ENTIER_Racine_Carree( e_1, e_2 );
    printf( "racine(1) = +1 ?\n" );
    printf( "          = " );
    ENTIER_Afficher_Console( e_1 );

    ENTIER_Modifier_De_Chaine( e_2, "+2" );
    ENTIER_Racine_Carree( e_1, e_2 );
    printf( "racine(2) = +1 ?\n" );
    printf( "          = " );
    ENTIER_Afficher_Console( e_1 );

    ENTIER_Modifier_De_Chaine( e_2, "+3" );
    ENTIER_Racine_Carree( e_1, e_2 );
    printf( "racine(3) = +1 ?\n" );
    printf( "          = " );
    ENTIER_Afficher_Console( e_1 );

    ENTIER_Modifier_De_Chaine( e_2, "+4" );
    ENTIER_Racine_Carree( e_1, e_2 );
    printf( "racine(4) = +2 ?\n" );
    printf( "          = " );
    ENTIER_Afficher_Console( e_1 );

    ENTIER_Modifier_De_Chaine( e_2, "+5" );
    ENTIER_Racine_Carree( e_1, e_2 );
    printf( "racine(5) = +2 ?\n" );
    printf( "          = " );
    ENTIER_Afficher_Console( e_1 );

    ENTIER_Modifier_De_Chaine( e_2, "+987654321012345678" );
    ENTIER_Racine_Carree( e_1, e_2 );
    printf( "racine(987654321012345678) = +993807990 ?\n" );
    printf( "                           = " );
    ENTIER_Afficher_Console( e_1 );

    ENTIER_Modifier_De_Chaine( e_2, "+345148025049" );
    ENTIER_Racine_Carree( e_1, e_2 );
    printf( "racine(345148025049) = +587493 ?\n" );
    printf( "                     = " );
    ENTIER_Afficher_Console( e_1 );

    ENTIER_Modifier_De_Chaine( e_2, "+210550181084" );
    ENTIER_Racine_Carree( e_1, e_2 );
    printf( "racine(210550181084) = +458857 ?\n" );
    printf( "                     = " );
    ENTIER_Afficher_Console( e_1 );


    ENTIER_Modifier_De_Chaine( e_2, "-15" );
    ENTIER_Racine_Carree( e_1, e_2 );
    printf( "racine(-15) = invalide ?\n" );
    printf( "            = " );
    ENTIER_Afficher_Console( e_1 );

    ENTIER_Modifier_De_Chaine( e_2, "+0" );
    ENTIER_Racine_Carree( e_1, e_2 );
    printf( "racine(0) = +0 ?\n" );
    printf( "          = " );
    ENTIER_Afficher_Console( e_1 );

    ENTIER_Racine_Carree( e_1, e_p_inf );
    printf( "racine(+inf) = +inf ?\n" );
    printf( "             = " );
    ENTIER_Afficher_Console( e_1 );

    ENTIER_Racine_Carree( e_1, e_m_inf );
    printf( "racine(-inf) = +0 ?\n" );
    printf( "             = " );
    ENTIER_Afficher_Console( e_1 );

    /* ENTIER_Charger_Nombres_Premiers */
    printf( "\n** ENTIER_Charger_Nombres_Premiers **\n" );

    ENTIER_Modifier_De_Chaine( e_2, "+1" );
    printf( "limite = " );
    ENTIER_Afficher_Console( e_2 );
    liste_prm = ENTIER_Charger_Nombres_Premiers( e_2 );
    LISTE_Appliquer_A_Tous( liste_prm, ENTIER_Afficher_Console );

    ENTIER_Modifier_De_Chaine( e_2, "+11" );
    printf( "limite = " );
    ENTIER_Afficher_Console( e_2 );
    liste_prm = ENTIER_Charger_Nombres_Premiers( e_2 );
    LISTE_Appliquer_A_Tous( liste_prm, ENTIER_Afficher_Console );

    ENTIER_Modifier_De_Chaine( e_2, "+12" );
    printf( "limite = " );
    ENTIER_Afficher_Console( e_2 );
    liste_prm = ENTIER_Charger_Nombres_Premiers( e_2 );
    LISTE_Appliquer_A_Tous( liste_prm, ENTIER_Afficher_Console );

    ENTIER_Modifier_De_Chaine( e_2, "+13" );
    printf( "limite = " );
    ENTIER_Afficher_Console( e_2 );
    liste_prm = ENTIER_Charger_Nombres_Premiers( e_2 );
    LISTE_Appliquer_A_Tous( liste_prm, ENTIER_Afficher_Console );

    ENTIER_Modifier_De_Chaine( e_2, "+2" );
    printf( "limite = " );
    ENTIER_Afficher_Console( e_2 );
    liste_prm = ENTIER_Charger_Nombres_Premiers( e_2 );
    LISTE_Appliquer_A_Tous( liste_prm, ENTIER_Afficher_Console );


    /* ENTIER_Est_Premier */
    printf( "\n** ENTIER_Est_Premier **\n" );

    ENTIER_Modifier_De_Chaine( e_1, "+169000000" );
    printf( "+169000000 premier ? : %d\n" , ENTIER_Est_Premier( e_1 ) );

    ENTIER_Modifier_De_Chaine( e_1, "+16900" );
    printf( "+16900 premier ? : %d\n" , ENTIER_Est_Premier( e_1 ) );

    ENTIER_Modifier_De_Chaine( e_1, "+5441" );
    printf( "+5441 premier ? : %d\n" , ENTIER_Est_Premier( e_1 ) );

    ENTIER_Modifier_De_Chaine( e_1, "+2" );
    printf( "+2 premier ? : %d\n" , ENTIER_Est_Premier( e_1 ) );

    ENTIER_Modifier_De_Chaine( e_1, "+1" );
    printf( "+1 premier ? : %d\n" , ENTIER_Est_Premier( e_1 ) );

    ENTIER_Modifier_De_Chaine( e_1, "+5" );
    printf( "+5 premier ? : %d\n" , ENTIER_Est_Premier( e_1 ) );

    printf( "+0 premier ? : %d\n" , ENTIER_Est_Premier( e_zero ) );
    printf( "+inf premier ? : %d\n" , ENTIER_Est_Premier( e_p_inf ) );
    printf( "-inf premier ? : %d\n" , ENTIER_Est_Premier( e_m_inf ) );

    /* ENTIER_Decomposer_Fact_Premiers */
    printf( "\n** ENTIER_Decomposer_Fact_Premiers **\n" );

    printf( "\nDecomposition de : " );
    ENTIER_Modifier_De_Chaine( e_1, "+169000000" );
    ENTIER_Afficher_Console( e_1 );
    dec_fct_prm = ENTIER_Decomposer_Fact_Premiers( e_1 );
    LISTE_Appliquer_A_Tous( dec_fct_prm, ENTIER_Afficher_Console );
    ENTIER_Detruire_Liste_Entier( &dec_fct_prm );

    printf( "\nDecomposition de : " );
    ENTIER_Modifier_De_Chaine( e_1, "+16900" );
    ENTIER_Afficher_Console( e_1 );
    dec_fct_prm = ENTIER_Decomposer_Fact_Premiers( e_1 );
    LISTE_Appliquer_A_Tous( dec_fct_prm, ENTIER_Afficher_Console );
    ENTIER_Detruire_Liste_Entier( &dec_fct_prm );

    printf( "\nDecomposition de : " );
    ENTIER_Modifier_De_Chaine( e_1, "+600851475143" );
    ENTIER_Afficher_Console( e_1 );
    dec_fct_prm = ENTIER_Decomposer_Fact_Premiers( e_1 );
    LISTE_Appliquer_A_Tous( dec_fct_prm, ENTIER_Afficher_Console );
    ENTIER_Detruire_Liste_Entier( &dec_fct_prm );

    printf( "\nDecomposition de : " );
    ENTIER_Modifier_De_Chaine( e_1, "+5441" );
    ENTIER_Afficher_Console( e_1 );
    dec_fct_prm = ENTIER_Decomposer_Fact_Premiers( e_1 );
    LISTE_Appliquer_A_Tous( dec_fct_prm, ENTIER_Afficher_Console );
    ENTIER_Detruire_Liste_Entier( &dec_fct_prm );

    printf( "\nDecomposition de : " );
    ENTIER_Modifier_De_Chaine( e_1, "+2" );
    ENTIER_Afficher_Console( e_1 );
    dec_fct_prm = ENTIER_Decomposer_Fact_Premiers( e_1 );
    LISTE_Appliquer_A_Tous( dec_fct_prm, ENTIER_Afficher_Console );
    ENTIER_Detruire_Liste_Entier( &dec_fct_prm );

    printf( "\nDecomposition de : " );
    ENTIER_Modifier_De_Chaine( e_1, "+1" );
    ENTIER_Afficher_Console( e_1 );
    dec_fct_prm = ENTIER_Decomposer_Fact_Premiers( e_1 );
    LISTE_Appliquer_A_Tous( dec_fct_prm, ENTIER_Afficher_Console );
    ENTIER_Detruire_Liste_Entier( &dec_fct_prm );

    printf( "\nDecomposition de : " );
    ENTIER_Modifier_De_Chaine( e_1, "+5" );
    ENTIER_Afficher_Console( e_1 );
    dec_fct_prm = ENTIER_Decomposer_Fact_Premiers( e_1 );
    LISTE_Appliquer_A_Tous( dec_fct_prm, ENTIER_Afficher_Console );
    ENTIER_Detruire_Liste_Entier( &dec_fct_prm );

    printf( "\nDecomposition de : " );
    dec_fct_prm = ENTIER_Decomposer_Fact_Premiers( e_zero );
    ENTIER_Afficher_Console( e_zero );
    LISTE_Appliquer_A_Tous( dec_fct_prm, ENTIER_Afficher_Console );
    ENTIER_Detruire_Liste_Entier( &dec_fct_prm );

    printf( "\nDecomposition de : " );
    dec_fct_prm = ENTIER_Decomposer_Fact_Premiers( e_p_inf );
    ENTIER_Afficher_Console( e_p_inf );
    LISTE_Appliquer_A_Tous( dec_fct_prm, ENTIER_Afficher_Console );
    ENTIER_Detruire_Liste_Entier( &dec_fct_prm );

    printf( "\nDecomposition de : " );
    dec_fct_prm = ENTIER_Decomposer_Fact_Premiers( e_m_inf );
    ENTIER_Afficher_Console( e_m_inf );
    LISTE_Appliquer_A_Tous( dec_fct_prm, ENTIER_Afficher_Console );
    ENTIER_Detruire_Liste_Entier( &dec_fct_prm );

    printf( "\nDecomposition de : " );
    ENTIER_Modifier_De_Chaine( e_1, "+210550181084" );
    ENTIER_Afficher_Console( e_1 );
    dec_fct_prm = ENTIER_Decomposer_Fact_Premiers( e_1 );
    LISTE_Appliquer_A_Tous( dec_fct_prm, ENTIER_Afficher_Console );
    ENTIER_Detruire_Liste_Entier( &dec_fct_prm );


#else
    ENTIER_Chercher_Premiers_Suivants();
#endif
    return EXIT_SUCCESS;
}
