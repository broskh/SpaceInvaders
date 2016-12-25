/*
 * File contenente il modulo per la gestione della grafica.
 */

using namespace std;
#include <iostream>
#include <cassert>
#include <cstdio>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "strutture_dati.h"
#include "gestione_grafica.h"
#include "gestione_menu.h"
#include "gestione_partita.h"

//INIZIO CONFIGURAZIONE TRACING
/*#ifdef DEBUG_MODE
	#ifdef DEBUG_LEVEL
		static unsigned int debug_level = DEBUG_LEVEL;
	#else
		static unsigned int debug_level = 0;
	#endif
#endif*/
//FINE CONFIGURAZIONE TRACING

//INIZIO VARIABILI DI MODULO
static ALLEGRO_BITMAP *unita_barriera = NULL; /**<Immagine utilizzata per rappresentare un'unità di barriera.*/
static ALLEGRO_BITMAP *carro_armato = NULL; /**<Immagine utilizzata per rappresentare il carro armato.*/
static ALLEGRO_BITMAP *esplosione_alieno = NULL; /**<Immagine utilizzata per rappresentare l'esplosione di un alieno.*/
static ALLEGRO_BITMAP *esplosione_carro = NULL; /**<Immagine utilizzata per rappresentare l'esplosione del carro armato.*/
static ALLEGRO_BITMAP *navicella_misteriosa = NULL; /**<Immagine utilizzata per rappresentare la navicella misteriosa.*/
static ALLEGRO_BITMAP *spari_alieni [N_TIPI_ALIENI] = {NULL, NULL}; /**<Immagini utilizzate per rappresentare gli spari alieni.*/
static ALLEGRO_BITMAP *sparo_carro = NULL; /**<Immagine utilizzata per rappresentare lo sparo del carro armato.*/
static ALLEGRO_BITMAP *tipi_alieni [N_TIPI_ALIENI] = {NULL, NULL, NULL}; /**<Immagine utilizzata per rappresentare i diversi alieni.*/
static ALLEGRO_COLOR ARANCIONE; /**<Colore arancione.*/
static ALLEGRO_COLOR BIANCO; /**<Colore bianco.*/
static ALLEGRO_COLOR BLU; /**<Colore blu.*/
static ALLEGRO_COLOR COLORE_DEFAULT; /**<Colore usato di default.*/
static ALLEGRO_COLOR GIALLO; /**<Colore giallo.*/
static ALLEGRO_COLOR GRIGIO; /**<Colore grigio.*/
static ALLEGRO_COLOR NERO; /**<Colore nero.*/
static ALLEGRO_COLOR ROSSO; /**<Colore rosso.*/
static ALLEGRO_COLOR VERDE; /**<Colore verde.*/
static ALLEGRO_FONT *font_testo = NULL; /**<Font utilizzato per scrivere il testo presente all'interno del gioco.*/
static ALLEGRO_FONT *font_titolo = NULL; /**<Font utilizzato per scrivere esclusivamente il titolo del gioco nel menù principale.*/
//FINE VARIABILI DI MODULO

//INIZIO MODULO
//INIZIO FUNZIONI PRIVATE
/*
 * Disegna una barriera data la matrice contenente lo stato di ogni unità della barriera e le posizioni rispetto
 * all'asse x e y del punto iniziale.
 */
void disegnaBarriera (stato_barriera barriera [ALTEZZA_BARRIERA] [LARGHEZZA_BARRIERA], unsigned int pos_x, unsigned int pos_y)
{
	assert (unita_barriera);
	unsigned int dx = pos_x; 
	unsigned int dy = pos_y;

	for (unsigned int i = 0; i < ALTEZZA_BARRIERA; i++)
	{
		for (unsigned int j = 0; j < LARGHEZZA_BARRIERA; j++)
		{
			if (barriera [i] [j] == integra)
			{
				al_draw_tinted_bitmap_region(unita_barriera, COLORE_DEFAULT, 0, 0, larghezzaLatoUnitaBarriera (), altezzaLatoUnitaBarriera (), dx, dy, 0);
			}
			else if (barriera [i] [j] == parziale)
			{
				al_draw_tinted_bitmap_region(unita_barriera, COLORE_DEFAULT, larghezzaLatoUnitaBarriera (), 0, larghezzaLatoUnitaBarriera (), altezzaLatoUnitaBarriera (), dx, dy, 0);
			}
			dx += larghezzaLatoUnitaBarriera ();
		}
		dx = pos_x;
		dy += larghezzaLatoUnitaBarriera ();
	}
}

