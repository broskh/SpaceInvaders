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
//#include <allegro5/allegro_image.h>
//#include <allegro5/allegro_font.h>
//#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "struttura_dati.h"
#include "gestione_partita.h"
#include "gestione_impostazioni.h"
#include "gestione_highscores.h"
#include "gestione_menu.h"
#include "gestione_grafica.h"

#include <iostream>
using namespace std;

//INIZIO COSTANTI PER VARI TIMER
const float FPS_GENERALE = 60; /**<FPS generale del gioco.*/
const float FPS_LAMPEGGIO_MENU = 3.5; /**<FPS per la frequenza in grado di consentire l'effetto di lampeggio sull'opzione selezionata dei menù.*/
const float FPS_COMPARSA_SPARO_ALIENI = 1.5; /**<FPS per la frequenza di creazione degli spari da parte degli alieni.*/
const float FPS_ANIMAZIONE = 4; /**<FPS per la frequenza di cambiamento necessaria per realizzare l'animazione.*/
const float FPS_COMPARSA_NAVICELLA_MISTERIOSA = 1; /**<FPS per la frequenza della possibile comparsa della navicella misteriosa.*/
const float FPS_SPOSTAMENTO_ONDATA = 30; /**<FPS per la frequenza dello spostamento dell'ondata aliena.*/
const float FPS_SPOSTAMENTO_NAVICELLA_MISTERIOSA = 240;
const float FPS_SPOSTAMENTO_SPARI = 210;
//FINE COSTANTI PER VARI TIMER

//INIZIO COSTANTI PER FILE
const char FILE_MUSICA_PRINCIPALE [] = "Sounds/principale.flac"; /**<Percorso del file contenente la musica principale.*/
//FINE COSTANTI PER FILE

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

/*void disegnaBarriera (ALLEGRO_BITMAP *barriera_parziale, ALLEGRO_BITMAP *barriera_integra, stato_barriera barriera [ALT_BARRIERA] [LARG_BARRIERA], unsigned int pos_x, unsigned int pos_y);

ALLEGRO_BITMAP* scegliAlieno (unsigned int numero_fila, ALLEGRO_BITMAP *alieno_tipo_1, ALLEGRO_BITMAP *alieno_tipo_2, ALLEGRO_BITMAP *alieno_tipo_3);

ALLEGRO_BITMAP * scegliSparo (int pos_x, ALLEGRO_BITMAP * sparo_alieni_1, ALLEGRO_BITMAP * sparo_alieni_2);*/

/**
 * FARE DOCUMENTAZIONE PER MAIN
 */
