/*
 * File contenente il modulo di gestione della grafica.
 */

#include <cstdio>
//#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "struttura_dati.h"
#include "gestione_grafica.h"
#include "gestione_menu.h"

//INIZIO VARIABILI DI MODULO
static ALLEGRO_DISPLAY *display = NULL;
static ALLEGRO_BITMAP *barriera = NULL;
static ALLEGRO_BITMAP *carro_armato = NULL;
static ALLEGRO_BITMAP *sparo_carro = NULL;
static ALLEGRO_BITMAP *navicella_misteriosa = NULL;
static ALLEGRO_BITMAP *alieno_tipo_1 = NULL;
static ALLEGRO_BITMAP *alieno_tipo_2 = NULL;
static ALLEGRO_BITMAP *alieno_tipo_3 = NULL;
static ALLEGRO_BITMAP *sparo_alieni_1 = NULL;
static ALLEGRO_BITMAP *sparo_alieni_2 = NULL;
static ALLEGRO_BITMAP *esplosione_carro = NULL;
static ALLEGRO_BITMAP *esplosione_alieno = NULL;
static ALLEGRO_FONT *font_titolo = NULL;
static ALLEGRO_FONT *font_testo = NULL;
static ALLEGRO_COLOR VERDE;
static ALLEGRO_COLOR BIANCO;
static ALLEGRO_COLOR ARANCIONE;
static ALLEGRO_COLOR GIALLO;
static ALLEGRO_COLOR BLU;
static ALLEGRO_COLOR ROSSO;
static ALLEGRO_COLOR NERO;
static ALLEGRO_COLOR GRIGIO;
static ALLEGRO_COLOR COLORE_DEFAULT;
//FINE VARIABILI DI MODULO

//INIZIO MODULO
ALLEGRO_BITMAP* scegliAlieno (unsigned int numero_fila)
{
	if (numero_fila < 2)
	{
		return alieno_tipo_1;
	}
	else if (numero_fila < 4)
	{
		return alieno_tipo_2;
	}
	else if (numero_fila < 6)
	{
		return alieno_tipo_3;
	}

	return NULL;
}

ALLEGRO_BITMAP * scegliSparo (int pos_x)
{
	if (pos_x % 2 == 0)
	{
		return sparo_alieni_1;		
	}
	else
	{
		return sparo_alieni_2;
	}
}

ALLEGRO_COLOR scelgliColore (colore colore_alieni)
{
	ALLEGRO_COLOR colore_allegro = VERDE;
	switch (colore_alieni)
	{
		case verde:
			colore_allegro = VERDE;
			break;
		case bianco:
			colore_allegro = BIANCO;
			break;
		case arancione:
			colore_allegro = ARANCIONE;
			break;
		case giallo:
			colore_allegro = GIALLO;
			break;
		case blu:
			colore_allegro = BLU;
			break;
	}
	return colore_allegro;
}

ALLEGRO_DISPLAY * inizializzaGrafica ()
{
	assert (al_init_image_addon());
	assert (al_init_font_addon());
	assert (al_init_ttf_addon()); 

	display = al_create_display(LARGHEZZA_DISPLAY, ALTEZZA_DISPLAY);
	assert (display);

	font_titolo = al_load_ttf_font(FILE_FONT_TITOLO, DIMENSIONE_TITOLO, 0);
	assert (font_titolo);
	font_testo = al_load_ttf_font(FILE_FONT_TESTO, DIMENSIONE_TESTO, 0);
 	assert (font_testo);
	
	barriera = al_load_bitmap(FILE_BARRIERA);
	assert (barriera);
	sparo_alieni_1 = al_load_bitmap(FILE_SPARO_ALIENI_1);
	assert (sparo_alieni_1);
	sparo_alieni_2 = al_load_bitmap(FILE_SPARO_ALIENI_2);
	assert (sparo_alieni_2);
	esplosione_carro = al_load_bitmap(FILE_ESPLOSIONE_CARRO);
	assert (esplosione_carro);
	esplosione_alieno = al_load_bitmap(FILE_ESPLOSIONE_ALIENO);
	assert (esplosione_alieno);
	carro_armato = al_load_bitmap(FILE_CARRO_ARMATO);
	assert (carro_armato);
	sparo_carro = al_load_bitmap(FILE_SPARO_CARRO);
	assert (sparo_carro);
	navicella_misteriosa = al_load_bitmap(FILE_NAVICELLA_MISTERIOSA);
	assert (navicella_misteriosa);
	alieno_tipo_1 = al_load_bitmap(FILE_ALIENO_TIPO_1);
	assert (alieno_tipo_1);
	alieno_tipo_2 = al_load_bitmap(FILE_ALIENO_TIPO_2);
	assert (alieno_tipo_2);
	alieno_tipo_3 = al_load_bitmap(FILE_ALIENO_TIPO_3);
	assert (alieno_tipo_3);

	VERDE = al_map_rgb(0, 255, 0);
	BIANCO = al_map_rgb(255, 255, 255);
	ARANCIONE = al_map_rgb(255, 128, 0);
	GIALLO = al_map_rgb(255, 255, 0);
	BLU = al_map_rgb(0, 0, 255);
	ROSSO = al_map_rgb(255, 0, 0);
	NERO = al_map_rgb(0, 0, 0);
	GRIGIO = al_map_rgb(84, 84, 84);
	COLORE_DEFAULT = VERDE;

	return display;
}

