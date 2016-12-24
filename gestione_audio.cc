/*
 * File contenente il modulo per la gestione dell'audio.
 */

using namespace std;
#include <iostream>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "strutture_dati.h"
#include "gestione_audio.h"

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
static ALLEGRO_SAMPLE *musica_principale = NULL; /**<Musica principale.*/
static ALLEGRO_SAMPLE *musica_sottofondo_ondata = NULL; /**<Musica di sottofondo all'ondata di alieni in movimento.*/
static ALLEGRO_SAMPLE *suono_esplosione_alieno = NULL; /**<Suono dell'esplosione di un alieno.*/
static ALLEGRO_SAMPLE *suono_esplosione_carro_armato = NULL; /**<Suono dell'esplosione del carro armato.*/
static ALLEGRO_SAMPLE *suono_esplosione_navicella_misteriosa = NULL; /**<Suono dell'esplosione della navicella misteriosa.*/
static ALLEGRO_SAMPLE *suono_navicella_misteriosa = NULL; /**<Suono della navicella msiteriosa in movimento.*/
static ALLEGRO_SAMPLE *suono_sparo_carro_armato = NULL; /**<Suono dello sparo del carro armato.*/

static ALLEGRO_SAMPLE_INSTANCE *istanza_esplosione_alieno = NULL; /**<Istanza del suono di esplosione di un alieno.*/
static ALLEGRO_SAMPLE_INSTANCE *istanza_esplosione_carro_armato = NULL; /**<Istanza del suono di esplosione del carro armato.*/
static ALLEGRO_SAMPLE_INSTANCE *istanza_esplosione_navicella_misteriosa = NULL; /**<Istanza del suono di esplosione della navicella misteriosa.*/
static ALLEGRO_SAMPLE_INSTANCE *istanza_navicella_misteriosa = NULL; /**<Istanza del suono della navicella misteriosa in movimento.*/
static ALLEGRO_SAMPLE_INSTANCE *istanza_sottofondo_ondata = NULL; /**<Istanza della musica di sottofondo all'ondata di alieni in movimento.*/
static ALLEGRO_SAMPLE_INSTANCE *istanza_sparo_carro_armato = NULL; /**<Istanza del suono dello sparo del carro armato.*/
//FINE VARIABILI DI MODULO

//INIZIO MODULO
void avviaMusicaOndata ()
{
	al_play_sample_instance(istanza_sottofondo_ondata);
}

