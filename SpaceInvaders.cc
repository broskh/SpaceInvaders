/* 
 * File contenente il modulo Main.
 */

/**
 * Riproduzione del celebre videogioco "Space Inavaders"..
 * 
 * Mantiene inalterate tutte le caratteristiche di base del gioco originale.
 * Avremo quindi a che fare con un carro armato, il quale avrà il compito di
 * abbattere, finchè avrà vite a disposizione, tutte le ondate di alieni che
 * ripetutamente si avvicineranno.
 *
 * Man mano che colpirà gli alieni, a seconda del tipo di alieno colpito,
 * il giocatore incrementerà il proprio vantaggio. Una volta che un'intera ondata
 * verrà distrutta, ne ricomparirà subito un'altra.
 *
 * Ad intervalli di tempo casuali comparirà anche una navicella misteriosa. Se essa
 * verrà colpita il giocatore avrà un incremento rilevante e casuale del punteggio.
 *
 * Il giocatore ad inizio partita avrà a disposizione tre barriere. Ogni qualvolta esse
 * verranno colpite dagli alieni o dal carro armato, tenderanno prima a sgretolarsi, e 
 * infine a distruggersi.
 * 
 * Al termine della partita, se è stato ottenuto un punteggio degno di essere inserito 
 * nella classifica degli highscores, è possibile digitare un nome di massimo tre lettere 
 * e salvare il punteggio.
 *
 * Attraverso le impostazioni è possibile abilitare o meno la musica e gli effetti
 * audio. Inoltre è possibile modificare la grafica cromatica degli alieni e
 * impostare il numero di vite con le quali si intende iniziare la partita.
 *
 * Durante una partita è possibile mettere il gioco in pausa ed eventualmente
 * effettuare un salvataggio della partita. In questo modo sarà possibile ricominciare 
 * la stessa in un secondo momento, dall'esatto punto nel quale era stata precedentemente interrotta.
 * 
 * Dal menù principale è inoltre possibile visualizzare la classifica dei dieci migliori
 * punteggi raggiunti e il nome dei giocatori che hanno raggiunto tali risultati.
 *
 * @author Alessio Scheri
 */

using namespace std;
#include <iostream>
#include <allegro5/allegro.h>
#include "strutture_dati.h"
#include "gestione_partita.h"
#include "gestione_impostazioni.h"
#include "gestione_classifica.h"
#include "gestione_menu.h"
#include "gestione_grafica.h"
#include "gestione_audio.h"
#include "gestione_timer.h"

//INIZIO CONFIGURAZIONE TRACING
#ifdef DEBUG_MODE
	#ifdef DEBUG_LEVEL
		static unsigned int debug_level = DEBUG_LEVEL;
	#else
		static unsigned int debug_level = 0;
	#endif
#endif
//FINE CONFIGURAZIONE TRACING

//INIZIO COSTANTI MAIN
const char TITOLO_FINESTRA [] = "Space Invaders"; /**<Titolo della finestra del gioco.*/
//FINE OCSTANTI MAIN

//INIZIO FUNZIONI PRIVATE
/*
 * Dealloca la memoria riguardante la coda degli eventi.
 */
void distruggiCoda ();

/*
 * Dealloca la memoria riguardante il display.
 */
void distruggiDisplay ();

/*
 * Calcola la percentuale della velocità dell'ondata aliena prendendo in considerazione gli alieni rimasti e il
 * il range percentuale di incremento della velocità.
 */
unsigned int percentualeVelocitaOndata (Partita partita);
//FINE FUNZIONI PRIVATE

//INIZIO VARIABILI GLOBALI
static ALLEGRO_EVENT_QUEUE *coda_eventi = NULL; /**<Coda degli eventi.*/
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
 * se è "3" si è verificato qualche errore in fase di inizializzazione delle librerie. 
 * se è "4" si è verificato un errore di altro tipo.
 */