void distruggiGrafica ()
{
	al_destroy_display(display);
	al_destroy_font (font_testo);
	al_destroy_font (font_titolo);
	al_destroy_bitmap(sparo_alieni_1);
	al_destroy_bitmap(sparo_alieni_2);
	al_destroy_bitmap(barriera);
	al_destroy_bitmap(carro_armato);
	al_destroy_bitmap(sparo_carro);
	al_destroy_bitmap(navicella_misteriosa);
	al_destroy_bitmap(alieno_tipo_1);
	al_destroy_bitmap(alieno_tipo_2);
	al_destroy_bitmap(alieno_tipo_3);
	al_destroy_bitmap(esplosione_carro);
	al_destroy_bitmap(esplosione_alieno);
}

void stampaMenuPrincipale (Menu menu_principale, bool redraw_lampeggio, bool partita_salvata, colore colore_alieni)
{
	//INIZIO VISUALIZZAZIONE
	al_clear_to_color(NERO);

	//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
	al_draw_text(font_titolo, COLORE_DEFAULT, POS_CENTRO_X, POS_Y_TITOLO_MENU_PRINCIPALE, ALLEGRO_ALIGN_CENTRE, ".");
	//FINE DELLA VISUALIZZAZIONE DEL TITOLO

	//INIZIO DELLA VISUALIZZAZIONE DEGLI ALIENI E I RELATIVI PUNTEGGI
	ALLEGRO_COLOR colore_allegro = scelgliColore (colore_alieni);
	unsigned int pos_y_attuale = POS_Y_ESMEPIO_ALIENI;
	al_draw_tinted_bitmap_region(alieno_tipo_1, colore_allegro, 0, 0, larghezzaAlieno1 (), al_get_bitmap_height (alieno_tipo_1), POS_X_ESEMPIO_ALIENI - al_get_bitmap_width (alieno_tipo_1) / (N_STATI_SPRITE * 2), pos_y_attuale, 0);
	al_draw_text(font_testo, COLORE_DEFAULT, POS_X_ESEMPIO_PUNTEGGIO, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, "=      10  PTS");

	pos_y_attuale = POS_Y_ESMEPIO_ALIENI + SPAZIO_TESTO + al_get_bitmap_height (alieno_tipo_1);
	al_draw_tinted_bitmap_region(alieno_tipo_2, colore_allegro, 0, 0, larghezzaAlieno2 (), al_get_bitmap_height (alieno_tipo_2), POS_X_ESEMPIO_ALIENI - al_get_bitmap_width (alieno_tipo_2) / (N_STATI_SPRITE * 2), pos_y_attuale, 0);
	al_draw_text(font_testo, COLORE_DEFAULT, POS_X_ESEMPIO_PUNTEGGIO, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, "=      20  PTS");

	pos_y_attuale = POS_Y_ESMEPIO_ALIENI + (SPAZIO_TESTO + al_get_bitmap_height (alieno_tipo_1)) * 2;
	al_draw_tinted_bitmap_region(alieno_tipo_3, colore_allegro, 0, 0, larghezzaAlieno3 (), al_get_bitmap_height (alieno_tipo_3), POS_X_ESEMPIO_ALIENI - al_get_bitmap_width (alieno_tipo_3) / (N_STATI_SPRITE * 2), pos_y_attuale, 0);
	al_draw_text(font_testo, COLORE_DEFAULT, POS_X_ESEMPIO_PUNTEGGIO, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, "=      30  PTS");

	pos_y_attuale = POS_Y_ESMEPIO_ALIENI + (SPAZIO_TESTO + al_get_bitmap_height (alieno_tipo_1)) * 3;
	al_draw_tinted_bitmap(navicella_misteriosa, ROSSO, POS_X_ESEMPIO_ALIENI - al_get_bitmap_width (navicella_misteriosa) / 2, pos_y_attuale, 0);
	al_draw_text(font_testo, COLORE_DEFAULT, POS_X_ESEMPIO_PUNTEGGIO, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, "=         ?  PTS");
	//FINE DELLA VISUALIZZAZIONE DEGLI ALIENI E I RELATIVI PUNTEGGI

	//INIZIO DELLA VISUALIZZAZIONE DEL MENU
	for (int i = 0; i < menu_principale.n_voci; i++)
	{
		if (!(menu_principale.voce_sel == i && !redraw_lampeggio))
		{
			pos_y_attuale = POS_Y_VOCI_MENU_PRINCIPALE + (SPAZIO_TESTO + DIMENSIONE_TESTO) * i;
			if ((!partita_salvata) && (static_cast <voce_menu_principale> (i) == v_carica))
			{
				al_draw_text(font_testo, GRIGIO, POS_CENTRO_X, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, menu_principale.testi_menu [i]);
			}
			else
			{
				al_draw_text(font_testo, COLORE_DEFAULT, POS_CENTRO_X, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, menu_principale.testi_menu [i]);
			}
		}
	}
	//FINE DELLA VISUALIZZAZIONE DEL MENU

	al_flip_display();
	//FINE VISUALIZZAZIONE
}

