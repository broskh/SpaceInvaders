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
#include <allegro5/allegro_image.h>
#include "struttura_dati.h"
#include "gestione_partita.h"
#include "gestione_impostazioni.h"
#include "gestione_highscores.h"
#include "gestione_menu.h"

using namespace std;

const float FPS_GENERALE = 60;  /**<FPS generale del gioco.*/
const float FPS_LAMPEGGIO_MENU = 3.5; /**FPS per mostrare l'effetto di lampeggio sull'opzione selezionata del menù.*/
const float FPS_SPARO_ALIENI = 1.5;
const float FPS_ROTAZIONE_SPARO = 5;
const float FPS_NAVICELLA_MISTERIOSA = 1;

const unsigned int SPAZIO_TESTO = 10; /**<Spazio fra righe di testo adiacenti.*/
const unsigned int SPAZIO_TESTO_GRANDE = 30; /**<Spazio grande fra righe di testo adiacenti.*/
const unsigned int DIM_FONT_TITOLO = 140; /**<Dimensione del font utilizzato per il titolo.*/
const unsigned int DIM_FONT_TESTO = 15; /**<Dimensione del font utilizzato per i testi generali.*/
const unsigned int DIM_MOSTRI = 20; /**<Dimensione del font utilizzato per i mostri*/

const unsigned int LARGHEZZA_DISPLAY = 640; /**<Larghezza della finestra del gioco.*/
const unsigned int ALTEZZA_DISPLAY = 480; /**<Altezza della finestra del gioco.*/

const unsigned int POS_X_ESEMPIO_MOSTRI = 255; /**<Posizione rispetto all'asse x dalla quale mostrare i mostri nel menù principale.*/
const unsigned int POS_X_ESEMPIO_PUNTEGGIO = 350; /**<Posizione rispetto all'asse x dalla quale mostrare i punteggi nel menù principale.*/
const unsigned int POS_X_FRECCIA_MENU_PRINCIPALE = 450; /**<Posizione rispetto all'asse x dalla quale mostrare la freccia di selezione del menu nel menù principale.*/
const unsigned int POS_Y_TITOLO_MENU_PRINCIPALE = 25; /**<Posizione rispetto all'asse y dalla quale mostrare il titolo nel menù principale.*/
const unsigned int POS_Y_ESMEPIO_MOSTRI = 200; /**<Posizione rispetto all'asse y dalla quale mostrare i mostri nel menù principale.*/
const unsigned int POS_Y_VOCI_MENU_PRINCIPALE = 340; /**<Posizione rispetto all'asse y dalla quale mostrare il menu nel menù principale.*/

const unsigned int POS_Y_INFORMAZIONI_PARTITA = 10; /**<Posizione rispetto all'asse y dalla quale mostrare le informazioni della partita.*/
const unsigned int POS_Y_PRIMA_FILA_ONDATA = 80; /**<Posizione rispetto all'asse y dalla quale mostrare la prima fila di mostri.*/
const unsigned int POS_Y_BARRIERE = 360; /**<Posizone rispetto all'asse y dalla quale mostrare la prima barriera.*/
const unsigned int POS_Y_CARRO = 450; /**<Posizione rispetto all'asse y dalla quale mostrare il carro armato.*/
const unsigned int POS_Y_SPARO = POS_Y_CARRO - DIM_FONT_TESTO - 1; /**<Posizione iniziale rispetto all'asse y dello sparo.*/

const unsigned int POS_X_VOCI_IMPOSTAZIONI = 95; /**<Posizione rispetto all'asse x dalla quale mostrare  il contenuto.*/
const unsigned int POS_X_VALORI_IMPOSTAZIONI = 295; /**<Posizione rispetto all'asse x dalla quale mostrare i valori dei vari campi impostazioni.*/
const unsigned int POS_Y_TITOLO_IMPOSTAZIONI = 60; /**<Posizione rispetto all'asse y dalla quale mostrare il titolo.*/
const unsigned int POS_Y_IMPOSTAZIONI = 105; /**<Posizione rispetto all'asse y dalla quale mostrare l'elenco delle impostazioni.*/
const unsigned int POS_Y_INDICAZIONI_IMPOSTAZIONI = 310; /**<Posizione rispetto all'asse y dalla quale mostrare il premi enter.*/

const unsigned int POS_X_NUMERAZIONE_PUNTEGGI = 250; /**<Posizione rispetto all'asse x dalla quale mostrare il contenuto.*/
const unsigned int POS_X_NOMI_PUNTEGGI = 280; /**<Posizione rispetto all'asse x dalla quale mostrare i nomi dei punteggi.*/
const unsigned int POS_X_VALORI_PUNTEGGI = 330; /**<Posizione rispetto all'asse x dalla quale mostrare i valori dei punteggi.*/
const unsigned int POS_Y_HIGHSCORES_TITOLO = 60; /**<Posizione rispetto all'asse y dalla quale mostrare il titolo.*/
const unsigned int POS_Y_ELENCO_PUNTEGGI = 90; /**<Posizione rispetto all'asse y dalla quale mostrare i punteggi.*/
const unsigned int POS_Y_INDICAZIONI_HIGHSCORES = 410; /**<Posizione rispetto all'asse y dalla quale mostrare il premi enter.*/

const unsigned int POS_Y_VOCI_PAUSA = 220; /**<Posizione rispetto all'asse y dalla quale mostrare il menu di pausa.*/
const unsigned int POS_Y_TITOLO_PAUSA = 100; /**<Posizione rispetto all'asse y dalla quale mostrare il titolo del menù di pausa.*/

const unsigned int CENTRO_ORIZ = LARGHEZZA_DISPLAY / 2; /**<Posizione centrale della larghezza del display.*/
const unsigned int MARGINE_SX_GIOCO = 40; /**<Margine sinistro del gioco.*/
const unsigned int MARGINE_DX_GIOCO = LARGHEZZA_DISPLAY - MARGINE_SX_GIOCO; /**<Margine destro del gioco.*/
const unsigned int MARGINE_SUP_GIOCO = 45; /**<Margine superiore del gioco.*/

