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
#include "struttura_dati.h"

using namespace std;

const unsigned int LARGHEZZA_DISPLAY = 640; /**<Larghezza della finestra del gioco.*/
const unsigned int ALTEZZA_DISPLAY = 480; /**<Altezza della finestra del gioco.*/
const float FPS = 60;  /**<FPS del gioco.*/
const float FPS_LAMPEGGIO_MENU = 5; /**FPS per mostrare l'effetto di lampeggio sull'opzione selezionata del menù.*/
const unsigned int CENTRO_ORIZ = LARGHEZZA_DISPLAY / 2; /**<Posizione centrale della larghezza del display.*/
const unsigned int SPAZIO_TESTO = 10; /**<Spazio fra righe di testo adiacenti.*/
const unsigned int DIM_FONT_TITOLO = 140; /**<Dimensione del font utilizzato per il titolo.*/
const unsigned int DIM_FONT_MENU = 15; /**<Dimensione del font utilizzato per il menu principale.*/
const unsigned int DIM_MOSTRI = 20; /**<Dimensione del font utilizzato per i mostri*/

const char M_10 [] = "B"; /**<Stringa per rappresentare il mostro da 10 punti.*/
const char M_20 [] = "D"; /**<Stringa per rappresentare il mostro da 20 punti.*/
const char M_40 [] = "F"; /**<Stringa per rappresentare il mostro da 40 punti.*/
const char M_X [] = "2"; /**<Stringa per rappresentare la navicella misteriosa.*/

const char FRECCIA [] = "<-"; /**<Stringa per rappresentare la freccia di selezione del menù.*/

const char FILE_HIGHSCORES [] = "highscores"; /**<Nome del file contenente gli highscores.*/
const char FILE_IMPOSTAZIONI [] = "SpaceInvaders.config"; /**<Nome del file contenente le impostazioni salvate.*/
const char FILE_SALVATAGGIO_PARTITA [] = "partita.sav"; /**<Nome del file contenente la partita salvata.*/

const char FONT_TEXT_FILE [] = "space_invaders.ttf"; /**<File contenente il font utilizzato per i testi.*/
const char FONT_IMAGE_FILE [] = "dustbust_invaders.ttf"; /**<File contenente il font utilizzato per i mostri e tutte le altre immagini presenti nel gioco.*/

const unsigned int ALT_TITOLO = ALTEZZA_DISPLAY * 0.07; /**<Altezza del display dal quale mostrare il titolo.*/
const unsigned int ALT_MOSTRI = ALTEZZA_DISPLAY* 0.44; /**<Altezza del display dal quale mostrare i mostri.*/
const unsigned int ALT_MENU = ALTEZZA_DISPLAY * 0.73; /**<Altezza del display dal quale mostrare il menu.*/

const unsigned int LARG_MOSTRI = LARGHEZZA_DISPLAY * 0.4; /**<Larghezza del display dal quale mostrare i mostri.*/
const unsigned int LARG_PUNTEGGIO = LARGHEZZA_DISPLAY * 0.55; /**<Larghezza del display dal quale mostrare i punteggi.*/
const unsigned int LARG_FRECCIA = LARGHEZZA_DISPLAY * 0.7; /**<Larghezza del display dal quale mostrare la freccia di selezione del menu.*/

const char MENU [] [15] = {"Gioca", "Carica partita", "Opzioni", "Highscores"}; /**<Voci del munù iniziale*/
const int N_VOCI_MENU = 4; /**<Numero di voci del menù.*/

/**
 * Mostra il menù principale e ne gestisce il contenuto.
 * 
 * @param font_titolo Font utilizzato per scrivere il titolo.
 * @param font_titolo Font utilizzato per scrivere il menù.
 * @param font_titolo Font utilizzato per disegnare i mostri.
 * @param voce Voce di menù selezionata.
 * @param redraw_voce Indica se la voce di menù è da ridisegnare o no (utilizzato per mostrare l'effetto lampeggiante sull'opzione di menù selezioanta).
 */
inline void menuPrincipale (ALLEGRO_FONT *font_titolo, ALLEGRO_FONT *font_menu, ALLEGRO_FONT *font_mostri, voce_menu &voce, bool &redraw_voce);

/**
 * Calcola il valore della voce di menù precedente a quella attuale.
 * 
 * @param voce Valore relativo alla voce di menù attuale.
 * @param n_voci Numero totale delle voci di menù esistenti.
 *
 * @return il valore della voce di menù precedente.
 */
voce_menu prevVoce (voce_menu voce, int n_voci);

/**
 * Calcola il valore della voce di menù successiva a quella attuale.
 * 
 * @param voce Valore relativo alla voce di menù attuale.
 * @param n_voci Numero totale delle voci di menù esistenti.
 *
 * @return il valore della voce di menù successiva.
 */
voce_menu nextVoce (voce_menu voce, int n_voci);