void disegnaBarriera (ALLEGRO_BITMAP *barriera_sprite, stato_barriera barriera [ALT_BARRIERA] [LARG_BARRIERA], unsigned int pos_x, unsigned int pos_y)
{
	unsigned int dx = pos_x; 
	unsigned int dy = pos_y;

	for (unsigned int i = 0; i < ALT_BARRIERA; i++)
	{
		for (unsigned int j = 0; j < LARG_BARRIERA; j++)
		{
			if (barriera [i] [j] == integra)
			{
				al_draw_tinted_bitmap_region(barriera_sprite, COLORE_DEFAULT, 0, 0, larghezzaLatoUnitaBarriera (), al_get_bitmap_height (barriera_sprite), dx, dy, 0);
			}
			else if (barriera [i] [j] == parziale)
			{
				al_draw_tinted_bitmap_region(barriera_sprite, COLORE_DEFAULT, larghezzaLatoUnitaBarriera (), 0, larghezzaLatoUnitaBarriera (), al_get_bitmap_height (barriera_sprite), dx, dy, 0);
			}
			dx += larghezzaLatoUnitaBarriera ();
		}
		dx = pos_x;
		dy += larghezzaLatoUnitaBarriera ();
	}
}

void stampaGioca (Partita partita, bool animazione, colore colore_alieni)
{
	//INIZIO VISUALIZZAZIONE
	al_clear_to_color(NERO);

	unsigned int pos_y_attuale;
	unsigned int pos_x_attuale;

	//INIZIO DELLA VISUALIZZAZIONE DELLE INFORMAZIONI
	char stringa_punteggio [] = "Punteggio:    ";
	char valore_punteggio [MAX_STRINGA_GENERICA];
	sprintf(valore_punteggio, "%d", partita.punteggio.valore);
	strcat (stringa_punteggio, valore_punteggio);
	pos_x_attuale = (POS_CENTRO_X - al_get_text_width(font_testo, stringa_punteggio)) / 2;
	al_draw_text(font_testo, COLORE_DEFAULT, pos_x_attuale, POS_Y_INFORMAZIONI_PARTITA, ALLEGRO_ALIGN_LEFT, stringa_punteggio);

	char stringa_vite [] = "Vite:    ";
	char valore_vite [MAX_STRINGA_GENERICA];
	sprintf(valore_vite, "%d", partita.vite_rimanenti);
	strcat (stringa_vite, valore_vite);
	pos_x_attuale = (POS_CENTRO_X - al_get_text_width(font_testo, stringa_vite)) / 2 + POS_CENTRO_X;
	al_draw_text(font_testo, COLORE_DEFAULT, pos_x_attuale, POS_Y_INFORMAZIONI_PARTITA, ALLEGRO_ALIGN_CENTRE, stringa_vite);
	//FINE DELLA VISUALIZZAZIONE DELLE INFORMAZIONI

	//INIZIO DELLA VISUALIZZAZIONE DELLA NAVICELLA MISTERIOSA
	if (partita.navicella_misteriosa.stato)
	{
		al_draw_tinted_bitmap(navicella_misteriosa, ROSSO, partita.navicella_misteriosa.pos_x, MARGINE_SUP_GIOCO, 0);
	}
	//FINE DELLA VISUALIZZAZIONE DELLA NAVICELLA MISTERIOSA

	//INIZIO DELLA VISUALIZZAZIONE DELL'ONDATA
	ALLEGRO_COLOR colore_ondata = scelgliColore (colore_alieni);
	pos_y_attuale = partita.ondata.pos_y;

	for (unsigned int i = 0; i < N_FILE_ALIENI; i++)
	{
		pos_x_attuale = partita.ondata.pos_x;
		for (unsigned int j = 0; j < N_COL_ALIENI; j++)
		{
			if (partita.ondata.alieni [i] [j].esplosione)
			{
				al_draw_tinted_bitmap(esplosione_alieno, colore_ondata, pos_x_attuale - (al_get_bitmap_width (esplosione_alieno) / 2), pos_y_attuale, 0);
			}
			else if (partita.ondata.alieni [i] [j].stato)
			{
				ALLEGRO_BITMAP * alieno_scelto = scegliAlieno (i);
				unsigned int larghezza_istantanea = al_get_bitmap_width (alieno_scelto) / 2;
				al_draw_tinted_bitmap_region(alieno_scelto, colore_ondata, larghezza_istantanea * animazione, 0, larghezza_istantanea, al_get_bitmap_height (alieno_scelto), pos_x_attuale - (larghezza_istantanea / 2), pos_y_attuale, 0);
			}
			pos_x_attuale += DISTANZA_ASSI_COL_ALIENI;
		}
		pos_y_attuale += DISTANZA_FILE_ALIENI;
	}
	//FINE DELLA VISUALIZZAZIONE DELL'ONDATA

	//INIZIO DELLA VISUALIZZAZIONE DELLO SPARO DEGLI ALIENI
	if (partita.sparo_alieni.stato)
	{
		unsigned int sx;
		ALLEGRO_BITMAP *sparo_attuale;
		sparo_attuale = scegliSparo (partita.sparo_alieni.pos_x);
		if (animazione)
		{
			sx = 0;			
		}
		else
		{
			sx = al_get_bitmap_width (sparo_attuale) / 2;
		}
		al_draw_tinted_bitmap_region(sparo_attuale, COLORE_DEFAULT, sx, 0, al_get_bitmap_width (sparo_attuale) / 2, al_get_bitmap_height (sparo_attuale), partita.sparo_alieni.pos_x, partita.sparo_alieni.pos_y, 0);
	}
	//FINE DELLA VISUALIZZAZIONE DELLO SPARO DEGLI ALIENI

	//INIZIO DELLA VISUALIZZAZIONE DELLE BARRIERE
	pos_x_attuale = DISTANZA_BARRIERE;
	for (unsigned int i = 0; i < N_BARRIERE; i++)
	{
		disegnaBarriera (barriera, partita.barriere [i], pos_x_attuale, POS_Y_BARRIERE);
		pos_x_attuale += DISTANZA_BARRIERE + larghezzaLatoUnitaBarriera () * LARG_BARRIERA;
	}
	//FINE DELLA VISUALIZZAZIONE DELLE BARRIERE

	//INIZIO DELLA VISUALIZZAZIONE DELLO SPARO DEL CARRO
	if (partita.carro_armato.sparo.stato)
	{
		al_draw_tinted_bitmap(sparo_carro, COLORE_DEFAULT, partita.carro_armato.sparo.pos_x, partita.carro_armato.sparo.pos_y, 0);
	}
	//FINE DELLA VISUALIZZAIZOEN DELLO SPARO DEL CARRO

	//INIZIO DELLA VISUALIZZAZIONE DEL CARRO ARMATO
	if (partita.carro_armato.esplosione > 1)
	{
		unsigned int sx;
		if (partita.carro_armato.esplosione % 2 == 1)
		{
			sx = 0;
		}
		else
		{
			sx = al_get_bitmap_width (esplosione_carro) / N_STATI_SPRITE;
		}
		al_draw_tinted_bitmap_region(esplosione_carro, COLORE_DEFAULT, sx, 0, al_get_bitmap_width (esplosione_carro) / N_STATI_SPRITE, al_get_bitmap_height (esplosione_carro), partita.carro_armato.pos_x, MARGINE_INF_GIOCO - al_get_bitmap_height (esplosione_carro), 0);
	}
	else
	{
		al_draw_tinted_bitmap(carro_armato, COLORE_DEFAULT, partita.carro_armato.pos_x, MARGINE_INF_GIOCO - al_get_bitmap_height (carro_armato), 0);
	}
	//FINE DELLA VISUALIZZAZIONE DEL CARRO ARMATO

	al_flip_display();
	//FINE VISUALIZZAZIONE
}

