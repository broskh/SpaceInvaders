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

//INIZIO MODULO
//INIZIO FUNZIONI PRIVATE
void output (Punteggio punteggio, ostream &os)
{
	os<<punteggio.nome<<" "<<punteggio.valore;	
}

void output (Classifica classifica, ostream &os)
{
	for (int i = 0; i < classifica.n_highscores; i++)
	{
		output (classifica.highscores [i], os);
		os<<endl;
	}
}

void scambiaPunteggio (Punteggio &punt1, Punteggio &punt2)
{
	Punteggio temp = punt2;
	punt2 = punt1;
	punt1 = temp;
}
//FINE FUNZIONI PRIVATE

void aggiungiPunteggio (Classifica &classifica, Punteggio nuovo_punteggio, int posizione)
{
	Punteggio pros = nuovo_punteggio;
	if (classifica.n_highscores < MAX_HIGHSCORES)
	{
		classifica.n_highscores++;
	}
	for (int i = posizione; i < classifica.n_highscores; i++)
	{
		scambiaPunteggio (classifica.highscores [i], pros);
	}
}

bool caricaPunteggi (Classifica &classifica)
{
	ifstream f (FILE_HIGHSCORES) ;
    	if (!f) {
		cerr<<"Errore nel caricamento del file "<<FILE_HIGHSCORES<<endl;
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

	assert (i <= 10);
	
	if (i == 0)
	{
		classifica.n_highscores = 0;
		return false;
	}
	classifica.n_highscores = i;
	return true;
}

void inizializzaPunteggio (Punteggio &punteggio, char nome [], int valore)
{
	strcpy (punteggio.nome, nome);
	punteggio.valore = valore;
}

int posizionePunteggio (Classifica classifica, Punteggio nuovo_punteggio)
{
	for (int i = 0; i < classifica.n_highscores; i++)
	{
		if (nuovo_punteggio.valore > classifica.highscores [i].valore)
		{
			return i;
		}
	}
	if (classifica.n_highscores < MAX_HIGHSCORES)
	{
//		classifica.n_highscores++;
		return classifica.n_highscores - 1;
	}
	return -1;
}

void salvaPunteggi (Classifica classifica)
{
	ofstream f(FILE_HIGHSCORES) ;
	output (classifica, f);
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