const unsigned int DISTANZA_ASSI_COL_MOSTRI = 40; /**<Distanza fra gli assi delle colonne di mostri.*/
const unsigned int DISTANZA_FILE_MOSTRI = 35; /**<Distamza fra le file di mostri.*/
const unsigned int DISTANZA_BARRIERE = (LARGHEZZA_DISPLAY - (LUNGHEZZA_PIXEL_BARRIERA * N_BARRIERE)) / (N_BARRIERE + 1); /**<Distanza in pixel fra le barriere.*/
const unsigned int POS_X_PRIMO_ASSE_MOSTRI = CENTRO_ORIZ - (DISTANZA_ASSI_COL_MOSTRI * (N_COL_MOSTRI - 1) / 2); /**<Posizone rispetto all'asse x nella quale è presente il primo asse delle colonne di mostri.*/

const char FILE_FONT_TESTO [] = "Fonts/space_invaders.ttf"; /**<File contenente il font utilizzato per i testi.*/
const char FILE_FONT_IMMAGINI [] = "Fonts/dustbust_invaders.ttf"; /**<File contenente il font utilizzato per i mostri e tutte le altre immagini presenti nel gioco.*/

const char FILE_HIGHSCORES [] = "highscores"; /**<Nome del file contenente gli highscores.*/
const char FILE_IMPOSTAZIONI [] = "SpaceInvaders.config"; /**<Nome del file contenente le impostazioni salvate.*/
const char FILE_SALVATAGGIO_PARTITA [] = "partita.sav"; /**<Nome del file contenente la partita salvata.*/

const char FILE_BARRIERA_PARZIALE [] = "Images/barriera_parziale.png";
const char FILE_BARRIERA_INTEGRA [] = "Images/barriera_integra.png";

const char FILE_SPARO_MOSTRI_1 [] = "Images/sparo_mostri_1.png";
const char FILE_SPARO_MOSTRI_2 [] = "Images/sparo_mostri_2.png";

const char FILE_MUSICA_PRINCIPALE [] = "Sounds/principale.flac"; /**<Nome del file contenente la musica principale.*/

/**
 * Calcola il valore della prossima schermata da mostrare nel menù principale.
 * 
 * @param voce Voce di menu attualmente selezionata.
 *
 * @return il valore della prossima schermata da mostrare.
 */
schermata cambiaSchermataMenuPrincipale (voce_menu_principale voce);

/**
 * Calcola il valore della prossima schermata da mostrare nel menù di pausa e agisce di ocnseguenza sulla partita
 * (se necessario).
 * 
 * @param voce Voce di menu attualmente selezionata.
 * @param spaceInvaders Struttura {@link SpaceInvaders} contenente tutte le informazioni del gioco in esecuzione.
 * @param file_salvataggio File nel quale salvare la partita.
 *
 * @return il valore della prossima schermata da mostrare.
 */
schermata cambiaSchermataMenuPausa (voce_menu_pausa voce, SpaceInvaders &spaceInvaders, const char file_salvataggio []);

/**
 * Mostra il menù principale e ne gestisce il contenuto.
 * 
 * @param font_titolo Font utilizzato per scrivere il titolo.
 * @param font_menu Font utilizzato per scrivere il menù.
 * @param font_mostri Font utilizzato per disegnare i mostri.
 * @param menu Menu' principale.
 * @param redraw_lampeggio Indica se la voce di menù è da ridisegnare o no (utilizzato per mostrare l'effetto lampeggiante sull'opzione di menù selezioanta).
 * @param salvataggio Indica se esiste o meno il salvataggio di una partita precedente (necessario per sapere di che colore disegnare la voce di menù caric).
 */
inline void menuPrincipale (ALLEGRO_FONT *font_titolo, ALLEGRO_FONT *font_menu, ALLEGRO_FONT *font_mostri, Menu menu, bool redraw_lampeggio, bool salvataggio);

/**
 * Mostra il gioco vero e proprio.
 * 
 * @param font_mostri Font con il quale vengono disegnati i mostri.
 * @param font_testo Font utilizzato per scrivere le stringhe di testo.
 * @param barriera_parziale Bitmap rappresentante un unità della barriera nello stato "parziale".
 * @param barriera_integra Bitmap rappresentante un unità della barriera nello stato "integra".
 * @param partita Struttura {@link Partita} contenente le informazioni relative alla partita attuale.
 * @param impostazioni Impostazioni generali del gioco.
 */
inline void gioca (ALLEGRO_FONT *font_mostri, ALLEGRO_FONT *font_testo, ALLEGRO_BITMAP *sparo_mostri_1, ALLEGRO_BITMAP *sparo_mostri_2, ALLEGRO_BITMAP *barriera_parziale, ALLEGRO_BITMAP *barriera_integra, Partita &partita, Impostazioni impostazioni, bool ruota_sparo);

/**
 * Mostra il menu di modifica delle impostazioni.
 * 
 * @param font_testo Font utilizzato per scrivere la classifica dei punteggi.
 * @param impostazioni Impostazioni attuali.
 * @param menu Menu' delle impostazioni.
 * @param redraw_lampeggio Indica se la voce del menù è da ridisegnare o no (utilizzato per mostrare l'effetto lampeggiante sull'opzione di menù selezioanta).
 */
inline void modificaImpostazioni (ALLEGRO_FONT *font_testo, Impostazioni impostazioni, Menu menu, bool redraw_lampeggio);

/**
 * Mostra la classifica dei migliori punteggi.
 * 
 * @param font_testo Font utilizzato per scrivere la classifica dei punteggi.
 * @param highscors Array di strutture {@link Punteggio} contenente i migliori punteggi.
 * @param n_punteggi Numero di punteggi presenti nelal classifica.
 */
inline void classificaHighscores (ALLEGRO_FONT *font_testo, Punteggio highscores [], int n_punteggi);

/**
 * Mostra il menù di pausa.
 * 
 * @param font_testo Font utilizzato per scrivere i testi.
 * @param partita Struttura {@link Partita} contenente le informazioni relative alla partita attuale.
 * @param menu Menu' di pausa.
 * @param redraw_lampeggio Indica se la voce di menù è da ridisegnare o no (utilizzato per mostrare l'effetto lampeggiante sull'opzione di menù selezioanta).
 */
inline void pausa (ALLEGRO_FONT *font_testo, Partita partita, Menu menu, bool redraw_lampeggio);