void stampaImpostazioni (Impostazioni impostazioni, Menu menu_impostazioni, bool redraw_lampeggio)
{
	//INIZIO VISUALIZZAZIONE
	al_clear_to_color(NERO);

	unsigned int pos_y_attuale = POS_Y_TITOLO_IMPOSTAZIONI;
	unsigned int pos_x_attuale = POS_X_VOCI_IMPOSTAZIONI;

	//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
	al_draw_text(font_testo, COLORE_DEFAULT, pos_x_attuale, pos_y_attuale, ALLEGRO_ALIGN_LEFT, "IMPOSTAZIONI:");
	//FINE DELLA VISUALIZZAZIONE DEL TITOLO

	//INIZIO DELLA VISUALIZZAZIONE DELLE IMPOSTAZIONI
	pos_y_attuale = POS_Y_IMPOSTAZIONI;
	for (int i = 0; i < N_VOCI_MENU_IMPO; i++)
	{	
		pos_y_attuale += DIMENSIONE_TESTO + SPAZIO_TESTO;
		al_draw_text(font_testo, COLORE_DEFAULT, POS_X_VOCI_IMPOSTAZIONI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, menu_impostazioni.testi_menu [i]);
		pos_x_attuale = POS_X_VALORI_IMPOSTAZIONI;
		if (!(menu_impostazioni.voce_sel == i && !redraw_lampeggio))
		{
			char str_stato [MAX_STRINGA_GENERICA] = "<    ";
			char str_valore [MAX_STRINGA_GENERICA];
			assert(stringaValoreVoceImpostazioni (str_valore, static_cast <voce_menu_impostazioni> (i), impostazioni));
			strcat (str_stato, str_valore);
			strcat (str_stato, "     >");
			al_draw_text(font_testo, COLORE_DEFAULT, pos_x_attuale, pos_y_attuale, ALLEGRO_ALIGN_LEFT, str_stato);
		}
	}
	//FINE DELLA VISUALIZZAZIONE DELLE IMPOSTAZIONI

	//INIZIO DELLA VISUALIZZAZIONE DELLE INDICAZIONI
	pos_y_attuale = POS_Y_INDICAZIONI_IMPOSTAZIONI;
	for (int i = 0; i < N_INDICAZIONI_MENU_IMPO; i++)
	{
		al_draw_text(font_testo, COLORE_DEFAULT, POS_CENTRO_X, pos_y_attuale, ALLEGRO_ALIGN_CENTER, INDICAZIONI_IMPOSTAZIONI [i]);
		pos_y_attuale += DIMENSIONE_TESTO * 2;
	}
	//FINE DELLA VISUALIZZAZIONE DELLE INDICAZIONI	

	al_flip_display();
	//FINE VISUALIZZAZIONE
}