/*
 * Sceglie l'alieno da mostrare sulla base del numero di fila dell'ondata nella quale si trova.
 */
ALLEGRO_BITMAP* scegliAlieno (unsigned int numero_fila)
{
	if (numero_fila < N_FILE_ALIENI)
	{
		unsigned int range = N_FILE_ALIENI / N_TIPI_ALIENI;
		return tipi_alieni [numero_fila / range];
	}
	return NULL;
}

/*
 * Converte una variabile di tipo "colore" in una di tipo "ALLEGRO_COLOR".
 */
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

/*
 * Sceglie lo sparo da mostrare sulla base della posizione rispetto all'asse x dello sparo.
 */
ALLEGRO_BITMAP * scegliSparo (int pos_x)
{
	assert (spari_alieni [pos_x % 2]); 
	return spari_alieni [pos_x % 2];
}
//FINE FUNZIONI PRIVATE

unsigned int altezzaAlieno ()
{
	assert ((tipi_alieni [0]));
	return al_get_bitmap_height (tipi_alieni [0]); //gli alieni hanno tutta la stessa altezza
}

unsigned int altezzaCarroArmato ()
{
	assert (carro_armato);
	return al_get_bitmap_height (carro_armato);
}

unsigned int altezzaLatoUnitaBarriera ()
{
	assert (unita_barriera);
	return al_get_bitmap_height (unita_barriera);
}

unsigned int altezzaNavicellaMisteriosa ()
{
	assert (navicella_misteriosa);
	return al_get_bitmap_height (navicella_misteriosa);
}

unsigned int altezzaSparoAlienoAttuale (unsigned int pos_x_sparo)
{
	return al_get_bitmap_height (scegliSparo (pos_x_sparo)) / N_STATI_SPRITE;
}

unsigned int altezzaSparoCarroArmato ()
{
	assert (sparo_carro);
	return al_get_bitmap_height (sparo_carro);
}

void distruggiGrafica ()
{
	al_destroy_font (font_testo);
	al_destroy_font (font_titolo);
	al_destroy_bitmap(spari_alieni [0]);
	al_destroy_bitmap(spari_alieni [1]);
	al_destroy_bitmap(unita_barriera);
	al_destroy_bitmap(carro_armato);
	al_destroy_bitmap(sparo_carro);
	al_destroy_bitmap(navicella_misteriosa);
	al_destroy_bitmap(tipi_alieni [0]);
	al_destroy_bitmap(tipi_alieni [1]);
	al_destroy_bitmap(tipi_alieni [2]);
	al_destroy_bitmap(esplosione_carro);
	al_destroy_bitmap(esplosione_alieno);
}

