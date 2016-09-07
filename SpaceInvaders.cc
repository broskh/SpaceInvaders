/**
 * Riproduzione del celebre videogioco "Space Inavaders" con qualche lieve
 * variazione rispetto all'originale.
 * 
 * Mantiene inalterate tutte le caratteristiche del gioco originale.
 * Avremo quindi a che fare con una navicella, la quale avrà il compito di
 * abbattere, finchè avrà vite a disposizione, tutte le ondate di alieni che
 * ripetutamente si avvicineranno.
 *
 * Man mano che colpirà gli alieni, a seconda del tipo di alieno colpito,
 * il giocatore incrementerà il proprio vantaggio.
 *
 * Il giocatore ad inizio partita avrà a disposizione tre barriere che quando
 * colpite dagli alieni tenderanno prima a sgretolarsi, e infine a distruggersi.
 *
 * Attraverso le impostazioni è possibile abilitare o meno la musica e gli effetti
 * audio. Inoltre è possibile modificare la grafica cromatica degli alieni e
 * impostare il numero di vite con le quali si intende iniziare la partita.
 *
 * All'interno della partita è possibile mettere in pausa il gioco ed eventualmente
 * effettuare un salvataggio della partita, per poter così ricominciare a
 * giocare in un secondo momento da dove è stata precedentemente interrotta una
 * partita.
 *
 * Vedere la documentazione della funzione ::main
 * per maggiori dettagli sulle funzionalita' e sulla loro
 * implementazione.
 *
 * @author Alessio Scheri
 */

/* 
 * File contenente il modulo Main.
 */

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "struttura_dati.h"
#include "gestione_partita.h"
#include "gestione_impostazioni.h"
#include "gestione_highscores.h"
#include "gestione_menu.h"

using namespace std;

const unsigned int LARGHEZZA_DISPLAY = 640; /**<Larghezza della finestra del gioco.*/
const unsigned int ALTEZZA_DISPLAY = 480; /**<Altezza della finestra del gioco.*/

const float FPS = 60;  /**<FPS del gioco.*/
const float FPS_LAMPEGGIO_MENU = 3.5; /**FPS per mostrare l'effetto di lampeggio sull'opzione selezionata del menù.*/
const unsigned int CENTRO_ORIZ = LARGHEZZA_DISPLAY / 2; /**<Posizione centrale della larghezza del display.*/

const unsigned int SPAZIO_TESTO = 10; /**<Spazio fra righe di testo adiacenti.*/
const unsigned int DIM_FONT_TITOLO = 140; /**<Dimensione del font utilizzato per il titolo.*/
const unsigned int DIM_FONT_TEXT = 15; /**<Dimensione del font utilizzato per i testi generali.*/
const unsigned int DIM_MOSTRI = 20; /**<Dimensione del font utilizzato per i mostri*/
//const float RAPP_DIM = 0.9;

const char FRECCIA [] = "<-"; /**<Stringa per rappresentare la freccia di selezione del menù.*/

const char FILE_FONT_TESTO [] = "Fonts/space_invaders.ttf"; /**<File contenente il font utilizzato per i testi.*/
const char FILE_FONT_IMMAGINI [] = "Fonts/dustbust_invaders.ttf"; /**<File contenente il font utilizzato per i mostri e tutte le altre immagini presenti nel gioco.*/

const char FILE_HIGHSCORES [] = "highscores"; /**<Nome del file contenente gli highscores.*/
const char FILE_IMPOSTAZIONI [] = "SpaceInvaders.config"; /**<Nome del file contenente le impostazioni salvate.*/
const char FILE_SALVATAGGIO_PARTITA [] = "partita.sav"; /**<Nome del file contenente la partita salvata.*/

const char FILE_MUSICA_PRINCIPALE [] = "Sounds/principale.flac"; /**<Nome del file contenente la musica principale.*/