void stampaHighscores (Punteggio highscores [], int n_highscores)
{
	//INIZIO VISUALIZZAZIONE
	al_clear_to_color(NERO);

	unsigned int pos_y_attuale = POS_Y_HIGHSCORES_TITOLO;

	//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
	al_draw_text(font_testo, COLORE_DEFAULT, POS_X_NUMERAZIONE_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, "HIGHSCORES:");
	//FINE DELLA VISUALIZZAZIONE DEL TITOLO

	//INIZIO DELLA VISUALIZZAZIONE DEGLI HIGHSCORES
	pos_y_attuale = POS_Y_ELENCO_PUNTEGGI;

	for (int i = 0; i < n_highscores; i++)
	{
		pos_y_attuale += DIMENSIONE_TESTO + SPAZIO_TESTO;
		char str_numero [MAX_STRINGA_NUMERAZIONE] = "";
		sprintf(str_numero, "%d", i + 1);
		strcat (str_numero, ".");
		al_draw_text(font_testo, COLORE_DEFAULT, POS_X_NUMERAZIONE_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, str_numero);

		char str_valore [] = "";
		sprintf(str_valore, "%d", highscores [i].valore);
		al_draw_text(font_testo, COLORE_DEFAULT, POS_X_NOMI_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, highscores [i].nome);
		al_draw_text(font_testo, COLORE_DEFAULT, POS_X_VALORI_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, str_valore);
	}
	//FINE DELLA VISUALIZZAZIONE DEGLI HIGHSCORES

	//INIZIO DELLA VISUALIZZAZIONE DEL PREMI ENTER
	pos_y_attuale = POS_Y_INDICAZIONI_HIGHSCORES;
	al_draw_text(font_testo, COLORE_DEFAULT, POS_CENTRO_X, pos_y_attuale, ALLEGRO_ALIGN_CENTER, "Premi enter per tornare al menu principale");
	//FINE DELLA VISUALIZZAZIONE DEL PREMI ENTER

	al_flip_display();
	//FINE VISUALIZZAZIONE
}
void stampaMenuPausa (Menu menu_pausa, bool redraw_lampeggio)
{
	//INIZIO VISUALIZZAZIONE
	al_clear_to_color(NERO);
	
	unsigned int pos_y_attuale;

	//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
	al_draw_text(font_testo, COLORE_DEFAULT, POS_CENTRO_X, POS_Y_TITOLO_PAUSA, ALLEGRO_ALIGN_CENTRE, "PAUSA");
	//FINE DELLA VISUALIZZAZIONE DEL TITOLO

	//INIZIO DELLA VISUALIZZAZIONE DEL MENU DI PAUSA
	pos_y_attuale = POS_Y_VOCI_PAUSA;
	for (int i = 0; i < menu_pausa.n_voci; i++)
	{
		if (!(menu_pausa.voce_sel == i && !redraw_lampeggio))
		{
			al_draw_text(font_testo, COLORE_DEFAULT, POS_CENTRO_X, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, menu_pausa.testi_menu [i]);
		}
		pos_y_attuale += SPAZIO_TESTO_GRANDE + DIMENSIONE_TESTO;
	}
	//FINE DELLA VISUALIZZAZIONE DEL MENU DI PAUSA

	al_flip_display();
	//FINE VISUALIZZAZIONE
}