/**
 * Mostra la schermata di fine partita.
 * 
 * @param font_testo Font utilizzato per scrivere la classifica dei punteggi.
 * @param highscors Array di strutture {@link Punteggio} contenente i migliori punteggi.
 * @param n_punteggi Numero di punteggi presenti nelal classifica.
 * @param nuovo_punteggio Nuovo punteggio raggiunto.
 * @param posizione Posizione dell'array contenente gli highscores nella quale merita di essere inseirto il nuovo punteggio.
 * @param redraw_lampeggio Indica se la dicitura premi enter è da ridisegnare o no (utilizzato per mostrare l'effetto lampeggiante sulla dicitura).
 */
inline void finePartita (ALLEGRO_FONT *font_testo, Punteggio highscores [], int n_punteggi, Punteggio nuovo_punteggio, int posizione, bool redraw_lampeggio);

/**
 * FARE DOCUMENTAZIONE PER MAIN
 */
int main ()
{
	ALLEGRO_DISPLAY *display = NULL;
   	ALLEGRO_EVENT_QUEUE *coda_eventi = NULL;
	ALLEGRO_TIMER *frame_rate_generale = NULL;
	ALLEGRO_TIMER *lampeggio_voce = NULL;
	ALLEGRO_TIMER *timer_sparo_mostri= NULL;
	ALLEGRO_TIMER *timer_rotazione_sparo = NULL;
	ALLEGRO_TIMER *timer_comparsa_navicella = NULL;
	ALLEGRO_FONT *font_titolo = NULL;
	ALLEGRO_FONT *font_testo = NULL;
	ALLEGRO_FONT *font_mostri = NULL;
	ALLEGRO_BITMAP *barriera_parziale = NULL;
	ALLEGRO_BITMAP *barriera_integra = NULL;
	ALLEGRO_BITMAP *sparo_mostri_1 = NULL;
	ALLEGRO_BITMAP *sparo_mostri_2 = NULL;
   	ALLEGRO_SAMPLE *musica_principale = NULL;
	bool redraw = true;
 
	assert (al_init());
	assert (al_init_font_addon());
	assert (al_init_ttf_addon()); 
	assert (al_install_keyboard());
	assert (al_init_image_addon());
	assert (al_install_audio());
	assert (al_init_acodec_addon());
	assert (al_reserve_samples(true));
 
   	display = al_create_display(LARGHEZZA_DISPLAY, ALTEZZA_DISPLAY);
   	assert (display);
 
   	coda_eventi = al_create_event_queue();
   	assert (coda_eventi);
 
	frame_rate_generale = al_create_timer(1.0 / FPS_GENERALE);
	assert (frame_rate_generale);

	lampeggio_voce = al_create_timer(1.0 / FPS_LAMPEGGIO_MENU);
	assert (lampeggio_voce);

	timer_sparo_mostri = al_create_timer(1.0 / FPS_SPARO_ALIENI);
	assert (timer_sparo_mostri);

	timer_rotazione_sparo = al_create_timer(1.0 / FPS_ROTAZIONE_SPARO);
	assert (timer_rotazione_sparo);

	timer_comparsa_navicella = al_create_timer(1.0 / FPS_NAVICELLA_MISTERIOSA);
	assert (timer_comparsa_navicella);

	font_titolo = al_load_ttf_font(FILE_FONT_IMMAGINI, DIM_FONT_TITOLO, 0);
	assert (font_titolo);
	font_testo = al_load_ttf_font(FILE_FONT_TESTO, DIM_FONT_TESTO, 0);
 	assert (font_testo);
	font_mostri = al_load_ttf_font(FILE_FONT_IMMAGINI, DIM_MOSTRI, 0);
 	assert (font_mostri);
	
	barriera_parziale = al_load_bitmap(FILE_BARRIERA_PARZIALE);
	assert (barriera_parziale);
	barriera_integra = al_load_bitmap(FILE_BARRIERA_INTEGRA);
	assert (barriera_integra);
	sparo_mostri_1 = al_load_bitmap(FILE_SPARO_MOSTRI_1);
	assert (sparo_mostri_1);
	sparo_mostri_2 = al_load_bitmap(FILE_SPARO_MOSTRI_2);
	assert (sparo_mostri_2);

	musica_principale = al_load_sample (FILE_MUSICA_PRINCIPALE);
	assert (musica_principale);
 
   	al_register_event_source(coda_eventi, al_get_display_event_source(display));
	al_register_event_source(coda_eventi, al_get_timer_event_source(frame_rate_generale));
	al_register_event_source(coda_eventi, al_get_timer_event_source(lampeggio_voce));
	al_register_event_source(coda_eventi, al_get_timer_event_source(timer_sparo_mostri));
	al_register_event_source(coda_eventi, al_get_timer_event_source(timer_rotazione_sparo));
	al_register_event_source(coda_eventi, al_get_timer_event_source(timer_comparsa_navicella));
	al_register_event_source(coda_eventi, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_start_timer(frame_rate_generale);
	
	//INIZIO INIZIALIZZAZIONE DELLA STRUTTURA PRINCIPALE
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
	nuovaPartita (generale.partita_in_corso, generale.impostazioni, CENTRO_ORIZ, POS_X_PRIMO_ASSE_MOSTRI, POS_Y_PRIMA_FILA_ONDATA, MARGINE_SX_GIOCO);
	//FINE INIZIALIZZAZIONE DELLA STRUTTURA PRINCIPALE
	
	schermata schermata_att = s_menu;
	bool cambia_schermata;
	
	Menu menu_principale;
	inizializzaMenu (menu_principale, MENU_PRINCIPALE, N_VOCI_MENU_PRINC, v_gioca);
	Menu menu_impostazioni;
	inizializzaMenu (menu_impostazioni, MENU_IMPOSTAZIONI, N_VOCI_MENU_IMPO, v_musica);
	Menu menu_pausa;
	inizializzaMenu (menu_pausa, MENU_PAUSA, N_VOCI_MENU_PAUSA, v_continua);
	bool redraw_lampeggio;
	bool ruota_sparo;

	int posizione;
	char input [] = " ";

	while (true)
	{
		cambia_schermata = false;
		redraw_lampeggio = false;
		ruota_sparo = false;
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
						if (ev.timer.source == frame_rate_generale)
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
				eliminaFileSalvataggio (FILE_SALVATAGGIO_PARTITA, generale);
				if (generale.impostazioni.musica)
				{
					al_stop_samples();
				}
				al_start_timer(timer_sparo_mostri);
				al_start_timer(timer_rotazione_sparo);
				al_start_timer(timer_comparsa_navicella);

				while(!cambia_schermata)
			   	{
					ALLEGRO_EVENT ev;
					al_wait_for_event(coda_eventi, &ev);

					if(ev.type == ALLEGRO_EVENT_TIMER)
					{
						if (ev.timer.source == frame_rate_generale)
						{
							redraw = true;
						}
						else if (ev.timer.source == timer_rotazione_sparo)
						{
							ruota_sparo = !ruota_sparo;
						}
						else if (ev.timer.source == timer_sparo_mostri)
						{
							if (!generale.partita_in_corso.sparo_mostri.stato)
							{
								creaSparoMostri (generale.partita_in_corso, DIM_MOSTRI, DISTANZA_FILE_MOSTRI, font_mostri, DISTANZA_ASSI_COL_MOSTRI);
							}
						}
						else if (ev.timer.source == timer_comparsa_navicella)
						{
							if (!generale.partita_in_corso.navicella_misteriosa.stato)
							{
								creaNavicellaMisteriosa (generale.partita_in_corso, MARGINE_SX_GIOCO);
							}
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
							case ALLEGRO_KEY_ESCAPE:
								schermata_att = s_pausa;
								cambia_schermata = true;
								break;
							/*case ALLEGRO_KEY_BACKSPACE:
								while (true)
								{
									;
								}
								break;*/
						}
					}
					else if(ev.type == ALLEGRO_EVENT_KEY_CHAR)
					{
						switch(ev.keyboard.keycode)
						{
							case ALLEGRO_KEY_LEFT:
								muoviSinistraCarro (generale.partita_in_corso.pos_x_carro, MARGINE_SX_GIOCO);
								break;
							case ALLEGRO_KEY_RIGHT:
								muoviDestraCarro (generale.partita_in_corso.pos_x_carro, MARGINE_DX_GIOCO);
								break;
							case ALLEGRO_KEY_SPACE:
								if (!generale.partita_in_corso.sparo_carro.stato)
								{
									generale.partita_in_corso.sparo_carro.stato = true;
									generale.partita_in_corso.sparo_carro.pos_x = generale.partita_in_corso.pos_x_carro + 1;
									generale.partita_in_corso.sparo_carro.pos_y = POS_Y_SPARO;
								}
								break;
						}
					}				

					if(redraw && al_is_event_queue_empty(coda_eventi))
					{
        					al_clear_to_color(al_map_rgb(0, 0, 0));
						gioca (font_mostri, font_testo, sparo_mostri_1, sparo_mostri_2, barriera_parziale, barriera_integra, generale.partita_in_corso, generale.impostazioni, ruota_sparo);

						//INIZIO DEI CONTROLLI
						if (controlloCollisioneCarroDaSparoMostri (generale.partita_in_corso, al_get_text_width(font_mostri, STRINGA_CARRO_ARMATO), al_get_bitmap_height (sparoScelto (generale.partita_in_corso.sparo_mostri.pos_x, sparo_mostri_1, sparo_mostri_2)), DIM_MOSTRI, POS_Y_CARRO))
						{
						}
						if (generale.partita_in_corso.vite_rimanenti < 0 || controlloCollisioneCarroDaOndata (generale.partita_in_corso, DIM_MOSTRI, DISTANZA_FILE_MOSTRI, DISTANZA_ASSI_COL_MOSTRI, POS_Y_CARRO))
						{
							schermata_att = s_fine_partita;
							cambia_schermata = true;
							break;
						}
						if (controlloCollisioneMostri (generale.partita_in_corso, DIM_MOSTRI, DISTANZA_FILE_MOSTRI, font_mostri, DISTANZA_ASSI_COL_MOSTRI))
						{
						}
						if (controlloCollisioneBarriereDaSparoCarro (generale.partita_in_corso, DISTANZA_BARRIERE, POS_Y_BARRIERE, DISTANZA_BARRIERE))
						{
						}
						if (controlloCollisioneBarriereDaSparoMostri (generale.partita_in_corso, DISTANZA_BARRIERE, POS_Y_BARRIERE, DISTANZA_BARRIERE, al_get_bitmap_height (sparoScelto (generale.partita_in_corso.sparo_mostri.pos_x, sparo_mostri_1, sparo_mostri_2))))
						{
						}
						if (controlloCollisioneNavicellaMisteriosa (generale.partita_in_corso, al_get_text_width(font_mostri, STRINGA_M_X), DIM_MOSTRI, MARGINE_SUP_GIOCO))
						{
						}
						if (controlloCollisioneBarriereDaOndata (generale.partita_in_corso, DISTANZA_BARRIERE, POS_Y_BARRIERE, DISTANZA_BARRIERE, DIM_MOSTRI, font_mostri, DISTANZA_FILE_MOSTRI, DISTANZA_ASSI_COL_MOSTRI))
						{
						}
						//FINE DEI CONTROLLI
						//INIZIO DEI CAMBIAMENTI
						if (generale.partita_in_corso.sparo_carro.stato)
						{
							muoviSparoCarro (generale.partita_in_corso.sparo_carro, MARGINE_SUP_GIOCO);
						}
						if (generale.partita_in_corso.sparo_mostri.stato)
						{
							muoviSparoMostri (generale.partita_in_corso.sparo_mostri, POS_Y_CARRO + DIM_MOSTRI - 8);
						}
						if (generale.partita_in_corso.navicella_misteriosa.stato)
						{
							muoviNavicellaMisteriosa (generale.partita_in_corso, MARGINE_DX_GIOCO + al_get_text_width(font_mostri, STRINGA_M_X));
						}
						muoviMostri (generale.partita_in_corso.ondata, MARGINE_SX_GIOCO, MARGINE_DX_GIOCO, POS_Y_CARRO, DISTANZA_ASSI_COL_MOSTRI, al_get_text_width(font_mostri, STRINGA_M_30), DISTANZA_FILE_MOSTRI);
						//FINE DEI CAMBIAMENTI
					}
			   	}
				al_stop_timer(timer_sparo_mostri);
				al_stop_timer(timer_rotazione_sparo);
				al_stop_timer(timer_comparsa_navicella);
				break;
			case s_carica:
				assert (caricaPartita (generale.partita_in_corso, FILE_SALVATAGGIO_PARTITA));
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
						if (ev.timer.source == frame_rate_generale)
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
				while(!cambia_schermata)
			   	{				
					ALLEGRO_EVENT ev;
					al_wait_for_event(coda_eventi, &ev);

					if(ev.type == ALLEGRO_EVENT_TIMER)
					{
						if (ev.timer.source == frame_rate_generale)
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
						classificaHighscores (font_testo, generale.highscores, generale.n_highscores);
					}
			   	}
				break;
			case s_pausa:
				menu_pausa.voce_sel = v_continua;
				al_start_timer(lampeggio_voce);
				
				while(!cambia_schermata)
			   	{
					ALLEGRO_EVENT ev;
					al_wait_for_event(coda_eventi, &ev);

					if(ev.type == ALLEGRO_EVENT_TIMER)
					{
						if (ev.timer.source == frame_rate_generale)
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
								vocePrec (menu_pausa);
								break;
							case ALLEGRO_KEY_DOWN:
								voceSuc (menu_pausa);
								break;
							case ALLEGRO_KEY_ENTER:
								schermata_att = cambiaSchermataMenuPausa (static_cast <voce_menu_pausa> (menu_pausa.voce_sel), generale, FILE_SALVATAGGIO_PARTITA);
								cambia_schermata = true;
								break;
						}
					}

					if(redraw && al_is_event_queue_empty(coda_eventi))
					{
        					al_clear_to_color(al_map_rgb(0, 0, 0));
						pausa (font_testo, generale.partita_in_corso, menu_pausa, redraw_lampeggio);
					}
			   	}
				al_stop_timer(lampeggio_voce);
				break;
			case s_fine_partita:	
				al_start_timer(lampeggio_voce);
				posizione = posizionePunteggio (generale.highscores, generale.n_highscores, generale.partita_in_corso.punteggio);
				
				while(!cambia_schermata)
			   	{				
					ALLEGRO_EVENT ev;
					al_wait_for_event(coda_eventi, &ev);

					if(ev.type == ALLEGRO_EVENT_TIMER)
					{
						if (ev.timer.source == frame_rate_generale)
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
								aggiungiPunteggio (generale.highscores, generale.n_highscores, generale.partita_in_corso.punteggio, posizione);
								salvaPunteggi (generale.highscores, generale.n_highscores, FILE_HIGHSCORES);
								nuovaPartita (generale.partita_in_corso, generale.impostazioni, CENTRO_ORIZ, POS_X_PRIMO_ASSE_MOSTRI, POS_Y_PRIMA_FILA_ONDATA, MARGINE_SX_GIOCO);
								schermata_att = s_menu;
								cambia_schermata = true;
								break;
							case ALLEGRO_KEY_BACKSPACE:
								generale.partita_in_corso.punteggio.nome [strlen (generale.partita_in_corso.punteggio.nome) - 1] = '\0';
								break;
							default:
								if (ev.keyboard.keycode >= ALLEGRO_KEY_A && ev.keyboard.keycode <= ALLEGRO_KEY_Z)
								{
									if (strlen (generale.partita_in_corso.punteggio.nome) < CARATTERI_NOME)
									{
										input [0] = ev.keyboard.keycode - ALLEGRO_KEY_A + 'A';
										strcat (generale.partita_in_corso.punteggio.nome, input);
									}
									else
									{
										generale.partita_in_corso.punteggio.nome [CARATTERI_NOME - 1] = ev.keyboard.keycode - ALLEGRO_KEY_A + 'a';
									}
								}
								break;
						}
					}

					if(redraw && al_is_event_queue_empty(coda_eventi))
					{
        					al_clear_to_color(al_map_rgb(0, 0, 0));
						finePartita (font_testo, generale.highscores, generale.n_highscores, generale.partita_in_corso.punteggio, posizione, redraw_lampeggio);
					}
			   	}
				al_stop_timer(lampeggio_voce);
				break;
			case s_esci:
				al_destroy_display(display);
				al_destroy_event_queue(coda_eventi);
				al_destroy_timer(frame_rate_generale);
				al_destroy_timer(lampeggio_voce);
				al_destroy_timer(timer_sparo_mostri);
				al_destroy_timer(timer_rotazione_sparo);
				al_destroy_timer(timer_comparsa_navicella);
   				al_destroy_bitmap(sparo_mostri_1);
   				al_destroy_bitmap(sparo_mostri_2);
   				al_destroy_bitmap(barriera_parziale);
   				al_destroy_bitmap(barriera_integra);
				al_destroy_sample(musica_principale);
				return 0;
			default:
				al_destroy_display(display);
				al_destroy_event_queue(coda_eventi);
				al_destroy_timer(frame_rate_generale);
				al_destroy_timer(lampeggio_voce);
				al_destroy_timer(timer_sparo_mostri);
				al_destroy_timer(timer_rotazione_sparo);
				al_destroy_timer(timer_comparsa_navicella);
   				al_destroy_bitmap(sparo_mostri_1);
   				al_destroy_bitmap(sparo_mostri_2);
				al_destroy_bitmap(barriera_parziale);
				al_destroy_bitmap(barriera_integra);
				al_destroy_sample(musica_principale);
				return 2;
		}
	}
 
	al_destroy_display(display);
	al_destroy_event_queue(coda_eventi);
	al_destroy_timer(frame_rate_generale);
	al_destroy_timer(lampeggio_voce);
	al_destroy_timer(timer_sparo_mostri);
	al_destroy_timer(timer_rotazione_sparo);
	al_destroy_timer(timer_comparsa_navicella);
	al_destroy_bitmap(sparo_mostri_1);
	al_destroy_bitmap(sparo_mostri_2);
	al_destroy_bitmap(barriera_parziale);
	al_destroy_bitmap(barriera_integra);
	al_destroy_sample(musica_principale);
   	return 1;
}

