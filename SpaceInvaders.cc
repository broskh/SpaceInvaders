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

#include <iostream>
using namespace std;

//INIZIO COSTANTI GENERALI PER DISPLAY
const unsigned int LARGHEZZA_DISPLAY = 640; /**<Larghezza della finestra del gioco.*/
const unsigned int ALTEZZA_DISPLAY = 480; /**<Altezza della finestra del gioco.*/

const unsigned int MARGINE_SX_GIOCO = 40; /**<Margine sinistro del gioco.*/
const unsigned int MARGINE_DX_GIOCO = LARGHEZZA_DISPLAY - MARGINE_SX_GIOCO; /**<Margine destro del gioco.*/
const unsigned int MARGINE_SUP_GIOCO = 45; /**<Margine superiore del gioco.*/
const unsigned int MARGINE_INF_GIOCO = 470; /**<Margine inferiore del gioco.*/
const unsigned int POS_CENTRO_X = ((MARGINE_DX_GIOCO - MARGINE_SX_GIOCO) / 2) + MARGINE_SX_GIOCO; /**<Posizione centrale della del display rispetto all'asse delle x.*/
//FINE COSTANTI GENERALI PER DISPLAY

//INIZIO COSTANTI PER VARI TIMER
const float FPS_GENERALE = 60; /**<FPS generale del gioco.*/
const float FPS_LAMPEGGIO_MENU = 3.5; /**<FPS per la frequenza in grado di consentire l'effetto di lampeggio sull'opzione selezionata dei menù.*/
const float FPS_SPARO_ALIENI = 1.5; /**<FPS per la frequenza di creazione degli spari da parte degli alieni.*/
const float FPS_CAMBIO_SPARO_ALIENI = 5; /**<FPS per la frequenza di cambiamento degli spari degli alieni.*/
const float FPS_NAVICELLA_MISTERIOSA = 1; /**<FPS per la frequenza della possibile comparsa della navicella misteriosa.*/
const float FPS_SPOSTAMENTO_ONDATA = 30; /**<FPS per la frequenza dello spostamento dell'ondata aliena.*/
//FINE COSTANTI PER VARI TIMER

//INIZIO COSTANTI E COSTANTI PER FILE
const char FILE_FONT_TESTO [] = "Fonts/space_invaders.ttf"; /**<File contenente il font utilizzato per i testi.*/
const char FILE_FONT_IMMAGINI [] = "Fonts/dustbust_invaders.ttf"; /**<File contenente il font utilizzato per gli alieni e altri elementi in tema nel gioco.*/
const char FILE_BARRIERA_PARZIALE [] = "Images/barriera_parziale.png"; /**<Percorso del file contenente l'immagine per rappresentare un elemento della barriera allo stato "parziale". (Deve essere 4x4 pixel)*/
const char FILE_BARRIERA_INTEGRA [] = "Images/barriera_integra.png"; /**<Percorso del file contenente l'immagine per rappresentare un elemento della barriera allo stato "integra". (Deve essere 4x4 pixel)*/
const char FILE_SPARO_ALIENI_1 [] = "Images/sparo_alieni_1.png"; /**<Percorso del file contenente l'immagine per rappresentare lo sparo degli alieni con posizione relativa all'asse x pari.*/
const char FILE_SPARO_ALIENI_2 [] = "Images/sparo_alieni_2.png"; /**<Percorso del file contenente l'immagine per rappresentare lo sparo degli alieni con posizione relativa all'asse x dispari.*/
const char FILE_MUSICA_PRINCIPALE [] = "Sounds/principale.flac"; /**<Percorso del file contenente la musica principale.*/
const char FILE_HIGHSCORES [] = "highscores"; /**<Percorso del file contenente gli highscores.*/
const char FILE_IMPOSTAZIONI [] = "SpaceInvaders.config"; /**<Percorso del file contenente le impostazioni salvate.*/
const char FILE_SALVATAGGIO_PARTITA [] = "partita.sav"; /**<Percorso del file contenente la partita salvata.*/
//FINE COSTANTI E COSTANTI PER FILE