void stampaFinePartita (SpaceInvaders generale, int posizione_punteggio_attuale, bool redraw_lampeggio)
{
	//INIZIO VISUALIZZAZIONE
	al_clear_to_color(NERO);

	unsigned int pos_y_attuale = POS_Y_HIGHSCORES_TITOLO;

	//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
	al_draw_text(font_testo, COLORE_DEFAULT, POS_X_NUMERAZIONE_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, "HIGHSCORES:");
	//FINE DELLA VISUALIZZAZIONE DEL TITOLO

	//INIZIO DELLA VISUALIZZAZIONE DEGLI HIGHSCORES
	pos_y_attuale = POS_Y_ELENCO_PUNTEGGI;

	for (int i = 0, p = 0; i <= generale.n_highscores && i < MAX_HIGHSCORES; i++, p++)
	{
		pos_y_attuale += DIMENSIONE_TESTO + SPAZIO_TESTO;
		char str_numero [MAX_STRINGA_NUMERAZIONE] = "";
		sprintf(str_numero, "%d", i + 1);
		strcat (str_numero, ".");
		al_draw_text(font_testo, COLORE_DEFAULT, POS_X_NUMERAZIONE_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, str_numero);

		char str_valore [] = "";
		unsigned int pos_x_attuale = POS_X_NOMI_PUNTEGGI;
		if (i == posizione_punteggio_attuale)
		{
			char nome_visualizzato [CARATTERI_NOME];
			strcpy (nome_visualizzato, generale.partita_in_corso.punteggio.nome);
			if (strlen (nome_visualizzato) < CARATTERI_NOME)
			{
				strcat (nome_visualizzato, "_");
			}
			p--;
			char lettera [] = " ";
			for (unsigned int j = 0; j < strlen (nome_visualizzato); j++)
			{
				if (!(j == strlen (nome_visualizzato) - 1 && redraw_lampeggio))
				{
					lettera [0] = nome_visualizzato [j];
					al_draw_text(font_testo, COLORE_DEFAULT, pos_x_attuale, pos_y_attuale, ALLEGRO_ALIGN_LEFT, lettera);
					pos_x_attuale += al_get_text_width (font_testo, lettera);
				}
			}
			sprintf(str_valore, "%d", generale.partita_in_corso.punteggio.valore);
		}
		else
		{
			al_draw_text(font_testo, COLORE_DEFAULT, POS_X_NOMI_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, generale.highscores [p].nome);
			sprintf(str_valore, "%d", generale.highscores [p].valore);
		}
		al_draw_text(font_testo, COLORE_DEFAULT, POS_X_VALORI_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, str_valore);
	}
	//FINE DELLA VISUALIZZAZIONE DEGLI HIGHSCORES

	//INIZIO DELLA VISUALIZZAZIONE DEL PREMI ENTER
	al_draw_text(font_testo, COLORE_DEFAULT, POS_CENTRO_X, POS_Y_INDICAZIONI_HIGHSCORES, ALLEGRO_ALIGN_CENTER, "Premi enter per salvare e tornare al menu principale");
	//FINE DELLA VISUALIZZAZIONE DEL PREMI ENTER

	al_flip_display();
	//FINE VISUALIZZAZIONE
}