schermata cambiaSchermataMenuPrincipale (voce_menu_principale voce)
{
	if (voce == v_gioca)
	{
		return s_gioca;
	}
	else if (voce == v_carica)
	{
		return s_carica;
	}
	else if (voce == v_opzioni)
	{
		return s_opzioni;
	}
	else if (voce == v_highscores)
	{
		return s_highscores;
	}
	else if (voce == v_esci)
	{
		return s_esci;
	}
	return s_menu;
}

schermata cambiaSchermataMenuPausa (voce_menu_pausa voce, SpaceInvaders &spaceInvaders, const char file_salvataggio [])
{
	if (voce == v_continua)
	{
		return s_gioca;
	}
	else if (voce == v_salva)
	{
		salvaPartita (spaceInvaders, file_salvataggio);
	}
	else if (voce == v_abbandona)
	{
		;
	}
	nuovaPartita (spaceInvaders.partita_in_corso, spaceInvaders.impostazioni, CENTRO_ORIZ, POS_X_PRIMO_ASSE_MOSTRI, POS_Y_PRIMA_FILA_ONDATA, MARGINE_SX_GIOCO);
	return s_menu;
}

void disegnaBarriera (ALLEGRO_BITMAP *barriera_parziale, ALLEGRO_BITMAP *barriera_integra, stato_barriera barriera [ALT_BARRIERA] [LARG_BARRIERA], unsigned int pos_x, unsigned int pos_y)
{
	unsigned int dx = pos_x; 
	unsigned int dy = pos_y;

	for (unsigned int i = 0; i < ALT_BARRIERA; i++)
	{
		for (unsigned int j = 0; j < LARG_BARRIERA; j++)
		{
			if (barriera [i] [j] == integra)
			{
				al_draw_tinted_bitmap (barriera_integra, al_map_rgb(0, 255, 0), dx, dy, 0);
			}
			else if (barriera [i] [j] == parziale)
			{
				al_draw_tinted_bitmap (barriera_parziale, al_map_rgb(0, 255, 0), dx, dy, 0);
			}
			dx += LATO_UNITA;
		}
		dx = pos_x;
		dy += LATO_UNITA;
	}
}

