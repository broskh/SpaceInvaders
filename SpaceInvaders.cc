/* 
 * File contenente il modulo Main.
 */

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
 * colpite dagli alieni o dal carro armato tenderanno prima a sgretolarsi, e 
 * infine a distruggersi.
 * 
 * Al termine della partita, se è stato ottenuto un punteggio degno di essere inserito 
 * nella classifica degli highscores, è possibile scegliere un nome di tre lettere 
 * e memorizzare il punteggio.
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
 * Dal menù principale è inoltre possibile visualizzare la classifica dei dieci migliori
 * punteggi raggiunti e il nome dei giocatori che hanno raggiunto tali risultati.
 *
 * @author Alessio Scheri
 */

#include <allegro5/allegro.h>
#include "strutture_dati.h"
#include "gestione_partita.h"
#include "gestione_impostazioni.h"
#include "gestione_classifica.h"
#include "gestione_menu.h"
#include "gestione_grafica.h"
#include "gestione_audio.h"

//INIZIO COSTANTI PER ANIMAZIONE
const unsigned int STADI_INCREMENTO_VELOCITA_ONDATA = 6; /**<Stadi di incremento della velocità dell'ondata.*/
const unsigned int RANGE_PERCENTUALE_INCREMENTO_VELOCITA_ONDATA = 100 / STADI_INCREMENTO_VELOCITA_ONDATA; /**<Range percentualedi incremento della velocità.*/
//FINE COSTANTI PER ANIMAZIONE

//INIZIO COSTANTI PER VARI TIMER
const float FREQUENZA_ANIMAZIONE = 4; /**<Frequenza dell'animazione.*/
const float FREQUENZA_COMPARSA_NAVICELLA_MISTERIOSA = 1; /**<Frequenza della possibile comparsa della navicella misteriosa.*/
const float FREQUENZA_COMPARSA_SPARO_ALIENI = 1.5; /**<Frequenza di creazione degli spari alieni.*/
const float FPS_GIOCO = 60; /**<FPS del gioco.*/
const float FREQUENZA_LAMPEGGIO_MENU = 3.5; /**<Frequenza dell'effetto lampeggiante sull'opzione selezionata dei menù.*/
const float FREQUENZA_SPOSTAMENTO_CARRO_ARMATO = 115; /**<Frequenza dello spostamento del carro armato.*/
const float FREQUENZA_SPOSTAMENTO_NAVICELLA_MISTERIOSA = 220; /**<Frequenza dello spostamento della navicella misteriosa.*/
const float FREQUENZA_SPOSTAMENTO_ONDATA_MAX = 260; /**<Frequenza massima del movimento dell'ondata.*/
const float FREQUENZA_SPOSTAMENTO_ONDATA_MIN = 70; /**<Frequenza minima del movimento dell'ondata.*/
const float FREQUENZA_SPOSTAMENTO_SPARI = 150; /**<Frequenza dello spostamento degli spari.*/
//FINE COSTANTI PER VARI TIMER

//INIZIO FUNZIONI PRIVATE
/*
 * Ritorna la percentuale della velocità dell'ondata aliena prendendo in considerazione gli alieni rimasti e il
 * il range percentuale di incremento della velocità.
 */
unsigned int percentualeVelocitaOndata (Partita partita);

/*
 * Dealloca la memoria riguardante la coda degli eventi.
 */
void distruggiCoda ();

/*
 * Dealloca la memoria riguardante il display.
 */
void distruggiDisplay ();

/*
 * Dealloca la memoria riguardante i timer.
 */
void distruggiTimer ();
//FINE FUNZIONI PRIVATE

//INIZIO VARIABILI GLOBALI
static ALLEGRO_EVENT_QUEUE *coda_eventi = NULL; /**<Coda degli eventi.*/
static ALLEGRO_TIMER *timer_fps = NULL; /**<Timer per ricaricamento grafica generale.*/
static ALLEGRO_TIMER *timer_lampeggio_voce = NULL; /**<Timer per effettuare l'effetto lampeggiante.*/
static ALLEGRO_TIMER *timer_comparsa_sparo_alieni= NULL; /**<Timer per la comparsa degli spari alieni.*/
static ALLEGRO_TIMER *timer_animazione = NULL; /**<Timer per l'animazione.*/
static ALLEGRO_TIMER *timer_spostamento_carro_armato = NULL; /**<Timer per lo spostamento del carro armato.*/
static ALLEGRO_TIMER *timer_comparsa_navicella = NULL; /**<Timer per la comparsa della navicella misteriosa.*/
static ALLEGRO_TIMER *timer_spostamento_ondata = NULL; /**<Timer per lo spostamento dell'ondata aliena.*/
static ALLEGRO_TIMER *timer_spostamento_navicella = NULL; /**<Timer per lo spostamento della navicella misteriosa.*/
static ALLEGRO_TIMER *timer_spostamento_spari = NULL; /**<Timer per lo spostamento degli spari.*/
static ALLEGRO_DISPLAY *display = NULL; /**<Display del gioco.*/
//FINE VARIABILI GLOBALI

