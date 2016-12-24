/*
 * File contenente il modulo per la gestione delle impostazioni.
 */

using namespace std;
#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>
#include "strutture_dati.h"
#include "gestione_impostazioni.h"

//INIZIO CONFIGURAZIONE TRACING
#ifdef DEBUG_MODE
	#ifdef DEBUG_LEVEL
		static unsigned int debug_level = DEBUG_LEVEL;
	#else
		static unsigned int debug_level = 0;
	#endif
#endif
//FINE CONFIGURAZIONE TRACING

//INIZIO MODULO
//INIZIO FUNZIONI PRIVATE
/*
 * Inizializza le impostazioni con le informazioni di base.
 */
void inizializzaImpostazioni (Impostazioni &impostazioni, bool musica, bool effetti_audio, colore colore_alieni, unsigned int vite_iniziali)
{
	impostazioni.musica = musica;
	impostazioni.eff_audio = effetti_audio;
	impostazioni.colore_alieni = colore_alieni;
	impostazioni.vite_iniziali = vite_iniziali;
}

/*
 * Stampa tutte le informazioni delle Impostazioni sullo stream passato per parametro.
 */
void output (Impostazioni impostazioni, ostream &os)
{
	os<<CAMPO_MUSICA<<" = "<<impostazioni.musica<<endl;
	os<<CAMPO_EFFETTI_AUDIO<<" = "<<impostazioni.eff_audio<<endl;
	os<<CAMPO_COLORE_ALIENI<<" = "<<impostazioni.colore_alieni<<endl;
	os<<CAMPO_VITE_INIZIALI<<" = "<<impostazioni.vite_iniziali<<endl;
}
//FINE FUNZIONI PRIVATE

bool caricaImpostazioni (Impostazioni &impostazioni)
{
	ifstream f (FILE_IMPOSTAZIONI) ;
	if (!f) {
		D1(cout<<"Errore nel caricamento del file di configurazione. File non esistente."<<endl);
		return false ;
	}
	bool musica_trov = false, eff_audio_trov = false, mod_grafica_trov = false, vite_iniz_trov = false;
	bool musica, eff_audio;
	colore colore_alieni;
	unsigned int vite_iniziali;
	generic_string voice;

	while (f>>voice) //fatta in questa modo la lettura da file, così le voci possono essere anche in disordine
	{
		f.ignore (2, '=');
		if (strcmp(voice, CAMPO_MUSICA) == 0)
		{
			f>>musica;
			musica_trov = true;
		}
		else if (strcmp(voice, CAMPO_EFFETTI_AUDIO) == 0)
		{
			f>>eff_audio;
			eff_audio_trov = true;
		}
		else if (strcmp(voice, CAMPO_COLORE_ALIENI) == 0)
		{
			int colore_int;
			f>>colore_int;
			colore_alieni = static_cast <colore> (colore_int);
			mod_grafica_trov = true;
		}
		else if (strcmp(voice, CAMPO_VITE_INIZIALI) == 0)
		{
			f>>vite_iniziali;
			vite_iniz_trov = true;
		}
	}
	assert (musica_trov && eff_audio_trov && mod_grafica_trov && vite_iniz_trov); //se non vengono trovati, il file è corrotto
	inizializzaImpostazioni (impostazioni, musica, eff_audio, colore_alieni, vite_iniziali);
	D1(cout<<"Caricamento del file di configurazione avvenuto con successo."<<endl);
	return true;
}

void impostaValoriDefault (Impostazioni &impostazioni)
{
	inizializzaImpostazioni (impostazioni, DEFAULT_MUSICA, DEFAULT_EFFETTI_AUDIO, DEFAULT_COLORE_ALIENI, DEFAULT_VITE_INIZIALI);
}

void salvaImpostazioni (Impostazioni impostazioni)
{
	ofstream f(FILE_IMPOSTAZIONI) ;
	output (impostazioni, f);
	D1(cout<<"Salvataggio del file di configurazione avvenuto con successo."<<endl);
}

void stampa (Impostazioni impostazioni)
{
	output (impostazioni, cout);
}

colore statoColoreAlieni (Impostazioni impostazioni)
{
	return impostazioni.colore_alieni;
}

bool statoEffettiAudio (Impostazioni impostazioni)
{
	return impostazioni.eff_audio;
}

bool statoMusica (Impostazioni impostazioni)
{
	return impostazioni.musica;
}
//FINE MODULO