inline void menuPrincipale (ALLEGRO_FONT *font_titolo, ALLEGRO_FONT *font_menu, ALLEGRO_FONT *font_mostri, Menu menu, bool redraw_lampeggio, bool salvataggio)
{
	unsigned int pos_y_attuale = POS_Y_TITOLO_MENU_PRINCIPALE;
	unsigned pos_y_freccia = POS_Y_VOCI_MENU_PRINCIPALE + (SPAZIO_TESTO + DIM_FONT_TESTO) * menu.voce_sel;

	//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
	al_draw_text(font_titolo, al_map_rgb(0, 255, 0), CENTRO_ORIZ, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, ".");
	//FINE DELLA VISUALIZZAZIONE DEL TITOLO

	//INIZIO DELLA VISUALIZZAZIONE DEI MOSTRI E I RELATIVI PUNTEGGI
	pos_y_attuale = POS_Y_ESMEPIO_MOSTRI;
	al_draw_text(font_mostri, al_map_rgb(0, 255, 0), POS_X_ESEMPIO_MOSTRI, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, STRINGA_M_10);
	al_draw_text(font_menu, al_map_rgb(0, 255, 0), POS_X_ESEMPIO_PUNTEGGIO, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, "=      10  PTS");

	pos_y_attuale = POS_Y_ESMEPIO_MOSTRI + SPAZIO_TESTO + DIM_MOSTRI;
	al_draw_text(font_mostri, al_map_rgb(0, 255, 0), POS_X_ESEMPIO_MOSTRI, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, STRINGA_M_20);
	al_draw_text(font_menu, al_map_rgb(0, 255, 0), POS_X_ESEMPIO_PUNTEGGIO, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, "=      20  PTS");

	pos_y_attuale = POS_Y_ESMEPIO_MOSTRI + (SPAZIO_TESTO + DIM_MOSTRI) * 2;
	al_draw_text(font_mostri, al_map_rgb(0, 255, 0), POS_X_ESEMPIO_MOSTRI, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, STRINGA_M_30);
	al_draw_text(font_menu, al_map_rgb(0, 255, 0), POS_X_ESEMPIO_PUNTEGGIO, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, "=      30  PTS");

	pos_y_attuale = POS_Y_ESMEPIO_MOSTRI + (SPAZIO_TESTO + DIM_MOSTRI) * 3;
	al_draw_text(font_mostri, al_map_rgb(255, 0, 0), POS_X_ESEMPIO_MOSTRI, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, STRINGA_M_X);
	al_draw_text(font_menu, al_map_rgb(0, 255, 0), POS_X_ESEMPIO_PUNTEGGIO, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, "=         ?  PTS");
	//FINE DELLA VISUALIZZAZIONE DEI MOSTRI E I RELATIVI PUNTEGGI
	
	//INIZIO DELLA VISUALIZZAZIONE DEL MENU
	for (int i = 0; i < menu.n_voci; i++)
	{
		if (!(menu.voce_sel == i && !redraw_lampeggio))
		{
			pos_y_attuale = POS_Y_VOCI_MENU_PRINCIPALE + (SPAZIO_TESTO + DIM_FONT_TESTO) * i;
			if ((!salvataggio) && (static_cast <voce_menu_principale> (i) == v_carica))
			{
				al_draw_text(font_menu, al_map_rgb(84, 84, 84), CENTRO_ORIZ, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, menu.testi_menu [i]);
			}
			else
			{
				al_draw_text(font_menu, al_map_rgb(0, 255, 0), CENTRO_ORIZ, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, menu.testi_menu [i]);
			}
		}
	}

	if (redraw_lampeggio)
	{
		al_draw_text(font_menu, al_map_rgb(0, 255, 0), POS_X_FRECCIA_MENU_PRINCIPALE, pos_y_freccia, ALLEGRO_ALIGN_LEFT, "<-");
	}
	//FINE DELLA VISUALIZZAZIONE DEL MENU

	al_flip_display();
}

