/*
 * File contenente il modulo di gestione delle impostazioni.
 */

#include "struttura_dati.h"
#include "gestione_impostazioni.h"

const unsigned int MAX_STRING = 15;

//INIZIO MODULO
void output (Impostazioni impostazioni, ostream &os)
{
	os<<"musica = "<<impostazioni.musica<<endl;
	os<<"effetti_audio = "<<impostazioni.eff_audio<<endl;
	os<<"grafica = "<<impostazioni.mod_grafica<<endl;
	os<<"vite_iniziali = "<<impostazioni.vite_iniziali<<endl;
}

bool caricaImpostazioni (Impostazioni &impostazioni)
{
	ifstream f (FILE_IMPOSTAZIONI) ;
    	if (!f) {
		cerr<<"Errore nel caricamento del file "<<FILE_IMPOSTAZIONI<<endl;
		return false ;
    	}
	bool musica_trov = false, eff_audio_trov = false, mod_grafica_trov = false, vite_iniz_trov = false;
	bool musica, eff_audio;
	grafica mod_grafica;
	unsigned int vite_iniziali;
	char voice [MAX_STRING];

	while (f>>voice)
	{
		f.ignore (2, '=');
		if (strcmp(voice, "musica") == 0)
		{
			f>>musica;
			musica_trov = true;
		}
		else if (strcmp(voice, "effetti_audio") == 0)
		{
			f>>eff_audio;
			eff_audio_trov = true;
		}
		else if (strcmp(voice, "grafica") == 0)
		{
			int grafica_int;
			f>>grafica_int;
			mod_grafica = static_cast <grafica> (grafica_int);
			mod_grafica_trov = true;
		}
		else if (strcmp(voice, "vite_iniziali") == 0)
		{
			f>>vite_iniziali;
			vite_iniz_trov = true;
		}
    	}
	if (musica_trov || eff_audio_trov || mod_grafica_trov || vite_iniz_trov)
	{
		inizializzaImpostazioni (impostazioni, musica, eff_audio, mod_grafica, vite_iniziali);
		return true;
	}
	cerr<<"File di configurazione incompleto"<<endl;
	return false;
}

void salvaImpostazioni (Impostazioni impostazioni)
{
	ofstream f(FILE_IMPOSTAZIONI) ;
	output (impostazioni, f);
}

void inizializzaImpostazioni (Impostazioni &impostazioni, bool musica, bool effetti_audio, grafica modalita_grafica, unsigned int vite_iniziali)
{
	impostazioni.musica = musica;
	impostazioni.eff_audio = effetti_audio;
	impostazioni.mod_grafica = modalita_grafica;
	impostazioni.vite_iniziali = vite_iniziali;
}

void impostaValoriImpostazioniDefault (Impostazioni &impostazioni)
{
	inizializzaImpostazioni (impostazioni, DEFAULT_MUSICA, DEFAULT_EFFETTI_AUDIO, DEFAULT_MODALITA_GRAFICA, DEFAULT_VITE_INIZIALI);
}

void stampa (Impostazioni impostazioni)
{
	output (impostazioni, cout);
}
//FINE MODULO