//INIZIO COSTANTI E COSTANTI PER FONT E TESTI
const unsigned int SPAZIO_TESTO = 10; /**<Spazio fra righe di testo adiacenti.*/
const unsigned int SPAZIO_TESTO_GRANDE = 30; /**<Spazio grande fra righe di testo adiacenti.*/
const unsigned int DIMENSIONE_TITOLO = 140; /**<Dimensione del font utilizzato per il titolo.*/
const unsigned int DIMENSIONE_TESTO = 15; /**<Dimensione del font utilizzato per i testi generali.*/
const unsigned int DIM_ALIENI = 20; /**<Dimensione del font utilizzato per i alieni*/
//FINE COSTANTI E COSTANTI PER FONT E TESTI

//INIZIO COSTANTI PER POSIZIONI NELLA SCHERMATA DEL MENU PRINCIPALE
const unsigned int POS_X_ESEMPIO_ALIENI = 255; /**<Posizione rispetto all'asse x dalla quale mostrare i alieni nel menù principale.*/
const unsigned int POS_X_ESEMPIO_PUNTEGGIO = 350; /**<Posizione rispetto all'asse x dalla quale mostrare i punteggi nel menù principale.*/
const unsigned int POS_Y_TITOLO_MENU_PRINCIPALE = 25; /**<Posizione rispetto all'asse y dalla quale mostrare il titolo nel menù principale.*/
const unsigned int POS_Y_ESMEPIO_ALIENI = 200; /**<Posizione rispetto all'asse y dalla quale mostrare i alieni nel menù principale.*/
const unsigned int POS_Y_VOCI_MENU_PRINCIPALE = 340; /**<Posizione rispetto all'asse y dalla quale mostrare il menu nel menù principale.*/
//FINE COSTANTI PER POSIZIONI NELLA SCHERMATA DEL MENU PRINCIPALE

//INIZIO COSTANTI PER POSIZIONI NELLA SCHERMATA DI GIOCO
const unsigned int POS_Y_INFORMAZIONI_PARTITA = 10; /**<Posizione rispetto all'asse y dalla quale mostrare le informazioni della partita.*/
const unsigned int POS_Y_PRIMA_FILA_ONDATA = 80; /**<Posizione rispetto all'asse y dalla quale mostrare la prima fila di alieni.*/
const unsigned int POS_Y_BARRIERE = 360; /**<Posizone rispetto all'asse y dalla quale mostrare la prima barriera.*/
const unsigned int POS_Y_CARRO = MARGINE_INF_GIOCO - DIM_ALIENI;; /**<Posizione rispetto all'asse y dalla quale mostrare il carro armato.*/
const unsigned int POS_Y_SPARO = POS_Y_CARRO - DIMENSIONE_TESTO - 1; /**<Posizione iniziale rispetto all'asse y dello sparo.*/

const unsigned int DISTANZA_ASSI_COL_ALIENI = 40; /**<Distanza fra gli assi delle colonne di alieni.*/
const unsigned int DISTANZA_FILE_ALIENI = 35; /**<Distamza fra le file di alieni.*/
const unsigned int DISTANZA_BARRIERE = (LARGHEZZA_DISPLAY - (LARGHEZZA_PIXEL_BARRIERA * N_BARRIERE)) / (N_BARRIERE + 1); /**<Distanza in pixel fra le barriere.*/
const unsigned int POS_X_PRIMA_BARRIERA = DISTANZA_BARRIERE; /**<Posizione rispetto all'asse x della prima barriera.*/
const unsigned int POS_X_PRIMO_ASSE_ALIENI = POS_CENTRO_X - (DISTANZA_ASSI_COL_ALIENI * (N_COL_ALIENI - 1) / 2); /**<Posizone rispetto all'asse x nella quale è presente il primo asse delle colonne di alieni.*/
//FINE COSTANTI PER POSIZIONI NELLA SCHERMATA DI GIOCO

//INIZIO COSTANTI PER POSIZIONI NELLA SCHERMATA DEL MENU IMPOSTAZIONI
const unsigned int POS_X_VOCI_IMPOSTAZIONI = 95; /**<Posizione rispetto all'asse x dalla quale mostrare  il contenuto.*/
const unsigned int POS_X_VALORI_IMPOSTAZIONI = 295; /**<Posizione rispetto all'asse x dalla quale mostrare i valori dei vari campi impostazioni.*/
const unsigned int POS_Y_TITOLO_IMPOSTAZIONI = 60; /**<Posizione rispetto all'asse y dalla quale mostrare il titolo.*/
const unsigned int POS_Y_IMPOSTAZIONI = 105; /**<Posizione rispetto all'asse y dalla quale mostrare l'elenco delle impostazioni.*/
const unsigned int POS_Y_INDICAZIONI_IMPOSTAZIONI = 310; /**<Posizione rispetto all'asse y dalla quale mostrare il premi enter.*/
//FINE COSTANTI PER POSIZIONI NELLA SCHERMATA DEL MENU IMPOSTAZIONI