/**
 * Calcola il valore della prossima schermata da mostrare.
 * 
 * @param voce Voce di menu attualmente selezionata.
 *
 * @return il valore della prossima schermata da mostrare.
 */
schermata cambiaSchermata (voce_menu voce);

/**
 * FARE DOCUMENTAZIONE PER MAIN
 */
int main ()
{
	ALLEGRO_DISPLAY *display = NULL;
   	ALLEGRO_EVENT_QUEUE *coda_eventi = NULL;
	ALLEGRO_TIMER *frame_rate = NULL;
	ALLEGRO_TIMER *lampeggio_voce_att = NULL;
	bool redraw = true;
 
	assert (al_init());
	assert (al_init_font_addon());
	assert (al_init_ttf_addon()); 
	assert(al_install_keyboard());
 
	frame_rate = al_create_timer(1.0 / FPS);
	assert (frame_rate);

	lampeggio_voce_att = al_create_timer(1.0 / FPS_LAMPEGGIO_MENU);
	assert (lampeggio_voce_att);
 
   	display = al_create_display(LARGHEZZA_DISPLAY, ALTEZZA_DISPLAY);
   	assert (display);
 
   	coda_eventi = al_create_event_queue();
   	assert (coda_eventi);

	ALLEGRO_FONT *font_titolo = al_load_ttf_font(FONT_IMAGE_FILE, DIM_FONT_TITOLO, 0);
	assert (font_titolo);
	ALLEGRO_FONT *font_menu = al_load_ttf_font(FONT_TEXT_FILE, DIM_FONT_MENU, 0);
 	assert (font_menu);
	ALLEGRO_FONT *font_mostri = al_load_ttf_font(FONT_IMAGE_FILE, DIM_MOSTRI, 0);
 	assert (font_mostri);
 
   	al_register_event_source(coda_eventi, al_get_display_event_source(display));
	al_register_event_source(coda_eventi, al_get_timer_event_source(frame_rate));
	al_register_event_source(coda_eventi, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_start_timer(frame_rate);

	schermata schermata_att = s_menu;
	bool cambia_schermata;
	
	voce_menu voce_att;
	bool redraw_voce;

	while (true)
	{		
		cambia_schermata = false;
		switch (schermata_att)
		{
			case s_menu:
				voce_att = v_gioca;
				redraw_voce = false;
				al_register_event_source(coda_eventi, al_get_timer_event_source(lampeggio_voce_att));
				al_start_timer(lampeggio_voce_att);

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
						else if (ev.timer.source == lampeggio_voce_att)
						{
							redraw_voce = !redraw_voce;
						}
					}
					else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
					{
						al_destroy_timer(frame_rate);
						al_destroy_timer(lampeggio_voce_att);
						al_destroy_display(display);
   						al_destroy_event_queue(coda_eventi);
						return 0;
					}
					else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
					{
						switch(ev.keyboard.keycode)
						{
							case ALLEGRO_KEY_UP:
										voce_att = prevVoce (voce_att, N_VOCI_MENU);
										break;
							case ALLEGRO_KEY_DOWN:
										voce_att = nextVoce (voce_att, N_VOCI_MENU);
										break;
							case ALLEGRO_KEY_ENTER:
										schermata_att = cambiaSchermata (voce_att);
										cambia_schermata = true;
										break;
						}
					}

					if(redraw && al_is_event_queue_empty(coda_eventi))
					{
        					al_clear_to_color(al_map_rgb(0, 0, 0));
						menuPrincipale (font_titolo, font_menu, font_mostri, voce_att, redraw_voce);
					}
			   	}
				break;
			case s_gioca:
				//gioco
				break;
			case s_opzioni:
				//opzioni
				break;
			case s_highscores:
				//highscores
				break;
			case s_pausa:
				//pausa
				break;
			default:
				return 2;
		}
	}
 
	al_destroy_timer(frame_rate);
	al_destroy_timer(lampeggio_voce_att);
   	al_destroy_display(display);
   	al_destroy_event_queue(coda_eventi);
   	return 1;
}

