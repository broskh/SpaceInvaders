/*
 * File contenente il modulo di gestione dell'audio.
 */

//#include <cstdio>
//#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
//#include "struttura_dati.h"
#include "gestione_audio.h"

//INIZIO VARIABILI DI MODULO
static ALLEGRO_SAMPLE *musica_principale = NULL;
static ALLEGRO_SAMPLE *musica_sottofondo_ondata = NULL;
static ALLEGRO_SAMPLE *suono_esplosione_carro_armato = NULL;
static ALLEGRO_SAMPLE *suono_esplosione_alieno = NULL;
static ALLEGRO_SAMPLE *suono_esplosione_navicella_misteriosa = NULL;
static ALLEGRO_SAMPLE *suono_sparo_carro_armato = NULL;
static ALLEGRO_SAMPLE *suono_navicella_misteriosa = NULL;

static ALLEGRO_SAMPLE_INSTANCE *istanza_sottofondo_ondata = NULL;
static ALLEGRO_SAMPLE_INSTANCE *istanza_esplosione_carro_armato = NULL;
static ALLEGRO_SAMPLE_INSTANCE *istanza_esplosione_alieno = NULL;
static ALLEGRO_SAMPLE_INSTANCE *istanza_esplosione_navicella_misteriosa = NULL;
static ALLEGRO_SAMPLE_INSTANCE *istanza_sparo_carro_armato = NULL;
static ALLEGRO_SAMPLE_INSTANCE *istanza_navicella_misteriosa = NULL;
//FINE VARIABILI DI MODULO

//INIZIO MODULO
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
	al_attach_sample_instance_to_mixer(istanza_sottofondo_ondata, al_get_default_mixer());
	al_set_sample_instance_playmode(istanza_sottofondo_ondata, ALLEGRO_PLAYMODE_LOOP);

	suono_esplosione_carro_armato = al_load_sample (FILE_SUONO_ESPLOSIONE_CARRO_ARMATO);
	assert (suono_esplosione_carro_armato);
	istanza_esplosione_carro_armato = al_create_sample_instance (suono_esplosione_carro_armato);
	al_attach_sample_instance_to_mixer(istanza_esplosione_carro_armato, al_get_default_mixer());

	suono_esplosione_alieno = al_load_sample (FILE_SUONO_ESPLOSIONE_ALIENO);
	assert (suono_esplosione_alieno);
	istanza_esplosione_alieno = al_create_sample_instance (suono_esplosione_alieno);
	al_attach_sample_instance_to_mixer(istanza_esplosione_alieno, al_get_default_mixer());

	suono_esplosione_navicella_misteriosa = al_load_sample (FILE_SUONO_ESPLOSIONE_NAVICELLA_MISTERIOSA);
	assert (suono_esplosione_navicella_misteriosa);
	istanza_esplosione_navicella_misteriosa = al_create_sample_instance (suono_esplosione_navicella_misteriosa);
	al_attach_sample_instance_to_mixer(istanza_esplosione_navicella_misteriosa, al_get_default_mixer());

	suono_sparo_carro_armato = al_load_sample (FILE_SUONO_SPARO_CARRO_ARMATO);
	assert (suono_sparo_carro_armato);
	istanza_sparo_carro_armato = al_create_sample_instance (suono_sparo_carro_armato);
	al_attach_sample_instance_to_mixer(istanza_sparo_carro_armato, al_get_default_mixer());

	suono_navicella_misteriosa = al_load_sample (FILE_SUONO_NAVICELLA_MISTERIOSA);
	assert (suono_navicella_misteriosa);
	istanza_navicella_misteriosa = al_create_sample_instance (suono_navicella_misteriosa);
	al_attach_sample_instance_to_mixer(istanza_navicella_misteriosa, al_get_default_mixer());
	al_set_sample_instance_playmode(istanza_navicella_misteriosa, ALLEGRO_PLAYMODE_LOOP);
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

void avviaMusicaPrincipale ()
{
	al_play_sample(musica_principale, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
}

void fermaMusicaPrincipale ()
{
	al_stop_samples ();
}

void avviaMusicaOndata ()
{
	al_play_sample_instance(istanza_sottofondo_ondata);
}

void fermaMusicaOndata ()
{
	al_stop_sample_instance(istanza_sottofondo_ondata);
}

void avviaSuonoNavicellaMisteriosa ()
{
	al_play_sample_instance(istanza_navicella_misteriosa);
}

void fermaSuonoNavicellaMisteriosa ()
{
	al_stop_sample_instance(istanza_navicella_misteriosa);
}

void avviaSuonoSparoCarroArmato ()
{
	al_play_sample_instance(istanza_sparo_carro_armato);
}

void avviaSuonoEsplosioneCarroArmato ()
{
	al_play_sample_instance(istanza_esplosione_carro_armato);
}

void avviaSuonoEsplosioneAlieno ()
{
	al_play_sample_instance(istanza_esplosione_alieno);
}

void avviaSuonoEsplosioneNavicellaMisteriosa ()
{
	al_play_sample_instance(istanza_esplosione_navicella_misteriosa);
}

void modificaVelocitaMusicaOndata (unsigned int percentuale_velocita_ondata)
{
	al_set_sample_instance_speed(istanza_sottofondo_ondata,((VELOCITA_SOTTOFONDO_ONDATA_MAX - VELOCITA_SOTTOFONDO_ONDATA_MIN) / 100 * percentuale_velocita_ondata) + VELOCITA_SOTTOFONDO_ONDATA_MIN);
}
//FINE MODULO