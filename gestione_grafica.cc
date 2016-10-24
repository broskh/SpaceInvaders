/*
 * File contenente il modulo di gestione della grafica.
 */

#include <allegro5/allegro.h>
//#include <allegro5/allegro_font.h>
//#include <allegro5/allegro_ttf.h>
//#include <allegro5/allegro_audio.h>
//#include <allegro5/allegro_acodec.h>
//#include <allegro5/allegro_image.h>
#include "struttura_dati.h"
#include "gestione_grafica.h"

//INIZIO MODULO
void stampaMenuPrincipale ()
{
	//INIZIO VISUALIZZAZIONE
	al_clear_to_color(al_map_rgb(0, 0, 0));

	//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
	al_draw_text(font_titolo, al_map_rgb(0, 255, 0), POS_CENTRO_X, POS_Y_TITOLO_MENU_PRINCIPALE, ALLEGRO_ALIGN_CENTRE, ".");
	//FINE DELLA VISUALIZZAZIONE DEL TITOLO

	//INIZIO DELLA VISUALIZZAZIONE DEGLI ALIENI E I RELATIVI PUNTEGGI
	unsigned int pos_y_attuale = POS_Y_ESMEPIO_ALIENI;
	al_draw_tinted_bitmap_region(alieno_tipo_1, al_map_rgb(0, 255, 0), 0, 0, al_get_bitmap_width (alieno_tipo_1) / N_STATI_SPRITE, al_get_bitmap_height (alieno_tipo_1), POS_X_ESEMPIO_ALIENI - al_get_bitmap_width (alieno_tipo_1) / (N_STATI_SPRITE * 2), pos_y_attuale, 0);
	al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_X_ESEMPIO_PUNTEGGIO, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, "=      10  PTS");

	pos_y_attuale = POS_Y_ESMEPIO_ALIENI + SPAZIO_TESTO + al_get_bitmap_height (alieno_tipo_1);
	al_draw_tinted_bitmap_region(alieno_tipo_2, al_map_rgb(0, 255, 0), 0, 0, al_get_bitmap_width (alieno_tipo_2) / N_STATI_SPRITE, al_get_bitmap_height (alieno_tipo_2), POS_X_ESEMPIO_ALIENI - al_get_bitmap_width (alieno_tipo_2) / (N_STATI_SPRITE * 2), pos_y_attuale, 0);
	al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_X_ESEMPIO_PUNTEGGIO, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, "=      20  PTS");

	pos_y_attuale = POS_Y_ESMEPIO_ALIENI + (SPAZIO_TESTO + al_get_bitmap_height (alieno_tipo_1)) * 2;
	al_draw_tinted_bitmap_region(alieno_tipo_3, al_map_rgb(0, 255, 0), 0, 0, al_get_bitmap_width (alieno_tipo_3) / N_STATI_SPRITE, al_get_bitmap_height (alieno_tipo_3), POS_X_ESEMPIO_ALIENI - al_get_bitmap_width (alieno_tipo_3) / (N_STATI_SPRITE * 2), pos_y_attuale, 0);
	al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_X_ESEMPIO_PUNTEGGIO, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, "=      30  PTS");

	pos_y_attuale = POS_Y_ESMEPIO_ALIENI + (SPAZIO_TESTO + al_get_bitmap_height (alieno_tipo_1)) * 3;
	al_draw_tinted_bitmap(navicella_misteriosa, al_map_rgb(255, 0, 0), POS_X_ESEMPIO_ALIENI - al_get_bitmap_width (navicella_misteriosa) / 2, pos_y_attuale, 0);
	al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_X_ESEMPIO_PUNTEGGIO, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, "=         ?  PTS");
	//FINE DELLA VISUALIZZAZIONE DEGLI ALIENI E I RELATIVI PUNTEGGI

	//INIZIO DELLA VISUALIZZAZIONE DEL MENU
	for (int i = 0; i < menu_principale.n_voci; i++)
	{
		if (!(menu_principale.voce_sel == i && !redraw_lampeggio))
		{
			pos_y_attuale = POS_Y_VOCI_MENU_PRINCIPALE + (SPAZIO_TESTO + DIMENSIONE_TESTO) * i;
			if ((!generale.partita_salvata) && (static_cast <voce_menu_principale> (i) == v_carica))
			{
				al_draw_text(font_testo, al_map_rgb(84, 84, 84), POS_CENTRO_X, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, menu_principale.testi_menu [i]);
			}
			else
			{
				al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_CENTRO_X, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, menu_principale.testi_menu [i]);
			}
		}
	}
	//FINE DELLA VISUALIZZAZIONE DEL MENU

	al_flip_display();
	//FINE VISUALIZZAZIONE
}

void stampaGioca ()
{
}

void stampaOpzioni ()
{
}

void stampaHighscores ()
{
}

//FINE MODULO