/**
 * Mostra il menù principale e ne gestisce il contenuto.
 * 
 * @param font_titolo Font utilizzato per scrivere il titolo.
 * @param font_titolo Font utilizzato per scrivere il menù.
 * @param font_titolo Font utilizzato per disegnare i mostri.
 * @param voce Voce di menù selezionata.
 * @param redraw_lampeggio Indica se la voce di menù è da ridisegnare o no (utilizzato per mostrare l'effetto lampeggiante sull'opzione di menù selezioanta).
 * @param salvataggio Indica se esiste o meno il salvataggio di una partita precedente (necessario per sapere di che colore disegnare la voce di menù caric).
 */
inline void menuPrincipale (ALLEGRO_FONT *font_titolo, ALLEGRO_FONT *font_menu, ALLEGRO_FONT *font_mostri, Menu menu, bool &redraw_lampeggio, bool salvataggio);

/**
 * Mostra il gioco vero e proprio.
 * 
 * @param font_mostri Font con il quale vengono disegnati i mostri.
 * @param font_testo Font utilizzato per scrivere le stringhe di testo.
 * @param partita Struttura {@link Partita} contenente le informazioni relative alla partita attuale.
 * @param impostazioni Impostazioni generali del gioco.
 */
inline void gioca (ALLEGRO_FONT *font_mostri, ALLEGRO_FONT *font_testo, Partita partita, Impostazioni impostazioni);

/**
 * Mostra il menu di modifica delle impostazioni.
 * 
 * @param font_testo Font utilizzato per scrivere la classifica dei punteggi.
 * @param impostazioni Impostazioni attuali.
 * @param voce Voce del menù impostazioni selezionata.
 * @param redraw_lampeggio Indica se la voce del menù è da ridisegnare o no (utilizzato per mostrare l'effetto lampeggiante sull'opzione di menù selezioanta).
 */
inline void modificaImpostazioni (ALLEGRO_FONT *font_testo, Impostazioni impostazioni, Menu menu, bool redraw_lampeggio);

/**
 * Mostra la classifica dei migliori punteggi.
 * 
 * @param font_testo Font utilizzato per scrivere la classifica dei punteggi.
 * @param highscors Array di strutture {@link Punteggio} contenente i migliori punteggi.
 * @param n_punteggi Numero di punteggi presenti nelal classifica.
 * @param redraw_lampeggio Indica se la dicitura premi enter è da ridisegnare o no (utilizzato per mostrare l'effetto lampeggiante sulla dicitura).
 */
inline void classificaHighscores (ALLEGRO_FONT *font_testo, Punteggio highscores [], int n_punteggi, bool &redraw_lampeggio);

/**
 * FARE DOCUMENTAZIONE PER MAIN
 */