int main ()
{

	ALLEGRO_SAMPLE *musica_principale = NULL;
	ALLEGRO_EVENT_QUEUE *coda_eventi = NULL;
	ALLEGRO_TIMER *frame_rate_generale = NULL;
	ALLEGRO_TIMER *timer_lampeggio_voce = NULL;
	ALLEGRO_TIMER *timer_comparsa_sparo_alieni= NULL;
	ALLEGRO_TIMER *timer_animazione = NULL;
	ALLEGRO_TIMER *timer_comparsa_navicella = NULL;
	ALLEGRO_TIMER *timer_spostamento_ondata = NULL;
	ALLEGRO_TIMER *timer_spostamento_navicella = NULL;
	ALLEGRO_TIMER *timer_spostamento_spari = NULL;

	bool redraw = true;

	assert (al_init());
	assert (al_install_keyboard());
	assert (al_install_audio());
	assert (al_init_acodec_addon());
	assert (al_reserve_samples(true));
	
	ALLEGRO_DISPLAY * display = inizializzaGrafica ();
 
   	coda_eventi = al_create_event_queue();
   	assert (coda_eventi);
 
	frame_rate_generale = al_create_timer(1.0 / FPS_GENERALE);
	assert (frame_rate_generale);

	timer_lampeggio_voce = al_create_timer(1.0 / FPS_LAMPEGGIO_MENU);
	assert (timer_lampeggio_voce);

	timer_comparsa_sparo_alieni = al_create_timer(1.0 / FPS_COMPARSA_SPARO_ALIENI);
	assert (timer_comparsa_sparo_alieni);

	timer_animazione = al_create_timer(1.0 / FPS_ANIMAZIONE);
	assert (timer_animazione);

	timer_comparsa_navicella = al_create_timer(1.0 / FPS_COMPARSA_NAVICELLA_MISTERIOSA);
	assert (timer_comparsa_navicella);

	timer_spostamento_navicella = al_create_timer(1.0 / FPS_SPOSTAMENTO_NAVICELLA_MISTERIOSA);
	assert (timer_spostamento_navicella);

	timer_spostamento_spari= al_create_timer(1.0 / FPS_SPOSTAMENTO_SPARI);
	assert (timer_spostamento_spari);

	timer_spostamento_ondata = al_create_timer(1.0 / FPS_SPOSTAMENTO_ONDATA);
	assert (timer_spostamento_ondata);

	musica_principale = al_load_sample (FILE_MUSICA_PRINCIPALE);
	assert (musica_principale);
 
   	al_register_event_source(coda_eventi, al_get_display_event_source(display));
	al_register_event_source(coda_eventi, al_get_timer_event_source(frame_rate_generale));
	al_register_event_source(coda_eventi, al_get_timer_event_source(timer_lampeggio_voce));
	al_register_event_source(coda_eventi, al_get_timer_event_source(timer_comparsa_sparo_alieni));
	al_register_event_source(coda_eventi, al_get_timer_event_source(timer_animazione));
	al_register_event_source(coda_eventi, al_get_timer_event_source(timer_comparsa_navicella));
	al_register_event_source(coda_eventi, al_get_timer_event_source(timer_spostamento_navicella));
	al_register_event_source(coda_eventi, al_get_timer_event_source(timer_spostamento_spari));
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

	int posizione;
	char input [] = " ";
	
	while (true)
	{
		cambia_schermata = false;
		redraw_lampeggio = false;
		animazione = false;
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
				nuovaPartita (generale.partita_in_corso, generale.impostazioni, POS_X_PRIMO_ASSE_ALIENI, POS_Y_PRIMA_FILA_ONDATA, POS_CENTRO_X - larghezzaCarroArmato () / 2);
				generale.partita_salvata = esisteSalvataggio ();
				al_start_timer(timer_lampeggio_voce);
				
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
						else if (ev.timer.source == timer_lampeggio_voce)
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
						stampaMenuPrincipale (menu_principale, redraw_lampeggio, generale.partita_salvata);
					}
			   	}
				al_stop_timer(timer_lampeggio_voce);
				break;
			case s_gioca:
				eliminaFileSalvataggio (generale);
				if (generale.impostazioni.musica)
				{
					al_stop_samples();
				}
				al_start_timer(timer_comparsa_sparo_alieni);
				al_start_timer(timer_animazione);
				al_start_timer(timer_comparsa_navicella);
				al_start_timer(timer_spostamento_navicella);
				al_start_timer(timer_spostamento_spari);
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
							if (generale.partita_in_corso.carro_armato.esplosione)
							{
								if (generale.partita_in_corso.carro_armato.esplosione <= RIPETIZIONI_ANIMAZIONE_ESPLOSIONE_CARRO * 2)
								{
									generale.partita_in_corso.carro_armato.esplosione++;
								}
								else
								{
									generale.partita_in_corso.carro_armato.esplosione = false;
								}
							}
							//per animazione di esplosione degli alieni
							for (unsigned int i = 0; i < N_FILE_ALIENI; i++)
							{
								for (unsigned int j = 0; j < N_COL_ALIENI; j++)
								{
									if (generale.partita_in_corso.ondata.alieni [i] [j].esplosione)
									{
										if (generale.partita_in_corso.ondata.alieni [i] [j].esplosione <= RIPETIZIONI_ANIMAZIONE_ESPLOSIONE_ALIENI)
										{
											generale.partita_in_corso.ondata.alieni [i] [j].esplosione++;
										}
										else
										{
											generale.partita_in_corso.ondata.alieni [i] [j].esplosione = false;
										}
									}
								}
							}
						}
						else if (!generale.partita_in_corso.carro_armato.esplosione)
						{
							if (ev.timer.source == timer_comparsa_sparo_alieni)
							{
								if (!generale.partita_in_corso.sparo_alieni.stato)
								{
									creaSparoAlieni (generale.partita_in_corso, larghezzaSparoAlienoAttuale (generale.partita_in_corso.sparo_alieni.pos_x), DISTANZA_FILE_ALIENI, DISTANZA_ASSI_COL_ALIENI, altezzaAlieni (), larghezzaAlieno1 (), larghezzaAlieno2 (), larghezzaAlieno3 ());
								}
							}
							else if (ev.timer.source == timer_comparsa_navicella)
							{
								if (!generale.partita_in_corso.navicella_misteriosa.stato)
								{
									creaNavicellaMisteriosa (generale.partita_in_corso, MARGINE_SX_GIOCO);
								}
							}
							else if (ev.timer.source == timer_spostamento_navicella)
							{
								if (generale.partita_in_corso.navicella_misteriosa.stato)
								{
									muoviNavicellaMisteriosa (generale.partita_in_corso, MARGINE_DX_GIOCO + larghezzaNavicellaMisteriosa ());
								}								
							}
							else if (ev.timer.source == timer_spostamento_spari)
							{
								if (generale.partita_in_corso.carro_armato.sparo.stato)
								{
									muoviSparoCarro (generale.partita_in_corso.carro_armato.sparo, MARGINE_SUP_GIOCO);
								}
								if (generale.partita_in_corso.sparo_alieni.stato)
								{
									muoviSparoAlieni (generale.partita_in_corso.sparo_alieni, MARGINE_INF_GIOCO - altezzaSparoAlienoAttuale (generale.partita_in_corso.sparo_alieni.pos_x));
								}
							}
							else if (ev.timer.source == timer_spostamento_ondata)
							{
								muoviAlieni (generale.partita_in_corso.ondata, DISTANZA_FILE_ALIENI, DISTANZA_ASSI_COL_ALIENI, MARGINE_INF_GIOCO - altezzaCarroArmato (), MARGINE_DX_GIOCO - (larghezzaAlieno3 ()) / 2, MARGINE_SX_GIOCO);
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
						if (!generale.partita_in_corso.carro_armato.esplosione)
						{
							switch(ev.keyboard.keycode)
							{
								case ALLEGRO_KEY_LEFT:
									muoviSinistraCarro (generale.partita_in_corso.carro_armato.pos_x, MARGINE_SX_GIOCO);
									break;
								case ALLEGRO_KEY_RIGHT:
									muoviDestraCarro (generale.partita_in_corso.carro_armato.pos_x, MARGINE_DX_GIOCO - larghezzaCarroArmato ());
									break;
								case ALLEGRO_KEY_SPACE:
									if (!generale.partita_in_corso.carro_armato.sparo.stato)
									{
										creaSparoCarroArmato (generale.partita_in_corso.carro_armato, generale.partita_in_corso.carro_armato.pos_x + larghezzaCarroArmato () / 2, MARGINE_INF_GIOCO - altezzaCarroArmato () - altezzaSparoCarroArmato ());
									}
									break;
							}
						}
					}				

					if(redraw && al_is_event_queue_empty(coda_eventi))
					{
						stampaGioca (generale.partita_in_corso, animazione);

						//INIZIO DEI CONTROLLI
						if (!generale.partita_in_corso.carro_armato.esplosione)
						{
							if (controlloCollisioneCarroDaSparoAlieni (generale.partita_in_corso, larghezzaCarroArmato (), altezzaSparoAlienoAttuale (generale.partita_in_corso.sparo_alieni.pos_x), larghezzaSparoAlienoAttuale (generale.partita_in_corso.sparo_alieni.pos_x), MARGINE_INF_GIOCO - altezzaCarroArmato ()))
							{
								generale.partita_in_corso.carro_armato.esplosione = 1;
							}
							if (controlloFinePartita (generale.partita_in_corso) || controlloCollisioneCarroDaOndata (generale.partita_in_corso, DISTANZA_FILE_ALIENI, altezzaAlieni (), MARGINE_INF_GIOCO - altezzaCarroArmato ()))
							{
								schermata_att = s_fine_partita;
								cambia_schermata = true;
								break;
							}
							if (controlloCollisioneAlieni (generale.partita_in_corso, larghezzaSparoCarroArmato (), DISTANZA_FILE_ALIENI, DISTANZA_ASSI_COL_ALIENI, altezzaAlieni (), larghezzaAlieno1 (), larghezzaAlieno2 (), larghezzaAlieno3 ()))
							{
							}
							if (controlloCollisioneBarriereDaSparoCarro (generale.partita_in_corso, POS_X_PRIMA_BARRIERA, POS_Y_BARRIERE, DISTANZA_BARRIERE, larghezzaSparoCarroArmato ()))
							{
							}
							if (controlloCollisioneBarriereDaSparoAlieni (generale.partita_in_corso, POS_X_PRIMA_BARRIERA, POS_Y_BARRIERE, DISTANZA_BARRIERE, altezzaSparoAlienoAttuale (generale.partita_in_corso.sparo_alieni.pos_x), larghezzaSparoAlienoAttuale (generale.partita_in_corso.sparo_alieni.pos_x)))
							{
							}
							if (controlloCollisioneNavicellaMisteriosa (generale.partita_in_corso, MARGINE_SUP_GIOCO + altezzaNavicellaMisteriosa (), larghezzaNavicellaMisteriosa (), larghezzaSparoCarroArmato ()))
							{
							}
							if (controlloCollisioneBarriereDaOndata (generale.partita_in_corso, POS_X_PRIMA_BARRIERA, POS_Y_BARRIERE, DISTANZA_BARRIERE, DISTANZA_FILE_ALIENI, DISTANZA_ASSI_COL_ALIENI, altezzaAlieni (), larghezzaAlieno1 (), larghezzaAlieno2 (), larghezzaAlieno3 ()))
							{
							}
							if (controlloFineOndata (generale.partita_in_corso.ondata))
							{
								nuovaPartita (generale.partita_in_corso, generale.impostazioni, POS_X_PRIMO_ASSE_ALIENI, POS_Y_PRIMA_FILA_ONDATA, POS_CENTRO_X - larghezzaCarroArmato () / 2);
							}
							//FINE DEI CONTROLLI
						}
					}
			   	}
				al_stop_timer(timer_comparsa_sparo_alieni);
				al_stop_timer(timer_animazione);
				al_stop_timer(timer_comparsa_navicella);
				al_stop_timer(timer_spostamento_navicella);
				al_stop_timer(timer_spostamento_spari);
				al_stop_timer(timer_spostamento_ondata);
				break;
			case s_carica:
				assert (caricaPartita (generale.partita_in_corso));
				schermata_att = s_gioca;
				cambia_schermata = true;
				break;
			case s_opzioni:
				al_start_timer(timer_lampeggio_voce);
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
						else if (ev.timer.source == timer_lampeggio_voce)
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
						stampaImpostazioni (generale.impostazioni, menu_impostazioni, redraw_lampeggio);
					}
			   	}
				al_stop_timer(timer_lampeggio_voce);
				break;
			case s_highscores:
				al_start_timer(timer_lampeggio_voce);
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
						else if (ev.timer.source == timer_lampeggio_voce)
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
						stampaHighscores (generale.highscores, generale.n_highscores);
					}
			   	}
				al_stop_timer(timer_lampeggio_voce);
				break;
			case s_pausa:
				menu_pausa.voce_sel = v_continua;
				al_start_timer(timer_lampeggio_voce);
				
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
						else if (ev.timer.source == timer_lampeggio_voce)
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
						stampaMenuPausa (menu_pausa, redraw_lampeggio);
					}
			   	}
				al_stop_timer(timer_lampeggio_voce);
				break;
			case s_fine_partita:	
				al_start_timer(timer_lampeggio_voce);
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
						else if (ev.timer.source == timer_lampeggio_voce)
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

								nuovaPartita (generale.partita_in_corso, generale.impostazioni, POS_X_PRIMO_ASSE_ALIENI, POS_Y_PRIMA_FILA_ONDATA, POS_CENTRO_X - larghezzaCarroArmato () / 2);
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
						stampaFinePartita (generale, posizione, redraw_lampeggio);
					}
			   	}
				al_stop_timer(timer_lampeggio_voce);
				break;
			case s_esci:
				distruggiGrafica ();
				al_destroy_event_queue(coda_eventi);
				al_destroy_timer(frame_rate_generale);
				al_destroy_timer(timer_lampeggio_voce);
				al_destroy_timer(timer_comparsa_sparo_alieni);
				al_destroy_timer(timer_animazione);
				al_destroy_timer(timer_comparsa_navicella);
				al_destroy_timer(timer_spostamento_navicella);
				al_destroy_timer(timer_spostamento_spari);
				al_destroy_timer(timer_spostamento_ondata);
				al_destroy_sample(musica_principale);
				return 0;
			default:
				distruggiGrafica ();
				al_destroy_event_queue(coda_eventi);
				al_destroy_timer(frame_rate_generale);
				al_destroy_timer(timer_lampeggio_voce);
				al_destroy_timer(timer_comparsa_sparo_alieni);
				al_destroy_timer(timer_animazione);
				al_destroy_timer(timer_comparsa_navicella);
				al_destroy_timer(timer_spostamento_navicella);
				al_destroy_timer(timer_spostamento_spari);
				al_destroy_timer(timer_spostamento_ondata);
				al_destroy_sample(musica_principale);
				return 2;
		}
	}
	distruggiGrafica ();
	al_destroy_event_queue(coda_eventi);
	al_destroy_timer(frame_rate_generale);
	al_destroy_timer(timer_lampeggio_voce);
	al_destroy_timer(timer_comparsa_sparo_alieni);
	al_destroy_timer(timer_animazione);
	al_destroy_timer(timer_comparsa_navicella);
	al_destroy_timer(timer_spostamento_navicella);
	al_destroy_timer(timer_spostamento_spari);
	al_destroy_timer(timer_spostamento_ondata);
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