bool inizializzaGrafica ()
{ 
	if (!al_init_image_addon())
	{
		D1(cout<<"<Image addon non inizializzato correttamente."<<endl);
		return false;
	}
	if (!al_init_font_addon())
	{
		D1(cout<<"Font addon non inizializzato correttamente."<<endl);
		return false;
	}
	if (!al_init_ttf_addon())
	{
		D1(cout<<"ttf addon non inizializzato correttamente."<<endl);
		return false;
	} 

	font_titolo = al_load_ttf_font(FILE_FONT_TITOLO, DIMENSIONE_TITOLO, 0);
	if (!font_titolo)
	{
		D1(cout<<"font_titolo non creato correttamente."<<endl);
		return false;
	}
	font_testo = al_load_ttf_font(FILE_FONT_TESTO, DIMENSIONE_TESTO, 0);
 	if (!font_testo)
	{
		D1(cout<<"font_testo non creato correttamente."<<endl);
		return false;
	}
	
	unita_barriera = al_load_bitmap(FILE_BARRIERA);
	if (!unita_barriera)
	{
		D1(cout<<"unita_barriera non creata correttamente."<<endl);
		return false;
	}
	spari_alieni [0] = al_load_bitmap(FILE_SPARO_ALIENI_1);
	if (!spari_alieni [0])
	{
		D1(cout<<"spari_alieni [0] non creato correttamente."<<endl);
		return false;
	}
	spari_alieni [1] = al_load_bitmap(FILE_SPARO_ALIENI_2);
	if (!spari_alieni [1])
	{
		D1(cout<<"spari_alieni [1] non creato correttamente."<<endl);
		return false;
	}
	esplosione_carro = al_load_bitmap(FILE_ESPLOSIONE_CARRO);
	if (!esplosione_carro)
	{
		D1(cout<<"esplosione_carro non creata correttamente."<<endl);
		return false;
	}
	esplosione_alieno = al_load_bitmap(FILE_ESPLOSIONE_ALIENO);
	if (!esplosione_alieno)
	{
		D1(cout<<"esplosione_alieno non creata correttamente."<<endl);
		return false;
	}
	carro_armato = al_load_bitmap(FILE_CARRO_ARMATO);
	if (!carro_armato)
	{
		D1(cout<<"carro_armato non creato correttamente."<<endl);
		return false;
	}
	sparo_carro = al_load_bitmap(FILE_SPARO_CARRO);
	if (!sparo_carro)
	{
		D1(cout<<"sparo_carro non creato correttamente."<<endl);
		return false;
	}
	navicella_misteriosa = al_load_bitmap(FILE_NAVICELLA_MISTERIOSA);
	if (!navicella_misteriosa)
	{
		D1(cout<<"navicella_misteriosa non creata correttamente."<<endl);
		return false;
	}
	tipi_alieni [0] = al_load_bitmap(FILE_ALIENO_TIPO_1);
	if (!tipi_alieni [0])
	{
		D1(cout<<"tipi_alieni [0] non creato correttamente."<<endl);
		return false;
	}
	tipi_alieni [1] = al_load_bitmap(FILE_ALIENO_TIPO_2);
	if (!tipi_alieni [1])
	{
		D1(cout<<"tipi_alieni [1] non creato correttamente."<<endl);
		return false;
	}
	tipi_alieni [2] = al_load_bitmap(FILE_ALIENO_TIPO_3);
	if (!tipi_alieni [2])
	{
		D1(cout<<"tipi_alieni [2] non creato correttamente."<<endl);
		return false;
	}

	VERDE = al_map_rgb(0, 255, 0);
	BIANCO = al_map_rgb(255, 255, 255);
	ARANCIONE = al_map_rgb(255, 128, 0);
	GIALLO = al_map_rgb(255, 255, 0);
	BLU = al_map_rgb(0, 0, 255);
	ROSSO = al_map_rgb(255, 0, 0);
	NERO = al_map_rgb(0, 0, 0);
	GRIGIO = al_map_rgb(84, 84, 84);
	COLORE_DEFAULT = VERDE;
	return true;
}

unsigned int larghezzaAlieno (unsigned int n_fila_alieno)
{
	assert (tipi_alieni [n_fila_alieno]);
	return al_get_bitmap_width (tipi_alieni [n_fila_alieno]) / N_STATI_SPRITE;
}

unsigned int larghezzaCarroArmato ()
{
	assert (carro_armato);
	return al_get_bitmap_width (carro_armato);
}

unsigned int larghezzaLatoUnitaBarriera ()
{
	assert (unita_barriera);
	return al_get_bitmap_width (unita_barriera) / N_STATI_SPRITE;
}

unsigned int larghezzaNavicellaMisteriosa ()
{
	assert (navicella_misteriosa);
	return al_get_bitmap_width (navicella_misteriosa);
}

unsigned int larghezzaSparoAlienoAttuale (unsigned int pos_x_sparo)
{
	return al_get_bitmap_width (scegliSparo (pos_x_sparo)) / N_STATI_SPRITE;
}

unsigned int larghezzaSparoCarroArmato ()
{
	assert (sparo_carro);
	return al_get_bitmap_width (sparo_carro);
}

