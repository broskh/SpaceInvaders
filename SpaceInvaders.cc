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

const unsigned int MARGINE_SX_GIOCO = 30; /**<Margine sinistro del gioco.*/
const unsigned int MARGINE_DX_GIOCO = LARGHEZZA_DISPLAY - MARGINE_SX_GIOCO; /**<Margine destro del gioco.*/
const unsigned int MARGINE_SUP_GIOCO = 45; /**<Margine superiore del gioco.*/
const unsigned int MARGINE_INF_GIOCO = 470; /**<Margine inferiore del gioco.*/
const unsigned int POS_CENTRO_X = ((MARGINE_DX_GIOCO - MARGINE_SX_GIOCO) / 2) + MARGINE_SX_GIOCO; /**<Posizione centrale della del display rispetto all'asse delle x.*/
//FINE COSTANTI GENERALI PER DISPLAY

//INIZIO COSTANTI PER VARI TIMER
const float FPS_GENERALE = 60; /**<FPS generale del gioco.*/
const float FPS_LAMPEGGIO_MENU = 3.5; /**<FPS per la frequenza in grado di consentire l'effetto di lampeggio sull'opzione selezionata dei menù.*/
const float FPS_SPARO_ALIENI = 1.5; /**<FPS per la frequenza di creazione degli spari da parte degli alieni.*/
const float FPS_ANIMAZIONE = 4; /**<FPS per la frequenza di cambiamento necessaria per realizzare l'animazione.*/
const float FPS_NAVICELLA_MISTERIOSA = 1; /**<FPS per la frequenza della possibile comparsa della navicella misteriosa.*/
const float FPS_SPOSTAMENTO_ONDATA = 30; /**<FPS per la frequenza dello spostamento dell'ondata aliena.*/
//FINE COSTANTI PER VARI TIMER

//INIZIO COSTANTI PER FILE
const char FILE_FONT_TESTO [] = "Fonts/space_invaders.ttf"; /**<File contenente il font utilizzato per i testi.*/
const char FILE_FONT_TITOLO [] = "Fonts/dustbust_invaders.ttf"; /**<File contenente il font utilizzato per il titolo nel menù principale del gioco.*/
const char FILE_BARRIERA_PARZIALE [] = "Images/barriera_parziale.png"; /**<Percorso del file contenente l'immagine per rappresentare un elemento della barriera allo stato "parziale". (Deve essere 4x4 pixel)*/
const char FILE_BARRIERA_INTEGRA [] = "Images/barriera_integra.png"; /**<Percorso del file contenente l'immagine per rappresentare un elemento della barriera allo stato "integra". (Deve essere 4x4 pixel)*/
const char FILE_SPARO_ALIENI_1 [] = "Images/sparo_alieni_1.png"; /**<Percorso del file contenente l'immagine per rappresentare lo sparo degli alieni con posizione relativa all'asse x pari.*/
const char FILE_SPARO_ALIENI_2 [] = "Images/sparo_alieni_2.png"; /**<Percorso del file contenente l'immagine per rappresentare lo sparo degli alieni con posizione relativa all'asse x dispari.*/
const char FILE_CARRO_ARMATO [] ="Images/carro_armato.png";
const char FILE_SPARO_CARRO [] ="Images/sparo_carro.png";
const char FILE_NAVICELLA_MISTERIOSA [] ="Images/navicella_misteriosa.png";
const char FILE_ALIENO_TIPO_1 [] ="Images/alieno1.png";
const char FILE_ALIENO_TIPO_2 [] ="Images/alieno2.png";
const char FILE_ALIENO_TIPO_3 [] ="Images/alieno3.png";
const char FILE_ESPLOSIONE_CARRO [] = "Images/esplosione_carro.png"; /**<Percorso del file contenente l'immagine per rappresentare lo sparo degli alieni con posizione relativa all'asse x dispari.*/
const char FILE_MUSICA_PRINCIPALE [] = "Sounds/principale.flac"; /**<Percorso del file contenente la musica principale.*/
//FINE COSTANTI PER FILE