//INIZIO COSTANTI PER POSIZIONI NELLA SCHERMATA DEGLI HIGHSCORES
const unsigned int POS_X_NUMERAZIONE_PUNTEGGI = 250; /**<Posizione rispetto all'asse x dalla quale mostrare il contenuto.*/
const unsigned int POS_X_NOMI_PUNTEGGI = 280; /**<Posizione rispetto all'asse x dalla quale mostrare i nomi dei punteggi.*/
const unsigned int POS_X_VALORI_PUNTEGGI = 330; /**<Posizione rispetto all'asse x dalla quale mostrare i valori dei punteggi.*/
const unsigned int POS_Y_HIGHSCORES_TITOLO = 60; /**<Posizione rispetto all'asse y dalla quale mostrare il titolo.*/
const unsigned int POS_Y_ELENCO_PUNTEGGI = 90; /**<Posizione rispetto all'asse y dalla quale mostrare i punteggi.*/
const unsigned int POS_Y_INDICAZIONI_HIGHSCORES = 410; /**<Posizione rispetto all'asse y dalla quale mostrare il premi enter.*/
//FINE COSTANTI PER POSIZIONI NELLA SCHERMATA DEGLI HIGHSCORES

//INIZIO COSTANTI PER POSIZIONI NELLA SCHERMATA DEL MENU DI PAUSA
const unsigned int POS_Y_VOCI_PAUSA = 220; /**<Posizione rispetto all'asse y dalla quale mostrare il menu di pausa.*/
const unsigned int POS_Y_TITOLO_PAUSA = 100; /**<Posizione rispetto all'asse y dalla quale mostrare il titolo del menù di pausa.*/
//FINE COSTANTI PER POSIZIONI NELLA SCHERMATA DEL MENU DI PAUSA

//INIZIO VARIABILI PER FONT E IMMAGINI DI GIOCOÌ
ALLEGRO_FONT *font_alieni = NULL;
ALLEGRO_BITMAP *sparo_alieni_1 = NULL;
ALLEGRO_BITMAP *sparo_alieni_2 = NULL;
//INIZIO VARIABILI PER FONT E IMMAGINI DI GIOCO

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
 *
 * @return il valore della prossima schermata da mostrare.
 */
schermata cambiaSchermataMenuPausa (voce_menu_pausa voce, SpaceInvaders &spaceInvaders);

/**
 * Mostra il menù principale e ne gestisce il contenuto.
 * 
 * @param font_titolo Font utilizzato per scrivere il titolo.
 * @param font_menu Font utilizzato per scrivere il menù.
 * @param font_alieni Font utilizzato per disegnare i alieni.
 * @param menu Menu' principale.
 * @param redraw_lampeggio Indica se la voce di menù è da ridisegnare o no (utilizzato per mostrare l'effetto lampeggiante sull'opzione di menù selezioanta).
 * @param salvataggio Indica se esiste o meno il salvataggio di una partita precedente (necessario per sapere di che colore disegnare la voce di menù caric).
 */
inline void menuPrincipale (ALLEGRO_FONT *font_titolo, ALLEGRO_FONT *font_menu, ALLEGRO_FONT *font_alieni, Menu menu, bool redraw_lampeggio, bool salvataggio);

/**
 * Mostra il gioco vero e proprio.
 * 
 * @param font_alieni Font con il quale vengono disegnati i alieni.
 * @param font_testo Font utilizzato per scrivere le stringhe di testo.
 * @param barriera_parziale Bitmap rappresentante un unità della barriera nello stato "parziale".
 * @param barriera_integra Bitmap rappresentante un unità della barriera nello stato "integra".
 * @param partita Struttura {@link Partita} contenente le informazioni relative alla partita attuale.
 * @param impostazioni Impostazioni generali del gioco.
 */