inline void gioca (ALLEGRO_FONT *font_mostri, ALLEGRO_FONT *font_testo, ALLEGRO_BITMAP *sparo_mostri_1, ALLEGRO_BITMAP *sparo_mostri_2, ALLEGRO_BITMAP *barriera_parziale, ALLEGRO_BITMAP *barriera_integra, Partita &partita, Impostazioni impostazioni, bool ruota_sparo)
{
	unsigned int pos_y_attuale;
	unsigned int pos_x_attuale;

	//INIZIO DELLA VISUALIZZAZIONE DELLE INFORMAZIONI
	char stringa_punteggio [] = "Punteggio:    ";
	char valore_punteggio [MAX_STRINGA_GENERICA];
	sprintf(valore_punteggio, "%d", partita.punteggio.valore);
	strcat (stringa_punteggio, valore_punteggio);
	pos_x_attuale = (CENTRO_ORIZ - al_get_text_width(font_testo, stringa_punteggio)) / 2;
	al_draw_text(font_testo, al_map_rgb(0, 255, 0), pos_x_attuale, POS_Y_INFORMAZIONI_PARTITA, ALLEGRO_ALIGN_LEFT, stringa_punteggio);

	char stringa_vite [] = "Vite:    ";
	char valore_vite [MAX_STRINGA_GENERICA];
	sprintf(valore_vite, "%d", partita.vite_rimanenti);
	strcat (stringa_vite, valore_vite);
	pos_x_attuale = (CENTRO_ORIZ - al_get_text_width(font_testo, stringa_vite)) / 2 + CENTRO_ORIZ;
	al_draw_text(font_testo, al_map_rgb(0, 255, 0), pos_x_attuale, POS_Y_INFORMAZIONI_PARTITA, ALLEGRO_ALIGN_CENTRE, stringa_vite);
	//FINE DELLA VISUALIZZAZIONE DELLE INFORMAZIONI

	//INIZIO DELLA VISUALIZZAZIONE DELLA NAVICELLA MISTERIOSA
	if (partita.navicella_misteriosa.stato)
	{
		al_draw_text(font_mostri, al_map_rgb(255, 0, 0), partita.pos_x_navicella, MARGINE_SUP_GIOCO, ALLEGRO_ALIGN_LEFT, partita.navicella_misteriosa.stringa);
	}
	//FINE DELLA VISUALIZZAZIONE DELLA NAVICELLA MISTERIOSA

	//INIZIO DELLA VISUALIZZAZIONE DELL'ONDATA
	pos_y_attuale = partita.ondata.pos_y;

	for (unsigned int i = 0; i < N_FILE_MOSTRI; i++)
	{
		pos_x_attuale = partita.ondata.pos_x;
		for (unsigned int j = 0; j < N_COL_MOSTRI; j++)
		{
			if (partita.ondata.mostri [i] [j].stato)
			{
				al_draw_text(font_mostri, al_map_rgb(0, 255, 0), pos_x_attuale, pos_y_attuale, ALLEGRO_ALIGN_CENTER, partita.ondata.mostri [i] [j].stringa);
			}
			pos_x_attuale += DISTANZA_ASSI_COL_MOSTRI;
		}
		pos_y_attuale += DISTANZA_FILE_MOSTRI;
	}
	//FINE DELLA VISUALIZZAZIONE DELL'ONDATA

	//INIZIO DELLA VISUALIZZAZIONE DELLO SPARO DEI MOSTRI
	if (partita.sparo_mostri.stato)
	{
		int angolo;
		ALLEGRO_BITMAP *sparo_attuale;
		sparo_attuale = sparoScelto (partita.sparo_mostri.pos_x, sparo_mostri_1, sparo_mostri_2);
		if (ruota_sparo)
		{
			angolo = 0;			
		}
		else
		{
			angolo = ALLEGRO_PI;
		}
		al_draw_tinted_rotated_bitmap(sparo_attuale, al_map_rgb(0, 255, 0), al_get_bitmap_width (sparo_attuale) / 2 + 1, al_get_bitmap_height (sparo_attuale) / 2, partita.sparo_mostri.pos_x, partita.sparo_mostri.pos_y, angolo, 0);
	}
	//FINE DELLA VISUALIZZAZIONE DELLO SPARO DEI MOSTRI

	//INIZIO DELLA VISUALIZZAZIONE DELLE BARRIERE
	pos_x_attuale = DISTANZA_BARRIERE;
	for (unsigned int i = 0; i < N_BARRIERE; i++)
	{
		disegnaBarriera (barriera_parziale, barriera_integra, partita.barriere [i], pos_x_attuale, POS_Y_BARRIERE);
		pos_x_attuale += DISTANZA_BARRIERE + LUNGHEZZA_PIXEL_BARRIERA;
	}
	//FINE DELLA VISUALIZZAZIONE DELLE BARRIERE
	
	//INIZIO DELLA VISUALIZZAZIONE DELLO SPARO
	if (partita.sparo_carro.stato)
	{
		al_draw_text(font_testo, al_map_rgb(0, 255, 0), partita.sparo_carro.pos_x, partita.sparo_carro.pos_y, ALLEGRO_ALIGN_CENTER, STRINGA_SPARO);
	}
	//FINE DELLA VISUALIZZAIZOEN DELLO SPARO

	//INIZIO DELLA VISUALIZZAZIOEN DEL CARRO ARMATO
	al_draw_text(font_mostri, al_map_rgb(0, 255, 0), partita.pos_x_carro, POS_Y_CARRO, ALLEGRO_ALIGN_CENTER, STRINGA_CARRO_ARMATO);
	//FINE DELLA VISUALIZZAZIONE DEL CARRO ARMATO

	al_flip_display();
}

