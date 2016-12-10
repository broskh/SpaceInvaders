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
#include "strutture_dati.h"
#include "gestione_partita.h"
#include "gestione_impostazioni.h"
#include "gestione_classifica.h"
#include "gestione_menu.h"
#include "gestione_grafica.h"
#include "gestione_audio.h"

#include <iostream>
using namespace std;

//INIZIO COSTANTI PER VARI TIMER
const float FPS_GENERALE = 60; /**<FPS generale del gioco.*/
const float FPS_LAMPEGGIO_MENU = 3.5; /**<FPS per la frequenza in grado di consentire l'effetto di lampeggio sull'opzione selezionata dei menù.*/
const float FPS_COMPARSA_SPARO_ALIENI = 1.5; /**<FPS per la frequenza di creazione degli spari da parte degli alieni.*/
const float FPS_ANIMAZIONE = 4; /**<FPS per la frequenza di cambiamento necessaria per realizzare l'animazione.*/
const float FPS_COMPARSA_NAVICELLA_MISTERIOSA = 1; /**<FPS per la frequenza della possibile comparsa della navicella misteriosa.*/
const float FPS_SPOSTAMENTO_ONDATA_MIN = 70;
const float FPS_SPOSTAMENTO_ONDATA_MAX = 240;
const unsigned int STADI_INCREMENTO_VELOCITA_ONDATA = 5;
const unsigned int RANGE_PERCENTUALE_INCREMENTO_VELOCITA_ONDATA = 100 / STADI_INCREMENTO_VELOCITA_ONDATA;
const float FPS_SPOSTAMENTO_NAVICELLA_MISTERIOSA = 220;
const float FPS_SPOSTAMENTO_SPARI = 210;
//FINE COSTANTI PER VARI TIMER

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
schermata cambiaSchermataMenuPausa (voce_menu_pausa voce, Partita partita_in_corso, bool &partita_salvata);

unsigned int percentualeVelocitaOndata (Ondata ondata);

void distruggiTimer ();

void distruggiCoda ();

static ALLEGRO_EVENT_QUEUE *coda_eventi = NULL;
static ALLEGRO_TIMER *frame_rate_generale = NULL;
static ALLEGRO_TIMER *timer_lampeggio_voce = NULL;
static ALLEGRO_TIMER *timer_comparsa_sparo_alieni= NULL;
static ALLEGRO_TIMER *timer_animazione = NULL;
static ALLEGRO_TIMER *timer_comparsa_navicella = NULL;
static ALLEGRO_TIMER *timer_spostamento_ondata = NULL;
static ALLEGRO_TIMER *timer_spostamento_navicella = NULL;
static ALLEGRO_TIMER *timer_spostamento_spari = NULL;
static ALLEGRO_DISPLAY *display = NULL; /**<Display del gioco.*/

/**
 * FARE DOCUMENTAZIONE PER MAIN
 */