//INIZIO COSTANTI PER FONT E TESTI
const unsigned int SPAZIO_TESTO = 10; /**<Spazio fra righe di testo adiacenti.*/
const unsigned int SPAZIO_TESTO_GRANDE = 30; /**<Spazio grande fra righe di testo adiacenti.*/
const unsigned int DIMENSIONE_TITOLO = 140; /**<Dimensione del font utilizzato per il titolo.*/
const unsigned int DIMENSIONE_TESTO = 15; /**<Dimensione del font utilizzato per i testi generali.*/
//FINE COSTANTI PER FONT E TESTI

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

//INIZIO COSTANTI GENERICHE DI GIOCO
const int RIPETIZIONI_ANIMAZIONE_ESPLOSIONE_CARRO = 2;
const unsigned int N_STATI_SPRITE = 2;
const unsigned int N_TIPI_ALIENI = 3;
//FINE COSTANTI GENERICHE DI GIOCO

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

void disegnaBarriera (ALLEGRO_BITMAP *barriera_parziale, ALLEGRO_BITMAP *barriera_integra, stato_barriera barriera [ALT_BARRIERA] [LARG_BARRIERA], unsigned int pos_x, unsigned int pos_y);

void disegnaAlieno (ALLEGRO_BITMAP *alieno_scelto, unsigned int pos_x, unsigned int pos_y);

