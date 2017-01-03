/*
 * File contenente il modulo per la gestione dei timer.
 */

using namespace std;
#include <iostream>
#include <cassert>
#include <allegro5/allegro.h>
#include "strutture_dati.h"
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
	assert (timer_spostamento_ondata);
	al_set_timer_speed(timer_spostamento_ondata, 1.0 / (((FREQUENZA_SPOSTAMENTO_ONDATA_MAX - FREQUENZA_SPOSTAMENTO_ONDATA_MIN) / 100 * percentuale_velocita_alieni) + FREQUENZA_SPOSTAMENTO_ONDATA_MIN));
}

void avviaTimerAnimazione ()
{
	assert (timer_animazione);
	al_start_timer(timer_animazione);
}

void avviaTimerComparsaNavicellaMisteriosa ()
{
	assert (timer_comparsa_navicella);
	al_start_timer(timer_comparsa_navicella);
}

void avviaTimerComparsaSparoAlieni ()
{
	assert (timer_comparsa_sparo_alieni);
	al_start_timer(timer_comparsa_sparo_alieni);
}

void avviaTimerEffettoLampeggio ()
{
	assert (timer_lampeggio_voce);
	al_start_timer(timer_lampeggio_voce);
}

void avviaTimerFps ()
{
	assert (timer_fps);
	al_start_timer(timer_fps);
}

void avviaTimerSpostamentoCarroArmato ()
{
	assert (timer_spostamento_carro_armato);
	al_start_timer(timer_spostamento_carro_armato);
}

void avviaTimerSpostamentoOndata ()
{
	assert (timer_spostamento_ondata);
	al_start_timer(timer_spostamento_ondata);
}

void avviaTimerSpostamentoNavicellaMisteriosa ()
{
	assert (timer_spostamento_navicella);
	al_start_timer(timer_spostamento_navicella);
}

void avviaTimerSpostamentoSpari ()
{
	assert (timer_spostamento_spari);
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
	assert (timer_animazione);
	al_stop_timer(timer_animazione);
}

void fermaTimerComparsaNavicellaMisteriosa ()
{
	assert (timer_comparsa_navicella);
	al_stop_timer(timer_comparsa_navicella);
}

void fermaTimerComparsaSparoAlieni ()
{
	assert (timer_comparsa_sparo_alieni);
	al_stop_timer(timer_comparsa_sparo_alieni);
}

void fermaTimerEffettoLampeggio ()
{
	assert (timer_lampeggio_voce);
	al_stop_timer(timer_lampeggio_voce);
}

void fermaTimerFps ()
{
	assert (timer_fps);
	al_stop_timer(timer_fps);
}

void fermaTimerSpostamentoCarroArmato ()
{
	assert (timer_spostamento_carro_armato);
	al_stop_timer(timer_spostamento_carro_armato);
}

void fermaTimerSpostamentoOndata ()
{
	assert (timer_spostamento_ondata);
	al_stop_timer(timer_spostamento_ondata);
}

void fermaTimerSpostamentoNavicellaMisteriosa ()
{
	assert (timer_spostamento_navicella);
	al_stop_timer(timer_spostamento_navicella);
}

void fermaTimerSpostamentoSpari ()
{
	assert (timer_spostamento_spari);
	al_stop_timer(timer_spostamento_spari);
}