inline void modificaImpostazioni (ALLEGRO_FONT *font_testo, Impostazioni impostazioni, Menu menu, bool redraw_lampeggio)
{
	unsigned int pos_y_attuale = POS_Y_TITOLO_IMPOSTAZIONI;
	unsigned int pos_x_attuale = POS_X_VOCI_IMPOSTAZIONI;

	//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
	al_draw_text(font_testo, al_map_rgb(0, 255, 0), pos_x_attuale, pos_y_attuale, ALLEGRO_ALIGN_LEFT, "IMPOSTAZIONI:");
	//FINE DELLA VISUALIZZAZIONE DEL TITOLO

	//INIZIO DELLA VISUALIZZAZIONE DELLE IMPOSTAZIONI
	pos_y_attuale = POS_Y_IMPOSTAZIONI;
	for (int i = 0; i < N_VOCI_MENU_IMPO; i++)
	{	
		pos_y_attuale += DIM_FONT_TESTO + SPAZIO_TESTO;
		al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_X_VOCI_IMPOSTAZIONI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, menu.testi_menu [i]);
		pos_x_attuale = POS_X_VALORI_IMPOSTAZIONI;
		if (!(menu.voce_sel == i && !redraw_lampeggio))
		{
			char str_stato [MAX_STRINGA_GENERICA] = "<    ";
			char str_valore [MAX_STRINGA_GENERICA];
			assert(stringaValoreVoceImpostazioni (str_valore, static_cast <voce_menu_impostazioni> (i), impostazioni));
			strcat (str_stato, str_valore);
			strcat (str_stato, "     >");
			al_draw_text(font_testo, al_map_rgb(0, 255, 0), pos_x_attuale, pos_y_attuale, ALLEGRO_ALIGN_LEFT, str_stato);
		}
	}
	//FINE DELLA VISUALIZZAZIONE DELLE IMPOSTAZIONI

	//INIZIO DELLA VISUALIZZAZIONE DELLE INDICAZIONI
	pos_y_attuale = POS_Y_INDICAZIONI_IMPOSTAZIONI;
	for (int i = 0; i < N_INDICAZIONI_MENU_IMPO; i++)
	{
		al_draw_text(font_testo, al_map_rgb(0, 255, 0), CENTRO_ORIZ, pos_y_attuale, ALLEGRO_ALIGN_CENTER, INDICAZIONI_IMPOSTAZIONI [i]);
		pos_y_attuale += DIM_FONT_TESTO * 2;
	}
	//FINE DELLA VISUALIZZAZIONE DELLE INDICAZIONI	

	al_flip_display();
}

