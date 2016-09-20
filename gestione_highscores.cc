/*
 * File contenente il modulo di gestione degli highscores.
 */

#include "struttura_dati.h"
#include "gestione_highscores.h"

//INIZIO MODULO
void output (Punteggio punteggio, ostream &os)
{
	os<<punteggio.nome<<" "<<punteggio.valore;	
}

void output (Punteggio highscores [], int n, ostream &os)
{
	for (int i = 0; i < n; i++)
	{
		output (highscores [i], os);
		os<<endl;
	}
}

void scambiaPunteggio (Punteggio &punt1, Punteggio &punt2)
{
	Punteggio temp = punt2;
	punt2 = punt1;
	punt1 = temp;
}

bool caricaPunteggi (Punteggio (&highscores) [MAX_HIGHSCORES], int &n_highscores)
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
		inizializzaPunteggio (highscores [i], nome, valore);
		i++;
    	}

	assert (i <= 10);
	
	if (i == 0)
	{
		n_highscores = 0;
		return false;
	}
	n_highscores = i;
	return true;
}

void salvaPunteggi (Punteggio highscores [], int n_highscores)
{
	ofstream f(FILE_HIGHSCORES) ;
	output (highscores, n_highscores, f);
}

void inizializzaPunteggio (Punteggio &punteggio, char nome [], int valore)
{
	strcpy (punteggio.nome, nome);
	punteggio.valore = valore;
}

void aggiungiPunteggio (Punteggio (&highscores) [MAX_HIGHSCORES], int &n_highscores, Punteggio nuovo_punteggio, int posizione)
{
	Punteggio pros = nuovo_punteggio;
	if (n_highscores < MAX_HIGHSCORES)
	{
		n_highscores++;
	}
	for (int i = posizione; i < n_highscores; i++)
	{
		scambiaPunteggio (highscores [i], pros);
	}
}

int posizionePunteggio (Punteggio (&highscores) [MAX_HIGHSCORES], int &n_highscores, Punteggio nuovo_punteggio)
{
	for (int i = 0; i < n_highscores; i++)
	{
		if (nuovo_punteggio.valore > highscores [i].valore)
		{
			return i;
		}
	}
	if (n_highscores < MAX_HIGHSCORES)
	{
		n_highscores++;
		return n_highscores - 1;
	}
	return -1;
}

void stampa (Punteggio punteggio)
{
	output (punteggio, cout);
}

void stampa (Punteggio highscores [], int n)
{
	output (highscores, n, cout);
}
//FINE MODULO