int main ()
{
	assert (al_init());
	assert (al_install_keyboard());
	inizializzaGrafica ();
	inizializzaAudio ();

	display = al_create_display (LARGHEZZA_DISPLAY, ALTEZZA_DISPLAY);
	assert (display);
 
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

	timer_spostamento_ondata = al_create_timer(1.0 / FPS_SPOSTAMENTO_ONDATA_MAX);
	assert (timer_spostamento_ondata);
 
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
	Partita partita_in_corso;
	bool partita_salvata;
	Classifica classifica;
	Impostazioni impostazioni;
	if (!caricaImpostazioni (impostazioni))
	{
		impostaValoriDefault (impostazioni);
		salvaImpostazioni (impostazioni);
	}
	if (!caricaPunteggi (classifica))
	{
		classifica.n_highscores = 0;
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

	bool redraw = true;
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
				if (impostazioni.musica)
				{
					avviaMusicaPrincipale ();
				}
				else
				{
					fermaMusicaPrincipale ();
				}
				menu_principale.voce_selezionata = v_gioca;
				nuovaPartita (partita_in_corso, impostazioni);
				partita_salvata = esisteSalvataggio ();
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
								if (partita_salvata)
								{
									vocePrec (menu_principale);
								}
								else
								{
									vocePrec (menu_principale, v_carica);
								}
								break;
							case ALLEGRO_KEY_DOWN:
								if (partita_salvata)
								{
									voceSuc (menu_principale);
								}
								else
								{
									voceSuc (menu_principale, v_carica);
								}
								break;
							case ALLEGRO_KEY_ENTER:
								schermata_att = cambiaSchermataMenuPrincipale (static_cast <voce_menu_principale> (menu_principale.voce_selezionata));
								cambia_schermata = true;
								break;
						}
					}

					if(redraw && al_is_event_queue_empty(coda_eventi))
					{
						stampaMenuPrincipale (menu_principale, partita_salvata, impostazioni.colore_alieni, redraw_lampeggio);
					}
			   	}
				al_stop_timer(timer_lampeggio_voce);
				break;
			case s_gioca:
				eliminaFileSalvataggio (partita_salvata);
				if (impostazioni.musica)
				{
					fermaMusicaPrincipale ();
					avviaMusicaOndata ();
					modificaVelocitaMusicaOndata (percentualeVelocitaOndata (partita_in_corso.ondata));
				}
				if (impostazioni.eff_audio && partita_in_corso.navicella_misteriosa.stato)
				{
					avviaSuonoNavicellaMisteriosa ();
				}

				al_start_timer(timer_comparsa_sparo_alieni);
				al_start_timer(timer_animazione);
				al_start_timer(timer_comparsa_navicella);
				al_start_timer(timer_spostamento_navicella);
				al_start_timer(timer_spostamento_spari);
				al_set_timer_speed(timer_spostamento_ondata, 1.0 / (((FPS_SPOSTAMENTO_ONDATA_MAX - FPS_SPOSTAMENTO_ONDATA_MIN) / 100 * percentualeVelocitaOndata (partita_in_corso.ondata)) + FPS_SPOSTAMENTO_ONDATA_MIN));
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
							if (partita_in_corso.carro_armato.esplosione)
							{
								if (partita_in_corso.carro_armato.esplosione <= RIPETIZIONI_ANIMAZIONE_ESPLOSIONE_CARRO * 2)
								{
									partita_in_corso.carro_armato.esplosione++;
								}
								else
								{
									partita_in_corso.carro_armato.esplosione = false;
								}
							}
							//per animazione di esplosione degli alieni
							for (unsigned int i = 0; i < N_FILE_ALIENI; i++)
							{
								for (unsigned int j = 0; j < N_COL_ALIENI; j++)
								{
									if (partita_in_corso.ondata.alieni [i] [j].esplosione)
									{
										if (partita_in_corso.ondata.alieni [i] [j].esplosione <= RIPETIZIONI_ANIMAZIONE_ESPLOSIONE_ALIENI)
										{
											partita_in_corso.ondata.alieni [i] [j].esplosione++;
										}
										else
										{
											partita_in_corso.ondata.alieni [i] [j].esplosione = false;
										}
									}
								}
							}
						}
						else if (!partita_in_corso.carro_armato.esplosione)
						{
							if (ev.timer.source == timer_comparsa_sparo_alieni)
							{
								if (!partita_in_corso.sparo_alieni.stato)
								{
									creaSparoAlieni (partita_in_corso);
								}
							}
							else if (ev.timer.source == timer_comparsa_navicella)
							{
								if (!partita_in_corso.navicella_misteriosa.stato)
								{
									creaNavicellaMisteriosa (partita_in_corso);
									if (impostazioni.eff_audio && partita_in_corso.navicella_misteriosa.stato)
									{
										avviaSuonoNavicellaMisteriosa ();
									}
								}
							}
							else if (ev.timer.source == timer_spostamento_navicella)
							{
								if (partita_in_corso.navicella_misteriosa.stato)
								{
									muoviNavicellaMisteriosa (partita_in_corso);
								}
							}
							else if (ev.timer.source == timer_spostamento_spari)
							{
								if (partita_in_corso.carro_armato.sparo.stato)
								{
									muoviSparoCarro (partita_in_corso.carro_armato.sparo);
								}
								if (partita_in_corso.sparo_alieni.stato)
								{
									muoviSparoAlieni (partita_in_corso.sparo_alieni);
								}
							}
							else if (ev.timer.source == timer_spostamento_ondata)
							{
								muoviAlieni (partita_in_corso.ondata);
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
						}
					}
					else if(ev.type == ALLEGRO_EVENT_KEY_CHAR)
					{
						if (!partita_in_corso.carro_armato.esplosione)
						{
							switch(ev.keyboard.keycode)
							{
								case ALLEGRO_KEY_LEFT:
									muoviCarroSinistra (partita_in_corso.carro_armato.pos_x);
									break;
								case ALLEGRO_KEY_RIGHT:
									muoviCarroDestra (partita_in_corso.carro_armato.pos_x);
									break;
								case ALLEGRO_KEY_SPACE:
									if (!partita_in_corso.carro_armato.sparo.stato)
									{
										creaSparoCarroArmato (partita_in_corso.carro_armato);
										if (impostazioni.eff_audio)
										{
											avviaSuonoSparoCarroArmato ();
										}
									}
									break;
							}
						}
					}				

					if(redraw && al_is_event_queue_empty(coda_eventi))
					{
						stampaGioca (partita_in_corso, animazione, impostazioni.colore_alieni);

						//INIZIO DEI CONTROLLI
						if (!partita_in_corso.carro_armato.esplosione)
						{
							if (controlloCollisioneCarroDaSparoAlieni (partita_in_corso))
							{
								partita_in_corso.carro_armato.esplosione = 1;
								if (impostazioni.eff_audio)
								{
									avviaSuonoEsplosioneCarroArmato ();
								}
							}
							if (controlloFinePartita (partita_in_corso) || controlloCollisioneCarroDaOndata (partita_in_corso))
							{
								schermata_att = s_fine_partita;
								cambia_schermata = true;
								break;
							}
							if (controlloCollisioneAlieni (partita_in_corso))
							{
								if (impostazioni.musica)
								{
									modificaVelocitaMusicaOndata (percentualeVelocitaOndata (partita_in_corso.ondata));
								}
								if (impostazioni.eff_audio)
								{
									avviaSuonoEsplosioneAlieno ();
								}
							}
							if (controlloCollisioneBarriereDaSparoCarro (partita_in_corso))
							{
								;
							}
							if (controlloCollisioneBarriereDaSparoAlieni (partita_in_corso))
							{
								;
							}
							if (controlloCollisioneNavicellaMisteriosa (partita_in_corso))
							{
								if (impostazioni.eff_audio)
								{
									avviaSuonoEsplosioneNavicellaMisteriosa ();
								}
							}
							if (controlloCollisioneBarriereDaOndata (partita_in_corso))
							{
								;
							}
							if (controlloFineOndata (partita_in_corso.ondata))
							{
								nuovaOndata (partita_in_corso.ondata);
							}
							if (impostazioni.eff_audio)
							{								
								if (!partita_in_corso.navicella_misteriosa.stato)
								{
									fermaSuonoNavicellaMisteriosa ();
								}
							}
							//FINE DEI CONTROLLI
						}
					}
			   	}
				fermaSuonoNavicellaMisteriosa ();
				fermaMusicaOndata ();

				al_stop_timer(timer_comparsa_sparo_alieni);
				al_stop_timer(timer_animazione);
				al_stop_timer(timer_comparsa_navicella);
				al_stop_timer(timer_spostamento_navicella);
				al_stop_timer(timer_spostamento_spari);
				al_stop_timer(timer_spostamento_ondata);
				break;
			case s_carica:
				assert (caricaPartita (partita_in_corso));
				schermata_att = s_gioca;
				cambia_schermata = true;
				break;
			case s_opzioni:
				al_start_timer(timer_lampeggio_voce);
				menu_impostazioni.voce_selezionata = v_musica;

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
								assert (valoreCampoImpostazioniPrec (static_cast <voce_menu_impostazioni> (menu_impostazioni.voce_selezionata), impostazioni));
								break;
							case ALLEGRO_KEY_RIGHT:
								assert (valoreCampoImpostazioniSuc (static_cast <voce_menu_impostazioni> (menu_impostazioni.voce_selezionata), impostazioni));
								break;
							case ALLEGRO_KEY_ENTER:
								salvaImpostazioni (impostazioni);
								schermata_att = s_menu;
								cambia_schermata = true;
								break;
							case ALLEGRO_KEY_R:
								impostaValoriDefault (impostazioni);
								break;
						}
					}

					if(redraw && al_is_event_queue_empty(coda_eventi))
					{
						stampaImpostazioni (menu_impostazioni, impostazioni, redraw_lampeggio);
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
						stampaHighscores (classifica);
					}
			   	}
				al_stop_timer(timer_lampeggio_voce);
				break;
			case s_pausa:
				menu_pausa.voce_selezionata = v_continua;
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
								schermata_att = cambiaSchermataMenuPausa (static_cast <voce_menu_pausa> (menu_pausa.voce_selezionata), partita_in_corso, partita_salvata);
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
				posizione = posizionePunteggio (classifica, partita_in_corso.punteggio);
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
									aggiungiPunteggio (classifica, partita_in_corso.punteggio, posizione);
									salvaPunteggi (classifica);
								}

								nuovaPartita (partita_in_corso, impostazioni);
								schermata_att = s_menu;
								cambia_schermata = true;
								break;
							case ALLEGRO_KEY_BACKSPACE:
								partita_in_corso.punteggio.nome [strlen (partita_in_corso.punteggio.nome) - 1] = '\0';
								break;
							default:
								if (ev.keyboard.keycode >= ALLEGRO_KEY_A && ev.keyboard.keycode <= ALLEGRO_KEY_Z)
								{
									if (strlen (partita_in_corso.punteggio.nome) < CARATTERI_NOME)
									{
										input [0] = ev.keyboard.keycode - ALLEGRO_KEY_A + 'A';
										strcat (partita_in_corso.punteggio.nome, input);
									}
									else
									{
										partita_in_corso.punteggio.nome [CARATTERI_NOME - 1] = ev.keyboard.keycode - ALLEGRO_KEY_A + 'a';
									}
								}
								break;
						}
					}

					if(redraw && al_is_event_queue_empty(coda_eventi))
					{
						stampaFinePartita (classifica, partita_in_corso.punteggio, posizione, redraw_lampeggio);
					}
			   	}
				al_stop_timer(timer_lampeggio_voce);
				break;
			case s_esci:
				distruggiGrafica ();
				distruggiAudio ();
				distruggiCoda ();
				distruggiTimer ();
				return 0;
			default:
				distruggiGrafica ();
				distruggiAudio ();
				distruggiCoda ();
				distruggiTimer ();
				return 2;
		}
	}
	distruggiGrafica ();
	distruggiAudio ();
	distruggiCoda ();
	distruggiTimer ();
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

