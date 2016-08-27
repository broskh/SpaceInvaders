/*
 * File contenente il modulo di salvataggio/caricamento delle impostazioni.
 */

#include "struttura_dati.h"
#include "gestione_input-output.h"

//INIZIO MODULO

void menuPrincipale ()
{
	const unsigned int DIM_FONT_TITOLO = 55; /*Dimensione del font utilizzato per il titolo.*/
	const unsigned int DIM_FONT_MENU = 15; /*Dimensione del font utilizzato per il menu principale.*/
	const unsigned int ALT_TITOLO = ALTEZZA_DISPLAY / 100 * 8; /*Altezza del display dal quale mostrare il titolo.*/
	const unsigned int ALT_MENU = ALTEZZA_DISPLAY / 100 * 90; /*Altezza del display dal quale mostrare il menu.*/

	ALLEGRO_FONT *font_titolo = al_load_ttf_font(FONT_FILE, DIM_FONT_TITOLO, 0);
	assert (font_titolo);

	ALLEGRO_FONT *font_menu = al_load_ttf_font(FONT_FILE, DIM_FONT_MENU, 0);
 	assert (font_menu);

	al_draw_text(font_titolo, al_map_rgb(0, 255, 0), (CENTRO_ORIZ), (ALT_TITOLO), ALLEGRO_ALIGN_CENTRE, "SPACE");
	al_draw_text(font_titolo, al_map_rgb(255, 255, 255), (CENTRO_ORIZ), (ALT_TITOLO + SPAZIO_TESTO + DIM_FONT_TITOLO), ALLEGRO_ALIGN_CENTRE, "INVADERS");

	al_draw_text(font_menu, al_map_rgb(0, 255, 0), CENTRO_ORIZ, ALT_MENU, ALLEGRO_ALIGN_CENTRE, MENU [0]);
	al_draw_text(font_menu, al_map_rgb(0, 255, 0), CENTRO_ORIZ, (ALT_MENU + SPAZIO_TESTO + DIM_FONT_MENU), ALLEGRO_ALIGN_CENTRE, MENU [1]);
	al_draw_text(font_menu, al_map_rgb(0, 255, 0), CENTRO_ORIZ, (ALT_MENU + (SPAZIO_TESTO + DIM_FONT_MENU) * 2), ALLEGRO_ALIGN_CENTRE, MENU [2]);
	al_draw_text(font_menu, al_map_rgb(0, 255, 0), CENTRO_ORIZ, (ALT_MENU + (SPAZIO_TESTO + DIM_FONT_MENU) * 3), ALLEGRO_ALIGN_CENTRE, MENU [3]);

	al_flip_display();
}

//FINE MODULO
