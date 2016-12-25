/*
 * File contenente il modulo per la gestione dell'audio.
 */

using namespace std;
#include <iostream>
#include <cassert>
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
	assert (istanza_sottofondo_ondata);
	al_play_sample_instance(istanza_sottofondo_ondata);
}

void avviaMusicaPrincipale ()
{
	assert (musica_principale);
	al_play_sample(musica_principale, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
}

void avviaSuonoEsplosioneAlieno ()
{
	assert (istanza_esplosione_alieno);
	al_play_sample_instance(istanza_esplosione_alieno);
}

void avviaSuonoEsplosioneCarroArmato ()
{
	assert (istanza_esplosione_carro_armato);
	al_play_sample_instance(istanza_esplosione_carro_armato);
}

void avviaSuonoEsplosioneNavicellaMisteriosa ()
{
	assert (istanza_esplosione_navicella_misteriosa);
	al_play_sample_instance(istanza_esplosione_navicella_misteriosa);
}

void avviaSuonoNavicellaMisteriosa ()
{
	assert (istanza_navicella_misteriosa);
	al_play_sample_instance(istanza_navicella_misteriosa);
}

void avviaSuonoSparoCarroArmato ()
{
	assert (istanza_sparo_carro_armato);
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
	assert (istanza_sottofondo_ondata);
	al_stop_sample_instance(istanza_sottofondo_ondata);
}

void fermaMusicaPrincipale ()
{
	assert (musica_principale);
	al_stop_samples ();
}

void fermaSuonoNavicellaMisteriosa ()
{
	assert (istanza_navicella_misteriosa);
	al_stop_sample_instance(istanza_navicella_misteriosa);
}

bool inizializzaAudio ()
{
	if (!al_install_audio())
	{
		D1(cout<<"Audio non installato correttamente."<<endl);
		return false;
	}
	if (!al_init_acodec_addon())
	{
		D1(cout<<"Codec addon non installato correttamente."<<endl);
		return false;
	}
	if (!al_reserve_samples(true))
	{
		D1(cout<<"ALLEGRO_SAMPLE non collegati correttamente al mixer di default."<<endl);
		return false;
	}

	musica_principale = al_load_sample (FILE_MUSICA_PRINCIPALE);
	if (!musica_principale)
	{
		D1(cout<<"musica_principale non creata correttamente."<<endl);
		return false;
	}

	musica_sottofondo_ondata = al_load_sample (FILE_MUSICA_SOTTOFONDO_ONDATA);
	if (!musica_sottofondo_ondata)
	{
		D1(cout<<"musica_sottofondo_ondata non creata correttamente."<<endl);
		return false;
	}
	istanza_sottofondo_ondata = al_create_sample_instance (musica_sottofondo_ondata);
	if (!istanza_sottofondo_ondata)
	{
		D1(cout<<"istanza_sottofondo_ondata non creata correttamente."<<endl);
		return false;
	}
	al_attach_sample_instance_to_mixer(istanza_sottofondo_ondata, al_get_default_mixer());
	al_set_sample_instance_playmode(istanza_sottofondo_ondata, ALLEGRO_PLAYMODE_LOOP);

	suono_esplosione_carro_armato = al_load_sample (FILE_SUONO_ESPLOSIONE_CARRO_ARMATO);
	if (!suono_esplosione_carro_armato)
	{
		D1(cout<<"suono_esplosione_carro_armato non creato correttamente."<<endl);
		return false;
	}
	istanza_esplosione_carro_armato = al_create_sample_instance (suono_esplosione_carro_armato);
	if (!istanza_esplosione_carro_armato)
	{
		D1(cout<<"istanza_esplosione_carro_armato non creata correttamente."<<endl);
		return false;
	}
	al_attach_sample_instance_to_mixer(istanza_esplosione_carro_armato, al_get_default_mixer());

	suono_esplosione_alieno = al_load_sample (FILE_SUONO_ESPLOSIONE_ALIENO);
	if (!suono_esplosione_alieno)
	{
		D1(cout<<"suono_esplosione_alieno non creato correttamente."<<endl);
		return false;
	}
	istanza_esplosione_alieno = al_create_sample_instance (suono_esplosione_alieno);
	if (!istanza_esplosione_alieno)
	{
		D1(cout<<"istanza_esplosione_alieno non creata correttamente."<<endl);
		return false;
	}
	al_attach_sample_instance_to_mixer(istanza_esplosione_alieno, al_get_default_mixer());

	suono_esplosione_navicella_misteriosa = al_load_sample (FILE_SUONO_ESPLOSIONE_NAVICELLA_MISTERIOSA);
	if (!suono_esplosione_navicella_misteriosa)
	{
		D1(cout<<"suono_esplosione_navicella_misteriosa non creato correttamente."<<endl);
		return false;
	}
	istanza_esplosione_navicella_misteriosa = al_create_sample_instance (suono_esplosione_navicella_misteriosa);
	if (!istanza_esplosione_navicella_misteriosa)
	{
		D1(cout<<"istanza_esplosione_navicella_misteriosa non creata correttamente."<<endl);
		return false;
	}
	al_attach_sample_instance_to_mixer(istanza_esplosione_navicella_misteriosa, al_get_default_mixer());

	suono_sparo_carro_armato = al_load_sample (FILE_SUONO_SPARO_CARRO_ARMATO);
	if (!suono_sparo_carro_armato)
	{
		D1(cout<<"suono_sparo_carro_armato non creato correttamente."<<endl);
		return false;
	}
	istanza_sparo_carro_armato = al_create_sample_instance (suono_sparo_carro_armato);
	if (!istanza_sparo_carro_armato)
	{
		D1(cout<<"istanza_sparo_carro_armato non creata correttamente."<<endl);
		return false;
	}
	al_attach_sample_instance_to_mixer(istanza_sparo_carro_armato, al_get_default_mixer());

	suono_navicella_misteriosa = al_load_sample (FILE_SUONO_NAVICELLA_MISTERIOSA);
	if (!suono_navicella_misteriosa)
	{
		D1(cout<<"suono_navicella_misteriosa non creato correttamente."<<endl);
		return false;
	}
	istanza_navicella_misteriosa = al_create_sample_instance (suono_navicella_misteriosa);
	if (!istanza_navicella_misteriosa)
	{
		D1(cout<<"istanza_navicella_misteriosa non creata correttamente."<<endl);
		return false;
	}
	al_attach_sample_instance_to_mixer(istanza_navicella_misteriosa, al_get_default_mixer());
	al_set_sample_instance_playmode(istanza_navicella_misteriosa, ALLEGRO_PLAYMODE_LOOP);
	return true;
}

void modificaVelocitaMusicaOndata (unsigned int percentuale_velocita_ondata)
{
	assert (istanza_sottofondo_ondata);
	al_set_sample_instance_speed(istanza_sottofondo_ondata,((VELOCITA_SOTTOFONDO_ONDATA_MAX - VELOCITA_SOTTOFONDO_ONDATA_MIN) / 100 * percentuale_velocita_ondata) + VELOCITA_SOTTOFONDO_ONDATA_MIN);
	D1(cout<<"Velocita' della musica di sottofondo dell'ondata aliena modificata."<<endl);
}
//FINE MODULO