schermata cambiaSchermataMenuPausa (voce_menu_pausa voce, Partita partita_in_corso, bool &partita_salvata)
{
	if (voce == v_continua)
	{
		return s_gioca;
	}
	else if (voce == v_salva)
	{
		salvaPartita (partita_in_corso, partita_salvata);
	}
	else if (voce == v_abbandona)
	{
		;
	}
	return s_menu;
}

unsigned int percentualeVelocitaOndata (Ondata ondata)
{
	int percentuale_alieni_eliminati = percentualeAlieniEliminati (ondata);
	return percentuale_alieni_eliminati - (percentuale_alieni_eliminati % RANGE_PERCENTUALE_INCREMENTO_VELOCITA_ONDATA);
}

void distruggiTimer ()
{
	al_destroy_display(display);
	al_destroy_timer(frame_rate_generale);
	al_destroy_timer(timer_lampeggio_voce);
	al_destroy_timer(timer_comparsa_sparo_alieni);
	al_destroy_timer(timer_animazione);
	al_destroy_timer(timer_comparsa_navicella);
	al_destroy_timer(timer_spostamento_navicella);
	al_destroy_timer(timer_spostamento_spari);
	al_destroy_timer(timer_spostamento_ondata);
}

void distruggiCoda ()
{
	al_destroy_event_queue(coda_eventi);
}