inline void gioca (ALLEGRO_FONT *font_alieni, ALLEGRO_FONT *font_testo, ALLEGRO_BITMAP *sparo_alieni_1, ALLEGRO_BITMAP *sparo_alieni_2, ALLEGRO_BITMAP *barriera_parziale, ALLEGRO_BITMAP *barriera_integra, Partita &partita, Impostazioni impostazioni, bool ruota_sparo);

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
	ALLEGRO_TIMER *timer_sparo_alieni= NULL;
	ALLEGRO_TIMER *timer_rotazione_sparo = NULL;
	ALLEGRO_TIMER *timer_comparsa_navicella = NULL;
	ALLEGRO_TIMER *timer_spostamento_ondata = NULL;
	ALLEGRO_FONT *font_titolo = NULL;
	ALLEGRO_FONT *font_testo = NULL;
	ALLEGRO_BITMAP *barriera_parziale = NULL;
	ALLEGRO_BITMAP *barriera_integra = NULL;
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

	timer_sparo_alieni = al_create_timer(1.0 / FPS_SPARO_ALIENI);
	assert (timer_sparo_alieni);

	timer_rotazione_sparo = al_create_timer(1.0 / FPS_CAMBIO_SPARO_ALIENI);
	assert (timer_rotazione_sparo);

	timer_comparsa_navicella = al_create_timer(1.0 / FPS_NAVICELLA_MISTERIOSA);
	assert (timer_comparsa_navicella);

	timer_spostamento_ondata = al_create_timer(1.0 / FPS_SPOSTAMENTO_ONDATA);
	assert (timer_spostamento_ondata);

	font_titolo = al_load_ttf_font(FILE_FONT_IMMAGINI, DIMENSIONE_TITOLO, 0);
	assert (font_titolo);
	font_testo = al_load_ttf_font(FILE_FONT_TESTO, DIMENSIONE_TESTO, 0);
 	assert (font_testo);
	font_alieni = al_load_ttf_font(FILE_FONT_IMMAGINI, DIM_ALIENI, 0);
 	assert (font_alieni);
	
	barriera_parziale = al_load_bitmap(FILE_BARRIERA_PARZIALE);
	assert (barriera_parziale);
	barriera_integra = al_load_bitmap(FILE_BARRIERA_INTEGRA);
	assert (barriera_integra);
	sparo_alieni_1 = al_load_bitmap(FILE_SPARO_ALIENI_1);
	assert (sparo_alieni_1);
	sparo_alieni_2 = al_load_bitmap(FILE_SPARO_ALIENI_2);
	assert (sparo_alieni_2);

	musica_principale = al_load_sample (FILE_MUSICA_PRINCIPALE);
	assert (musica_principale);
 
   	al_register_event_source(coda_eventi, al_get_display_event_source(display));
	al_register_event_source(coda_eventi, al_get_timer_event_source(frame_rate_generale));
	al_register_event_source(coda_eventi, al_get_timer_event_source(lampeggio_voce));
	al_register_event_source(coda_eventi, al_get_timer_event_source(timer_sparo_alieni));
	al_register_event_source(coda_eventi, al_get_timer_event_source(timer_rotazione_sparo));
	al_register_event_source(coda_eventi, al_get_timer_event_source(timer_comparsa_navicella));
	al_register_event_source(coda_eventi, al_get_timer_event_source(timer_spostamento_ondata));
	al_register_event_source(coda_eventi, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_start_timer(frame_rate_generale);
	
	//INIZIO INIZIALIZZAZIONE DELLA STRUTTURA PRINCIPALE
	SpaceInvaders generale;
	if (!caricaImpostazioni (generale.impostazioni))
	{
		impostaValoriImpostazioniDefault (generale.impostazioni);
		salvaImpostazioni (generale.impostazioni);
	}
	if (!caricaPunteggi (generale.highscores, generale.n_highscores))
	{
		generale.n_highscores = 0;
	}
	generale.partita_salvata = esisteSalvataggio ();
	nuovaPartita (generale.partita_in_corso, generale.impostazioni);
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
						menuPrincipale (font_titolo, font_testo, font_alieni, menu_principale, redraw_lampeggio, generale.partita_salvata);
					}
			   	}
				al_stop_timer(lampeggio_voce);
				break;
			case s_gioca:
				eliminaFileSalvataggio (generale);
				if (generale.impostazioni.musica)
				{
					al_stop_samples();
				}
				al_start_timer(timer_sparo_alieni);
				al_start_timer(timer_rotazione_sparo);
				al_start_timer(timer_comparsa_navicella);
				al_start_timer(timer_spostamento_ondata);

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
						else if (ev.timer.source == timer_sparo_alieni)
						{
							if (!generale.partita_in_corso.sparo_alieni.stato)
							{
								creaSparoAlieni (generale.partita_in_corso);
							}
						}
						else if (ev.timer.source == timer_comparsa_navicella)
						{
							if (!generale.partita_in_corso.navicella_misteriosa.stato)
							{
								creaNavicellaMisteriosa (generale.partita_in_corso);
							}
						}
						else if (ev.timer.source == timer_spostamento_ondata)
						{
							muoviAlieni (generale.partita_in_corso.ondata);
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
							case ALLEGRO_KEY_BACKSPACE:
								while (true)
								{
									;
								}
								break;
						}
					}
					else if(ev.type == ALLEGRO_EVENT_KEY_CHAR)
					{
						switch(ev.keyboard.keycode)
						{
							case ALLEGRO_KEY_LEFT:
								muoviSinistraCarro (generale.partita_in_corso.pos_x_carro);
								break;
							case ALLEGRO_KEY_RIGHT:
								muoviDestraCarro (generale.partita_in_corso.pos_x_carro);
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
						gioca (font_alieni, font_testo, sparo_alieni_1, sparo_alieni_2, barriera_parziale, barriera_integra, generale.partita_in_corso, generale.impostazioni, ruota_sparo);

						//INIZIO DEI CONTROLLI
						if (controlloCollisioneCarroDaSparoAlieni (generale.partita_in_corso))
						{
						}
						if (generale.partita_in_corso.vite_rimanenti < 0 || controlloCollisioneCarroDaOndata (generale.partita_in_corso))
						{
							schermata_att = s_fine_partita;
							cambia_schermata = true;
							break;
						}
						if (controlloCollisioneAlieni (generale.partita_in_corso))
						{
						}
						if (controlloCollisioneBarriereDaSparoCarro (generale.partita_in_corso))
						{
						}
						if (controlloCollisioneBarriereDaSparoAlieni (generale.partita_in_corso))
						{
						}
						if (controlloCollisioneNavicellaMisteriosa (generale.partita_in_corso))
						{
						}
						if (controlloCollisioneBarriereDaOndata (generale.partita_in_corso))
						{
						}
						//FINE DEI CONTROLLI
						//INIZIO DEI CAMBIAMENTI
						if (generale.partita_in_corso.sparo_carro.stato)
						{
							muoviSparoCarro (generale.partita_in_corso.sparo_carro);
						}
						if (generale.partita_in_corso.sparo_alieni.stato)
						{
							muoviSparoAlieni (generale.partita_in_corso.sparo_alieni);
						}
						if (generale.partita_in_corso.navicella_misteriosa.stato)
						{
							muoviNavicellaMisteriosa (generale.partita_in_corso);
						}
						//FINE DEI CAMBIAMENTI
					}
			   	}
				al_stop_timer(timer_sparo_alieni);
				al_stop_timer(timer_rotazione_sparo);
				al_stop_timer(timer_comparsa_navicella);
				al_stop_timer(timer_spostamento_ondata);
				break;
			case s_carica:
				assert (caricaPartita (generale.partita_in_corso));
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
								salvaImpostazioni (generale.impostazioni);
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
								schermata_att = cambiaSchermataMenuPausa (static_cast <voce_menu_pausa> (menu_pausa.voce_sel), generale);
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
								if (posizione != -1)
								{
									aggiungiPunteggio (generale.highscores, generale.n_highscores, generale.partita_in_corso.punteggio, posizione);
									salvaPunteggi (generale.highscores, generale.n_highscores);
								}

								nuovaPartita (generale.partita_in_corso, generale.impostazioni);
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
				al_destroy_timer(timer_sparo_alieni);
				al_destroy_timer(timer_rotazione_sparo);
				al_destroy_timer(timer_comparsa_navicella);
				al_destroy_timer(timer_spostamento_ondata);
   				al_destroy_bitmap(sparo_alieni_1);
   				al_destroy_bitmap(sparo_alieni_2);
   				al_destroy_bitmap(barriera_parziale);
   				al_destroy_bitmap(barriera_integra);
				al_destroy_sample(musica_principale);
				return 0;
			default:
				al_destroy_display(display);
				al_destroy_event_queue(coda_eventi);
				al_destroy_timer(frame_rate_generale);
				al_destroy_timer(lampeggio_voce);
				al_destroy_timer(timer_sparo_alieni);
				al_destroy_timer(timer_rotazione_sparo);
				al_destroy_timer(timer_comparsa_navicella);
				al_destroy_timer(timer_spostamento_ondata);
   				al_destroy_bitmap(sparo_alieni_1);
   				al_destroy_bitmap(sparo_alieni_2);
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
	al_destroy_timer(timer_sparo_alieni);
	al_destroy_timer(timer_rotazione_sparo);
	al_destroy_timer(timer_comparsa_navicella);
	al_destroy_timer(timer_spostamento_ondata);
	al_destroy_bitmap(sparo_alieni_1);
	al_destroy_bitmap(sparo_alieni_2);
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