unsigned int altezzaCarroArmato ()
{
	return al_get_bitmap_height (carro_armato);
}

unsigned int larghezzaCarroArmato ()
{
	return al_get_bitmap_width (carro_armato);
}

unsigned int altezzaNavicellaMisteriosa ()
{
	return al_get_bitmap_height (navicella_misteriosa);
}

unsigned int larghezzaNavicellaMisteriosa ()
{
	return al_get_bitmap_width (navicella_misteriosa);
}

unsigned int altezzaSparoAlienoAttuale (unsigned int pos_x_sparo)
{
	return al_get_bitmap_height (scegliSparo (pos_x_sparo)) / N_STATI_SPRITE;
}

unsigned int larghezzaSparoAlienoAttuale (unsigned int pos_x_sparo)
{
	return al_get_bitmap_width (scegliSparo (pos_x_sparo)) / N_STATI_SPRITE;
}

unsigned int altezzaSparoCarroArmato ()
{
	return al_get_bitmap_height (carro_armato);
}

unsigned int larghezzaSparoCarroArmato ()
{
	return al_get_bitmap_width (sparo_carro);
}

unsigned int altezzaAlieni ()
{
	return al_get_bitmap_height (alieno_tipo_1);
}

unsigned int larghezzaAlieno1 ()
{
	return al_get_bitmap_width (alieno_tipo_1) / N_STATI_SPRITE;
}

unsigned int larghezzaAlieno2 ()
{
	return al_get_bitmap_width (alieno_tipo_2) / N_STATI_SPRITE;
}

unsigned int larghezzaAlieno3 ()
{
	return al_get_bitmap_width (alieno_tipo_3) / N_STATI_SPRITE;
}

unsigned int larghezzaLatoUnitaBarriera ()
{
	return al_get_bitmap_width (barriera) / N_STATI_SPRITE;
}
//FINE MODULO