void avviaMusicaPrincipale ()
{
	al_play_sample(musica_principale, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
}

void avviaSuonoEsplosioneAlieno ()
{
	al_play_sample_instance(istanza_esplosione_alieno);
}

void avviaSuonoEsplosioneCarroArmato ()
{
	al_play_sample_instance(istanza_esplosione_carro_armato);
}

void avviaSuonoEsplosioneNavicellaMisteriosa ()
{
	al_play_sample_instance(istanza_esplosione_navicella_misteriosa);
}

void avviaSuonoNavicellaMisteriosa ()
{
	al_play_sample_instance(istanza_navicella_misteriosa);
}

void avviaSuonoSparoCarroArmato ()
{
	al_play_sample_instance(istanza_sparo_carro_armato);
}

void distruggiAudio ()
{
	al_destroy_sample(musica_principale);
	al_destroy_sample(musica_sottofondo_ondata);
	al_destroy_sample(suono_esplosione_carro_armato);
	al_destroy_sample(suono_esplosione_alieno);
	al_destroy_sample(suono_esplosione_navicella_misteriosa);
	al_destroy_sample(suono_sparo_carro_armato);
	al_destroy_sample(suono_navicella_misteriosa);
	al_destroy_sample_instance (istanza_sottofondo_ondata);
	al_destroy_sample_instance (istanza_esplosione_carro_armato);
	al_destroy_sample_instance (istanza_esplosione_alieno);
	al_destroy_sample_instance (istanza_esplosione_navicella_misteriosa);
	al_destroy_sample_instance (istanza_sparo_carro_armato);
	al_destroy_sample_instance (istanza_navicella_misteriosa);
}

void fermaMusicaOndata ()
{
	al_stop_sample_instance(istanza_sottofondo_ondata);
}

void fermaMusicaPrincipale ()
{
	al_stop_samples ();
}

void fermaSuonoNavicellaMisteriosa ()
{
	al_stop_sample_instance(istanza_navicella_misteriosa);
}

void inizializzaAudio ()
{
	assert (al_install_audio());
	assert (al_init_acodec_addon());
	assert (al_reserve_samples(true));

	musica_principale = al_load_sample (FILE_MUSICA_PRINCIPALE);
	assert (musica_principale);

	musica_sottofondo_ondata = al_load_sample (FILE_MUSICA_SOTTOFONDO_ONDATA);
	assert (musica_sottofondo_ondata);
	istanza_sottofondo_ondata = al_create_sample_instance (musica_sottofondo_ondata);
	assert (istanza_sottofondo_ondata);
	al_attach_sample_instance_to_mixer(istanza_sottofondo_ondata, al_get_default_mixer());
	al_set_sample_instance_playmode(istanza_sottofondo_ondata, ALLEGRO_PLAYMODE_LOOP);

	suono_esplosione_carro_armato = al_load_sample (FILE_SUONO_ESPLOSIONE_CARRO_ARMATO);
	assert (suono_esplosione_carro_armato);
	istanza_esplosione_carro_armato = al_create_sample_instance (suono_esplosione_carro_armato);
	assert (istanza_esplosione_carro_armato);
	al_attach_sample_instance_to_mixer(istanza_esplosione_carro_armato, al_get_default_mixer());

	suono_esplosione_alieno = al_load_sample (FILE_SUONO_ESPLOSIONE_ALIENO);
	assert (suono_esplosione_alieno);
	istanza_esplosione_alieno = al_create_sample_instance (suono_esplosione_alieno);
	assert (istanza_esplosione_alieno);
	al_attach_sample_instance_to_mixer(istanza_esplosione_alieno, al_get_default_mixer());

	suono_esplosione_navicella_misteriosa = al_load_sample (FILE_SUONO_ESPLOSIONE_NAVICELLA_MISTERIOSA);
	assert (suono_esplosione_navicella_misteriosa);
	istanza_esplosione_navicella_misteriosa = al_create_sample_instance (suono_esplosione_navicella_misteriosa);
	assert (istanza_esplosione_navicella_misteriosa);
	al_attach_sample_instance_to_mixer(istanza_esplosione_navicella_misteriosa, al_get_default_mixer());

	suono_sparo_carro_armato = al_load_sample (FILE_SUONO_SPARO_CARRO_ARMATO);
	assert (suono_sparo_carro_armato);
	istanza_sparo_carro_armato = al_create_sample_instance (suono_sparo_carro_armato);
	assert (istanza_sparo_carro_armato);
	al_attach_sample_instance_to_mixer(istanza_sparo_carro_armato, al_get_default_mixer());

	suono_navicella_misteriosa = al_load_sample (FILE_SUONO_NAVICELLA_MISTERIOSA);
	assert (suono_navicella_misteriosa);
	istanza_navicella_misteriosa = al_create_sample_instance (suono_navicella_misteriosa);
	assert (istanza_navicella_misteriosa);
	al_attach_sample_instance_to_mixer(istanza_navicella_misteriosa, al_get_default_mixer());
	al_set_sample_instance_playmode(istanza_navicella_misteriosa, ALLEGRO_PLAYMODE_LOOP);
}

void modificaVelocitaMusicaOndata (unsigned int percentuale_velocita_ondata)
{
	al_set_sample_instance_speed(istanza_sottofondo_ondata,((VELOCITA_SOTTOFONDO_ONDATA_MAX - VELOCITA_SOTTOFONDO_ONDATA_MIN) / 100 * percentuale_velocita_ondata) + VELOCITA_SOTTOFONDO_ONDATA_MIN);
	D1(cout<<"Velocita' della musica di sottofondo dell'ondata aliena modificata."<<endl);
}
//FINE MODULO