/**
 * Combina tutti i moduli e le strutture dati per realizzare il gioco.
 * In particolare si occupa di gestire il cambio delle varie schermate e la coda degli eventi che interagisce con esse.
 * Dopo una prima fase di inizializzazione, all'interno di un loop infinito è presente uno switch-case dove ad ogni 
 * case corrisponde la gestione di una schermata differente del gioco. Sarà quindi all'interno di questo blocco che, 
 * se necessaria, verrà gestita correttamente anche la coda degli eventi.
 * In particolare, il case che si occupa di gestire la schermata di uscita dal gioco è l'unico modo per uscire 
 * correttamente dal gioco (il main ritorna il valore 0), ed è per questo che, anche quando viene registrato 
 * il click sulla crocetta in altro a destra della finestra, si passa per questa schermata.
 * 
 * @return lo stato di uscita del programma\: 
 * se è "0", tutto è andato correttamente; 
 * se è "1" il programma è uscito inaspettatamente dal ciclo di gestione delle schermate; 
 * se è "2" il programma ha tentato di gestire una schermata inesistente.
 */
int main ()
{
	//INIZIALIZZAZIONE DELLE LIBRERIE E DEI MODULI
	assert (al_init());
	assert (al_install_keyboard());
	inizializzaGrafica ();
	inizializzaAudio ();

	//INIZIALIZZAZIONE DEL DISPLAY
	display = al_create_display (LARGHEZZA_DISPLAY, ALTEZZA_DISPLAY);
	assert (display);
 
	//INIZIALIZZAZIONE DELLA CODA DEGLI EVENTI
   	coda_eventi = al_create_event_queue();
   	assert (coda_eventi);
	ALLEGRO_EVENT ev;
 
	//INIZIALIZZAZIONE DEI TIMER
	timer_fps = al_create_timer(1.0 / FPS_GIOCO);
	assert (timer_fps);

	timer_lampeggio_voce = al_create_timer(1.0 / FREQUENZA_LAMPEGGIO_MENU);
	assert (timer_lampeggio_voce);

	timer_comparsa_sparo_alieni = al_create_timer(1.0 / FREQUENZA_COMPARSA_SPARO_ALIENI);
	assert (timer_comparsa_sparo_alieni);

	timer_animazione = al_create_timer(1.0 / FREQUENZA_ANIMAZIONE);
	assert (timer_animazione);

	timer_comparsa_navicella = al_create_timer(1.0 / FREQUENZA_COMPARSA_NAVICELLA_MISTERIOSA);
	assert (timer_comparsa_navicella);

	timer_spostamento_carro_armato = al_create_timer(1.0 / FREQUENZA_SPOSTAMENTO_CARRO_ARMATO);
	assert (timer_spostamento_carro_armato);

	timer_spostamento_navicella = al_create_timer(1.0 / FREQUENZA_SPOSTAMENTO_NAVICELLA_MISTERIOSA);
	assert (timer_spostamento_navicella);

	timer_spostamento_spari= al_create_timer(1.0 / FREQUENZA_SPOSTAMENTO_SPARI);
	assert (timer_spostamento_spari);

	timer_spostamento_ondata = al_create_timer(1.0 / FREQUENZA_SPOSTAMENTO_ONDATA_MAX);
	assert (timer_spostamento_ondata);
 
	//REGISTRAZIONE DEGLI EVENTI NELLA CODA
   	al_register_event_source(coda_eventi, al_get_display_event_source(display));
	al_register_event_source(coda_eventi, al_get_timer_event_source(timer_fps));
	al_register_event_source(coda_eventi, al_get_timer_event_source(timer_lampeggio_voce));
	al_register_event_source(coda_eventi, al_get_timer_event_source(timer_comparsa_sparo_alieni));
	al_register_event_source(coda_eventi, al_get_timer_event_source(timer_animazione));
	al_register_event_source(coda_eventi, al_get_timer_event_source(timer_comparsa_navicella));
	al_register_event_source(coda_eventi, al_get_timer_event_source(timer_spostamento_navicella));
	al_register_event_source(coda_eventi, al_get_timer_event_source(timer_spostamento_carro_armato));
	al_register_event_source(coda_eventi, al_get_timer_event_source(timer_spostamento_spari));
	al_register_event_source(coda_eventi, al_get_timer_event_source(timer_spostamento_ondata));
	al_register_event_source(coda_eventi, al_get_keyboard_event_source());
	
	//INIZIALIZZAZIONE DELLE VARIABILI CONTENENTI LE INFORMAZIONI DI GIOCO
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
		inizializzaClassifica (classifica);
	}

	//INIZIALIZZAZIONE DELLE VARIABILI CONTENENTI LE INFORMAZIONI DI MENÙ
	Menu menu_principale;
	inizializzaMenuPrincipale (menu_principale);
	Menu menu_impostazioni;
	inizializzaMenuImpostazioni (menu_impostazioni);
	Menu menu_pausa;
	inizializzaMenuPausa (menu_pausa);

	//INIZIALIZZAZIONE DELLE VARIABILI NECESSARIE PER LA GRAFICA
	schermata schermata_att = s_menu;
	bool cambia_schermata;
	bool redraw = true;
	bool redraw_lampeggio;
	bool animazione;

	//VARIABILI NECESSARIE PER LA SCHERMATA DI FINE PARTITA
	int posizione;

	//VARIABILI NECESSARIE PER LA SCHERMATA DI GIOCO (IN PARTICOLARE PER PERMETTERE DI TENERE PREMUTI I TASTI DI MOVIMENTO E DI SPARO)
	bool muovi_carro_destra = false;
	bool muovi_carro_sinistra = false;
	bool sparo_carro = false;

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_start_timer(timer_fps);
	
	while (true) //loop infinito che gestisce tutte le schermate del gioco
	{
		cambia_schermata = false;
		redraw_lampeggio = false;
		animazione = false;
		switch (schermata_att) //ogni case corrisponde ad una schermata differente
		{
			case s_menu:
				if (statoMusica(impostazioni))
				{
					avviaMusicaPrincipale ();
				}
				else
				{
					fermaMusicaPrincipale (); //se è stata disattivata nelle impostazioni, viene disattivata
				}
				selezionaPrimaVoce (menu_principale); //quando avvio il menù la voce selezionata è sempre "gioca"
				nuovaPartita (partita_in_corso, impostazioni); //inizializzo una nuova partita
				partita_salvata = esisteSalvataggio (); //controllo se esiste una partita salvata
				al_start_timer(timer_lampeggio_voce);
				
				while(!cambia_schermata) //ciclo finchè non è necessario cambiare schermata
			   	{
					al_wait_for_event(coda_eventi, &ev);
					if(ev.type == ALLEGRO_EVENT_TIMER)
					{
						if (ev.timer.source == timer_fps)
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
						schermata_att = s_esci; //per chiudere il gioco correttamente chiamo la schermata di uscita
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
								schermata_att = cambiaSchermataMenuPrincipale (menu_principale); //capisce con questo metodo quale schermata deve aprire
								cambia_schermata = true;
								break;
						}
					}

					if(redraw && al_is_event_queue_empty(coda_eventi))
					{
						stampaMenuPrincipale (menu_principale, partita_salvata, statoColoreAlieni (impostazioni), redraw_lampeggio);
					}
			   	}
				al_stop_timer(timer_lampeggio_voce);
				al_flush_event_queue (coda_eventi);
				break;
			case s_gioca:
				if (eliminaFileSalvataggio ()) //elimino il salvataggio precedente
				{
					partita_salvata = false;
				}
				if (statoMusica (impostazioni))
				{
					fermaMusicaPrincipale ();
					avviaMusicaOndata ();
					modificaVelocitaMusicaOndata (percentualeVelocitaOndata (partita_in_corso)); //se è stata caricata una partita correggo subito la vleocità del sottofondo
				}
				if (statoEffettiAudio (impostazioni) && statoNavicellaMisteriosa (partita_in_corso)) //se è stata caricata una partita dove la navicella era in movimento
				{
					avviaSuonoNavicellaMisteriosa ();
				}
				al_start_timer(timer_comparsa_sparo_alieni);
				al_start_timer(timer_animazione);
				al_start_timer(timer_comparsa_navicella);
				al_start_timer(timer_spostamento_carro_armato);
				al_start_timer(timer_spostamento_navicella);
				al_start_timer(timer_spostamento_spari);
				al_set_timer_speed(timer_spostamento_ondata, 1.0 / (((FREQUENZA_SPOSTAMENTO_ONDATA_MAX - FREQUENZA_SPOSTAMENTO_ONDATA_MIN) / 100 * percentualeVelocitaOndata (partita_in_corso)) + FREQUENZA_SPOSTAMENTO_ONDATA_MIN)); //se è stata caricata una partita correggo subito la vleocità del movimento dell'ondata
				al_start_timer(timer_spostamento_ondata);

				while(!cambia_schermata)
			   	{
					al_wait_for_event(coda_eventi, &ev);
					if(ev.type == ALLEGRO_EVENT_TIMER)
					{
						if (ev.timer.source == timer_fps)
						{
							redraw = true;
						}
						else if (ev.timer.source == timer_animazione)
						{
							animazione = !animazione;
							if (statoEsplosioneCarroArmato (partita_in_corso))
							{
								if (statoEsplosioneCarroArmato (partita_in_corso) <= RIPETIZIONI_ANIMAZIONE_ESPLOSIONE_CARRO * 2) //necessario per realizzare l'effetto di animazione
								{
									avanzaEsplosioneCarroArmato (partita_in_corso);
								}
								else
								{
									terminaEsplosioneCarroArmato (partita_in_corso);
								}
							}
							//per controllare quali alieni necessitano di un effetto di animazione
							for (unsigned int i = 0; i < N_FILE_ALIENI; i++)
							{
								for (unsigned int j = 0; j < N_COL_ALIENI; j++)
								{
									if (statoEsplosioneAlieno (partita_in_corso, i, j))
									{
										if (statoEsplosioneAlieno (partita_in_corso, i, j) <= RIPETIZIONI_ANIMAZIONE_ESPLOSIONE_ALIENI)
										{
											avanzaEsplosioneAlieno (partita_in_corso, i, j);
										}
										else
										{
											terminaEsplosioneAlieno (partita_in_corso, i, j);
										}
									}
								}
							}
						}
						else if (!statoEsplosioneCarroArmato (partita_in_corso))
						{
							if (ev.timer.source == timer_comparsa_sparo_alieni)
							{
								if (!statoSparoAlieni (partita_in_corso))
								{
									creaSparoAlieni (partita_in_corso);
								}
							}
							else if (ev.timer.source == timer_comparsa_navicella)
							{
								if (!statoNavicellaMisteriosa (partita_in_corso))
								{
									creaNavicellaMisteriosa (partita_in_corso);
									if (statoEffettiAudio (impostazioni) && statoNavicellaMisteriosa (partita_in_corso))
									{
										avviaSuonoNavicellaMisteriosa ();
									}
								}
							}
							else if (ev.timer.source == timer_spostamento_carro_armato)
							{
								if (!statoEsplosioneCarroArmato (partita_in_corso))
								{
									if (muovi_carro_destra)
									{
										muoviCarroDestra (partita_in_corso);
									}
									else if (muovi_carro_sinistra)
									{
										muoviCarroSinistra (partita_in_corso);
									}
								}
							}
							else if (ev.timer.source == timer_spostamento_navicella)
							{
								if (statoNavicellaMisteriosa (partita_in_corso))
								{
									muoviNavicellaMisteriosa (partita_in_corso);
								}
							}
							else if (ev.timer.source == timer_spostamento_spari)
							{
								if (statoSparoCarroArmato (partita_in_corso))
								{
									muoviSparoCarro (partita_in_corso);
								}
								if (statoSparoAlieni (partita_in_corso))
								{
									muoviSparoAlieni (partita_in_corso);
								}
							}
							else if (ev.timer.source == timer_spostamento_ondata)
							{
								muoviAlieni (partita_in_corso);
							}
						}						
					}
					else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
					{
						switch(ev.keyboard.keycode)
						{
							case ALLEGRO_KEY_ESCAPE:
								schermata_att = s_pausa;
								cambia_schermata = true;
								break;
							case ALLEGRO_KEY_LEFT:
								muovi_carro_destra = false;
								muovi_carro_sinistra = true;
								break;
							case ALLEGRO_KEY_RIGHT:
								muovi_carro_sinistra = false;
								muovi_carro_destra = true;
								break;
							case ALLEGRO_KEY_SPACE:
								sparo_carro = true;
								break;
						}
					}
					else if(ev.type == ALLEGRO_EVENT_KEY_UP)
					{
						switch(ev.keyboard.keycode)
						{
							case ALLEGRO_KEY_LEFT:
								muovi_carro_sinistra = false;
								break;
							case ALLEGRO_KEY_RIGHT:
								muovi_carro_destra = false;
								break;
							case ALLEGRO_KEY_SPACE:
								sparo_carro = false;
								break;
						}
					}
					else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
					{
						schermata_att = s_esci;
						cambia_schermata = true;
						break;
					}

					if (sparo_carro && !statoEsplosioneCarroArmato (partita_in_corso)) //se è premuto il tasto per sparare, creo lo sparo (se non ne esiste già uno)
					{
						if (!statoSparoCarroArmato (partita_in_corso))
						{
							creaSparoCarroArmato (partita_in_corso);
							if (statoEffettiAudio (impostazioni))
							{
								avviaSuonoSparoCarroArmato ();
							}
						}
					}

					if(redraw && al_is_event_queue_empty(coda_eventi))
					{
						stampaGioca (partita_in_corso, animazione, statoColoreAlieni (impostazioni));
					}

					//INIZIO DEI CONTROLLI
					if (!statoEsplosioneCarroArmato (partita_in_corso))
					{
						if (controlloCollisioneCarroDaSparoAlieni (partita_in_corso))
						{
							avanzaEsplosioneCarroArmato (partita_in_corso);
							if (statoEffettiAudio (impostazioni))
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
							if (statoMusica (impostazioni))
							{
								modificaVelocitaMusicaOndata (percentualeVelocitaOndata (partita_in_corso));
							}
							if (statoEffettiAudio (impostazioni))
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
							if (statoEffettiAudio (impostazioni))
							{
								avviaSuonoEsplosioneNavicellaMisteriosa ();
							}
						}
						if (controlloCollisioneBarriereDaOndata (partita_in_corso))
						{
							;
						}
						if (controlloFineOndata (partita_in_corso))
						{
							nuovaOndata (partita_in_corso);
						}
						if (statoEffettiAudio (impostazioni))
						{								
							if (!statoNavicellaMisteriosa (partita_in_corso))
							{
								fermaSuonoNavicellaMisteriosa ();
							}
						}
					}
					//FINE DEI CONTROLLI
			   	}
				fermaSuonoNavicellaMisteriosa ();
				fermaMusicaOndata ();
				muovi_carro_destra = false;
				muovi_carro_sinistra = false;
				sparo_carro = false;

				al_stop_timer(timer_comparsa_sparo_alieni);
				al_stop_timer(timer_animazione);
				al_stop_timer(timer_comparsa_navicella);
				al_stop_timer(timer_spostamento_carro_armato);
				al_stop_timer(timer_spostamento_navicella);
				al_stop_timer(timer_spostamento_spari);
				al_stop_timer(timer_spostamento_ondata);
				al_flush_event_queue (coda_eventi);
				break;
			case s_carica: //carico la partita salvata e passo subito alla schermata di gioco
				assert (caricaPartita (partita_in_corso));
				schermata_att = s_gioca;
				cambia_schermata = true;
				break;
			case s_opzioni:
				selezionaPrimaVoce (menu_impostazioni); //quando passo alla schermata delle impostazioni, la voce musica è sempre selezionata inizialmente
				al_start_timer(timer_lampeggio_voce);

				while(!cambia_schermata)
			   	{
					al_wait_for_event(coda_eventi, &ev);
					if(ev.type == ALLEGRO_EVENT_TIMER)
					{
						if (ev.timer.source == timer_fps)
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
								valoreCampoImpostazioniPrec (menu_impostazioni, impostazioni);
								break;
							case ALLEGRO_KEY_RIGHT:
								valoreCampoImpostazioniSuc (menu_impostazioni, impostazioni);
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
				al_flush_event_queue (coda_eventi);
				break;
			case s_highscores:
				al_start_timer(timer_lampeggio_voce);

				while(!cambia_schermata)
			   	{
					al_wait_for_event(coda_eventi, &ev);
					if(ev.type == ALLEGRO_EVENT_TIMER)
					{
						if (ev.timer.source == timer_fps)
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
				al_flush_event_queue (coda_eventi);
				break;
			case s_pausa:
				selezionaPrimaVoce (menu_pausa); //quando passo alla schermata di pausa, la voce continua è sempre selezionata inizialmente
				al_start_timer(timer_lampeggio_voce);
		
				while(!cambia_schermata)
			   	{
					al_wait_for_event(coda_eventi, &ev);
					if(ev.type == ALLEGRO_EVENT_TIMER)
					{
						if (ev.timer.source == timer_fps)
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
								schermata_att = cambiaSchermataMenuPausa (menu_pausa, partita_in_corso, partita_salvata);
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
				al_flush_event_queue (coda_eventi);
				break;
			case s_fine_partita:
				posizione = posizionePunteggio (classifica, * (punteggioAttuale (partita_in_corso))); //salvo la posizione delal classifica nella quale potrebbe essere inserito il nuovo punteggio
				al_start_timer(timer_lampeggio_voce);

				while(!cambia_schermata)
			   	{
					al_wait_for_event(coda_eventi, &ev);
					if(ev.type == ALLEGRO_EVENT_TIMER)
					{
						if (ev.timer.source == timer_fps)
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
									aggiungiPunteggio (classifica, * (punteggioAttuale (partita_in_corso)), posizione);
									salvaPunteggi (classifica);
								}

								nuovaPartita (partita_in_corso, impostazioni); //inizializzo correttamente la variabile contenente la partita in corso
								schermata_att = s_menu;
								cambia_schermata = true;
								break;
							case ALLEGRO_KEY_BACKSPACE:
								cancellaUltimoCarattereNome (* (punteggioAttuale (partita_in_corso)));
								break;
							default:
								if (ev.keyboard.keycode >= ALLEGRO_KEY_A && ev.keyboard.keycode <= ALLEGRO_KEY_Z) //se è una lettera
								{
									aggiungiLetteraNomePunteggio (* (punteggioAttuale (partita_in_corso)), ev.keyboard.keycode - ALLEGRO_KEY_A + 'A');
								}
								break;
						}
					}

					if(redraw && al_is_event_queue_empty(coda_eventi))
					{
						stampaFinePartita (classifica, partita_in_corso, posizione, redraw_lampeggio);
					}
			   	}
				al_stop_timer(timer_lampeggio_voce);
				al_flush_event_queue (coda_eventi);
				break;
			case s_esci:
				distruggiGrafica ();
				distruggiAudio ();
				distruggiCoda ();
				distruggiTimer ();
				return 0; //uscita corretta dal gioco
			default:
				distruggiGrafica ();
				distruggiAudio ();
				distruggiCoda ();
				distruggiTimer ();
				return 2; //tentativo di gestione di una schermata inesistente
		}
	}
	distruggiGrafica ();
	distruggiAudio ();
	distruggiCoda ();
	distruggiTimer ();
   	return 1; //uscita non prevista dal ciclo di gestione delle schermate
}

unsigned int percentualeVelocitaOndata (Partita partita)
{
	int percentuale_alieni_eliminati = percentualeAlieniEliminati (partita);
	return percentuale_alieni_eliminati - (percentuale_alieni_eliminati % RANGE_PERCENTUALE_INCREMENTO_VELOCITA_ONDATA);
}

void distruggiDisplay ()
{
	al_destroy_display(display);
}

void distruggiTimer ()
{
	al_destroy_timer(timer_fps);
	al_destroy_timer(timer_lampeggio_voce);
	al_destroy_timer(timer_comparsa_sparo_alieni);
	al_destroy_timer(timer_animazione);
	al_destroy_timer(timer_comparsa_navicella);
	al_destroy_timer(timer_spostamento_carro_armato);
	al_destroy_timer(timer_spostamento_navicella);
	al_destroy_timer(timer_spostamento_spari);
	al_destroy_timer(timer_spostamento_ondata);
}

void distruggiCoda ()
{
	al_destroy_event_queue(coda_eventi);
}