int main ()
{
	ALLEGRO_DISPLAY *display = NULL;
   	ALLEGRO_EVENT_QUEUE *coda_eventi = NULL;
	ALLEGRO_TIMER *frame_rate = NULL;
	ALLEGRO_TIMER *lampeggio_voce = NULL;
   	ALLEGRO_SAMPLE *musica_principale = NULL;
	bool redraw = true;
 
	assert (al_init());
	assert (al_init_font_addon());
	assert (al_init_ttf_addon()); 
	assert (al_install_keyboard());
	assert (al_install_audio());
	assert (al_init_acodec_addon());
	assert (al_reserve_samples(true));
 
	frame_rate = al_create_timer(1.0 / FPS);
	assert (frame_rate);

	lampeggio_voce = al_create_timer(1.0 / FPS_LAMPEGGIO_MENU);
	assert (lampeggio_voce);
 
   	display = al_create_display(LARGHEZZA_DISPLAY, ALTEZZA_DISPLAY);
   	assert (display);
 
   	coda_eventi = al_create_event_queue();
   	assert (coda_eventi);

	ALLEGRO_FONT *font_titolo = al_load_ttf_font(FILE_FONT_IMMAGINI, DIM_FONT_TITOLO, 0);
	assert (font_titolo);
	ALLEGRO_FONT *font_testo = al_load_ttf_font(FILE_FONT_TESTO, DIM_FONT_TEXT, 0);
 	assert (font_testo);
	ALLEGRO_FONT *font_mostri = al_load_ttf_font(FILE_FONT_IMMAGINI, DIM_MOSTRI, 0);
 	assert (font_mostri);

	musica_principale = al_load_sample (FILE_MUSICA_PRINCIPALE);
	assert (musica_principale);
 
   	al_register_event_source(coda_eventi, al_get_display_event_source(display));
	al_register_event_source(coda_eventi, al_get_timer_event_source(frame_rate));
	al_register_event_source(coda_eventi, al_get_timer_event_source(lampeggio_voce));
	al_register_event_source(coda_eventi, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_start_timer(frame_rate);
	
	//INIZIO INIZIALIZZAZIONE DELLA STRUTTURA PRINCIPALE//
	SpaceInvaders generale;
	if (!caricaImpostazioni (generale.impostazioni, FILE_IMPOSTAZIONI))
	{
		impostaValoriImpostazioniDefault (generale.impostazioni);
		salvaImpostazioni (generale.impostazioni, FILE_IMPOSTAZIONI);
	}
	if (!caricaPunteggi (generale.highscores, generale.n_highscores, FILE_HIGHSCORES))
	{
		generale.n_highscores = 0;
	}
	generale.partita_salvata = esisteSalvataggio (FILE_SALVATAGGIO_PARTITA);
	nuovaPartita (generale.partita_in_corso, generale.impostazioni);
	//FINE INIZIALIZZAZIONE DELLA STRUTTURA PRINCIPALE//
	
	schermata schermata_att = s_menu;
	bool cambia_schermata;
	
	Menu menu_principale;
	inizializzaMenu (menu_principale, MENU_PRINCIPALE, N_VOCI_MENU_PRINC, v_gioca);
	Menu menu_impostazioni;
	inizializzaMenu (menu_impostazioni, MENU_IMPOSTAZIONI, N_VOCI_MENU_IMPO, v_musica);
	bool redraw_lampeggio;

	while (true)
	{
		cambia_schermata = false;
		redraw_lampeggio = false;
		switch (schermata_att)
		{
			case s_menu:
				if (generale.impostazioni.musica)
				{
					al_play_sample(musica_principale, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
				}
				else
				{
					al_stop_samples ();
				}
				menu_principale.voce_sel = v_gioca;
				al_start_timer(lampeggio_voce);
				
				while(!cambia_schermata)
			   	{
					ALLEGRO_EVENT ev;
					al_wait_for_event(coda_eventi, &ev);

					if(ev.type == ALLEGRO_EVENT_TIMER)
					{
						if (ev.timer.source == frame_rate)
						{
							redraw = true;
						}
						else if (ev.timer.source == lampeggio_voce)
						{
							redraw_lampeggio = !redraw_lampeggio;
						}
					}
					else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
					{
						schermata_att = s_esci;
						cambia_schermata = true;
						break;
					}
					else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
					{
						switch(ev.keyboard.keycode)
						{
							case ALLEGRO_KEY_UP:
								if (generale.partita_salvata)
								{
									vocePrec (menu_principale);
								}
								else
								{
									vocePrec (menu_principale, v_carica);
								}
								break;
							case ALLEGRO_KEY_DOWN:
								if (generale.partita_salvata)
								{
									voceSuc (menu_principale);
								}
								else
								{
									voceSuc (menu_principale, v_carica);
								}
								break;
							case ALLEGRO_KEY_ENTER:
								schermata_att = cambiaSchermataMenuPrincipale (static_cast <voce_menu_principale> (menu_principale.voce_sel));
								cambia_schermata = true;
								break;
						}
					}

					if(redraw && al_is_event_queue_empty(coda_eventi))
					{
        					al_clear_to_color(al_map_rgb(0, 0, 0));
						menuPrincipale (font_titolo, font_testo, font_mostri, menu_principale, redraw_lampeggio, generale.partita_salvata);
					}
			   	}
				al_stop_timer(lampeggio_voce);
				break;
			case s_gioca:
				if (generale.impostazioni.musica)
				{
					al_stop_samples();
				}
				while(!cambia_schermata)
			   	{
					ALLEGRO_EVENT ev;
					al_wait_for_event(coda_eventi, &ev);

					if(ev.type == ALLEGRO_EVENT_TIMER)
					{
						if (ev.timer.source == frame_rate)
						{
							redraw = true;
						}
					}
					else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
					{
						schermata_att = s_esci;
						cambia_schermata = true;
						break;
					}
					else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
					{
						switch(ev.keyboard.keycode)
						{
							case ALLEGRO_KEY_RIGHT:
								break;
							case ALLEGRO_KEY_LEFT:
								break;
							case ALLEGRO_KEY_SPACE:
								break;
							case ALLEGRO_KEY_ESCAPE:
								break;
						}
					}

					if(redraw && al_is_event_queue_empty(coda_eventi))
					{
        					al_clear_to_color(al_map_rgb(0, 0, 0));
						gioca (font_mostri, font_testo, generale.partita_in_corso, generale.impostazioni);
					}
			   	}
				break;
			case s_carica:
				caricaPartita (generale.partita_in_corso, FILE_SALVATAGGIO_PARTITA);
				schermata_att = s_gioca;
				cambia_schermata = true;
				break;
			case s_opzioni:
				al_start_timer(lampeggio_voce);
				menu_impostazioni.voce_sel = v_musica;

				while(!cambia_schermata)
			   	{				
					ALLEGRO_EVENT ev;
					al_wait_for_event(coda_eventi, &ev);

					if(ev.type == ALLEGRO_EVENT_TIMER)
					{
						if (ev.timer.source == frame_rate)
						{
							redraw = true;
						}
						else if (ev.timer.source == lampeggio_voce)
						{
							redraw_lampeggio = !redraw_lampeggio;
						}
					}
					else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
					{
						schermata_att = s_esci;
						cambia_schermata = true;
						break;
					}
					else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
					{
						switch(ev.keyboard.keycode)
						{
							case ALLEGRO_KEY_UP:
								vocePrec (menu_impostazioni);
								break;
							case ALLEGRO_KEY_DOWN:
								voceSuc (menu_impostazioni);
								break;
							case ALLEGRO_KEY_LEFT:
								assert (valoreCampoImpostazioniPrec (static_cast <voce_menu_impostazioni> (menu_impostazioni.voce_sel), generale.impostazioni));
								break;
							case ALLEGRO_KEY_RIGHT:
								assert (valoreCampoImpostazioniSuc (static_cast <voce_menu_impostazioni> (menu_impostazioni.voce_sel), generale.impostazioni));
								break;
							case ALLEGRO_KEY_ENTER:
								salvaImpostazioni (generale.impostazioni, FILE_IMPOSTAZIONI);
								schermata_att = s_menu;
								cambia_schermata = true;
								break;
							case ALLEGRO_KEY_R:
								impostaValoriImpostazioniDefault (generale.impostazioni);
								break;
						}
					}

					if(redraw && al_is_event_queue_empty(coda_eventi))
					{
        					al_clear_to_color(al_map_rgb(0, 0, 0));
						modificaImpostazioni (font_testo, generale.impostazioni, menu_impostazioni, redraw_lampeggio);
					}
			   	}
				al_stop_timer(lampeggio_voce);
				break;
			case s_highscores:				
				al_start_timer(lampeggio_voce);

				while(!cambia_schermata)
			   	{				
					ALLEGRO_EVENT ev;
					al_wait_for_event(coda_eventi, &ev);

					if(ev.type == ALLEGRO_EVENT_TIMER)
					{
						if (ev.timer.source == frame_rate)
						{
							redraw = true;
						}
						else if (ev.timer.source == lampeggio_voce)
						{
							redraw_lampeggio = !redraw_lampeggio;
						}
					}
					else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
					{
						schermata_att = s_esci;
						cambia_schermata = true;
						break;
					}
					else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
					{
						switch(ev.keyboard.keycode)
						{
							case ALLEGRO_KEY_ENTER:
								schermata_att = s_menu;
								cambia_schermata = true;
								break;
						}
					}

					if(redraw && al_is_event_queue_empty(coda_eventi))
					{
        					al_clear_to_color(al_map_rgb(0, 0, 0));
						classificaHighscores (font_testo, generale.highscores, generale.n_highscores, redraw_lampeggio);
					}
			   	}
				al_stop_timer(lampeggio_voce);
				break;
			case s_pausa:
				//pausa
				break;
			case s_esci:
				al_destroy_display(display);
				al_destroy_timer(frame_rate);
				al_destroy_timer(lampeggio_voce);
				al_destroy_event_queue(coda_eventi);
				al_destroy_sample(musica_principale);
				return 0;
			default:
				return 2;
		}
	}
 
   	al_destroy_display(display);
	al_destroy_timer(frame_rate);
	al_destroy_timer(lampeggio_voce);
   	al_destroy_event_queue(coda_eventi);
	al_destroy_sample(musica_principale);
   	return 1;
}

inline void menuPrincipale (ALLEGRO_FONT *font_titolo, ALLEGRO_FONT *font_menu, ALLEGRO_FONT *font_mostri, Menu menu, bool &redraw_lampeggio, bool salvataggio)
{

	const unsigned int LARG_MOSTRI = 255; /*Larghezza del display dal quale mostrare i mostri.*/
	const unsigned int LARG_PUNTEGGIO = 350; /*Larghezza del display dal quale mostrare i punteggi.*/
	const unsigned int LARG_FRECCIA = 450; /*Larghezza del display dal quale mostrare la freccia di selezione del menu.*/

	const unsigned int ALT_TITOLO = 25; /*Altezza del display dal quale mostrare il titolo.*/
	const unsigned int ALT_MOSTRI = 200; /*Altezza del display dal quale mostrare i mostri.*/
	const unsigned int ALT_MENU = 340; /*Altezza del display dal quale mostrare il menu.*/

	unsigned int alt_attuale = ALT_TITOLO;
	unsigned alt_freccia = ALT_MENU + (SPAZIO_TESTO + DIM_FONT_TEXT) * menu.voce_sel;

	//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
	al_draw_text(font_titolo, al_map_rgb(0, 255, 0), CENTRO_ORIZ, alt_attuale, ALLEGRO_ALIGN_CENTRE, ".");
	//FINE DELLA VISUALIZZAZIONE DEL TITOLO

	//INIZIO DELLA VISUALIZZAZIONE DEI MOSTRI E I RELATIVI PUNTEGGI
	alt_attuale = ALT_MOSTRI;
	al_draw_text(font_mostri, al_map_rgb(0, 255, 0), LARG_MOSTRI, alt_attuale, ALLEGRO_ALIGN_CENTRE, STRINGA_M_10);
	al_draw_text(font_menu, al_map_rgb(0, 255, 0), LARG_PUNTEGGIO, alt_attuale, ALLEGRO_ALIGN_CENTRE, "=      10  PTS");

	alt_attuale = ALT_MOSTRI + SPAZIO_TESTO + DIM_MOSTRI;
	al_draw_text(font_mostri, al_map_rgb(0, 255, 0), LARG_MOSTRI, alt_attuale, ALLEGRO_ALIGN_CENTRE, STRINGA_M_20);
	al_draw_text(font_menu, al_map_rgb(0, 255, 0), LARG_PUNTEGGIO, alt_attuale, ALLEGRO_ALIGN_CENTRE, "=      20  PTS");

	alt_attuale = ALT_MOSTRI + (SPAZIO_TESTO + DIM_MOSTRI) * 2;
	al_draw_text(font_mostri, al_map_rgb(0, 255, 0), LARG_MOSTRI, alt_attuale, ALLEGRO_ALIGN_CENTRE, STRINGA_M_30);
	al_draw_text(font_menu, al_map_rgb(0, 255, 0), LARG_PUNTEGGIO, alt_attuale, ALLEGRO_ALIGN_CENTRE, "=      30  PTS");

	alt_attuale = ALT_MOSTRI + (SPAZIO_TESTO + DIM_MOSTRI) * 3;
	al_draw_text(font_mostri, al_map_rgb(255, 0, 0), LARG_MOSTRI, alt_attuale, ALLEGRO_ALIGN_CENTRE, STRINGA_M_X);
	al_draw_text(font_menu, al_map_rgb(0, 255, 0), LARG_PUNTEGGIO, alt_attuale, ALLEGRO_ALIGN_CENTRE, "=         ?  PTS");
	//FINE DELLA VISUALIZZAZIONE DEI MOSTRI E I RELATIVI PUNTEGGI
	
	//INIZIO DELLA VISUALIZZAZIONE DEL MENU
	for (int i = 0; i < menu.n_voci; i++)
	{
		if (!(menu.voce_sel == i && !redraw_lampeggio))
		{
			alt_attuale = ALT_MENU + (SPAZIO_TESTO + DIM_FONT_TEXT) * i;
			if ((!salvataggio) && (static_cast <voce_menu_principale> (i) == v_carica))
			{
				al_draw_text(font_menu, al_map_rgb(84, 84, 84), CENTRO_ORIZ, alt_attuale, ALLEGRO_ALIGN_CENTRE, menu.testi_menu [i]);
			}
			else
			{
				al_draw_text(font_menu, al_map_rgb(0, 255, 0), CENTRO_ORIZ, alt_attuale, ALLEGRO_ALIGN_CENTRE, menu.testi_menu [i]);
			}
		}
	}

	if (redraw_lampeggio)
	{
		al_draw_text(font_menu, al_map_rgb(0, 255, 0), LARG_FRECCIA, alt_freccia, ALLEGRO_ALIGN_LEFT, FRECCIA);
	}
	//FINE DELLA VISUALIZZAZIONE DEL MENU

	al_flip_display();
}

inline void gioca (ALLEGRO_FONT *font_mostri, ALLEGRO_FONT *font_testo, Partita partita, Impostazioni impostazioni)
{
	const unsigned int ALT_INFO = 20; /*Altezza del display dal quale mostrare le informazioni della partita.*/
	const unsigned int ALT_PRIMA_FILA = 60; /*Altezza del display dal quale mostrare la prima fila di mostri.*/
	const unsigned int ALT_CARRO = 430; /*Altezza del display dal quale mostrare il carro armato.*/

	const unsigned int SPAZIO_ASSI_COL = 40; /*Spazio fra gli assi delle colonne di mostri.*/
	const unsigned int SPAZIO_FILE = 35; /*Spazio fra le file di mostri.*/

	const unsigned int LARG_PRIMO_ASSE = CENTRO_ORIZ - (SPAZIO_ASSI_COL * (N_COL_MOSTRI - 1) / 2); /*Larghezza del display nel quale è presente il primo asse delle colonne di mostri.*/

	unsigned int alt_attuale;
	unsigned int larg_attuale;

	//INIZIO DELLA VISUALIZZAZIONE DELLE INFORMAZIONI
	char stringa_punteggio [] = "Punteggio:    ";
	char valore_punteggio [MAX_STRINGA_GENERICA];
	sprintf(valore_punteggio, "%d", partita.punteggio.valore);
	strcat (stringa_punteggio, valore_punteggio);
	larg_attuale = (CENTRO_ORIZ - al_get_text_width(font_testo, stringa_punteggio)) / 2;
	al_draw_text(font_testo, al_map_rgb(0, 255, 0), larg_attuale, ALT_INFO, ALLEGRO_ALIGN_LEFT, stringa_punteggio);

	char stringa_vite [] = "Vite:    ";
	char valore_vite [MAX_STRINGA_GENERICA];
	sprintf(valore_vite, "%d", partita.vite_rimanenti);
	strcat (stringa_vite, valore_vite);
	larg_attuale = (CENTRO_ORIZ - al_get_text_width(font_testo, stringa_vite)) / 2 + CENTRO_ORIZ;
	al_draw_text(font_testo, al_map_rgb(0, 255, 0), larg_attuale, ALT_INFO, ALLEGRO_ALIGN_CENTRE, stringa_vite);
	//FINE DELLA VISUALIZZAZIONE DELLE INFORMAZIONI

	//INIZIO DELLA VISUALIZZAZIONE DELL'ONDATA
	alt_attuale = ALT_PRIMA_FILA;

	for (unsigned int i = 0; i < N_FILE_MOSTRI; i++)
	{
		larg_attuale = LARG_PRIMO_ASSE;
		for (unsigned int j = 0; j < N_COL_MOSTRI; j++)
		{
			if (partita.ondata.mostri [i] [j].stato)
			{
				al_draw_text(font_mostri, al_map_rgb(0, 255, 0), larg_attuale, alt_attuale, ALLEGRO_ALIGN_CENTER, partita.ondata.mostri [i] [j].stringa);
			}
			larg_attuale += SPAZIO_ASSI_COL;
		}
		alt_attuale += SPAZIO_FILE;
	}
	//FINE DELLA VISUALIZZAZIONE DELL'ONDATA

	//INIZIO DELLA VISUALIZZAZIONE DELLE BARRIERE
	//FINE DELLA VISUALIZZAZIONE DELLE BARRIERE
	
	//INIZIO DELLA VISUALIZZAZIONE DELLO SPARO
	alt_attuale = ALT_CARRO - DIM_MOSTRI;
	al_draw_text(font_testo, al_map_rgb(0, 255, 0), CENTRO_ORIZ + 1, alt_attuale, ALLEGRO_ALIGN_CENTER, STRINGA_SPARO);
	//FINE DELLA VISUALIZZAIZOEN DELLO SPARO

	//INIZIO DELLA VISUALIZZAZIOEN DEL CARRO ARMATO
	al_draw_text(font_mostri, al_map_rgb(0, 255, 0), CENTRO_ORIZ, ALT_CARRO, ALLEGRO_ALIGN_CENTER, STRINGA_CARRO_ARMATO);
	//FINE DELLA VISUALIZZAZIONE DEL CARRO ARMATO

	al_flip_display();
}

inline void modificaImpostazioni (ALLEGRO_FONT *font_testo, Impostazioni impostazioni, Menu menu, bool redraw_lampeggio)
{
	const unsigned int LARG_BASE = 95; /*Larghezza del display dal quale mostrare  il contenuto.*/
	const unsigned int LARG_VALORI = 295; /*Larghezza del display dal quale mostrare i valori dei vari campi impostazioni.*/

	const unsigned int ALT_TITOLO = 60; /*Altezza del display dal quale mostrare il titolo.*/
	const unsigned int ALT_IMPOSTAZIONI = 105; /*Altezza del display dal quale mostrare l'elenco delle impostazioni.*/
	const unsigned int ALT_INDICAZIONI = 310; /*Altezza del display dal quale mostrare il premi enter.*/

	unsigned int alt_attuale = ALT_TITOLO;
	unsigned int larg_attuale = LARG_BASE;

	//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
	al_draw_text(font_testo, al_map_rgb(0, 255, 0), larg_attuale, alt_attuale, ALLEGRO_ALIGN_LEFT, "IMPOSTAZIONI:");
	//FINE DELLA VISUALIZZAZIONE DEL TITOLO

	//INIZIO DELLA VISUALIZZAZIONE DELLE IMPOSTAZIONI
	alt_attuale = ALT_IMPOSTAZIONI;
	for (int i = 0; i < N_VOCI_MENU_IMPO; i++)
	{	
		alt_attuale += DIM_FONT_TEXT + SPAZIO_TESTO;
		al_draw_text(font_testo, al_map_rgb(0, 255, 0), LARG_BASE, alt_attuale, ALLEGRO_ALIGN_LEFT, menu.testi_menu [i]);
		larg_attuale = LARG_VALORI;
		if (!(menu.voce_sel == i && !redraw_lampeggio))
		{
			char str_stato [MAX_STRINGA_GENERICA] = "<    ";
			char str_valore [MAX_STRINGA_GENERICA];
			assert(stringaValoreVoceImpostazioni (str_valore, static_cast <voce_menu_impostazioni> (i), impostazioni));
			strcat (str_stato, str_valore);
			strcat (str_stato, "     >");
			al_draw_text(font_testo, al_map_rgb(0, 255, 0), larg_attuale, alt_attuale, ALLEGRO_ALIGN_LEFT, str_stato);
		}
	}
	//FINE DELLA VISUALIZZAZIONE DELLE IMPOSTAZIONI

	//INIZIO DELLA VISUALIZZAZIONE DELLE INDICAZIONI
	alt_attuale = ALT_INDICAZIONI;
	for (int i = 0; i < N_INDICAZIONI_MENU_IMPO; i++)
	{
		al_draw_text(font_testo, al_map_rgb(0, 255, 0), CENTRO_ORIZ, alt_attuale, ALLEGRO_ALIGN_CENTER, INDICAZIONI_IMPOSTAZIONI [i]);
		alt_attuale += DIM_FONT_TEXT * 2;
	}
	//FINE DELLA VISUALIZZAZIONE DELLE INDICAZIONI	

	al_flip_display();
}

inline void classificaHighscores (ALLEGRO_FONT *font_testo, Punteggio highscores [], int n_punteggi, bool &redraw_lampeggio)
{
	const unsigned int LARG_BASE = 260; /*Larghezza del display dal quale mostrare il contenuto.*/
	const unsigned int LARG_PUNTEGGI = 305; /*Larghezza del display dal quale mostrare i punteggi.*/

	const unsigned int ALT_TITOLO = 60; /*Altezza del display dal quale mostrare il titolo.*/
	const unsigned int ALT_PUNTEGGI = 90; /*Altezza del display dal quale mostrare i punteggi.*/
	const unsigned int ALT_PREMI_ENTER = 410; /*Altezza del display dal quale mostrare il premi enter.*/

	unsigned int alt_attuale = ALT_TITOLO;

	//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
	al_draw_text(font_testo, al_map_rgb(0, 255, 0), LARG_BASE, alt_attuale, ALLEGRO_ALIGN_LEFT, "HIGHSCORES:");
	//FINE DELLA VISUALIZZAZIONE DEL TITOLO

	//INIZIO DELLA VISUALIZZAZIONE DEGLI HIGHSCORES
	alt_attuale = ALT_PUNTEGGI;

	for (int i = 0; i < n_punteggi; i++)
	{
		alt_attuale += DIM_FONT_TEXT + SPAZIO_TESTO;
		char str_numero [MAX_STRINGA_NUMERAZIONE] = "";
		sprintf(str_numero, "%d", i + 1);
		strcat (str_numero, ".");
		al_draw_text(font_testo, al_map_rgb(0, 255, 0), LARG_BASE, alt_attuale, ALLEGRO_ALIGN_LEFT, str_numero);

		char str_punteggio [MAX_STRINGA_GENERICA] = "";
		strcpy (str_punteggio, highscores [i].nome);
		strcat (str_punteggio, "   ");
		char str_valore [] = "";
		sprintf(str_valore, "%d", highscores [i].valore);
		strcat (str_punteggio, str_valore);
		al_draw_text(font_testo, al_map_rgb(0, 255, 0), LARG_PUNTEGGI, alt_attuale, ALLEGRO_ALIGN_LEFT, str_punteggio);
	}
	//FINE DELLA VISUALIZZAZIONE DEGLI HIGHSCORES

	//INIZIO DELLA VISUALIZZAZIONE DEL PREMI ENTER
	if (redraw_lampeggio)
	{
		alt_attuale = ALT_PREMI_ENTER;
		al_draw_text(font_testo, al_map_rgb(0, 255, 0), CENTRO_ORIZ, alt_attuale, ALLEGRO_ALIGN_CENTER, "Premi enter per tornare al menu principale");
	}
	//FINE DELLA VISUALIZZAZIONE DEL PREMI ENTER

	al_flip_display();
}