schermata cambiaSchermataMenuPausa (voce_menu_pausa voce, SpaceInvaders &spaceInvaders)
{
	if (voce == v_continua)
	{
		return s_gioca;
	}
	else if (voce == v_salva)
	{
		salvaPartita (spaceInvaders);
	}
	else if (voce == v_abbandona)
	{
		;
	}
	nuovaPartita (spaceInvaders.partita_in_corso, spaceInvaders.impostazioni);
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
			dx += DIMENSIONE_LATO_UNITA_BARRIERA;
		}
		dx = pos_x;
		dy += DIMENSIONE_LATO_UNITA_BARRIERA;
	}
}

inline void menuPrincipale (ALLEGRO_FONT *font_titolo, ALLEGRO_FONT *font_menu, ALLEGRO_FONT *font_alieni, Menu menu, bool redraw_lampeggio, bool salvataggio)
{
	//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
	al_draw_text(font_titolo, al_map_rgb(0, 255, 0), POS_CENTRO_X, POS_Y_TITOLO_MENU_PRINCIPALE, ALLEGRO_ALIGN_CENTRE, ".");
	//FINE DELLA VISUALIZZAZIONE DEL TITOLO

	//INIZIO DELLA VISUALIZZAZIONE DEI ALIENI E I RELATIVI PUNTEGGI
	unsigned int pos_y_attuale = POS_Y_ESMEPIO_ALIENI;
	al_draw_text(font_alieni, al_map_rgb(0, 255, 0), POS_X_ESEMPIO_ALIENI, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, STRINGA_ALIENO_3);
	al_draw_text(font_menu, al_map_rgb(0, 255, 0), POS_X_ESEMPIO_PUNTEGGIO, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, "=      10  PTS");

	pos_y_attuale = POS_Y_ESMEPIO_ALIENI + SPAZIO_TESTO + DIM_ALIENI;
	al_draw_text(font_alieni, al_map_rgb(0, 255, 0), POS_X_ESEMPIO_ALIENI, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, STRINGA_ALIENO_2);
	al_draw_text(font_menu, al_map_rgb(0, 255, 0), POS_X_ESEMPIO_PUNTEGGIO, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, "=      20  PTS");

	pos_y_attuale = POS_Y_ESMEPIO_ALIENI + (SPAZIO_TESTO + DIM_ALIENI) * 2;
	al_draw_text(font_alieni, al_map_rgb(0, 255, 0), POS_X_ESEMPIO_ALIENI, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, STRINGA_ALIENO_1);
	al_draw_text(font_menu, al_map_rgb(0, 255, 0), POS_X_ESEMPIO_PUNTEGGIO, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, "=      30  PTS");

	pos_y_attuale = POS_Y_ESMEPIO_ALIENI + (SPAZIO_TESTO + DIM_ALIENI) * 3;
	al_draw_text(font_alieni, al_map_rgb(255, 0, 0), POS_X_ESEMPIO_ALIENI, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, STRINGA_NAVICELLA);
	al_draw_text(font_menu, al_map_rgb(0, 255, 0), POS_X_ESEMPIO_PUNTEGGIO, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, "=         ?  PTS");
	//FINE DELLA VISUALIZZAZIONE DEI ALIENI E I RELATIVI PUNTEGGI
	
	//INIZIO DELLA VISUALIZZAZIONE DEL MENU
	for (int i = 0; i < menu.n_voci; i++)
	{
		if (!(menu.voce_sel == i && !redraw_lampeggio))
		{
			pos_y_attuale = POS_Y_VOCI_MENU_PRINCIPALE + (SPAZIO_TESTO + DIMENSIONE_TESTO) * i;
			if ((!salvataggio) && (static_cast <voce_menu_principale> (i) == v_carica))
			{
				al_draw_text(font_menu, al_map_rgb(84, 84, 84), POS_CENTRO_X, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, menu.testi_menu [i]);
			}
			else
			{
				al_draw_text(font_menu, al_map_rgb(0, 255, 0), POS_CENTRO_X, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, menu.testi_menu [i]);
			}
		}
	}
	//FINE DELLA VISUALIZZAZIONE DEL MENU

	al_flip_display();
}