void stampaFinePartita (Classifica classifica, Partita partita, int posizione_punteggio_attuale, bool redraw_lampeggio)
{
	assert (font_testo);
	//INIZIO VISUALIZZAZIONE
	al_clear_to_color(NERO);

	//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
	unsigned int pos_y_attuale = POS_Y_HIGHSCORES_TITOLO;
	al_draw_text(font_testo, COLORE_DEFAULT, POS_X_NUMERAZIONE_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, STRINGA_TITOLO_HIGHSCORES);
	//FINE DELLA VISUALIZZAZIONE DEL TITOLO

	//INIZIO DELLA VISUALIZZAZIONE DEGLI HIGHSCORES
	pos_y_attuale = POS_Y_ELENCO_PUNTEGGI;

	posizione_punteggio_attuale--; //posizione nell'array
	for (int i = 0, p = 0; i <= classifica.n_highscores && i < MAX_HIGHSCORES; i++, p++)
	{
		pos_y_attuale += DIMENSIONE_TESTO + SPAZIO_TESTO;
		numbering_string str_numero = "";
		sprintf(str_numero, "%d", i + 1);
		strcat (str_numero, ".");
		al_draw_text(font_testo, COLORE_DEFAULT, POS_X_NUMERAZIONE_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, str_numero);

		generic_string str_valore = "";
		if (i == posizione_punteggio_attuale)
		{
			char nome_visualizzato [CARATTERI_NOME];
			strcpy (nome_visualizzato, partita.punteggio.nome);
			if (strlen (nome_visualizzato) < CARATTERI_NOME) //se il nome non ha raggiunto la dimensione massima metto come ultimo carattere _
			{
				strcat (nome_visualizzato, "_");
			}
			p--; //nel momento in cui vene mostrato il nuovo ponteggio nella corretta posizione, p assume un valore minore di 1 per poter mostrare correttamente gli altri punteggi in classifica
			if (redraw_lampeggio)
			{
				nome_visualizzato [strlen (nome_visualizzato) - 1] = '\0'; //se devo fare l'effetto lampeggio tolgo l'ultimo carattere del nome
			}
			al_draw_text(font_testo, COLORE_DEFAULT, POS_X_NOMI_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, nome_visualizzato);
			sprintf(str_valore, "%d", partita.punteggio.valore);
		}
		else
		{
			al_draw_text(font_testo, COLORE_DEFAULT, POS_X_NOMI_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, classifica.highscores [p].nome);
			sprintf(str_valore, "%d", classifica.highscores [p].valore);
		}
		al_draw_text(font_testo, COLORE_DEFAULT, POS_X_VALORI_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, str_valore);
	}
	//FINE DELLA VISUALIZZAZIONE DEGLI HIGHSCORES

	//INIZIO DELLA VISUALIZZAZIONE DEL PREMI ENTER
	al_draw_text(font_testo, COLORE_DEFAULT, POS_CENTRO_X, POS_Y_INDICAZIONI_HIGHSCORES, ALLEGRO_ALIGN_CENTER, STRINGA_INDICAZIONI_FINE_PARTITA);
	//FINE DELLA VISUALIZZAZIONE DEL PREMI ENTER

	al_flip_display();
	//FINE VISUALIZZAZIONE
}

