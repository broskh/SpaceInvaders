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
#include "gestione_input-output.h"

using namespace std;

const char FILE_HIGHSCORES [] = "highscores"; /**<Nome del file contenente gli highscores.*/
const char FILE_IMPOSTAZIONI [] = "SpaceInvaders.config"; /**<Nome del file contenente le impostazioni salvate.*/
const char FILE_SALVATAGGIO_PARTITA [] = "partita.sav"; /**<Nome del file contenente la partita salvata.*/

/**
 * FARE DOCUMENTAZIONE PER MAIN
 */
int main ()
{
	ALLEGRO_DISPLAY *display = NULL;
   	ALLEGRO_EVENT_QUEUE *coda_eventi = NULL;
	int mostra_menu = 0;
 
	if(!al_init())
	{
		fprintf(stderr, "Inizializzazione di allegro fallita!\n");
	      	return -1;
   	}
	al_init_font_addon();
	al_init_ttf_addon();
 
   	display = al_create_display(LARGHEZZA_DISPLAY, ALTEZZA_DISPLAY);
   	if(!display)
	{
	      	fprintf(stderr, "Creazione del display fallita!\n");
	     	return -1;
	}
 
   	coda_eventi = al_create_event_queue();
   	if(!coda_eventi)
	{
      		fprintf(stderr, "Creazione della coda degli eventi fallita!\n");
      		al_destroy_display(display);
		return -1;
	}
 
   	al_register_event_source(coda_eventi, al_get_display_event_source(display));
	al_clear_to_color(al_map_rgb(0,0,0));
 	
	while (true)
	{
		switch (mostra_menu)
		{
			case 0:
				menuPrincipale ();
				break;
			case 1:
				//gioco
				break;
			case 2:
				//carica
				break;
			case 3:
				//opzioni
				break;
			case 4:
				//highscores
				break;
			case 5:
				//pausa
				break;
			default:
				return 1;
		}
	}
	
	/*
   	while(true)
   	{
      		ALLEGRO_EVENT ev;
		ALLEGRO_TIMEOUT timeout;
      		al_init_timeout(&timeout, 0.06);
 
      		bool evento = al_wait_for_event_until(coda_eventi, &ev, &timeout);
 
      		if(evento && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
         		break;
      		}
 
      		al_clear_to_color(al_map_rgb(0,0,0));
      		al_flip_display();
   	}

	*/
 
   	al_destroy_display(display);
   	al_destroy_event_queue(coda_eventi);
 
   	return 0;
}