inline void gioca (ALLEGRO_FONT *font_alieni, ALLEGRO_FONT *font_testo, ALLEGRO_BITMAP *sparo_alieni_1, ALLEGRO_BITMAP *sparo_alieni_2, ALLEGRO_BITMAP *barriera_parziale, ALLEGRO_BITMAP *barriera_integra, Partita &partita, Impostazioni impostazioni, bool ruota_sparo)
{
	unsigned int pos_y_attuale;
	unsigned int pos_x_attuale;

	//INIZIO DELLA VISUALIZZAZIONE DELLE INFORMAZIONI
	char stringa_punteggio [] = "Punteggio:    ";
	char valore_punteggio [MAX_STRINGA_GENERICA];
	sprintf(valore_punteggio, "%d", partita.punteggio.valore);
	strcat (stringa_punteggio, valore_punteggio);
	pos_x_attuale = (POS_CENTRO_X - al_get_text_width(font_testo, stringa_punteggio)) / 2;
	al_draw_text(font_testo, al_map_rgb(0, 255, 0), pos_x_attuale, POS_Y_INFORMAZIONI_PARTITA, ALLEGRO_ALIGN_LEFT, stringa_punteggio);

	char stringa_vite [] = "Vite:    ";
	char valore_vite [MAX_STRINGA_GENERICA];
	sprintf(valore_vite, "%d", partita.vite_rimanenti);
	strcat (stringa_vite, valore_vite);
	pos_x_attuale = (POS_CENTRO_X - al_get_text_width(font_testo, stringa_vite)) / 2 + POS_CENTRO_X;
	al_draw_text(font_testo, al_map_rgb(0, 255, 0), pos_x_attuale, POS_Y_INFORMAZIONI_PARTITA, ALLEGRO_ALIGN_CENTRE, stringa_vite);
	//FINE DELLA VISUALIZZAZIONE DELLE INFORMAZIONI

	//INIZIO DELLA VISUALIZZAZIONE DELLA NAVICELLA MISTERIOSA
	if (partita.navicella_misteriosa.stato)
	{
		al_draw_text(font_alieni, al_map_rgb(255, 0, 0), partita.pos_x_navicella, MARGINE_SUP_GIOCO, ALLEGRO_ALIGN_LEFT, partita.navicella_misteriosa.stringa);
	}
	//FINE DELLA VISUALIZZAZIONE DELLA NAVICELLA MISTERIOSA

	//INIZIO DELLA VISUALIZZAZIONE DELL'ONDATA
	pos_y_attuale = partita.ondata.pos_y;

	for (unsigned int i = 0; i < N_FILE_ALIENI; i++)
	{
		pos_x_attuale = partita.ondata.pos_x;
		for (unsigned int j = 0; j < N_COL_ALIENI; j++)
		{
			if (partita.ondata.alieni [i] [j].stato)
			{
				al_draw_text(font_alieni, al_map_rgb(0, 255, 0), pos_x_attuale, pos_y_attuale, ALLEGRO_ALIGN_CENTER, partita.ondata.alieni [i] [j].stringa);
			}
			pos_x_attuale += DISTANZA_ASSI_COL_ALIENI;
		}
		pos_y_attuale += DISTANZA_FILE_ALIENI;
	}
	//FINE DELLA VISUALIZZAZIONE DELL'ONDATA

	//INIZIO DELLA VISUALIZZAZIONE DELLO SPARO DEI ALIENI
	if (partita.sparo_alieni.stato)
	{
		unsigned int sx;
		ALLEGRO_BITMAP *sparo_attuale;
		sparo_attuale = sparoScelto (partita.sparo_alieni.pos_x);
		if (ruota_sparo)
		{
			sx = 0;			
		}
		else
		{
			sx = al_get_bitmap_width (sparo_attuale) / 2;
		}
		al_draw_tinted_bitmap_region(sparo_attuale, al_map_rgb(0, 255, 0), sx, 0, al_get_bitmap_width (sparo_attuale) / 2, al_get_bitmap_height (sparo_attuale), partita.sparo_alieni.pos_x, partita.sparo_alieni.pos_y, 0);
	}
	//FINE DELLA VISUALIZZAZIONE DELLO SPARO DEI ALIENI

	//INIZIO DELLA VISUALIZZAZIONE DELLE BARRIERE
	pos_x_attuale = DISTANZA_BARRIERE;
	for (unsigned int i = 0; i < N_BARRIERE; i++)
	{
		disegnaBarriera (barriera_parziale, barriera_integra, partita.barriere [i], pos_x_attuale, POS_Y_BARRIERE);
		pos_x_attuale += DISTANZA_BARRIERE + LARGHEZZA_PIXEL_BARRIERA;
	}
	//FINE DELLA VISUALIZZAZIONE DELLE BARRIERE
	
	//INIZIO DELLA VISUALIZZAZIONE DELLO SPARO
	if (partita.sparo_carro.stato)
	{
		al_draw_text(font_testo, al_map_rgb(0, 255, 0), partita.sparo_carro.pos_x, partita.sparo_carro.pos_y, ALLEGRO_ALIGN_CENTER, STRINGA_SPARO);
	}
	//FINE DELLA VISUALIZZAIZOEN DELLO SPARO

	//INIZIO DELLA VISUALIZZAZIOEN DEL CARRO ARMATO
	al_draw_text(font_alieni, al_map_rgb(0, 255, 0), partita.pos_x_carro, POS_Y_CARRO, ALLEGRO_ALIGN_CENTER, STRINGA_CARRO_ARMATO);
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
		pos_y_attuale += DIMENSIONE_TESTO + SPAZIO_TESTO;
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
		al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_CENTRO_X, pos_y_attuale, ALLEGRO_ALIGN_CENTER, INDICAZIONI_IMPOSTAZIONI [i]);
		pos_y_attuale += DIMENSIONE_TESTO * 2;
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
		pos_y_attuale += DIMENSIONE_TESTO + SPAZIO_TESTO;
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
	al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_CENTRO_X, pos_y_attuale, ALLEGRO_ALIGN_CENTER, "Premi enter per tornare al menu principale");
	//FINE DELLA VISUALIZZAZIONE DEL PREMI ENTER

	al_flip_display();
}