int main ()
{
	//INIZIALIZZAZIONE DELLA LIBRERIA ALLEGRO
	if (!al_init())
	{
		D1(cout<<"Libreria allegro non inizializzata correttamente."<<endl);
		return 3;
	}
 
	//INIZIALIZZAZIONE DELLA CODA DEGLI EVENTI
   	coda_eventi = al_create_event_queue();
   	if (!coda_eventi)
	{
		D1(cout<<"Coda degli eventi non creata correttamente."<<endl);
		return 3;
	}
	ALLEGRO_EVENT ev;
	//INIZIALIZZAZIONE DEL DISPLAY
	display = al_create_display (LARGHEZZA_DISPLAY, ALTEZZA_DISPLAY);
	if (!display)
	{
		D1(cout<<"Display non creato correttamente."<<endl);
		distruggiCoda ();
		return 3;
	}
	al_set_window_title(display, TITOLO_FINESTRA);
   	al_register_event_source(coda_eventi, al_get_display_event_source(display));

	//INIZIALIZZAZIONE DELLA TASTIERA
	if (!al_install_keyboard())
	{
		D1(cout<<"Tastiera non installata correttamente."<<endl);
		distruggiDisplay ();
		distruggiCoda ();
		return 3;
	}
	al_register_event_source(coda_eventi, al_get_keyboard_event_source());

	//INIZIALIZZAZIONE DEI VARI MODULI
	if (!inizializzaGrafica ())
	{
		D1(cout<<"Modulo per la gestione della grafica non inizializzata correttamente."<<endl);
		distruggiGrafica ();
		distruggiDisplay ();
		distruggiCoda ();
		return 3;
	}
	if (!inizializzaAudio ())
	{
		D1(cout<<"Modulo per la gestione dell'audio non inizializzata correttamente."<<endl);
		distruggiAudio ();
		distruggiGrafica ();
		distruggiDisplay ();
		distruggiCoda ();
		return 3;
	}
	if (!inizializzaTimer (coda_eventi))
	{
		D1(cout<<"Modulo per la gestione dei timer non inizializzata correttamente."<<endl);
		distruggiTimer ();
		distruggiAudio ();
		distruggiGrafica ();
		distruggiDisplay ();
		distruggiCoda ();
		return 3;
	}
	
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
	avviaTimerFps ();
	
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
				avviaTimerEffettoLampeggio ();
				
				while(!cambia_schermata) //ciclo finchè non è necessario cambiare schermata
			   	{
					al_wait_for_event(coda_eventi, &ev);
					if(ev.type == ALLEGRO_EVENT_TIMER)
					{
						if (ev.timer.source == timerFps ())
						{
							redraw = true;
						}
						else if (ev.timer.source == timerEffettoLampeggio ())
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
				fermaTimerEffettoLampeggio ();
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
				avviaTimerComparsaSparoAlieni ();
				avviaTimerAnimazione ();
				avviaTimerComparsaNavicellaMisteriosa ();
				avviaTimerSpostamentoCarroArmato ();
				avviaTimerSpostamentoNavicellaMisteriosa ();
				avviaTimerSpostamentoSpari ();
				aggiornaVelocitaSpostamentoOndata (percentualeVelocitaOndata (partita_in_corso)); //se è stata caricata una partita correggo subito la vleocità del movimento dell'ondata
				avviaTimerSpostamentoOndata ();

				while(!cambia_schermata)
			   	{
					al_wait_for_event(coda_eventi, &ev);
					if(ev.type == ALLEGRO_EVENT_TIMER)
					{
						if (ev.timer.source == timerFps ())
						{
							redraw = true;
						}
						else if (ev.timer.source == timerAnimazione ())
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
							if (ev.timer.source == timerComparsaSparoAlieni ())
							{
								if (!statoSparoAlieni (partita_in_corso))
								{
									creaSparoAlieni (partita_in_corso);
								}
							}
							else if (ev.timer.source == timerComparsaNavicellaMisteriosa ())
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
							else if (ev.timer.source == timerSpostamentoCarroArmato ())
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
							else if (ev.timer.source == timerSpostamentoNavicellaMisteriosa ())
							{
								if (statoNavicellaMisteriosa (partita_in_corso))
								{
									muoviNavicellaMisteriosa (partita_in_corso);
								}
							}
							else if (ev.timer.source == timerSpostamentoSpari ())
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
							else if (ev.timer.source == timerSpostamentoOndata ())
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
							aggiornaVelocitaSpostamentoOndata (percentualeVelocitaOndata (partita_in_corso));
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
							if (statoMusica (impostazioni))
							{
								modificaVelocitaMusicaOndata (percentualeVelocitaOndata (partita_in_corso));
							}
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

				fermaTimerComparsaSparoAlieni ();
				fermaTimerAnimazione ();
				fermaTimerComparsaNavicellaMisteriosa ();
				fermaTimerSpostamentoCarroArmato ();
				fermaTimerSpostamentoNavicellaMisteriosa();
				fermaTimerSpostamentoSpari ();
				fermaTimerSpostamentoOndata ();
				al_flush_event_queue (coda_eventi);
				break;
			case s_carica: //carico la partita salvata e passo subito alla schermata di gioco
				if (!caricaPartita (partita_in_corso)) {					
					distruggiGrafica ();
					distruggiAudio ();
					distruggiCoda ();
					distruggiTimer ();
					return 4;
				}
				schermata_att = s_gioca;
				cambia_schermata = true;
				break;
			case s_opzioni:
				selezionaPrimaVoce (menu_impostazioni); //quando passo alla schermata delle impostazioni, la voce musica è sempre selezionata inizialmente
				avviaTimerEffettoLampeggio ();

				while(!cambia_schermata)
			   	{
					al_wait_for_event(coda_eventi, &ev);
					if(ev.type == ALLEGRO_EVENT_TIMER)
					{
						if (ev.timer.source == timerFps ())
						{
							redraw = true;
						}
						else if (ev.timer.source == timerEffettoLampeggio ())
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
				fermaTimerEffettoLampeggio ();
				al_flush_event_queue (coda_eventi);
				break;
			case s_highscores:
				avviaTimerEffettoLampeggio ();

				while(!cambia_schermata)
			   	{
					al_wait_for_event(coda_eventi, &ev);
					if(ev.type == ALLEGRO_EVENT_TIMER)
					{
						if (ev.timer.source == timerFps ())
						{
							redraw = true;
						}
						else if (ev.timer.source == timerEffettoLampeggio ())
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
				fermaTimerEffettoLampeggio ();
				al_flush_event_queue (coda_eventi);
				break;
			case s_pausa:
				selezionaPrimaVoce (menu_pausa); //quando passo alla schermata di pausa, la voce continua è sempre selezionata inizialmente
				avviaTimerEffettoLampeggio ();
		
				while(!cambia_schermata)
			   	{
					al_wait_for_event(coda_eventi, &ev);
					if(ev.type == ALLEGRO_EVENT_TIMER)
					{
						if (ev.timer.source == timerFps ())
						{
							redraw = true;
						}
						else if (ev.timer.source == timerEffettoLampeggio ())
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
				fermaTimerEffettoLampeggio ();
				al_flush_event_queue (coda_eventi);
				break;
			case s_fine_partita:
				posizione = posizionePunteggio (classifica, * (punteggioAttuale (partita_in_corso))); //salvo la posizione delal classifica nella quale potrebbe essere inserito il nuovo punteggio
				avviaTimerEffettoLampeggio ();

				while(!cambia_schermata)
			   	{
					al_wait_for_event(coda_eventi, &ev);
					if(ev.type == ALLEGRO_EVENT_TIMER)
					{
						if (ev.timer.source == timerFps ())
						{
							redraw = true;
						}
						else if (ev.timer.source == timerEffettoLampeggio ())
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
				fermaTimerEffettoLampeggio ();
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

void distruggiDisplay ()
{
	al_destroy_display(display);
}

void distruggiCoda ()
{
	al_destroy_event_queue(coda_eventi);
}

unsigned int percentualeVelocitaOndata (Partita partita)
{
	unsigned int percentuale_alieni_eliminati = percentualeAlieniEliminati (partita);
	return percentuale_alieni_eliminati - (percentuale_alieni_eliminati % RANGE_PERCENTUALE_INCREMENTO_VELOCITA_ONDATA);
}
