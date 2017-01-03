/*
 * File contenente il modulo per la gestione della classifica.
 */

using namespace std;
#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>
#include "strutture_dati.h"
#include "gestione_classifica.h"

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
 * Stampa tutte le informazioni di un Punteggio sullo stream passato per parametro.
 */
void output (Punteggio punteggio, ostream &os)
{
	os<<punteggio.nome<<" "<<punteggio.valore;	
}

/*
 * Stampa tutte le informazioni di una Classifica sullo stream passato per parametro.
 */
void output (Classifica classifica, ostream &os)
{
	for (int i = 0; i < classifica.n_highscores; i++)
	{
		output (classifica.highscores [i], os);
		os<<endl;
	}
}

/*
 * Scambia due punteggi fra loro.
 */
void scambiaPunteggio (Punteggio &punt1, Punteggio &punt2)
{
	Punteggio temp = punt2;
	punt2 = punt1;
	punt1 = temp;
}
//FINE FUNZIONI PRIVATE

void aggiungiLetteraNomePunteggio (Punteggio &punteggio, char nuova_lettera)
{	
	if (strlen (punteggio.nome) < CARATTERI_NOME) //se non sono è già stato raggiunto il limite di lunghezza del nome
	{
		char input [] = " ";
		input [0] = nuova_lettera;
		strcat (punteggio.nome, input); //aggiorno il nome del giocatore
	}
	else
	{
		punteggio.nome [CARATTERI_NOME - 1] = nuova_lettera; //modifico l'ultima lettera che è possibile inserire
	}
}

void aggiungiPunteggio (Classifica &classifica, Punteggio nuovo_punteggio, int posizione)
{
	Punteggio pros = nuovo_punteggio;
	posizione--; //posizione nell'array
	if (classifica.n_highscores < MAX_HIGHSCORES)
	{
		classifica.n_highscores++;
	}
	for (int i = posizione; i < classifica.n_highscores; i++)
	{
		scambiaPunteggio (classifica.highscores [i], pros);
	}
	D1(cout<<"Nuovo punteggio aggiunto nella posizione "<<posizione<<"."<<endl);
}

void cancellaUltimoCarattereNome (Punteggio &punteggio)
{
	punteggio.nome [strlen (punteggio.nome) - 1] = '\0';
}

bool caricaPunteggi (Classifica &classifica)
{
	ifstream f (FILE_HIGHSCORES) ;
	if (!f) {
		D1(cout<<"Errore nel caricamento del file degli highscores. File non esistente."<<endl);
		return false ;
	}
	int i = 0;
	char nome [CARATTERI_NOME + 1];
	int valore;
	while (f>>nome)
	{
		f>>valore;
		inizializzaPunteggio (classifica.highscores [i], nome, valore);
		i++;
	}
	assert (i <= 10); //se vengono letti più di 10 punteggi il file è corrotto
	
	if (i == 0)
	{
		classifica.n_highscores = 0;
		return false;
	}
	classifica.n_highscores = i;
	D1(cout<<"File degli highscores correttamente caricato."<<endl);
	return true;
}

void inizializzaClassifica (Classifica &classifica)
{
	classifica.n_highscores = 0;
}

void inizializzaPunteggio (Punteggio &punteggio, char nome [], int valore)
{
	strncpy (punteggio.nome, nome, sizeof (punteggio.nome));
	punteggio.valore = valore;
}

int posizionePunteggio (Classifica classifica, Punteggio nuovo_punteggio)
{
	for (int i = 0; i < classifica.n_highscores; i++)
	{
		if (nuovo_punteggio.valore > classifica.highscores [i].valore)
		{
			return i + 1; //+1 perchè altrimenti ritornerei la posizione dell'array, non quella della classifica
		}
	}
	if (classifica.n_highscores < MAX_HIGHSCORES)
	{
		return classifica.n_highscores + 1; //+1 perchè altrimenti ritornerei la posizione dell'array, non quella della classifica
	}
	return -1;
}

void salvaPunteggi (Classifica classifica)
{
	ofstream f(FILE_HIGHSCORES) ;
	output (classifica, f);
	D1(cout<<"File degli highscores correttamente salvato."<<endl);
}

void stampa (Classifica classifica)
{
	output (classifica, cout);
}

void stampa (Punteggio punteggio)
{
	output (punteggio, cout);
}
//FINE MODULO