inline void pausa (ALLEGRO_FONT *font_testo, Partita partita, Menu menu, bool redraw_lampeggio)
{
	unsigned int pos_y_attuale;

	//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
	al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_CENTRO_X, POS_Y_TITOLO_PAUSA, ALLEGRO_ALIGN_CENTRE, "PAUSA");
	//FINE DELLA VISUALIZZAZIONE DEL TITOLO

	//INIZIO DELLA VISUALIZZAZIONE DEL MENU DI PAUSA
	pos_y_attuale = POS_Y_VOCI_PAUSA;
	for (int i = 0; i < menu.n_voci; i++)
	{
		if (!(menu.voce_sel == i && !redraw_lampeggio))
		{
			al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_CENTRO_X, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, menu.testi_menu [i]);
		}
		pos_y_attuale += SPAZIO_TESTO_GRANDE + DIMENSIONE_TESTO;
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
		pos_y_attuale += DIMENSIONE_TESTO + SPAZIO_TESTO;
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
	al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_CENTRO_X, POS_Y_INDICAZIONI_HIGHSCORES, ALLEGRO_ALIGN_CENTER, "Premi enter per salvare e tornare al menu principale");
	//FINE DELLA VISUALIZZAZIONE DEL PREMI ENTER

	al_flip_display();
}