inline void classificaHighscores (ALLEGRO_FONT *font_testo, Punteggio highscores [], int n_punteggi)
{
	unsigned int pos_y_attuale = POS_Y_HIGHSCORES_TITOLO;

	//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
	al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_X_NUMERAZIONE_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, "HIGHSCORES:");
	//FINE DELLA VISUALIZZAZIONE DEL TITOLO

	//INIZIO DELLA VISUALIZZAZIONE DEGLI HIGHSCORES
	pos_y_attuale = POS_Y_ELENCO_PUNTEGGI;

	for (int i = 0; i < n_punteggi; i++)
	{
		pos_y_attuale += DIM_FONT_TESTO + SPAZIO_TESTO;
		char str_numero [MAX_STRINGA_NUMERAZIONE] = "";
		sprintf(str_numero, "%d", i + 1);
		strcat (str_numero, ".");
		al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_X_NUMERAZIONE_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, str_numero);

		char str_valore [] = "";
		sprintf(str_valore, "%d", highscores [i].valore);
		al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_X_NOMI_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, highscores [i].nome);
		al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_X_VALORI_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, str_valore);
	}
	//FINE DELLA VISUALIZZAZIONE DEGLI HIGHSCORES

	//INIZIO DELLA VISUALIZZAZIONE DEL PREMI ENTER
	pos_y_attuale = POS_Y_INDICAZIONI_HIGHSCORES;
	al_draw_text(font_testo, al_map_rgb(0, 255, 0), CENTRO_ORIZ, pos_y_attuale, ALLEGRO_ALIGN_CENTER, "Premi enter per tornare al menu principale");
	//FINE DELLA VISUALIZZAZIONE DEL PREMI ENTER

	al_flip_display();
}

inline void pausa (ALLEGRO_FONT *font_testo, Partita partita, Menu menu, bool redraw_lampeggio)
{
	unsigned int pos_y_attuale;

	//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
	al_draw_text(font_testo, al_map_rgb(0, 255, 0), CENTRO_ORIZ, POS_Y_TITOLO_PAUSA, ALLEGRO_ALIGN_CENTRE, "PAUSA");
	//FINE DELLA VISUALIZZAZIONE DEL TITOLO

	//INIZIO DELLA VISUALIZZAZIONE DEL MENU DI PAUSA
	pos_y_attuale = POS_Y_VOCI_PAUSA;
	for (int i = 0; i < menu.n_voci; i++)
	{
		if (!(menu.voce_sel == i && !redraw_lampeggio))
		{
			al_draw_text(font_testo, al_map_rgb(0, 255, 0), CENTRO_ORIZ, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, menu.testi_menu [i]);
		}
		pos_y_attuale += SPAZIO_TESTO_GRANDE + DIM_FONT_TESTO;
	}
	//FINE DELLA VISUALIZZAZIONE DEL MENU DI PAUSA

	al_flip_display();
}

inline void finePartita (ALLEGRO_FONT *font_testo, Punteggio highscores [], int n_punteggi, Punteggio nuovo_punteggio, int posizione, bool redraw_lampeggio)
{
	unsigned int pos_y_attuale = POS_Y_HIGHSCORES_TITOLO;

	//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
	al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_X_NUMERAZIONE_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, "HIGHSCORES:");
	//FINE DELLA VISUALIZZAZIONE DEL TITOLO

	//INIZIO DELLA VISUALIZZAZIONE DEGLI HIGHSCORES
	pos_y_attuale = POS_Y_ELENCO_PUNTEGGI;

	for (int i = 0, p = 0; i <= n_punteggi&& i < MAX_HIGHSCORES; i++, p++)
	{
		pos_y_attuale += DIM_FONT_TESTO + SPAZIO_TESTO;
		char str_numero [MAX_STRINGA_NUMERAZIONE] = "";
		sprintf(str_numero, "%d", i + 1);
		strcat (str_numero, ".");
		al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_X_NUMERAZIONE_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, str_numero);

		char str_valore [] = "";
		unsigned int pos_x_attuale = POS_X_NOMI_PUNTEGGI;
		if (i == posizione)
		{
			char nome_visualizzato [CARATTERI_NOME];
			strcpy (nome_visualizzato, nuovo_punteggio.nome);
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
					al_draw_text(font_testo, al_map_rgb(0, 255, 0), pos_x_attuale, pos_y_attuale, ALLEGRO_ALIGN_LEFT, lettera);
					pos_x_attuale += al_get_text_width (font_testo, lettera);
				}
			}
			sprintf(str_valore, "%d", nuovo_punteggio.valore);
		}
		else
		{
			al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_X_NOMI_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, highscores [p].nome);
			sprintf(str_valore, "%d", highscores [p].valore);
		}
		al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_X_VALORI_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, str_valore);
	}
	//FINE DELLA VISUALIZZAZIONE DEGLI HIGHSCORES

	//INIZIO DELLA VISUALIZZAZIONE DEL PREMI ENTER
	al_draw_text(font_testo, al_map_rgb(0, 255, 0), CENTRO_ORIZ, POS_Y_INDICAZIONI_HIGHSCORES, ALLEGRO_ALIGN_CENTER, "Premi enter per salvare e tornare al menu principale");
	//FINE DELLA VISUALIZZAZIONE DEL PREMI ENTER

	al_flip_display();
}