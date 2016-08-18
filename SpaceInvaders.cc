/*
 *
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

#include <iostream>
#include "struttura_dati.h"
#include <stdio.h>
#include <allegro5/allegro.h>

using namespace std;

/*
 * FARE DOCUMENTAZIONE PER MAIN
 */
int main ()
{
	ALLEGRO_DISPLAY *display = NULL;
   	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
 
	if(!al_init())
	{
		fprintf(stderr, "failed to initialize allegro!\n");
	      	return -1;
   	}
 
   	display = al_create_display(640, 480);
   	if(!display)
	{
	      	fprintf(stderr, "failed to create display!\n");
	     	return -1;
	}
 
   	event_queue = al_create_event_queue();
   	if(!event_queue)
	{
      		fprintf(stderr, "failed to create event_queue!\n");
      		al_destroy_display(display);
		return -1;
	}      
 
   	al_register_event_source(event_queue, al_get_display_event_source(display));
 
   	al_clear_to_color(al_map_rgb(0,0,0));
 
   	al_flip_display();
 
   	while(true)
   	{
      		ALLEGRO_EVENT ev;
		ALLEGRO_TIMEOUT timeout;
      		al_init_timeout(&timeout, 0.06);
 
      		bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);
 
      		if(get_event && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
         		break;
      		}
 
      		al_clear_to_color(al_map_rgb(0,0,0));
      		al_flip_display();
   	}
 
   	al_destroy_display(display);
   	al_destroy_event_queue(event_queue);
 
   	return 0;
}