ALLEGRO_BITMAP* scegliImmagine (unsigned int numero_fila, ALLEGRO_BITMAP *alieno_tipo_1, ALLEGRO_BITMAP *alieno_tipo_2, ALLEGRO_BITMAP *alieno_tipo_3);

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
	ALLEGRO_TIMER *timer_animazione = NULL;
	ALLEGRO_TIMER *timer_comparsa_navicella = NULL;
	ALLEGRO_TIMER *timer_spostamento_ondata = NULL;
	ALLEGRO_BITMAP *barriera_parziale = NULL;
	ALLEGRO_BITMAP *barriera_integra = NULL;
	ALLEGRO_BITMAP *carro_armato = NULL;
	ALLEGRO_BITMAP *sparo_carro = NULL;
	ALLEGRO_BITMAP *navicella_misteriosa = NULL;
	ALLEGRO_BITMAP *alieno_tipo_1 = NULL;
	ALLEGRO_BITMAP *alieno_tipo_2 = NULL;
	ALLEGRO_BITMAP *alieno_tipo_3 = NULL;
	ALLEGRO_BITMAP *sparo_alieni_1 = NULL;
	ALLEGRO_BITMAP *sparo_alieni_2 = NULL;
	ALLEGRO_FONT *font_titolo = NULL;
	ALLEGRO_FONT *font_testo = NULL;
   	ALLEGRO_SAMPLE *musica_principale = NULL;

	ALLEGRO_BITMAP *esplosione_carro = NULL;

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

	timer_animazione = al_create_timer(1.0 / FPS_ANIMAZIONE);
	assert (timer_animazione);

	timer_comparsa_navicella = al_create_timer(1.0 / FPS_NAVICELLA_MISTERIOSA);
	assert (timer_comparsa_navicella);

	timer_spostamento_ondata = al_create_timer(1.0 / FPS_SPOSTAMENTO_ONDATA);
	assert (timer_spostamento_ondata);

	font_titolo = al_load_ttf_font(FILE_FONT_TITOLO, DIMENSIONE_TITOLO, 0);
	assert (font_titolo);
	font_testo = al_load_ttf_font(FILE_FONT_TESTO, DIMENSIONE_TESTO, 0);
 	assert (font_testo);
	
	barriera_parziale = al_load_bitmap(FILE_BARRIERA_PARZIALE);
	assert (barriera_parziale);
	barriera_integra = al_load_bitmap(FILE_BARRIERA_INTEGRA);
	assert (barriera_integra);
	sparo_alieni_1 = al_load_bitmap(FILE_SPARO_ALIENI_1);
	assert (sparo_alieni_1);
	sparo_alieni_2 = al_load_bitmap(FILE_SPARO_ALIENI_2);
	assert (sparo_alieni_2);
	esplosione_carro = al_load_bitmap(FILE_ESPLOSIONE_CARRO);
	assert (esplosione_carro);

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

	musica_principale = al_load_sample (FILE_MUSICA_PRINCIPALE);
	assert (musica_principale);
 
   	al_register_event_source(coda_eventi, al_get_display_event_source(display));
	al_register_event_source(coda_eventi, al_get_timer_event_source(frame_rate_generale));
	al_register_event_source(coda_eventi, al_get_timer_event_source(lampeggio_voce));
	al_register_event_source(coda_eventi, al_get_timer_event_source(timer_sparo_alieni));
	al_register_event_source(coda_eventi, al_get_timer_event_source(timer_animazione));
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
	bool animazione;
	int animazione_esplosione_carro;

	int posizione;
	char input [] = " ";
	
	while (true)
	{
		cambia_schermata = false;
		redraw_lampeggio = false;
		animazione = false;
		animazione_esplosione_carro = 0;
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
				nuovaPartita (generale.partita_in_corso, generale.impostazioni, POS_CENTRO_X - al_get_bitmap_width (carro_armato) / 2);
				generale.partita_salvata = esisteSalvataggio ();
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
				al_start_timer(timer_animazione);
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
						else if (ev.timer.source == timer_animazione)
						{
							animazione = !animazione;
							if (generale.partita_in_corso.carro_armato.esploso)
							{
								if (animazione_esplosione_carro <= RIPETIZIONI_ANIMAZIONE_ESPLOSIONE_CARRO * 2)
								{
									animazione_esplosione_carro++;
								}
								else
								{
									animazione_esplosione_carro = 0;
									generale.partita_in_corso.carro_armato.esploso = false;
								}
							}
						}
						else if (!generale.partita_in_corso.carro_armato.esploso)
						{
							if (ev.timer.source == timer_sparo_alieni)
							{
								if (!generale.partita_in_corso.sparo_alieni.stato)
								{
									creaSparoAlieni (generale.partita_in_corso, al_get_bitmap_height (alieno_tipo_1), al_get_bitmap_width (alieno_tipo_1) / N_STATI_SPRITE, al_get_bitmap_width (alieno_tipo_2) / N_STATI_SPRITE, al_get_bitmap_width (alieno_tipo_3) / N_STATI_SPRITE);
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
								muoviAlieni (generale.partita_in_corso.ondata, al_get_bitmap_width (alieno_tipo_3) / N_STATI_SPRITE, MARGINE_INF_GIOCO - al_get_bitmap_height (carro_armato));
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
							case ALLEGRO_KEY_BACKSPACE:
								while (true)
								{
									;//DA CANCELLARE PRIMA O POI
								}
								break;
						}
					}
					else if(ev.type == ALLEGRO_EVENT_KEY_CHAR)
					{
						if (!generale.partita_in_corso.carro_armato.esploso)
						{
							switch(ev.keyboard.keycode)
							{
								case ALLEGRO_KEY_LEFT:
									muoviSinistraCarro (generale.partita_in_corso.carro_armato.pos_x);
									break;
								case ALLEGRO_KEY_RIGHT:
									muoviDestraCarro (generale.partita_in_corso.carro_armato.pos_x, al_get_bitmap_width (carro_armato));
									break;
								case ALLEGRO_KEY_SPACE:
									if (!generale.partita_in_corso.carro_armato.sparo.stato)
									{
										creaSparoCarroArmato (generale.partita_in_corso.carro_armato, al_get_bitmap_width (carro_armato), MARGINE_INF_GIOCO - al_get_bitmap_height (carro_armato) - al_get_bitmap_height (sparo_carro));
									}
									break;
							}
						}
					}				

					if(redraw && al_is_event_queue_empty(coda_eventi))
					{
						//INIZIO VISUALIZZAZIONE
        					al_clear_to_color(al_map_rgb(0, 0, 0));

						unsigned int pos_y_attuale;
						unsigned int pos_x_attuale;

						//INIZIO DELLA VISUALIZZAZIONE DELLE INFORMAZIONI
						char stringa_punteggio [] = "Punteggio:    ";
						char valore_punteggio [MAX_STRINGA_GENERICA];
						sprintf(valore_punteggio, "%d", generale.partita_in_corso.punteggio.valore);
						strcat (stringa_punteggio, valore_punteggio);
						pos_x_attuale = (POS_CENTRO_X - al_get_text_width(font_testo, stringa_punteggio)) / 2;
						al_draw_text(font_testo, al_map_rgb(0, 255, 0), pos_x_attuale, POS_Y_INFORMAZIONI_PARTITA, ALLEGRO_ALIGN_LEFT, stringa_punteggio);

						char stringa_vite [] = "Vite:    ";
						char valore_vite [MAX_STRINGA_GENERICA];
						sprintf(valore_vite, "%d", generale.partita_in_corso.vite_rimanenti);
						strcat (stringa_vite, valore_vite);
						pos_x_attuale = (POS_CENTRO_X - al_get_text_width(font_testo, stringa_vite)) / 2 + POS_CENTRO_X;
						al_draw_text(font_testo, al_map_rgb(0, 255, 0), pos_x_attuale, POS_Y_INFORMAZIONI_PARTITA, ALLEGRO_ALIGN_CENTRE, stringa_vite);
						//FINE DELLA VISUALIZZAZIONE DELLE INFORMAZIONI

						//INIZIO DELLA VISUALIZZAZIONE DELLA NAVICELLA MISTERIOSA
						if (generale.partita_in_corso.navicella_misteriosa.stato)
						{
							al_draw_tinted_bitmap(navicella_misteriosa, al_map_rgb(255, 0, 0), generale.partita_in_corso.navicella_misteriosa.pos_x, MARGINE_SUP_GIOCO, 0);
						}
						//FINE DELLA VISUALIZZAZIONE DELLA NAVICELLA MISTERIOSA

						//INIZIO DELLA VISUALIZZAZIONE DELL'ONDATA
						pos_y_attuale = generale.partita_in_corso.ondata.pos_y;

						for (unsigned int i = 0; i < N_FILE_ALIENI; i++)
						{
							pos_x_attuale = generale.partita_in_corso.ondata.pos_x;
							for (unsigned int j = 0; j < N_COL_ALIENI; j++)
							{
								if (generale.partita_in_corso.ondata.alieni [i] [j].stato)
								{
									disegnaAlieno (scegliImmagine (i, alieno_tipo_1, alieno_tipo_2, alieno_tipo_3), pos_x_attuale, pos_y_attuale);
								}
								pos_x_attuale += DISTANZA_ASSI_COL_ALIENI;
							}
							pos_y_attuale += DISTANZA_FILE_ALIENI;
						}
						//FINE DELLA VISUALIZZAZIONE DELL'ONDATA

						//INIZIO DELLA VISUALIZZAZIONE DELLO SPARO DEGLI ALIENI
						if (generale.partita_in_corso.sparo_alieni.stato)
						{
							unsigned int sx;
							ALLEGRO_BITMAP *sparo_attuale;
							sparo_attuale = sparoScelto (generale.partita_in_corso.sparo_alieni.pos_x, sparo_alieni_1, sparo_alieni_2);
							if (animazione)
							{
								sx = 0;			
							}
							else
							{
								sx = al_get_bitmap_width (sparo_attuale) / 2;
							}
							al_draw_tinted_bitmap_region(sparo_attuale, al_map_rgb(0, 255, 0), sx, 0, al_get_bitmap_width (sparo_attuale) / 2, al_get_bitmap_height (sparo_attuale), generale.partita_in_corso.sparo_alieni.pos_x, generale.partita_in_corso.sparo_alieni.pos_y, 0);
						}
						//FINE DELLA VISUALIZZAZIONE DELLO SPARO DEGLI ALIENI

						//INIZIO DELLA VISUALIZZAZIONE DELLE BARRIERE
						pos_x_attuale = DISTANZA_BARRIERE;
						for (unsigned int i = 0; i < N_BARRIERE; i++)
						{
							disegnaBarriera (barriera_parziale, barriera_integra, generale.partita_in_corso.barriere [i], pos_x_attuale, POS_Y_BARRIERE);
							pos_x_attuale += DISTANZA_BARRIERE + LARGHEZZA_PIXEL_BARRIERA;
						}
						//FINE DELLA VISUALIZZAZIONE DELLE BARRIERE

						//INIZIO DELLA VISUALIZZAZIONE DELLO SPARO DEL CARRO
						if (generale.partita_in_corso.carro_armato.sparo.stato)
						{
							al_draw_tinted_bitmap(sparo_carro, al_map_rgb(0, 255, 0), generale.partita_in_corso.carro_armato.sparo.pos_x, generale.partita_in_corso.carro_armato.sparo.pos_y, 0);
						}
						//FINE DELLA VISUALIZZAIZOEN DELLO SPARO DEL CARRO

						//INIZIO DELLA VISUALIZZAZIONE DEL CARRO ARMATO
						if (generale.partita_in_corso.carro_armato.esploso)
						{
							unsigned int sx;
							if (animazione_esplosione_carro % 2 == 1)
							{
								sx = 0;
							}
							else
							{
								sx = al_get_bitmap_width (esplosione_carro) / N_STATI_SPRITE;
							}
							al_draw_tinted_bitmap_region(esplosione_carro, al_map_rgb(0, 255, 0), sx, 0, al_get_bitmap_width (esplosione_carro) / N_STATI_SPRITE, al_get_bitmap_height (esplosione_carro), generale.partita_in_corso.carro_armato.pos_x, MARGINE_INF_GIOCO - al_get_bitmap_height (esplosione_carro), 0);
						}
						else
						{
							al_draw_tinted_bitmap(carro_armato, al_map_rgb(0, 255, 0), generale.partita_in_corso.carro_armato.pos_x, MARGINE_INF_GIOCO - al_get_bitmap_height (carro_armato), 0);
						}
						//FINE DELLA VISUALIZZAZIONE DEL CARRO ARMATO

						al_flip_display();
						//FINE VISUALIZZAZIONE

						//INIZIO DEI CONTROLLI
						if (!generale.partita_in_corso.carro_armato.esploso)
						{
							if (controlloCollisioneCarroDaSparoAlieni (generale.partita_in_corso, al_get_bitmap_width (carro_armato), al_get_bitmap_height (sparoScelto (generale.partita_in_corso.sparo_alieni.pos_x, sparo_alieni_1, sparo_alieni_2)), al_get_bitmap_width (sparoScelto (generale.partita_in_corso.sparo_alieni.pos_x, sparo_alieni_1, sparo_alieni_2)), MARGINE_INF_GIOCO - al_get_bitmap_height (carro_armato)))
							{
								animazione_esplosione_carro++;
							}
							if (generale.partita_in_corso.vite_rimanenti < 0 || controlloCollisioneCarroDaOndata (generale.partita_in_corso, al_get_bitmap_height (alieno_tipo_1), MARGINE_INF_GIOCO - al_get_bitmap_height (carro_armato)))
							{
								schermata_att = s_fine_partita;
								cambia_schermata = true;
								break;
							}
							if (controlloCollisioneAlieni (generale.partita_in_corso, al_get_bitmap_height (alieno_tipo_1), al_get_bitmap_width (alieno_tipo_1) / N_STATI_SPRITE, al_get_bitmap_width (alieno_tipo_2) / N_STATI_SPRITE, al_get_bitmap_width (alieno_tipo_3) / N_STATI_SPRITE, al_get_bitmap_width (sparo_carro)))
							{
							}
							if (controlloCollisioneBarriereDaSparoCarro (generale.partita_in_corso, al_get_bitmap_width (sparo_carro)))
							{
							}
							if (controlloCollisioneBarriereDaSparoAlieni (generale.partita_in_corso, al_get_bitmap_height (sparoScelto (generale.partita_in_corso.sparo_alieni.pos_x, sparo_alieni_1, sparo_alieni_2)), al_get_bitmap_width (sparoScelto (generale.partita_in_corso.sparo_alieni.pos_x, sparo_alieni_1, sparo_alieni_2))))
							{
							}
							if (controlloCollisioneNavicellaMisteriosa (generale.partita_in_corso, al_get_bitmap_height (navicella_misteriosa), al_get_bitmap_width (navicella_misteriosa), al_get_bitmap_width (sparo_carro)))
							{
							}
							if (controlloCollisioneBarriereDaOndata (generale.partita_in_corso, al_get_bitmap_height (alieno_tipo_1), al_get_bitmap_width (alieno_tipo_1) / N_STATI_SPRITE, al_get_bitmap_width (alieno_tipo_2) / N_STATI_SPRITE, al_get_bitmap_width (alieno_tipo_3) / N_STATI_SPRITE))
							{
							}
							//FINE DEI CONTROLLI
							//INIZIO DEI CAMBIAMENTI
							if (generale.partita_in_corso.carro_armato.sparo.stato)
							{
								muoviSparoCarro (generale.partita_in_corso.carro_armato.sparo);
							}
							if (generale.partita_in_corso.sparo_alieni.stato)
							{
								muoviSparoAlieni (generale.partita_in_corso.sparo_alieni, al_get_bitmap_height (sparoScelto (generale.partita_in_corso.sparo_alieni.pos_x, sparo_alieni_1, sparo_alieni_2)));
							}
							if (generale.partita_in_corso.navicella_misteriosa.stato)
							{
								muoviNavicellaMisteriosa (generale.partita_in_corso, al_get_bitmap_width (navicella_misteriosa));
							}
						}
						//FINE DEI CAMBIAMENTI
					}
			   	}
				al_stop_timer(timer_sparo_alieni);
				al_stop_timer(timer_animazione);
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
						//INIZIO VISUALIZZAZIONE
        					al_clear_to_color(al_map_rgb(0, 0, 0));

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
							al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_X_VOCI_IMPOSTAZIONI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, menu_impostazioni.testi_menu [i]);
							pos_x_attuale = POS_X_VALORI_IMPOSTAZIONI;
							if (!(menu_impostazioni.voce_sel == i && !redraw_lampeggio))
							{
								char str_stato [MAX_STRINGA_GENERICA] = "<    ";
								char str_valore [MAX_STRINGA_GENERICA];
								assert(stringaValoreVoceImpostazioni (str_valore, static_cast <voce_menu_impostazioni> (i), generale.impostazioni));
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
						//FINE VISUALIZZAZIONE
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
						//INIZIO VISUALIZZAZIONE
        					al_clear_to_color(al_map_rgb(0, 0, 0));

						unsigned int pos_y_attuale = POS_Y_HIGHSCORES_TITOLO;

						//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
						al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_X_NUMERAZIONE_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, "HIGHSCORES:");
						//FINE DELLA VISUALIZZAZIONE DEL TITOLO

						//INIZIO DELLA VISUALIZZAZIONE DEGLI HIGHSCORES
						pos_y_attuale = POS_Y_ELENCO_PUNTEGGI;

						for (int i = 0; i < generale.n_highscores; i++)
						{
							pos_y_attuale += DIMENSIONE_TESTO + SPAZIO_TESTO;
							char str_numero [MAX_STRINGA_NUMERAZIONE] = "";
							sprintf(str_numero, "%d", i + 1);
							strcat (str_numero, ".");
							al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_X_NUMERAZIONE_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, str_numero);

							char str_valore [] = "";
							sprintf(str_valore, "%d", generale.highscores [i].valore);
							al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_X_NOMI_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, generale.highscores [i].nome);
							al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_X_VALORI_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, str_valore);
						}
						//FINE DELLA VISUALIZZAZIONE DEGLI HIGHSCORES

						//INIZIO DELLA VISUALIZZAZIONE DEL PREMI ENTER
						pos_y_attuale = POS_Y_INDICAZIONI_HIGHSCORES;
						al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_CENTRO_X, pos_y_attuale, ALLEGRO_ALIGN_CENTER, "Premi enter per tornare al menu principale");
						//FINE DELLA VISUALIZZAZIONE DEL PREMI ENTER

						al_flip_display();
						//FINE VISUALIZZAZIONE
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
						//INIZIO VISUALIZZAZIONE
        					al_clear_to_color(al_map_rgb(0, 0, 0));
						
						unsigned int pos_y_attuale;

						//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
						al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_CENTRO_X, POS_Y_TITOLO_PAUSA, ALLEGRO_ALIGN_CENTRE, "PAUSA");
						//FINE DELLA VISUALIZZAZIONE DEL TITOLO

						//INIZIO DELLA VISUALIZZAZIONE DEL MENU DI PAUSA
						pos_y_attuale = POS_Y_VOCI_PAUSA;
						for (int i = 0; i < menu_pausa.n_voci; i++)
						{
							if (!(menu_pausa.voce_sel == i && !redraw_lampeggio))
							{
								al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_CENTRO_X, pos_y_attuale, ALLEGRO_ALIGN_CENTRE, menu_pausa.testi_menu [i]);
							}
							pos_y_attuale += SPAZIO_TESTO_GRANDE + DIMENSIONE_TESTO;
						}
						//FINE DELLA VISUALIZZAZIONE DEL MENU DI PAUSA

						al_flip_display();
						//FINE VISUALIZZAZIONE
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

								nuovaPartita (generale.partita_in_corso, generale.impostazioni, POS_CENTRO_X - al_get_bitmap_width (carro_armato) / 2);
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
						//INIZIO VISUALIZZAZIONE
        					al_clear_to_color(al_map_rgb(0, 0, 0));

						unsigned int pos_y_attuale = POS_Y_HIGHSCORES_TITOLO;

						//INIZIO DELLA VISUALIZZAZIONE DEL TITOLO
						al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_X_NUMERAZIONE_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, "HIGHSCORES:");
						//FINE DELLA VISUALIZZAZIONE DEL TITOLO

						//INIZIO DELLA VISUALIZZAZIONE DEGLI HIGHSCORES
						pos_y_attuale = POS_Y_ELENCO_PUNTEGGI;

						for (int i = 0, p = 0; i <= generale.n_highscores && i < MAX_HIGHSCORES; i++, p++)
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
										al_draw_text(font_testo, al_map_rgb(0, 255, 0), pos_x_attuale, pos_y_attuale, ALLEGRO_ALIGN_LEFT, lettera);
										pos_x_attuale += al_get_text_width (font_testo, lettera);
									}
								}
								sprintf(str_valore, "%d", generale.partita_in_corso.punteggio.valore);
							}
							else
							{
								al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_X_NOMI_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, generale.highscores [p].nome);
								sprintf(str_valore, "%d", generale.highscores [p].valore);
							}
							al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_X_VALORI_PUNTEGGI, pos_y_attuale, ALLEGRO_ALIGN_LEFT, str_valore);
						}
						//FINE DELLA VISUALIZZAZIONE DEGLI HIGHSCORES

						//INIZIO DELLA VISUALIZZAZIONE DEL PREMI ENTER
						al_draw_text(font_testo, al_map_rgb(0, 255, 0), POS_CENTRO_X, POS_Y_INDICAZIONI_HIGHSCORES, ALLEGRO_ALIGN_CENTER, "Premi enter per salvare e tornare al menu principale");
						//FINE DELLA VISUALIZZAZIONE DEL PREMI ENTER

						al_flip_display();
						//FINE VISUALIZZAZIONE
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
				al_destroy_timer(timer_animazione);
				al_destroy_timer(timer_comparsa_navicella);
				al_destroy_timer(timer_spostamento_ondata);
				al_destroy_font (font_testo);
				al_destroy_font (font_titolo);
   				al_destroy_bitmap(sparo_alieni_1);
   				al_destroy_bitmap(sparo_alieni_2);
				al_destroy_bitmap(barriera_parziale);
				al_destroy_bitmap(barriera_integra);
				al_destroy_bitmap(carro_armato);
				al_destroy_bitmap(sparo_carro);
				al_destroy_bitmap(navicella_misteriosa);
				al_destroy_bitmap(alieno_tipo_1);
				al_destroy_bitmap(alieno_tipo_2);
				al_destroy_bitmap(alieno_tipo_3);
				al_destroy_bitmap(esplosione_carro);
				al_destroy_sample(musica_principale);
				return 0;
			default:
				al_destroy_display(display);
				al_destroy_event_queue(coda_eventi);
				al_destroy_timer(frame_rate_generale);
				al_destroy_timer(lampeggio_voce);
				al_destroy_timer(timer_sparo_alieni);
				al_destroy_timer(timer_animazione);
				al_destroy_timer(timer_comparsa_navicella);
				al_destroy_timer(timer_spostamento_ondata);
				al_destroy_font (font_testo);
				al_destroy_font (font_titolo);
   				al_destroy_bitmap(sparo_alieni_1);
   				al_destroy_bitmap(sparo_alieni_2);
				al_destroy_bitmap(barriera_parziale);
				al_destroy_bitmap(barriera_integra);
				al_destroy_bitmap(carro_armato);
				al_destroy_bitmap(sparo_carro);
				al_destroy_bitmap(navicella_misteriosa);
				al_destroy_bitmap(alieno_tipo_1);
				al_destroy_bitmap(alieno_tipo_2);
				al_destroy_bitmap(alieno_tipo_3);
				al_destroy_bitmap(esplosione_carro);
				al_destroy_sample(musica_principale);
				return 2;
		}
	}
 
	al_destroy_display(display);
	al_destroy_event_queue(coda_eventi);
	al_destroy_timer(frame_rate_generale);
	al_destroy_timer(lampeggio_voce);
	al_destroy_timer(timer_sparo_alieni);
	al_destroy_timer(timer_animazione);
	al_destroy_timer(timer_comparsa_navicella);
	al_destroy_timer(timer_spostamento_ondata);
	al_destroy_font (font_testo);
	al_destroy_font (font_titolo);
	al_destroy_bitmap(sparo_alieni_1);
	al_destroy_bitmap(sparo_alieni_2);
	al_destroy_bitmap(barriera_parziale);
	al_destroy_bitmap(barriera_integra);
	al_destroy_bitmap(carro_armato);
	al_destroy_bitmap(sparo_carro);
	al_destroy_bitmap(navicella_misteriosa);
	al_destroy_bitmap(alieno_tipo_1);
	al_destroy_bitmap(alieno_tipo_2);
	al_destroy_bitmap(alieno_tipo_3);
	al_destroy_bitmap(esplosione_carro);
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

ALLEGRO_BITMAP* scegliImmagine (unsigned int numero_fila, ALLEGRO_BITMAP *alieno_tipo_1, ALLEGRO_BITMAP *alieno_tipo_2, ALLEGRO_BITMAP *alieno_tipo_3)
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

void disegnaAlieno (ALLEGRO_BITMAP *alieno_scelto, unsigned int pos_x, unsigned int pos_y)
{
	unsigned int larghezza_istantanea = al_get_bitmap_width (alieno_scelto) / 2;
	al_draw_tinted_bitmap_region(alieno_scelto, al_map_rgb(0, 255, 0), 0, 0, larghezza_istantanea, al_get_bitmap_height (alieno_scelto), pos_x - (larghezza_istantanea / 2), pos_y, 0); //larghezza_istantanea * (alieno.stadio_animazione - 1)
}