inline void menuPrincipale (ALLEGRO_FONT *font_titolo, ALLEGRO_FONT *font_menu, ALLEGRO_FONT *font_mostri, voce_menu &voce, bool &redraw_voce)
{
	unsigned int alt_attuale = ALT_TITOLO;
	unsigned alt_freccia = ALT_MENU + (SPAZIO_TESTO + DIM_FONT_MENU) * voce;

	//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
	al_draw_text(font_titolo, al_map_rgb(0, 255, 0), CENTRO_ORIZ, alt_attuale, ALLEGRO_ALIGN_CENTRE, ".");
	//FINE DELLA VISUALIZZAZIONE DEL TITOLO

	//INIZIO DELLA VISUALIZZAZIONE DEI MOSTRI E I RELATIVI PUNTEGGI
	alt_attuale = ALT_MOSTRI;
	al_draw_text(font_mostri, al_map_rgb(0, 255, 0), LARG_MOSTRI, alt_attuale, ALLEGRO_ALIGN_CENTRE, M_10);
	al_draw_text(font_menu, al_map_rgb(0, 255, 0), LARG_PUNTEGGIO, alt_attuale, ALLEGRO_ALIGN_CENTRE, "=      10  PTS");

	alt_attuale = ALT_MOSTRI + SPAZIO_TESTO + DIM_MOSTRI;
	al_draw_text(font_mostri, al_map_rgb(0, 255, 0), LARG_MOSTRI, alt_attuale, ALLEGRO_ALIGN_CENTRE, M_20);
	al_draw_text(font_menu, al_map_rgb(0, 255, 0), LARG_PUNTEGGIO, alt_attuale, ALLEGRO_ALIGN_CENTRE, "=      20  PTS");

	alt_attuale = ALT_MOSTRI + (SPAZIO_TESTO + DIM_MOSTRI) * 2;
	al_draw_text(font_mostri, al_map_rgb(0, 255, 0), LARG_MOSTRI, alt_attuale, ALLEGRO_ALIGN_CENTRE, M_40);
	al_draw_text(font_menu, al_map_rgb(0, 255, 0), LARG_PUNTEGGIO, alt_attuale, ALLEGRO_ALIGN_CENTRE, "=      40  PTS");

	alt_attuale = ALT_MOSTRI + (SPAZIO_TESTO + DIM_MOSTRI) * 3;
	al_draw_text(font_mostri, al_map_rgb(255, 0, 0), LARG_MOSTRI, alt_attuale, ALLEGRO_ALIGN_CENTRE, M_X);
	al_draw_text(font_menu, al_map_rgb(0, 255, 0), LARG_PUNTEGGIO, alt_attuale, ALLEGRO_ALIGN_CENTRE, "=         ?  PTS");
	//FINE DELLA VISUALIZZAZIONE DEI MOSTRI E I RELATIVI PUNTEGGI

	//INIZIO DELLA VISUALIZZAZIONE DEL MENU
	if (!(voce == v_gioca && !redraw_voce))
	{
		alt_attuale = ALT_MENU;
		al_draw_text(font_menu, al_map_rgb(0, 255, 0), CENTRO_ORIZ, alt_attuale, ALLEGRO_ALIGN_CENTRE, MENU [0]);
	}
	if (!(voce == v_carica && !redraw_voce))
	{
		alt_attuale = ALT_MENU + SPAZIO_TESTO + DIM_FONT_MENU;
		al_draw_text(font_menu, al_map_rgb(0, 255, 0), CENTRO_ORIZ, alt_attuale, ALLEGRO_ALIGN_CENTRE, MENU [1]);
	}
	if (!(voce == v_opzioni && !redraw_voce))
	{
		alt_attuale = ALT_MENU + (SPAZIO_TESTO + DIM_FONT_MENU) * 2;
		al_draw_text(font_menu, al_map_rgb(0, 255, 0), CENTRO_ORIZ, alt_attuale, ALLEGRO_ALIGN_CENTRE, MENU [2]);
	}
	if (!(voce == v_highscores && !redraw_voce))
	{
		alt_attuale = ALT_MENU + (SPAZIO_TESTO + DIM_FONT_MENU) * 3;
		al_draw_text(font_menu, al_map_rgb(0, 255, 0), CENTRO_ORIZ, alt_attuale, ALLEGRO_ALIGN_CENTRE, MENU [3]);
	}
	
	if (redraw_voce)
	{
		al_draw_text(font_menu, al_map_rgb(0, 255, 0), LARG_FRECCIA, alt_freccia, ALLEGRO_ALIGN_LEFT, FRECCIA);
	}
	//FINE DELLA VISUALIZZAZIONE DEL MENU

	al_flip_display();
}

voce_menu prevVoce (voce_menu voce, int n_voci)
{
	voce_menu prev = static_cast <voce_menu> (voce - 1);
	if (prev < 0)
	{
		prev = static_cast <voce_menu> (n_voci - 1);
	}
	return prev;
}

voce_menu nextVoce (voce_menu voce, int n_voci)
{
	voce_menu next = static_cast <voce_menu> (voce + 1);
	if (next > (n_voci - 1))
	{
		next = static_cast <voce_menu> (0);
	}
	return next;
}

schermata cambiaSchermata (voce_menu voce)
{
	if (voce == v_gioca)
	{
		return s_gioca;
	}
	else if (voce == v_carica)
	{
		//INSERIRE PARTICOLARE PER CARICAMENTO
		return s_gioca;
	}
	else if (voce == v_opzioni)
	{
		return s_opzioni;
	}
	else if (voce == v_highscores)
	{
		return s_highscores;
	}
	return s_pausa;	
}