bool inizializzaTimer (ALLEGRO_EVENT_QUEUE *coda)
{ 
	timer_fps = al_create_timer(1.0 / FPS_GIOCO);
	if (!timer_fps)
	{
		D1(cout<<"timer_fps non creato correttamente."<<endl);
		return false;
	}

	timer_lampeggio_voce = al_create_timer(1.0 / FREQUENZA_LAMPEGGIO_MENU);
	if (!timer_lampeggio_voce)
	{
		D1(cout<<"timer_lampeggio_veloce non creato correttamente."<<endl);
		return false;
	}

	timer_comparsa_sparo_alieni = al_create_timer(1.0 / FREQUENZA_COMPARSA_SPARO_ALIENI);
	if (!timer_comparsa_sparo_alieni)
	{
		D1(cout<<"timer_comparsa_sparo_alieni non creato correttamente."<<endl);
		return false;
	}

	timer_animazione = al_create_timer(1.0 / FREQUENZA_ANIMAZIONE);
	if (!timer_animazione)
	{
		D1(cout<<"timer_animazione non creato correttamente."<<endl);
		return false;
	}

	timer_comparsa_navicella = al_create_timer(1.0 / FREQUENZA_COMPARSA_NAVICELLA_MISTERIOSA);
	if (!timer_comparsa_navicella)
	{
		D1(cout<<"timer_comparsa_navicella non creato correttamente."<<endl);
		return false;
	}

	timer_spostamento_carro_armato = al_create_timer(1.0 / FREQUENZA_SPOSTAMENTO_CARRO_ARMATO);
	if (!timer_spostamento_carro_armato)
	{
		D1(cout<<"timer_spostamento_carro_armato non creato correttamente."<<endl);
		return false;
	}

	timer_spostamento_navicella = al_create_timer(1.0 / FREQUENZA_SPOSTAMENTO_NAVICELLA_MISTERIOSA);
	if (!timer_spostamento_navicella)
	{
		D1(cout<<"timer_spostamento_navicella non creato correttamente."<<endl);
		return false;
	}

	timer_spostamento_spari = al_create_timer(1.0 / FREQUENZA_SPOSTAMENTO_SPARI);
	if (!timer_spostamento_spari)
	{
		D1(cout<<"timer_spostamento_spari non creato correttamente."<<endl);
		return false;
	}

	timer_spostamento_ondata = al_create_timer(1.0 / FREQUENZA_SPOSTAMENTO_ONDATA_MAX);
	if (!timer_spostamento_ondata)
	{
		D1(cout<<"timer_spostamento_ondata non creato correttamente."<<endl);
		return false;
	}

	al_register_event_source(coda, al_get_timer_event_source(timer_fps));
	al_register_event_source(coda, al_get_timer_event_source(timer_lampeggio_voce));
	al_register_event_source(coda, al_get_timer_event_source(timer_comparsa_sparo_alieni));
	al_register_event_source(coda, al_get_timer_event_source(timer_animazione));
	al_register_event_source(coda, al_get_timer_event_source(timer_comparsa_navicella));
	al_register_event_source(coda, al_get_timer_event_source(timer_spostamento_navicella));
	al_register_event_source(coda, al_get_timer_event_source(timer_spostamento_carro_armato));
	al_register_event_source(coda, al_get_timer_event_source(timer_spostamento_spari));
	al_register_event_source(coda, al_get_timer_event_source(timer_spostamento_ondata));
	return true;
}

ALLEGRO_TIMER * timerAnimazione ()
{
	assert (timer_animazione);
	return timer_animazione;
}

ALLEGRO_TIMER * timerComparsaNavicellaMisteriosa ()
{
	assert (timer_comparsa_navicella);
	return timer_comparsa_navicella;
}

ALLEGRO_TIMER * timerComparsaSparoAlieni ()
{
	assert (timer_comparsa_sparo_alieni);
	return timer_comparsa_sparo_alieni;
}

ALLEGRO_TIMER * timerEffettoLampeggio ()
{
	assert (timer_lampeggio_voce);
	return timer_lampeggio_voce;
}

ALLEGRO_TIMER * timerFps ()
{
	assert (timer_fps);
	return timer_fps;
}

ALLEGRO_TIMER * timerSpostamentoCarroArmato ()
{
	assert (timer_spostamento_carro_armato);
	return timer_spostamento_carro_armato;
}

ALLEGRO_TIMER * timerSpostamentoOndata ()
{
	assert (timer_spostamento_ondata);
	return timer_spostamento_ondata;
}

ALLEGRO_TIMER * timerSpostamentoNavicellaMisteriosa ()
{
	assert (timer_spostamento_navicella);
	return timer_spostamento_navicella;
}

ALLEGRO_TIMER * timerSpostamentoSpari ()
{
	assert (timer_spostamento_spari);
	return timer_spostamento_spari;
}
//FINE MODULO
