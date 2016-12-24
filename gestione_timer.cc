/*
 * File contenente il modulo per la gestione dei timer.
 */

using namespace std;
#include <iostream>
#include <allegro5/allegro.h>
#include "strutture_dati.h"
#include "gestione_timer.h"

//INIZIO CONFIGURAZIONE TRACING
/*#ifdef DEBUG_MODE
	#ifdef DEBUG_LEVEL
		static unsigned int debug_level = DEBUG_LEVEL;
	#else
		static unsigned int debug_level = 0;
	#endif
#endif*/
//FINE CONFIGURAZIONE TRACING

//INIZIO VARIABILI DI MODULO
static ALLEGRO_TIMER *timer_fps = NULL; /**<Timer per ricaricamento grafica generale.*/
static ALLEGRO_TIMER *timer_lampeggio_voce = NULL; /**<Timer per effettuare l'effetto lampeggiante.*/
static ALLEGRO_TIMER *timer_comparsa_sparo_alieni= NULL; /**<Timer per la comparsa degli spari alieni.*/
static ALLEGRO_TIMER *timer_animazione = NULL; /**<Timer per l'animazione.*/
static ALLEGRO_TIMER *timer_spostamento_carro_armato = NULL; /**<Timer per lo spostamento del carro armato.*/
static ALLEGRO_TIMER *timer_comparsa_navicella = NULL; /**<Timer per la comparsa della navicella misteriosa.*/
static ALLEGRO_TIMER *timer_spostamento_ondata = NULL; /**<Timer per lo spostamento dell'ondata aliena.*/
static ALLEGRO_TIMER *timer_spostamento_navicella = NULL; /**<Timer per lo spostamento della navicella misteriosa.*/
static ALLEGRO_TIMER *timer_spostamento_spari = NULL; /**<Timer per lo spostamento degli spari.*/
//FINE VARIABILI DI MODULO

//INIZIO MODULO
//INIZIO FUNZIONI PRIVATE

//FINE FUNZIONI PRIVATE
void aggiornaVelocitaSpostamentoOndata (unsigned int percentuale_velocita_alieni)
{
	al_set_timer_speed(timer_spostamento_ondata, 1.0 / (((FREQUENZA_SPOSTAMENTO_ONDATA_MAX - FREQUENZA_SPOSTAMENTO_ONDATA_MIN) / 100 * percentuale_velocita_alieni) + FREQUENZA_SPOSTAMENTO_ONDATA_MIN));
}

void avviaTimerAnimazione ()
{
	al_start_timer(timer_animazione);
}

void avviaTimerComparsaNavicellaMisteriosa ()
{
	al_start_timer(timer_comparsa_navicella);
}

void avviaTimerComparsaSparoAlieni ()
{
	al_start_timer(timer_comparsa_sparo_alieni);
}

void avviaTimerEffettoLampeggio ()
{
	al_start_timer(timer_lampeggio_voce);
}

void avviaTimerFps ()
{
	al_start_timer(timer_fps);
}

void avviaTimerSpostamentoCarroArmato ()
{
	al_start_timer(timer_spostamento_carro_armato);
}

void avviaTimerSpostamentoOndata ()
{
	al_start_timer(timer_spostamento_ondata);
}

void avviaTimerSpostamentoNavicellaMisteriosa ()
{
	al_start_timer(timer_spostamento_navicella);
}

void avviaTimerSpostamentoSpari ()
{
	al_start_timer(timer_spostamento_spari);
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

void fermaTimerAnimazione ()
{
	al_stop_timer(timer_animazione);
}

void fermaTimerComparsaNavicellaMisteriosa ()
{
	al_stop_timer(timer_comparsa_navicella);
}

void fermaTimerComparsaSparoAlieni ()
{
	al_stop_timer(timer_comparsa_sparo_alieni);
}

void fermaTimerEffettoLampeggio ()
{
	al_stop_timer(timer_lampeggio_voce);
}

void fermaTimerFps ()
{
	al_stop_timer(timer_fps);
}

void fermaTimerSpostamentoCarroArmato ()
{
	al_stop_timer(timer_spostamento_carro_armato);
}

void fermaTimerSpostamentoOndata ()
{
	al_stop_timer(timer_spostamento_ondata);
}

void fermaTimerSpostamentoNavicellaMisteriosa ()
{
	al_stop_timer(timer_spostamento_navicella);
}

void fermaTimerSpostamentoSpari ()
{
	al_stop_timer(timer_spostamento_spari);
}

void inizializzaTimer (ALLEGRO_EVENT_QUEUE *coda)
{ 
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

	al_register_event_source(coda, al_get_timer_event_source(timer_fps));
	al_register_event_source(coda, al_get_timer_event_source(timer_lampeggio_voce));
	al_register_event_source(coda, al_get_timer_event_source(timer_comparsa_sparo_alieni));
	al_register_event_source(coda, al_get_timer_event_source(timer_animazione));
	al_register_event_source(coda, al_get_timer_event_source(timer_comparsa_navicella));
	al_register_event_source(coda, al_get_timer_event_source(timer_spostamento_navicella));
	al_register_event_source(coda, al_get_timer_event_source(timer_spostamento_carro_armato));
	al_register_event_source(coda, al_get_timer_event_source(timer_spostamento_spari));
	al_register_event_source(coda, al_get_timer_event_source(timer_spostamento_ondata));
}

ALLEGRO_TIMER * timerAnimazione ()
{
	return timer_animazione;
}

ALLEGRO_TIMER * timerComparsaNavicellaMisteriosa ()
{
	return timer_comparsa_navicella;
}

ALLEGRO_TIMER * timerComparsaSparoAlieni ()
{
	return timer_comparsa_sparo_alieni;
}

ALLEGRO_TIMER * timerEffettoLampeggio ()
{
	return timer_lampeggio_voce;
}

ALLEGRO_TIMER * timerFps ()
{
	return timer_fps;
}

ALLEGRO_TIMER * timerSpostamentoCarroArmato ()
{
	return timer_spostamento_carro_armato;
}

ALLEGRO_TIMER * timerSpostamentoOndata ()
{
	return timer_spostamento_ondata;
}

ALLEGRO_TIMER * timerSpostamentoNavicellaMisteriosa ()
{
	return timer_spostamento_navicella;
}

ALLEGRO_TIMER * timerSpostamentoSpari ()
{
	return timer_spostamento_spari;
}
//FINE MODULO