void stampaGioca (Partita partita, bool animazione, colore colore_alieni)
{
	assert (font_testo);
	assert (navicella_misteriosa);
	assert (esplosione_alieno);
	assert (sparo_carro);
	assert (esplosione_carro);
	assert (carro_armato);
	//INIZIO VISUALIZZAZIONE
	al_clear_to_color(NERO);

	unsigned int pos_y_attuale;
	unsigned int pos_x_attuale;

	//INIZIO DELLA VISUALIZZAZIONE DELLE INFORMAZIONI
	generic_string stringa_punteggio;
	strcpy (stringa_punteggio, STRINGA_PUNTEGGIO);
	generic_string valore_punteggio;
	sprintf(valore_punteggio, "%d", partita.punteggio.valore);
	strcat (stringa_punteggio, valore_punteggio);
	pos_x_attuale = (POS_CENTRO_X - al_get_text_width(font_testo, stringa_punteggio)) / 2;
	al_draw_text(font_testo, COLORE_DEFAULT, pos_x_attuale, POS_Y_INFORMAZIONI_PARTITA, ALLEGRO_ALIGN_LEFT, stringa_punteggio);

	generic_string stringa_vite;
	strcpy (stringa_vite, STRINGA_VITE);
	generic_string valore_vite;
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
		ALLEGRO_BITMAP * alieno_scelto = scegliAlieno (i);
		for (unsigned int j = 0; j < N_COL_ALIENI; j++)
		{
			if (partita.ondata.alieni [i] [j].esplosione)
			{
				al_draw_tinted_bitmap(esplosione_alieno, colore_ondata, pos_x_attuale - (al_get_bitmap_width (esplosione_alieno) / 2), pos_y_attuale, 0);
			}
			else if (partita.ondata.alieni [i] [j].stato)
			{
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
		disegnaBarriera (partita.barriere [i], pos_x_attuale, POS_Y_BARRIERE);
		pos_x_attuale += DISTANZA_BARRIERE + larghezzaLatoUnitaBarriera () * LARGHEZZA_BARRIERA;
	}
	//FINE DELLA VISUALIZZAZIONE DELLE BARRIERE

	//INIZIO DELLA VISUALIZZAZIONE DELLO SPARO DEL CARRO
	if (partita.carro_armato.sparo.stato)
	{
		al_draw_tinted_bitmap(sparo_carro, COLORE_DEFAULT, partita.carro_armato.sparo.pos_x, partita.carro_armato.sparo.pos_y, 0);
	}
	//FINE DELLA VISUALIZZAZIONE DELLO SPARO DEL CARRO

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

void stampaHighscores (Classifica classifica)
{
	assert (font_testo);
	//INIZIO VISUALIZZAZIONE
	al_clear_to_color(NERO);

	unsigned int pos_y_attuale = POS_Y_HIGHSCORES_TITOLO;

	//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
	al_draw_text(font_testo, COLORE_DEFAULT, POS_X_NUMERAZIONE_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, STRINGA_TITOLO_HIGHSCORES);
	//FINE DELLA VISUALIZZAZIONE DEL TITOLO

	//INIZIO DELLA VISUALIZZAZIONE DEGLI HIGHSCORES
	pos_y_attuale = POS_Y_ELENCO_PUNTEGGI;

	for (int i = 0; i < classifica.n_highscores; i++)
	{
		pos_y_attuale += DIMENSIONE_TESTO + SPAZIO_TESTO;
		numbering_string str_numero;
		sprintf(str_numero, "%d", i + 1);
		strcat (str_numero, ".");
		al_draw_text(font_testo, COLORE_DEFAULT, POS_X_NUMERAZIONE_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, str_numero);

		generic_string str_valore;
		sprintf(str_valore, "%d", classifica.highscores [i].valore);
		al_draw_text(font_testo, COLORE_DEFAULT, POS_X_NOMI_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, classifica.highscores [i].nome);
		al_draw_text(font_testo, COLORE_DEFAULT, POS_X_VALORI_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, str_valore);
	}
	//FINE DELLA VISUALIZZAZIONE DEGLI HIGHSCORES

	//INIZIO DELLA VISUALIZZAZIONE DEL PREMI ENTER
	pos_y_attuale = POS_Y_INDICAZIONI_HIGHSCORES;
	al_draw_text(font_testo, COLORE_DEFAULT, POS_CENTRO_X, pos_y_attuale, ALLEGRO_ALIGN_CENTER, STRINGA_INDICAZIONI_HIGHSCORES);
	//FINE DELLA VISUALIZZAZIONE DEL PREMI ENTER

	al_flip_display();
	//FINE VISUALIZZAZIONE
}

void stampaImpostazioni (Menu menu_impostazioni, Impostazioni impostazioni, bool redraw_lampeggio)
{
	assert (font_testo);
	//INIZIO VISUALIZZAZIONE
	al_clear_to_color(NERO);

	unsigned int pos_y_attuale = POS_Y_TITOLO_IMPOSTAZIONI;
	unsigned int pos_x_attuale = POS_X_VOCI_IMPOSTAZIONI;

	//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
	al_draw_text(font_testo, COLORE_DEFAULT, pos_x_attuale, pos_y_attuale, ALLEGRO_ALIGN_LEFT, STRINGA_TITOLO_IMPOSTAZIONI);
	//FINE DELLA VISUALIZZAZIONE DEL TITOLO

	//INIZIO DELLA VISUALIZZAZIONE DELLE IMPOSTAZIONI
	pos_y_attuale = POS_Y_IMPOSTAZIONI;
	for (int i = 0; i < N_VOCI_MENU_IMPO; i++)
	{	
		pos_y_attuale += DIMENSIONE_TESTO + SPAZIO_TESTO;
		al_draw_text(font_testo, COLORE_DEFAULT, POS_X_VOCI_IMPOSTAZIONI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, menu_impostazioni.testi_menu [i]);
		pos_x_attuale = POS_X_VALORI_IMPOSTAZIONI;
		if (!(menu_impostazioni.voce_selezionata == i && !redraw_lampeggio))
		{
			generic_string str_stato = "<    ";
			generic_string str_valore;
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

void stampaMenuPausa (Menu menu_pausa, bool redraw_lampeggio)
{
	assert (font_testo);
	//INIZIO VISUALIZZAZIONE
	al_clear_to_color(NERO);
	
	unsigned int pos_y_attuale;

	//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
	al_draw_text(font_testo, COLORE_DEFAULT, POS_CENTRO_X, POS_Y_TITOLO_PAUSA, ALLEGRO_ALIGN_CENTRE, STRINGA_TITOLO_PAUSA);
	//FINE DELLA VISUALIZZAZIONE DEL TITOLO

	//INIZIO DELLA VISUALIZZAZIONE DEL MENU DI PAUSA
	pos_y_attuale = POS_Y_VOCI_PAUSA;
	for (int i = 0; i < menu_pausa.n_voci; i++)
	{
		if (!(menu_pausa.voce_selezionata == i && !redraw_lampeggio))
		{
			al_draw_text(font_testo, COLORE_DEFAULT, POS_CENTRO_X, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, menu_pausa.testi_menu [i]);
		}
		pos_y_attuale += SPAZIO_TESTO_GRANDE + DIMENSIONE_TESTO;
	}
	//FINE DELLA VISUALIZZAZIONE DEL MENU DI PAUSA

	al_flip_display();
	//FINE VISUALIZZAZIONE
}

void stampaMenuPrincipale (Menu menu_principale, bool partita_salvata, colore colore_alieni, bool redraw_lampeggio)
{
	assert (font_titolo);
	assert (font_testo);
	assert (tipi_alieni [0]);
	assert (tipi_alieni [1]);
	assert (tipi_alieni [2]);
	assert (navicella_misteriosa);
	//INIZIO VISUALIZZAZIONE
	al_clear_to_color(NERO);

	//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
	al_draw_text(font_titolo, COLORE_DEFAULT, POS_CENTRO_X, POS_Y_TITOLO_MENU_PRINCIPALE, ALLEGRO_ALIGN_CENTRE, STRINGA_TITOLO_MENU_PRINCIPALE);
	//FINE DELLA VISUALIZZAZIONE DEL TITOLO

	//INIZIO DELLA VISUALIZZAZIONE DEGLI ALIENI E I RELATIVI PUNTEGGI
	ALLEGRO_COLOR colore_allegro = scelgliColore (colore_alieni);
	unsigned int pos_y_attuale = POS_Y_ESMEPIO_ALIENI;
	for (unsigned int i = 0; i < N_TIPI_ALIENI; i++)
	{
		al_draw_tinted_bitmap_region(tipi_alieni [i], colore_allegro, 0, 0, larghezzaAlieno (i), altezzaAlieno (), POS_X_ESEMPIO_ALIENI - larghezzaAlieno (i) / 2, pos_y_attuale, 0);
		char stringa_punteggio [] = "=      ";
		generic_string valore_punteggio;
		sprintf(valore_punteggio, "%d", PUNTEGGIO_ALIENI [i]);
		strcat (stringa_punteggio, valore_punteggio);
		strcat (stringa_punteggio, STRINGA_PUNTEGGIO_ALIENI);
		al_draw_text(font_testo, COLORE_DEFAULT, POS_X_ESEMPIO_PUNTEGGIO, pos_y_attuale, ALLEGRO_ALIGN_LEFT, stringa_punteggio);

		pos_y_attuale += SPAZIO_TESTO + altezzaAlieno ();
	}

	al_draw_tinted_bitmap(navicella_misteriosa, ROSSO, POS_X_ESEMPIO_ALIENI - al_get_bitmap_width (navicella_misteriosa) / 2, pos_y_attuale, 0);
	al_draw_text(font_testo, COLORE_DEFAULT, POS_X_ESEMPIO_PUNTEGGIO, pos_y_attuale, ALLEGRO_ALIGN_LEFT, STRINGA_PUNTEGGIO_NAVICELLA_MISTERIOSA);
	//FINE DELLA VISUALIZZAZIONE DEGLI ALIENI E I RELATIVI PUNTEGGI

	//INIZIO DELLA VISUALIZZAZIONE DEL MENU
	for (int i = 0; i < menu_principale.n_voci; i++)
	{
		if (!(menu_principale.voce_selezionata == i && !redraw_lampeggio))
		{
			pos_y_attuale = POS_Y_VOCI_MENU_PRINCIPALE + (SPAZIO_TESTO + DIMENSIONE_TESTO) * i;
			if ((!partita_salvata) && (static_cast <voce_menu_principale> (i) == v_carica)) //se non c'è una partita salvata e la voce che si sta rappresentando è quella del carica partita
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
//FINE MODULO
